
#pragma once

#include "PanelBase.h"

class CPanelElements : public CPanelBase
{
public:

	CPanelElements();   
	~CPanelElements();

	//{{AFX_DATA(CPanelElements)
	enum { IDD = IDP_ELEMENTS };
	float	m_aa;
	float	m_ee;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPanelElements)
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPanelElements)
	afx_msg void OnMat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

