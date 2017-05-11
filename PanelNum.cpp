#include "stdafx.h"
#include "ESFEA2D.h"
#include "PanelNum.h"
#include "SJSG.h"

CPanelNum::CPanelNum() : CPanelBase(CPanelNum::IDD)
{
	//{{AFX_DATA_INIT(CPanelNum)
	//}}AFX_DATA_INIT
}

CPanelNum::~CPanelNum()
{}

void CPanelNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelNum)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPanelNum, CPanelBase)
	//{{AFX_MSG_MAP(CPanelNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


