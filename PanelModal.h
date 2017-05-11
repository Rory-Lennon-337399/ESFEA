#pragma once

#include "PanelBase.h"

class CPanelModal : public CPanelBase
{
public:

	CPanelModal();   
	~CPanelModal();

	void animate_mode();

	//{{AFX_DATA(CPanelModal)
	enum { IDD = IDP_MODAL };
	int		m_modenum;
	int		m_numdofs;
	float		m_frq;
	float		m_period;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPanelModal)
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPanelModal)
	afx_msg void OnAnimateMode();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

