#include "stdafx.h"
#include "ESFEA2D.h"
#include "PanelModal.h"
#include "SJSG.h"
#include "MainFrm.h"

CPanelModal::CPanelModal() : CPanelBase(CPanelModal::IDD)
{
	//{{AFX_DATA_INIT(CPanelModal)
	m_modenum = 1;
	m_numdofs = 0;
	m_frq = 0.0f;
	m_period = 0.0f;
	//}}AFX_DATA_INIT
}

CPanelModal::~CPanelModal()
{}

void CPanelModal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanelModal)
	DDX_Text(pDX, IDE_MODENUM, m_modenum);
	DDX_Text(pDX, IDE_EIGVAL, m_frq);
	DDX_Text(pDX, IDE_NDOFS, m_numdofs);
	DDX_Text(pDX, IDE_PERIOD, m_period);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPanelModal, CPanelBase)
	//{{AFX_MSG_MAP(CPanelModal)
	ON_BN_CLICKED(IDC_ANIMATE_MODE, OnAnimateMode)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPanelModal::OnAnimateMode() 
{
	UpdateData(FROM_DIALOG);
	animate_mode();
}

void CPanelModal::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if(pNMUpDown->iDelta ==  1) m_modenum -= 1;
	if(pNMUpDown->iDelta == -1) m_modenum += 1;
	animate_mode();
	*pResult = 0;
}

void CPanelModal::animate_mode()
{
	m_frq = mp_sg->mp_mesh->create_mode_animation(m_modenum);
	if(m_frq != 0.0f) m_period = 1.0f / m_frq;
	m_numdofs = mp_sg->mp_mesh->m_numdofs;
	UpdateData(TO_DIALOG);
	((CMainFrame*)AfxGetMainWnd())->m_view.animate();
}
