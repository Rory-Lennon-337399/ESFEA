
#pragma once

#include "PanelBase.h"

class CPanelSelectNode : public CPanelBase
{
public:

	CPanelSelectNode();   
	~CPanelSelectNode();

	//{{AFX_DATA(CPanelSelectNode)
	enum { IDD = IDP_SEL_ND };

	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPanelSelectNode)
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPanelSelectNode)
	afx_msg void OnUnselNode();
	afx_msg void OnSelAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

