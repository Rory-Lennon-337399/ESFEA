
#pragma once

class SJSG;
class CViewPane;

class CPanelBase : public CPropertyPage
{
public:
	
						CPanelBase();
						CPanelBase(UINT val);
						~CPanelBase();
	BOOL				create_mod(UINT ID_dialog, CWnd* p_parent);
	void				set_states(SJSG* p_states);

protected:

	UINT				m_IDD;
	SJSG*				mp_sg;



	void				set_console(LONG console_state, LPCSTR p_str);
	bool				m_active;
	long				title_height;
	int				m_panel_mode; 
	SJVec3			m_panel_vec;

	bool				busy();
	CWnd*				get_frame();
	void				set_mode(int mode);
	int				get_mode();
	bool				get_drag_mode();
	void				set_direction(int pane);
	void				update_view();
	virtual void	mouse_move(int pane, double x, double y);
	virtual void	create_init();
	void				prepare_screen_move(int pane, double& x, double& y);
	void				pick_select();
	
	virtual int		get_select_type(); 

//{{AFX_MSG(CPanelBase)
	virtual BOOL	OnInitDialog();
	afx_msg LONG	on_update_data(WPARAM wParam, LPARAM lParam);
//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


