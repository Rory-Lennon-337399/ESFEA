#include "stdafx.h"
#include "ESFEA2D.h"
#include "FileIn.h"
#include "MainFrm.h"

BEGIN_MESSAGE_MAP(CESFEA2DApp, CWinApp)
//{{AFX_MSG_MAP(CESFEA2DApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CESFEA2DApp::CESFEA2DApp()
{}

CESFEA2DApp theApp;

BOOL CESFEA2DApp::InitInstance()
{
	Enable3dControls();	
	SetRegistryKey(_T("ESFEA"));
	LoadStdProfileSettings(8);

	CAnimateCtrl animctrl;

	m_sg.create_tree();

	m_i_manip_mode		= 0;
	m_drag_mode			= true;

	m_font.CreateFont(-11, 0, 0, 0, 0, 0, 0, 0,
							DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
							ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Arial"));

	m_font_small.CreateFont(-10, 0, 0, 0, FW_BOLD, 0, 0, 0,
								DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Arial Bold"));

	m_background_color.set_value(0.8f, 0.8f, 0.8f);

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	pFrame->LoadFrame(IDR_MAINFRAME, 
							WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, 
							NULL,
							NULL);

	m_app_icon = LoadIcon(IDI_SEJIKA);
	m_pMainWnd->SetIcon(m_app_icon, TRUE);
	m_pMainWnd->SetIcon(m_app_icon, FALSE);

	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	m_last_file = GetProfileString("user", "last_file", "..\\Mesh Files\\P3.xml");
	open_file(m_last_file);

	return TRUE;
}

class CAboutDlg : public CDialog
{
public:

	CAboutDlg();

//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
//}}AFX_DATA

//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
//}}AFX_VIRTUAL

protected:

//{{AFX_MSG(CAboutDlg)
//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
//{{AFX_DATA_INIT(CAboutDlg)
//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
//{{AFX_DATA_MAP(CAboutDlg)
//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CESFEA2DApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

CDocument* CESFEA2DApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	open_file(lpszFileName);
	return (CDocument*)TRUE;
}

CString CESFEA2DApp::get_mru_top()
{
	CString mru_str;
	m_pRecentFileList->GetDisplayName(mru_str, 0, "", 0, FALSE);
	return mru_str;
}

int CESFEA2DApp::ExitInstance() 
{
	WriteProfileString("user", "last_file", m_last_file);
	return CWinApp::ExitInstance();
}

void CESFEA2DApp::OnFileOpen() 
{
	BOOL b_save_or_open = TRUE;
	CString str_default_extension = "";
	CString str_file_title = "";
	CString str_filter = _T("ESFEA2D Project Files (*.xml)|*.xml||");

	CFileDialog dlg_file(b_save_or_open, 
							   str_default_extension, 
							   str_file_title,
							   OFN_HIDEREADONLY,
							   str_filter,
							   NULL);

	dlg_file.m_ofn.lpstrInitialDir = _T("..\\Mesh Files");
	int do_it = dlg_file.DoModal();
	if(do_it == 1) open_file(dlg_file.GetPathName());
}

void CESFEA2DApp::open_file(CString file_path)
{
	if(file_path == "") return;

	OnFileNew();

	m_last_file = file_path;

	OnFileNew();
	CFileIn file_in;
	if(!file_in.Open(file_path, false)) 
	{
		TRACE("File not opened\n");	
		return;
	}
	file_in.read_file();
	file_in.Close();

	((CMainFrame*)m_pMainWnd)->m_status.set_filename(file_in.GetFileName());
	AddToRecentFileList(file_path);

	m_pMainWnd->SendMessageToDescendants(ID_UPDATE_DATA, TO_DIALOG, 0);

	m_sg.fit_mesh();
	m_pMainWnd->Invalidate(TRUE);
}

void CESFEA2DApp::OnFileSave() 
{
	if(!save_file(m_last_file)) OnFileSaveAs(); 	
}

void CESFEA2DApp::OnFileSaveAs() 
{
	BOOL b_save_or_open = FALSE;
	CString str_default_extension = "cps";
	CString str_file_title = "";
	CString str_filter = _T("ESFEA2D Project Files (*.xml)|*.xml||");

	CFileDialog dlg_file(b_save_or_open, 
							   str_default_extension, 
							   str_file_title,
							   OFN_HIDEREADONLY,
							   str_filter,
							   NULL);

	dlg_file.m_ofn.lpstrInitialDir = _T("..\\Mesh Files");
	int do_it = dlg_file.DoModal();

	if(do_it == 1)
	{
		m_last_file = dlg_file.GetPathName();
		if(!save_file(dlg_file.GetPathName()))
		{
			MessageBox(NULL, "File Not Saved.", "Error", MB_OK | MB_ICONERROR);
		}
	}		
}

BOOL CESFEA2DApp::save_file(CString file_path)
{
	if(file_path == "") return FALSE;

	ofstream open_file(file_path);
	if(!open_file.is_open()) return FALSE;

	m_pMainWnd->SendMessageToDescendants(ID_UPDATE_DATA, FROM_DIALOG, 0);

	m_sg.traverse_write(&open_file);
	open_file.close();

	m_last_file = file_path;
	AddToRecentFileList(file_path);

	return TRUE;
}

void CESFEA2DApp::OnFileNew() 
{
	m_sg.new_file();	
	m_pMainWnd->Invalidate(TRUE);
}

void CESFEA2DApp::set_mode(int newmode)
{
	m_i_manip_mode	= newmode;
	m_pMainWnd->SendMessageToDescendants(ID_CHANGE_MODE, newmode, 0);
}

int CESFEA2DApp::get_mode()
{
	return m_i_manip_mode;
}
