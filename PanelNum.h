
#pragma once

#include "PanelBase.h"

class CPanelNum : public CPanelBase
{
public:

	CPanelNum();   
	~CPanelNum();

	//{{AFX_DATA(CPanelNum)
	enum { IDD = IDD_PANEL_NUM };

	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPanelNum)
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPanelNum)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

