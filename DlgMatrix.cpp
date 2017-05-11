#include "stdafx.h"
#include "ESFEA2D.h"
#include "DlgMatrix.h"

CDlgMatrix::CDlgMatrix(CWnd* pParent, SJMatrix* p_matrix, CString name) : CDialog(IDD_MATRIX)
{
	mp_matrix = p_matrix;
	m_name = name;
	//{{AFX_DATA_INIT(CDlgMatrix)
	//}}AFX_DATA_INIT
}

void CDlgMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMatrix)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgMatrix, CDialog)
	//{{AFX_MSG_MAP(CDlgMatrix)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgMatrix::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	double max = mp_matrix->draw(dc);
	m_max.Format("%10.5f", max);
	SetWindowText(m_name + " " + m_max);
}

void CDlgMatrix::OnClose() 
{
	GetParent()->PostMessage(ID_CLOSE_MATRIX, 0, 0);	
	CDialog::OnClose();
}

void CDlgMatrix::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	CDialog::OnCancel();	

//	GetParent()->PostMessage(ID_CLOSE_MATRIX, 0, 0);	
//	PostMessage(WM_CLOSE, 0, 0);		
}

BOOL CDlgMatrix::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;
}
