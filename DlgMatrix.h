#pragma once

class CDlgMatrix : public CDialog
{
public:

	CDlgMatrix(CWnd* pParent, SJMatrix* p_matrix, CString name);   // standard constructor

	//{{AFX_DATA(CDlgMatrix)
	enum { IDD = IDD_MATRIX };
	//}}AFX_DATA
	CString m_name;
	CString m_max;
	SJMatrix* mp_matrix;

	//{{AFX_VIRTUAL(CDlgMatrix)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CDlgMatrix)
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
