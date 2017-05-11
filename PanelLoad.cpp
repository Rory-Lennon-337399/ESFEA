#include "stdafx.h"
#include "ESFEA2D.h"
#include "PanelLoad.h"
#include "SJSG.h"

CPanelLoad::CPanelLoad() : CPanelBase(CPanelLoad::IDD)
{
	//{{AFX_DATA_INIT(CPanelLoad)
	m_fx = 0.0f;
	m_fy = 0.0f;
	m_ft = 0.0f;
	m_lump = 0.0f;
	//}}AFX_DATA_INIT
}

CPanelLoad::~CPanelLoad()
{}

void CPanelLoad::DoDataExchange(CDataExchange* pDX)
{
	if(!pDX->m_bSaveAndValidate)
	{
		m_ft = mp_sg->mp_mesh->m_ft;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelLoad)
	DDX_Text(pDX, IDE_FX, m_fx);
	DDX_Text(pDX, IDE_FY, m_fy);
	DDX_Text(pDX, IDE_FT, m_ft);
	DDX_Text(pDX, IDE_MASS, m_lump);
	//}}AFX_DATA_MAP

	if(pDX->m_bSaveAndValidate)
	{
		mp_sg->mp_mesh->m_ft = m_ft;
	}
}

BEGIN_MESSAGE_MAP(CPanelLoad, CPanelBase)
	//{{AFX_MSG_MAP(CPanelLoad)
	ON_BN_CLICKED(IDC_FIX, OnFix)
	ON_BN_CLICKED(IDC_APPLY, OnApplyForce)
	ON_BN_CLICKED(IDC_MASS, OnMass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPanelLoad::OnFix() 
{
	mp_sg->mp_mesh->fix();
	update_view();	
}

void CPanelLoad::OnApplyForce() 
{
	UpdateData(FROM_DIALOG);
	mp_sg->mp_mesh->force(m_fx, m_fy);
	update_view();	
}

void CPanelLoad::OnMass() 
{
	UpdateData(FROM_DIALOG);
	mp_sg->mp_mesh->mass(m_lump);	
	update_view();	
}
