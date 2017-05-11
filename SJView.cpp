#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJView.h"

SJView::SJView()
{
	m_render_mode = RENDER;
	mp_sg = &((CESFEA2DApp*)AfxGetApp())->m_sg;
}

SJView::~SJView()
{
}

BEGIN_MESSAGE_MAP(SJView, CWnd)
	//{{AFX_MSG_MAP(SJView)
	ON_MESSAGE(ID_CHANGE_MODE, on_change_mode)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void SJView::animate()
{
	m_render_mode = ANIMATE;
	KillTimer(1);
	mp_sg->mp_mesh->reset_animate();
	SetTimer(1, 50, NULL);	
}	

void SJView::OnTimer(UINT nIDEvent) 
{	
	if(!animate_frame()) 
	{
		KillTimer(1);
		m_render_mode = RENDER;
	}
	Invalidate();
}

BOOL SJView::animate_frame()
{
//	TRACE("SJView::animate_frame\n");
	if(!mp_sg->mp_mesh->next_frame()) return FALSE;
	Invalidate();
	return TRUE;
}

LONG SJView::on_change_mode(WPARAM wParam, LPARAM lParam)
{
	if(wParam == IDM_CREATE_EL) return TRUE;
	ml_elgens.delete_list_nodes();
	mp_sg->mp_mesh->unselect_nodes();
	return TRUE;
}

void SJView::OnPaint() 
{
	CPaintDC dc(this);
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mp_sg->traverse_render(m_render_mode);
	SwapBuffers(dc.m_ps.hdc);
	::glFlush();
}

BOOL SJView::create_gl_context(HDC hDC)
{
	m_hglrc = wglCreateContext(hDC);
	if(m_hglrc == NULL) return FALSE;
	if(::wglMakeCurrent(hDC, m_hglrc) == FALSE) return FALSE;
	return TRUE;
}

BOOL SJView::set_window_pixel_format(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags =	PFD_DRAW_TO_WINDOW | 
								PFD_SUPPORT_OPENGL |
								PFD_DOUBLEBUFFER |
								PFD_STEREO_DONTCARE;

	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);

	if(m_GLPixelIndex==0) // Choose default
	{
		m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc) == 0) return FALSE;
	}
	if(SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc)==FALSE) return FALSE;
	return TRUE;
}

void SJView::gl_init()
{
	::glEnable(GL_DEPTH_TEST);
	::glDisable(GL_DITHER);
	::glClearStencil(0x0);
	::glEnable(GL_STENCIL_TEST);

//	::glDrawBuffer(GL_FRONT_AND_BACK);
	::glClearDepth(1.0f);
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	::glColor3f(1.0f, 1.0f, 1.0f);
	::glMatrixMode(GL_TEXTURE);
	::glLoadIdentity();
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
//	::glDepthFunc(GL_LEQUAL);
	::glEnable(GL_DEPTH_TEST);
	::glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	::glShadeModel(GL_SMOOTH);

	::glEnable(GL_LIGHTING);
	::glEnable(GL_LIGHT1);
//	::glEnable(GL_COLOR_MATERIAL);
//	::glDisable(GL_COLOR_MATERIAL);

//	GLdouble vec1[] = { 0.3f, 0.3f, 0.3f, 0.0f };
//	::glLightfv(GL_LIGHT1, GL_AMBIENT, vec1);

	GLfloat pos[] = { 0.0f, 0.0f, 10.0f, 1.0f };
	::glLightfv(GL_LIGHT1, GL_POSITION, pos);

	GLfloat vec2[] = { 0.75f, 0.75f, 0.75f, 0.0f };
	::glLightfv(GL_LIGHT1, GL_DIFFUSE, vec2);
	
	GLfloat vec1[] = { 0.25f, 0.25f, 0.25f, 0.0f };
	::glLightfv(GL_LIGHT1, GL_AMBIENT, vec1);

//	COLORREF color = ::GetSysColor(COLOR_3DFACE);
//	glClearColor((float)GetRValue(color)/255.0f, (float)GetGValue(color)/255.0f, (float)GetBValue(color)/255.0f, 1.0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
}

int SJView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;
	
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if(set_window_pixel_format(hDC) == FALSE) return 0;
	if(create_gl_context(hDC) == FALSE) return 0;
	gl_init();

	return 0;
}

void SJView::OnSize(UINT nType, int cx, int cy) 
{
//	TRACE("SJView::OnSize\n");

	CWnd::OnSize(nType, cx, cy);

   ::glViewport(0, 0,  cx, cy);
	mp_sg->m_region.set_value(cx, cy);
	mp_sg->fit_mesh();
}

BOOL SJView::OnEraseBkgnd(CDC* pDC) 
{	
	return FALSE;
}

BOOL SJView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	return CWnd::PreCreateWindow(cs);
}

void SJView::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	CWnd::OnLButtonDown(nFlags, point);

	CESFEA2DApp* pSejikaApp = (CESFEA2DApp*)AfxGetApp();
	int mode = pSejikaApp->get_mode();

	switch(mode) 
	{	
		case IDM_SELECT_ND:
			select_single_node(point);
		break;
		case IDM_CREATE_EL:
			select_element_node(point);
		break;
	}
	Invalidate();
}

void SJView::select_single_node(CPoint point) 
{
	SJPoint* p_point = select_node(point);
	if(p_point) mp_sg->mp_mesh->select_point(p_point);


}

void SJView::select_element_node(CPoint point) 
{
	SJPoint* p_point = select_node(point);

//	TRACE("SJView::select_element_node %i\n", p_point);

	if(p_point == NULL) return;

	ml_elgens.add_tail(p_point);
	if(ml_elgens.get_count() == 4) 
	{
		mp_sg->mp_mesh->add_block(ml_elgens);
		ml_elgens.delete_list_nodes();
		mp_sg->mp_mesh->unselect_nodes();
	}
	else p_point->m_selection = 1;

}

SJPoint* SJView::select_node(CPoint pt)
{
	GLint viewport[4];
	::glGetIntegerv(GL_VIEWPORT, viewport);

	double px = (double)pt.x;
	double py = (double)(viewport[3] - pt.y);
	GLuint selectbuf[100];
	selectbuf[3] = NULL;
	GLint hits;

	::glSelectBuffer(100, selectbuf);
	::glRenderMode(GL_SELECT);
	::glInitNames();
	::glPushName(0);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	::gluPickMatrix(px, py, 1.0, 1.0, viewport);
	mp_sg->traverse_render(SELECT);
	::glFlush();

	hits = ::glRenderMode(GL_RENDER);
	if(hits > 0) 
	{
//		TRACE("SJView::select %i\n", selectbuf[3]);
		Invalidate(TRUE);
		return (SJPoint*)selectbuf[3];
	}
	return NULL;
}

