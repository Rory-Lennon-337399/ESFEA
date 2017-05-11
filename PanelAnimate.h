
#pragma once

#include "PanelBase.h"

class CPanelAnimate : public CPanelBase
{
public:

	CPanelAnimate();   
	~CPanelAnimate();

	//{{AFX_DATA(CPanelAnimate)
	enum { IDD = IDP_ANIMATE };
	CButton m_implicit;
	CButton m_explicit;
	float m_damp;
	float m_dt;
	float m_frac;
	float m_time;
	//}}AFX_DATA

	void set_integration(int type);

	//{{AFX_VIRTUAL(CPanelAnimate)
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPanelAnimate)
	afx_msg void OnDynamic();
	afx_msg void OnReset();
	afx_msg void OnExplicit();
	afx_msg void OnImplicit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

