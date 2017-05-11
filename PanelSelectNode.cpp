#include "stdafx.h"
#include "ESFEA2D.h"
#include "PanelSelectNode.h"
#include "SJSG.h"

CPanelSelectNode::CPanelSelectNode() : CPanelBase(CPanelSelectNode::IDD)
{
	//{{AFX_DATA_INIT(CPanelSelectNode)
	//}}AFX_DATA_INIT
}

CPanelSelectNode::~CPanelSelectNode()
{}

void CPanelSelectNode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelSelectNode)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPanelSelectNode, CPanelBase)
	//{{AFX_MSG_MAP(CPanelSelectNode)
	ON_BN_CLICKED(IDC_UNSEL_NODE, OnUnselNode)
	ON_BN_CLICKED(IDC_SEL_ALL, OnSelAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPanelSelectNode::OnUnselNode() 
{
	mp_sg->mp_mesh->unselect_nodes();
	update_view();	
}


void CPanelSelectNode::OnSelAll() 
{
	mp_sg->mp_mesh->select_all();
	update_view();		
}
