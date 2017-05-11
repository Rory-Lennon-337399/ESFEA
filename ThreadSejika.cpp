#include "stdafx.h"
#include "ESFEA2D.h"
#include "ThreadSejika.h"
#include "SJSG.h"

IMPLEMENT_DYNCREATE(CThreadSejika, CWinThread)

CThreadSejika::CThreadSejika(SJSG* p_sg, CWnd* p_wnd)
{
	mp_sg		= p_sg;
	mp_wnd	= p_wnd; 
}

CThreadSejika::CThreadSejika()
{}

CThreadSejika::~CThreadSejika()
{}

BOOL CThreadSejika::InitInstance()
{
//	CWinThread::InitInstance();

	SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);

	m_bAutoDelete = TRUE;
	mp_wnd->PostMessage(ID_CALC_STARTED, NULL, NULL);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CThreadSejika, CWinThread)
	//{{AFX_MSG_MAP(CThreadSejika)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreadSejika message handlers

int CThreadSejika::Run() 
{
/*
	SJTraverseMesh mesh_traversal(mp_sg, SJTraverseMesh::FILM_MODE);
	mesh_traversal.set_type(SJTraverseMesh::FILM_MODE);
	mesh_traversal.apply(mp_sg->get_root_pod());

	if(mesh_traversal.get_sub_sub_type() == SJTraverseMesh::NOTHING_THERE)
	{
		mp_wnd->PostMessage(ID_CALC_FINISHED, IDF_NOTHING_THERE, NULL);
		return TRUE;
	}
	if(mesh_traversal.get_sub_type() == SJTraverseMesh::FIX_MORE)
	{
		mp_wnd->PostMessage(ID_CALC_FINISHED, IDF_FIX_MORE, NULL);
		return TRUE;
	}
	if(mesh_traversal.get_sub_type() == SJTraverseMesh::LOAD_SOME)
	{
		mp_wnd->PostMessage(ID_CALC_FINISHED, IDF_LOAD_SOME, NULL);
		return TRUE;
	}
	mp_wnd->PostMessage(ID_CALC_FINISHED, IDF_FINISHED_DYNAMIC, NULL);
	return TRUE;
*/
	return true;
}
