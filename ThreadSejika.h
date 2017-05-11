
#pragma once

class SJSG;

class CThreadSejika : public CWinThread
{
	DECLARE_DYNCREATE(CThreadSejika)

public:

	CThreadSejika(SJSG* p_sg, CWnd* p_wnd);
	virtual ~CThreadSejika();

//{{AFX_VIRTUAL(CThreadSejika)
public:
	virtual BOOL	InitInstance();
	virtual int		Run();
//}}AFX_VIRTUAL

protected:

	CThreadSejika();

	SJSG*			mp_sg;
	CWnd*			mp_wnd;
	int			m_num_frames;

//{{AFX_MSG(CThreadSejika)
//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


