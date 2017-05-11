#include "stdafx.h"
#include "ESFEA2D.h"
#include "CtrlPaneBar.h"
#include "SJSG.h"

#define TL_WIDTH 25

IMPLEMENT_DYNAMIC(CCtrlPaneBar, CWnd)

CCtrlPaneBar::CCtrlPaneBar()
{}

CCtrlPaneBar::~CCtrlPaneBar()
{
	if(m_bk_brush.GetSafeHandle()) m_bk_brush.DeleteObject();
}

BEGIN_MESSAGE_MAP(CCtrlPaneBar, CWnd)
//{{AFX_MSG_MAP(CCtrlPaneBar)
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_MESSAGE(ID_BAR_LIGHT,			on_bar_light)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCtrlPaneBar::create_mod(SJSG* p_sg, 
										CWnd* p_parent, 
										LONG pane_number)
{
	m_pane_number	= pane_number;
	mp_sg		= p_sg;

	CWnd::Create(NULL, 
						NULL, 
						WS_CHILD | WS_VISIBLE, 
						CRect(0, 0, 100, 100), 
						p_parent, 
						1);

	this->SetWindowText("CCtrlPaneBar");
}

int CCtrlPaneBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;
	
	m_height = 12;

	if(m_bk_brush.GetSafeHandle()) m_bk_brush.DeleteObject();
	m_bk_brush.CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));

	m_TrafficLightOn.LoadBitmap(IDB_LONG_GREEN);
	m_TrafficLightOff.LoadBitmap(IDB_TL_OFF);

	SetTLWidth();

	m_TrafficLight = &m_TrafficLightOff;

	return 0;
}

BOOL CCtrlPaneBar::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	CBrush* pOldBrush = pDC->SelectObject(&m_bk_brush);
	pDC->GetClipBox(&rect);     // Erase the area needed
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	DrawLTandVS(pDC);

	DrawTL(pDC);

	DrawBorder(pDC);

	return FALSE;
}

CFont* CCtrlPaneBar::get_font()
{
	CESFEA2DApp* pSejikaApp = (CESFEA2DApp*)AfxGetApp();
	return &(pSejikaApp->m_font_small);
}

void CCtrlPaneBar::SetTLWidth()
{
	BITMAP bmInfo;
	m_TrafficLightOn.GetObject(sizeof(bmInfo), &bmInfo);
	m_TLWidth = bmInfo.bmWidth + 20;
}

void CCtrlPaneBar::SetVSWidth()
{
	int length = m_viewStr.GetLength();

	TEXTMETRIC	tm;
	CClientDC	dc(this);
	CFont* pOldFont = dc.SelectObject(get_font());
	dc.GetTextMetrics(&tm);
	dc.SelectObject(&pOldFont);

	m_VSWidth = (length + 10) * tm.tmAveCharWidth;
}

void CCtrlPaneBar::SetViewText(LPCSTR str)
{
	m_viewStr = str;
	SetVSWidth();
}

void CCtrlPaneBar::DrawLTandVS(CDC* p_dc)
{
	p_dc->SetBkMode(TRANSPARENT);	

	CFont* pOldFont = p_dc->SelectObject(get_font());
	UINT uFormat = DT_LEFT;
	CRect rect;
	GetClientRect(rect);
	rect.left = rect.right - TL_WIDTH - m_VSWidth;
	rect.right = rect.right - TL_WIDTH;
	p_dc->DrawText(m_viewStr, -1, rect, uFormat);
	p_dc->SelectObject(&pOldFont);

	p_dc->SetBkMode(BKMODE_LAST);
}

void CCtrlPaneBar::DrawTL(CDC* p_dc)
{
	CRect rect;
	GetClientRect(rect);

	int pos = rect.right - TL_WIDTH - 10;

	BITMAP bmInfo;
	m_TrafficLight->GetObject(sizeof(bmInfo), &bmInfo);

	CDC dcCompat;
	dcCompat.CreateCompatibleDC(p_dc);
	CBitmap* pBitmapOld = dcCompat.SelectObject(m_TrafficLight);
	p_dc->BitBlt(pos, 0, TL_WIDTH, bmInfo.bmHeight, &dcCompat, 10, 0, SRCCOPY);
	dcCompat.SelectObject(pBitmapOld);

	CPen penShadow(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
	CPen *pOldPen = p_dc->SelectObject(&penShadow);
	p_dc->MoveTo(rect.right - 10, rect.top);
	p_dc->LineTo(rect.right - 10, rect.bottom);
	p_dc->MoveTo(pos, rect.top);
	p_dc->LineTo(pos, rect.bottom);
	p_dc->SelectObject(pOldPen);

	dcCompat.DeleteDC();
}

void CCtrlPaneBar::DrawBorder(CDC* p_dc)
{
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);

	CPen penShadow(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
	CPen *pOldPen = p_dc->SelectObject(&penShadow);
	p_dc->MoveTo(rect.left,  rect.top);
	p_dc->LineTo(rect.right, rect.top);
	p_dc->SelectObject(pOldPen);

	penShadow.DeleteObject();
}

void CCtrlPaneBar::TrafficLight(bool on_off)
{
	if(on_off) m_TrafficLight = &m_TrafficLightOn;
	else		  m_TrafficLight = &m_TrafficLightOff;
	
	Invalidate(TRUE);
}

void CCtrlPaneBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CPoint clientPoint = point;
	ScreenToClient(&clientPoint);

	CRect rect;
	GetClientRect(rect);

	int left = rect.right - TL_WIDTH - m_VSWidth;
	int right = rect.right - TL_WIDTH;

	if(clientPoint.x >= left && clientPoint.x <= right)
	{
		CMenu	PopMenu;
		PopMenu.LoadMenu(IDR_CAMERA_MENU);
		CMenu* pSubPop = PopMenu.GetSubMenu(0);
		pSubPop->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, pWnd);
		pSubPop->DestroyMenu();
		PopMenu.DestroyMenu();
	}
}

void CCtrlPaneBar::update_pane()
{
	GetParent()->PostMessage(ID_UPDATE_PANE_NUM, m_pane_number, NULL);
}

BOOL CCtrlPaneBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{	
	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	return TRUE;
}

LONG CCtrlPaneBar::on_bar_light(LONG ID, LPARAM lParam)
{
	if(m_pane_number == ID)	m_TrafficLight = &m_TrafficLightOn;
	else							m_TrafficLight = &m_TrafficLightOff;

	Invalidate(TRUE);
	return TRUE;
}

void CCtrlPaneBar::PostNcDestroy() 
{	
	CWnd::PostNcDestroy();
}

int CCtrlPaneBar::get_view_type(int pane)
{
	CESFEA2DApp* pSejikaApp = (CESFEA2DApp*)AfxGetApp();
	return 0;
}
