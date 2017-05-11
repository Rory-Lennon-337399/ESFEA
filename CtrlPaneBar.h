
#pragma once

class SJSG;	

class CCtrlPaneBar : public CWnd
{
	DECLARE_DYNAMIC(CCtrlPaneBar)

public:
						CCtrlPaneBar();
	virtual			~CCtrlPaneBar();
	void				create_mod(SJSG* p_sg, CWnd* p_parent, LONG pane_number);
	void				TrafficLight(bool on_off);

	int				m_height;

//{{AFX_VIRTUAL(CCtrlPaneBar)
protected:
	virtual void	PostNcDestroy();
//}}AFX_VIRTUAL

protected:

	SJSG*				mp_sg;
	LONG				m_view_type;
	LONG				m_rotation_type;
	LONG				m_pane_number;
	bool				first_erase_call;
	CBitmap			m_LittleTriangle;
	int				m_LTWidth;
	CString			m_viewStr;
	int				m_VSWidth;
	CBitmap*			m_TrafficLight;
	int				m_TLWidth;
	CBitmap			m_TrafficLightOn;
	CBitmap			m_TrafficLightOff;
	CFont				m_boldFont;
	COLORREF			m_crBackground;
	CBrush			m_bk_brush;			

	void				update_pane();
	void				change_view(LPCSTR str, int view, int rotation);
	void				SetVSWidth();
	void				SetTLWidth();
	int				get_view_type(int pane);
	void				DrawLTandVS(CDC* p_dc);
	void				DrawBorder(CDC* pdc);
	void				DrawTL(CDC* p_dc);
	void				SetViewText(LPCSTR str);
	CFont*			get_font();

	//{{AFX_MSG(CCtrlPaneBar)
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg void	OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LONG	on_bar_light(LONG ID, LPARAM lParam);
	afx_msg BOOL	OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

