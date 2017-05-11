#include "stdafx.h"
#include "ESFEA2D.h"
#include "SejikaSheet.h"

IMPLEMENT_DYNAMIC(CSejikaSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CSejikaSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSejikaSheet)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSejikaSheet::CSejikaSheet() 
{
	AddPage(&m_panel_sel_nd);
	AddPage(&m_panel_nodes);
	AddPage(&m_panel_load);
	AddPage(&m_panel_modal);
	AddPage(&m_panel_animate);
	AddPage(&m_panel_elements);
}

CSejikaSheet::~CSejikaSheet()
{}

BOOL CSejikaSheet::OnInitDialog() 
{
	CPropertySheet::OnInitDialog();

	CTabCtrl* p_tab = GetTabControl();
	p_tab->ModifyStyle(NULL, TCS_BOTTOM);
	p_tab->EnableWindow(FALSE);
	p_tab->ShowWindow(SW_HIDE);

	for(int i = 0; i < GetPageCount(); i++) SetActivePage(i);
	return TRUE;
}

int CSejikaSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1) return -1;

	EnableStackedTabs(TRUE);
	m_tab_images.Create(IDB_IL_TAB, 16, 1, RGB(0,255,0));

	return 0;
}



