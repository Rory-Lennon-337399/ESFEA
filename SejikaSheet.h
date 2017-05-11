
#pragma once

#include "PanelTree.h"
#include "PanelNum.h"
#include "PanelNodes.h"
#include "PanelSelectNode.h"
#include "PanelLoad.h"
#include "PanelAnimate.h"
#include "PanelModal.h"
#include "PanelElements.h"

class	SJSG;

class CSejikaSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSejikaSheet)

public:
							CSejikaSheet();

	CRect					m_rectPage;
	CImageList			m_tab_images;	

/////////////////////////////////////////
	CPanelSelectNode	m_panel_sel_nd;
	CPanelNodes			m_panel_nodes;
	CPanelLoad			m_panel_load;
	CPanelAnimate		m_panel_animate;
	CPanelModal			m_panel_modal;
	CPanelElements		m_panel_elements;
/////////////////////////////////////////

	//{{AFX_VIRTUAL(CSejikaSheet)
	public:
	virtual BOOL		OnInitDialog();
	//}}AFX_VIRTUAL

	virtual ~CSejikaSheet();

protected:

	//{{AFX_MSG(CSejikaSheet)
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

