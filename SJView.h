#pragma once

class SJView : public CWnd
{
public:

	SJView();

public:

	//{{AFX_VIRTUAL(SJView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
	
	virtual ~SJView();
	BOOL create_gl_context(HDC hDC);
	BOOL set_window_pixel_format(HDC hDC);
	void gl_init();
	SJPoint* select_node(CPoint pt);
	void select_single_node(CPoint point);
	void select_element_node(CPoint point);
	void animate();
	BOOL animate_frame();

	SJSG*	mp_sg;
	HGLRC	m_hglrc;
	int m_GLPixelIndex;
	SJPL_POINTS	ml_elgens;
	int m_render_mode;

protected:

	//{{AFX_MSG(SJView)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LONG on_change_mode(WPARAM	wParam, LPARAM	lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
