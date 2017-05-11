
#pragma once

#include "PanelBase.h"
#include "DlgMatrix.h"

class CPanelTree : public CDialog
{
public:

	CPanelTree();   
	~CPanelTree();

	SJSG*	mp_sg;
	void set_mode(int mode);
	HTREEITEM InsertData(HTREEITEM parent, CString name, int data, int image);
	void build_tree();
	void show_matrix(int which);
	void set_panel(int num);
	CImageList m_img_list;
	CTreeCtrl m_tree_ctrl;

	//{{AFX_DATA(CPanelTree)
	enum { IDD = IDD_PANEL_TREE };

	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPanelTree)
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPanelTree)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

