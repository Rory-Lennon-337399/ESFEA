#include "stdafx.h"
#include "ESFEA2D.h"
#include "PanelTree.h"
#include "SJSG.h"
#include "MainFrm.h"

CPanelTree::CPanelTree() 
{
	//{{AFX_DATA_INIT(CPanelTree)
	//}}AFX_DATA_INIT
	mp_sg = &((CESFEA2DApp*)AfxGetApp())->m_sg;
}

CPanelTree::~CPanelTree()
{}

void CPanelTree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelTree)
	DDX_Control(pDX, IDC_TREE, m_tree_ctrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPanelTree, CDialog)
	//{{AFX_MSG_MAP(CPanelTree)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPanelTree::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_img_list.Create(IDB_TREE_LIST, 16, 10, RGB(255, 255, 255));
	m_tree_ctrl.SetImageList(&m_img_list, TVSIL_NORMAL);
	build_tree();
	return TRUE;  
}

HTREEITEM CPanelTree::InsertData(HTREEITEM parent, CString name, int data, int image)
{
	HTREEITEM new_parent;

	new_parent = m_tree_ctrl.InsertItem(
				TVIF_IMAGE | TVIF_PARAM | TVIF_SELECTEDIMAGE | TVIF_STATE | TVIF_TEXT,
				name,
				image,
				image,
				0,
				TVIS_BOLD,
				data,
				parent,
				TVI_LAST);

	return new_parent;
}

#define IMG_GREEN				0
#define IMG_BLUE				1
#define IMG_CROSS				2
#define IMG_DLG				3
#define IMG_SQUARE			4
#define IMG_MATRIX			6

void CPanelTree::build_tree()
{
	HTREEITEM p_VIEW =		InsertData(NULL,			"VIEW",			0,						IMG_GREEN);
									InsertData(p_VIEW,		"PAN",			IDM_PAN,				IMG_CROSS);
									InsertData(p_VIEW,		"SCALE",			IDM_SCALE,			IMG_CROSS);
									InsertData(p_VIEW,		"FIT",			IDM_FIT,				IMG_CROSS);

	HTREEITEM p_NODES =		InsertData(NULL,			"NODES",			0,						IMG_SQUARE);
									InsertData(p_NODES,		"SELECT",		IDM_SELECT_ND,		IMG_DLG);
									InsertData(p_NODES,		"CREATE",		IDM_CREATE_ND,		IMG_DLG);
									InsertData(p_NODES,		"LOADS",			IDM_LOAD,			IMG_DLG);

	HTREEITEM p_ELEMENTS =	InsertData(NULL,			"ELEMENTS",		0,						IMG_SQUARE);
									InsertData(p_ELEMENTS,	"CREATE",		IDM_CREATE_EL,		IMG_DLG);

	HTREEITEM p_CONTROLS =	InsertData(NULL,			"SOLUTION",		0,						IMG_BLUE);
									InsertData(p_CONTROLS,	"MODAL",			IDM_MODAL,			IMG_DLG);
	HTREEITEM p_DYNAMIC =	InsertData(p_CONTROLS,	"DYNAMIC",		IDM_DYNAMIC,		IMG_DLG);

	HTREEITEM p_MATRIX =		InsertData(NULL,			"MATRIX",		0,						IMG_MATRIX);
									InsertData(p_MATRIX,		"STIFFNESS",	IDM_STIFF,			IMG_DLG);
									InsertData(p_MATRIX,		"MASS",			IDM_MASS,			IMG_DLG);
									InsertData(p_MATRIX,		"MODES",			IDM_MODES,			IMG_DLG);


	m_tree_ctrl.Expand(p_VIEW, TVE_EXPAND);
	m_tree_ctrl.Expand(p_NODES, TVE_EXPAND);	
	m_tree_ctrl.Expand(p_ELEMENTS, TVE_EXPAND);	
	m_tree_ctrl.Expand(p_CONTROLS, TVE_EXPAND);
	m_tree_ctrl.Expand(p_MATRIX, TVE_EXPAND);

	m_tree_ctrl.SelectItem(p_DYNAMIC);
}

void CPanelTree::show_matrix(int which)
{
	SJMatrix* p_mat = NULL;
	CString wtxt;

	if(which == IDM_STIFF)
	{
		mp_sg->mp_mesh->arrange_stiffness();
		p_mat = &mp_sg->mp_mesh->m_stiff;
		wtxt = "STIFFNESS";
	}
/*
	if(which == IDM_MASS)
	{
		mp_sg->mp_mesh->arrange_stiffness();
		p_mat = &mp_sg->mp_mesh->m_mass;
		wtxt = "MASS";
	}
*/
	if(which == IDM_MODES)
	{
		mp_sg->mp_mesh->extract_modes();
		p_mat = &mp_sg->mp_mesh->m_modes;
		wtxt = "MODES";
	}
	if(p_mat == NULL) return;

	CDlgMatrix matrix_dlg(this, p_mat, wtxt);
	matrix_dlg.DoModal();
}

void CPanelTree::set_mode(int mode)
{
	CESFEA2DApp* pSejikaApp = (CESFEA2DApp*)AfxGetApp();
	pSejikaApp->set_mode(mode);
}

void CPanelTree::set_panel(int num)
{
	((CMainFrame*)AfxGetMainWnd())->m_sheet.SetActivePage(num);
}

void CPanelTree::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(!m_tree_ctrl) return;
	m_tree_ctrl.MoveWindow(5, 0, cx - 10, cy);
}

void CPanelTree::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM p_item = m_tree_ctrl.GetSelectedItem();
	int data = m_tree_ctrl.GetItemData(p_item);

	TRACE("CPanelTree::on_click_tree %i\n", data);

	switch (data) 
	{	
		case IDM_SCALE:
			set_mode(IDM_SCALE);
		break;
		case IDM_PAN:
			set_mode(IDM_PAN);
		break;
		case IDM_FIT:
			mp_sg->fit_mesh();
		break;
		case IDM_SELECT_ND:
			set_panel(0);
			set_mode(IDM_SELECT_ND);
		break;
		case IDM_CREATE_ND:
			set_panel(1);
		break;
		case IDM_CREATE_EL:
			set_panel(5);
			set_mode(IDM_CREATE_EL);
		break;
		case IDM_LOAD:
			set_panel(2);
		break;
		case IDM_STIFF:
			show_matrix(IDM_STIFF);
		break;
		case IDM_MASS:
			show_matrix(IDM_MASS);
		break;
		case IDM_MODES:
			show_matrix(IDM_MODES);
		break;
		case IDM_MODAL:
			set_panel(3);
		break;
		case IDM_DYNAMIC:
			set_panel(4);
		break;
	}
	if((data % 2) == 1) ((CESFEA2DApp*)AfxGetApp())->m_drag_mode = true;
	else ((CESFEA2DApp*)AfxGetApp())->m_drag_mode = false;
	
	*pResult = 1;
}
