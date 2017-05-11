#pragma once

#include "SJVector.h"

class SJMatrix
{
public:
				SJMatrix();
				SJMatrix(int sz);
				SJMatrix(SJMatrix &bm);
	void		size(int sz);
	float		&el(int i, int j);
	void		identity();
	void		clear();
	void		trace_matrix();
				SJMatrix::~SJMatrix();
	void		by_m(SJMatrix &m);
	void		by_mt(SJMatrix &m);
	void		t_by(SJMatrix &m);
	void		by_vt(SJVector &vt);
	void		v_by(SJVector &vt);
	void 		vt_by(SJVector &from, SJVector &to);
	void		copy(SJMatrix &m);
	int		jacobi(CWnd* p_wnd, SJMatrix &k, SJVector &d);
	void		eigsrt(SJVector &d); 
	void 		eignrm(SJVector &mass);
	float		draw(CPaintDC &dc);
	float		maxval();
	float		maxc(int col);
	void		scalecol(int colnum, float scalar);
	void		set_diagonal(float val);
	void		set_maxval();

	CString	m_name;
	int		m_size;
	int		m_nel;
	float		m_fmx;

protected:

	void		rotate(SJMatrix &a, int i, int j, int k, int l, float tau, float s);
	float		sabs(float in);
	float		sr(float in);
	float*	m_data;
};

