#include "stdafx.h"
#include "ESFEA2D.h"
#include "PanelElements.h"
#include "SJSG.h"

CPanelElements::CPanelElements() : CPanelBase(CPanelElements::IDD)
{
	//{{AFX_DATA_INIT(CPanelElements)
	m_aa = 0.0f;
	m_ee = 0.0f;
	//}}AFX_DATA_INIT
}

CPanelElements::~CPanelElements()
{}

void CPanelElements::DoDataExchange(CDataExchange* pDX)
{
	if(!pDX->m_bSaveAndValidate)
	{
		m_aa = mp_sg->mp_mesh->m_aa;
		m_ee = mp_sg->mp_mesh->m_ee;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelElements)
	DDX_Text(pDX, IDE_AREA, m_aa);
	DDX_Text(pDX, IDE_ELAST, m_ee);
	//}}AFX_DATA_MAP

	if(pDX->m_bSaveAndValidate)
	{
		mp_sg->mp_mesh->m_aa = m_aa;
		mp_sg->mp_mesh->m_ee = m_ee;
	}
}

BEGIN_MESSAGE_MAP(CPanelElements, CPanelBase)
	//{{AFX_MSG_MAP(CPanelElements)
	ON_BN_CLICKED(IDC_MAT, OnMat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPanelElements::OnMat() 
{
	UpdateData(FROM_DIALOG);
	mp_sg->mp_mesh->material(m_aa * m_ee);
}
