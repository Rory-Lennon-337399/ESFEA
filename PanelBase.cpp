#include "stdafx.h"
#include "ESFEA2D.h"
#include "PanelBase.h"
#include "MainFrm.h"
#include "SJSG.h"

CPanelBase::CPanelBase() 
{
	//{{AFX_DATA_INIT(CPanelBase)
	//}}AFX_DATA_INIT

	mp_sg = &((CESFEA2DApp*)AfxGetApp())->m_sg;
	m_active = false;
	m_panel_mode = -1;
	m_panel_vec.set_value(0.0f, 0.0f, 0.0f);
}

CPanelBase::CPanelBase(UINT val) : CPropertyPage(val)
{
	//{{AFX_DATA_INIT(CPanelBase)
	//}}AFX_DATA_INIT

	mp_sg = &((CESFEA2DApp*)AfxGetApp())->m_sg;
	m_active = false;
	m_panel_mode = -1;
	m_panel_vec.set_value(0.0f, 0.0f, 0.0f);
}

CPanelBase::~CPanelBase()
{}

BEGIN_MESSAGE_MAP(CPanelBase, CDialog)
	//{{AFX_MSG_MAP(CPanelBase)
	ON_MESSAGE(ID_UPDATE_DATA, on_update_data)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CPanelBase::on_update_data(WPARAM wParam, LPARAM lParam)
{
	UpdateData(wParam);
	return TRUE;
}

BOOL CPanelBase::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData(TO_DIALOG);
	return TRUE;
}

CWnd* CPanelBase::get_frame()
{
	CESFEA2DApp* pSejikaApp = (CESFEA2DApp*)AfxGetApp();
//	return GetTopLevelParent();
	return pSejikaApp->m_pMainWnd;
}

void CPanelBase::set_mode(int mode)
{
	CESFEA2DApp* pSejikaApp = (CESFEA2DApp*)AfxGetApp();
	pSejikaApp->set_mode(mode);
}

int CPanelBase::get_mode()
{
	CESFEA2DApp* pSejikaApp = (CESFEA2DApp*)AfxGetApp();
	return pSejikaApp->get_mode();
}

bool CPanelBase::get_drag_mode()
{
	CESFEA2DApp* pSejikaApp = (CESFEA2DApp*)AfxGetApp();
	return pSejikaApp->m_drag_mode;
}

BOOL CPanelBase::create_mod(UINT ID_dialog, CWnd* p_parent)
{
	BOOL return_value = CDialog::Create(ID_dialog, p_parent);
	SetDlgCtrlID(ID_dialog);
	return return_value;
}

void CPanelBase::set_states(SJSG* p_states)
{
	mp_sg = p_states;
}

void CPanelBase::set_direction(int pane)
{
//	SJTraverseMatrix bounds_traversal(SJTraverseMatrix::SET_UP);
//	mp_states->set_active_pane(pane);
//	bounds_traversal.apply(mp_states->get_root_pod());
}

void CPanelBase::prepare_screen_move(int pane, double &x, double &y)
{
	mp_sg->prepare_screen_move(pane, x, y);
}

void CPanelBase::pick_select()
{
	GetTopLevelParent()->PostMessage(ID_SELECT, get_select_type(), NULL);
}

int CPanelBase::get_select_type()
{
	return get_mode();
} 

void CPanelBase::set_console(LONG console_state, LPCSTR p_str)
{
//	CWnd* p_wnd = get_frame()->GetDlgItem(ID_CTRL_CONSOLE);
//	if(p_wnd == NULL) return;
//	p_wnd->PostMessage(ID_CONSOLE_STATE, console_state, (unsigned int)p_str);
}

bool CPanelBase::busy()
{
	CESFEA2DApp* p_sejika_app = (CESFEA2DApp*)AfxGetApp();
	return true;
}

void CPanelBase::mouse_move(int pane, double x, double y)
{} /* virtual */

void CPanelBase::create_init()
{} /* virtual */

void CPanelBase::update_view()
{
	((CMainFrame*)AfxGetMainWnd())->m_view.Invalidate();
}