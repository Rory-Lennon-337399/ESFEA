#include "stdafx.h"
#include "ESFEA2D.h"
#include "PanelAnimate.h"
#include "SJSG.h"
#include "MainFrm.h"

CPanelAnimate::CPanelAnimate() : CPanelBase(CPanelAnimate::IDD)
{
	//{{AFX_DATA_INIT(CPanelAnimate)
	//}}AFX_DATA_INIT
}

CPanelAnimate::~CPanelAnimate()
{}

void CPanelAnimate::DoDataExchange(CDataExchange* pDX)
{
	if(!pDX->m_bSaveAndValidate)
	{
		TRACE("TO\n");

		set_integration(mp_sg->mp_mesh->m_int);
		m_damp = mp_sg->mp_mesh->m_damp * 100.0f;
		m_frac = mp_sg->mp_mesh->m_frac * 100.0f;
		m_dt = mp_sg->mp_mesh->m_dt;
		m_time = mp_sg->mp_mesh->m_time;
	}

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelAnimate)
	DDX_Control(pDX, IDR_IMPLICIT, m_implicit);
	DDX_Control(pDX, IDR_EXPLICIT, m_explicit);
	DDX_Text(pDX, IDE_DAMP,	m_damp);
	DDX_Text(pDX, IDE_DT,	m_dt);
	DDX_Text(pDX, IDE_FRAC, m_frac);
	DDX_Text(pDX, IDE_TIME, m_time);
	//}}AFX_DATA_MAP

	if(pDX->m_bSaveAndValidate)
	{
		TRACE("FROM\n");

		if(m_implicit.GetCheck() == 1) mp_sg->mp_mesh->m_int = INTEGRATE_IMPLICIT;
		else mp_sg->mp_mesh->m_int = INTEGRATE_EXPLICIT;
		mp_sg->mp_mesh->m_damp = m_damp / 100.0f;
		mp_sg->mp_mesh->m_frac = m_frac / 100.0f;
		mp_sg->mp_mesh->m_dt = m_dt;
		mp_sg->mp_mesh->m_time = m_time;
	}
}

BEGIN_MESSAGE_MAP(CPanelAnimate, CPanelBase)
	//{{AFX_MSG_MAP(CPanelAnimate)
	ON_BN_CLICKED(IDC_DYNAMIC, OnDynamic)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDR_EXPLICIT, OnExplicit)
	ON_BN_CLICKED(IDR_IMPLICIT, OnImplicit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPanelAnimate::OnInitDialog() 
{
	CPanelBase::OnInitDialog();
	UpdateData(TO_DIALOG);
	return TRUE;  
}

void CPanelAnimate::OnDynamic() 
{
	UpdateData(FROM_DIALOG);
	if(m_implicit.GetCheck() == 1) mp_sg->mp_mesh->run_duhamel();
	else mp_sg->mp_mesh->run_rk4();
	((CMainFrame*)AfxGetMainWnd())->m_view.animate();
}

void CPanelAnimate::OnReset() 
{
//	UpdateData(FROM_DIALOG);
	if(mp_sg->mp_mesh->m_calcstage > MODES) mp_sg->mp_mesh->m_calcstage = MODES;
}

void CPanelAnimate::set_integration(int type)
{
	if(type == INTEGRATE_IMPLICIT) 
	{
		m_implicit.SetCheck(TRUE);
		m_explicit.SetCheck(FALSE);
	}
	if(type == INTEGRATE_EXPLICIT) 
	{
		m_implicit.SetCheck(FALSE);
		m_explicit.SetCheck(TRUE);
	}
}

void CPanelAnimate::OnImplicit() 
{
	set_integration(INTEGRATE_IMPLICIT);	
}

void CPanelAnimate::OnExplicit() 
{
	set_integration(INTEGRATE_EXPLICIT);	
}


