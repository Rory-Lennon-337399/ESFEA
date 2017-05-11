
#pragma once

#include "SJSG.h"
#include "fstream.h"
#include "PanelTree.h"
#include "SejikaSheet.h"
#include "SJView.h"
#include "SejikaStatus.h"

class CMainFrame : public CFrameWnd
{
protected: 

	DECLARE_DYNAMIC(CMainFrame)

public:
							CMainFrame();
	void					save_file(CString str);

//{{AFX_VIRTUAL(CMainFrame)
public:
	virtual BOOL		PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL		OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

	virtual				~CMainFrame();

	CSejikaStatus		m_status;
	SJView				m_view;
	SJSG*					mp_sg;
	CSejikaSheet		m_sheet;
	CPanelTree			m_tree;

//{{AFX_MSG(CMainFrame)
	afx_msg BOOL		OnEraseBkgnd			(CDC* pDC);
	afx_msg int			OnCreate					(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnSize					(UINT nType, int cx, int cy);
	afx_msg void		OnViewBackground		();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


