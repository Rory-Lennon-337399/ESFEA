#include "stdafx.h"
#include "ESFEA2D.h"
#include "SejikaStatus.h"

IMPLEMENT_DYNCREATE(CSejikaStatus, CStatusBar)

CSejikaStatus::CSejikaStatus()
{
	m_show_grid  = false;
	m_show_index = false;
}

CSejikaStatus::~CSejikaStatus()
{}

BEGIN_MESSAGE_MAP(CSejikaStatus, CStatusBar)
	//{{AFX_MSG_MAP(CSejikaStatus)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,	
	IDS_FILENAME,
	IDS_MODE
};

int CSejikaStatus::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1) return -1;
	SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	SetPaneInfo(0, ID_SEPARATOR, SBPS_STRETCH, 50);
	set_mode("MODE: ");
	return 0;
}

void CSejikaStatus::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBar::OnSize(nType, cx, cy);
}

void CSejikaStatus::set_filename(CString str_name)
{
	int pos = str_name.Find(".");

	CString new_name = str_name.Mid(0, pos);
	new_name.MakeUpper();
	new_name.Insert(0, "PROJECT: ");

	SetPaneText(CommandToIndex(IDS_FILENAME), new_name);
}

void CSejikaStatus::set_mode(CString str_mode)
{
	SetPaneText(CommandToIndex(IDS_MODE), str_mode);
}
