
#pragma once

class CSejikaStatus : public CStatusBar
{
	DECLARE_DYNCREATE(CSejikaStatus)
public:
						CSejikaStatus();

	//{{AFX_VIRTUAL(CSejikaStatus)
	//}}AFX_VIRTUAL

	virtual			~CSejikaStatus();
	void				set_filename(CString str_name);
	void				set_mode(CString str_mode);
	bool				m_show_grid;
	bool				m_show_index;

protected:
	
	//{{AFX_MSG(CSejikaStatus)
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


