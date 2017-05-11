#pragma once

#include "PanelBase.h"

class CPanelModal : public CPanelBase
{
public:

	CPanelModal();   
	~CPanelModal();

	void animate_mode();

	//{{AFX_DATA(CPanelModal)
	enum { IDD = IDP_ANIMATE };
	int		m_modenum;
	float	m_frq;
	float	m_damp;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPanelModal)
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPanelModal)
	afx_msg void OnAnimateMode();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDynamic();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

