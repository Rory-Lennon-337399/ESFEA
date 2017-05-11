
#pragma once

#include "PanelBase.h"

class CPanelNodes : public CPanelBase
{
public:

	CPanelNodes();   
	~CPanelNodes();

	//{{AFX_DATA(CPanelNodes)
	enum { IDD = IDP_NODES };
	float	m_x;
	float	m_y;
	float	m_dx;
	float	m_dy;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPanelNodes)
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPanelNodes)
	afx_msg void OnCreate();
	afx_msg void OnCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

