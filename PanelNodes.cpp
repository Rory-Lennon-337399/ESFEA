#include "stdafx.h"
#include "ESFEA2D.h"
#include "PanelNodes.h"
#include "SJSG.h"

CPanelNodes::CPanelNodes() : CPanelBase(CPanelNodes::IDD)
{
	//{{AFX_DATA_INIT(CPanelNodes)
	m_x	= 0.0f;
	m_y	= 0.0f;
	m_dx	= 0.0f;
	m_dy	= 0.0f;
	//}}AFX_DATA_INIT
}

CPanelNodes::~CPanelNodes()
{}

void CPanelNodes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelNodes)
	DDX_Text(pDX, IDE_X, m_x);
	DDX_Text(pDX, IDE_Y, m_y);
	DDX_Text(pDX, IDE_DX, m_dx);
	DDX_Text(pDX, IDE_DY, m_dy);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPanelNodes, CPanelBase)
	//{{AFX_MSG_MAP(CPanelNodes)
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPanelNodes::OnCreate() 
{
	UpdateData(FROM_DIALOG);
	mp_sg->mp_mesh->add_point(0, m_x, m_y);
	mp_sg->fit_mesh();
	update_view();
}

void CPanelNodes::OnCopy() 
{
	UpdateData(FROM_DIALOG);
	mp_sg->mp_mesh->copy_nodes(m_dx, m_dy);
	mp_sg->fit_mesh();
	update_view();	
}

