
#include "stdafx.h"
#include "ESFEA2D.h"
#include "MainFrm.h"
#include "SejikaSheet.h"
#include "FileIn.h"

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_BACKGROUND,	OnViewBackground)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
	mp_sg = &((CESFEA2DApp*)AfxGetApp())->m_sg;
}

CMainFrame::~CMainFrame()
{}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CFrameWnd::PreCreateWindow(cs))return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

#define TREE_WIDTH		160
#define CTRLS_HEIGHT		180

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	int STATUS_HEIGHT = 20;

	m_view.MoveWindow(TREE_WIDTH, 0, cx - TREE_WIDTH, cy - CTRLS_HEIGHT - STATUS_HEIGHT);
	m_tree.MoveWindow(0, 0, TREE_WIDTH, cy - CTRLS_HEIGHT - STATUS_HEIGHT);
	m_sheet.MoveWindow(0, cy - CTRLS_HEIGHT - STATUS_HEIGHT, cx, CTRLS_HEIGHT);

	CFrameWnd::OnSize(nType, cx, cy);
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	CBrush btn_brush;
	btn_brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
	CBrush* pOldBrush = pDC->SelectObject(&btn_brush);
	pDC->GetClipBox(&rect); 
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return FALSE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;

	m_status.Create(this);
	m_sheet.Create(this, WS_CHILD | WS_VISIBLE);
	m_view.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, 0, NULL);
	m_tree.Create(IDD_PANEL_TREE, this);
	m_tree.ShowWindow(SW_SHOW);

	return 0;
}

void CMainFrame::OnViewBackground() 
{
	CESFEA2DApp* pSejikaApp = (CESFEA2DApp*)AfxGetApp();

	SJVec3 vec(pSejikaApp->m_background_color);

	int red = (int)(255 * vec.get_component(0));
	int gre = (int)(255 * vec.get_component(1));
	int blu = (int)(255 * vec.get_component(2));

	COLORREF col = RGB(red, gre, blu);
	CColorDialog color_dialog(col);

	if(color_dialog.DoModal() == IDOK)
	{
		COLORREF col = color_dialog.GetColor();
		float red	= ((float)(int)GetRValue(col)) / 255.0f;
		float green	= ((float)(int)GetGValue(col)) / 255.0f;
		float blue	= ((float)(int)GetBValue(col)) / 255.0f;

		pSejikaApp->m_background_color.set_value(red, green, blue);
//		on_update_all_panes(0, 0);
	}	
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
//	mp_sheet->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



