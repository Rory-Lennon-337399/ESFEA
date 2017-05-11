#pragma once

#include "PanelBase.h"

class CPanelLoad : public CPanelBase
{
public:

	CPanelLoad();   
	~CPanelLoad();

	//{{AFX_DATA(CPanelLoad)
	enum { IDD = IDP_LOAD };
	float	m_fx;
	float	m_fy;
	float	m_ft;
	float	m_lump;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPanelLoad)
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPanelLoad)
	afx_msg void OnFix();
	afx_msg void OnApplyForce();
	afx_msg void OnMass();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

