#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJMatrix.h"
#include "math.h"

SJMatrix::SJMatrix()
{
	m_data = NULL;
	m_size = 0;
	m_nel = 0;
	m_fmx = 0;
}

SJMatrix::SJMatrix(int sz)
{
	m_data = NULL;
	size(sz);
}

SJMatrix::SJMatrix(SJMatrix &bm)
{
	m_data = NULL;
	size(bm.m_size);
	copy(bm);
}

SJMatrix::~SJMatrix()
{
	delete[] m_data;
}

void SJMatrix::size(int sz)
{
	m_fmx = 0;
	m_nel = 0;
	m_size = sz;
	delete[] m_data;
	m_data = NULL;
	if(m_size > 0) 
	{
		m_nel = (m_size + 2) * (m_size + 2);
		m_data = new float[m_nel];
		clear();
	}
}

float &SJMatrix::el(int i, int j) 
{
	return m_data[i * (m_size + 1) + (j + 1)];
}

void SJMatrix::set_maxval()
{
	m_fmx = maxval();
}

void SJMatrix::identity() 
{	
	set_diagonal(1.0f);
}

void SJMatrix::set_diagonal(float val)
{
	if(m_size < 1) return;
	clear();
	for (int i = 1; i <= m_size; i++) el(i, i) = val;
}

void SJMatrix::clear()
{
	for (int i = 0; i < m_nel; i++) m_data[i] = 0.0f;
}

void SJMatrix::copy(SJMatrix &m)
{
	if(m.m_size < 1) return;
	if(m_size != m.m_size) return;
	for(int i = 0; i < m_nel; i++) m_data[i] = m.m_data[i];
	set_maxval();
}

void SJMatrix::by_m(SJMatrix &m)
{
	int i, j, k;
   SJMatrix mt(m_size);

	for (i = 1; i <= m_size; i++) for (j = 1; j <= m_size; j++) 
	{ 
		mt.el(i, j) = 0.0f;
		for (k = 1; k <= m_size; k++) mt.el(i, j) += el(i, k) * m.el(k, j);  	                                            
   }
   copy(mt);
	set_maxval();
}

void SJMatrix::t_by(SJMatrix &m)
{
	int i, j, k;
   SJMatrix mt(m_size);

	for (i = 1; i <= m_size; i++) for (j = 1; j <= m_size; j++) 
	{ 
		mt.el(i, j) = 0.0f;
		for (k = 0; k < m_size; k++) mt.el(i, j) += el(k, i) * m.el(k, j);  	                                            
   }
   copy(mt);
	set_maxval();
}

void SJMatrix::by_mt(SJMatrix &m)
{
	int i, j, k;

   SJMatrix mt(m_size);

	for (i = 1; i <= m_size; i++) for (j = 1; j <= m_size; j++) 
	{ 
		mt.el(i, j) = 0.0f;
		for (k = 1; k <= m_size; k++) mt.el(i, j) += el(i, k) * m.el(j, k);  	                                            
   }
   copy(mt);
	set_maxval();
}

void SJMatrix::by_vt(SJVector &vt)
{
	int i, j;
	for (i = 1; i <= m_size; i++) for (j = 1; j <= m_size; j++) 
	{ 
		el(i, j) = el(i, j) * vt.el(i);  	                                            
   }
	set_maxval();
}

void SJMatrix::v_by(SJVector &v)
{
	int i, j;
	for (i = 1; i <= m_size; i++) for (j = 1; j <= m_size; j++) el(j, i) = el(j, i) * v.el(i);  
	set_maxval();
}

void SJMatrix::vt_by(SJVector &from, SJVector &to)
{
	int i, j;
	for (i = 1; i <= m_size; i++) for (j = 1; j <= m_size; j++) to.el(i) += from.el(j) * el(j, i); 
	set_maxval();
}

void SJMatrix::trace_matrix()
{
	int i, j;

	int out_size = m_size;
	if(out_size > 14) out_size = 14;

//	TRACE("\n    ");

//	for (i = 0; i < out_size; i++) TRACE("%8.2i", i);

//	TRACE("\n\n");

	for (i = 0; i < out_size; i++)
	{
//		TRACE("%2.2i  ", i);

		for (j = 0; j < out_size; j++)
		{
//			TRACE("%8.4f", el(i, j)); 
		}
//		TRACE("\n\n");
	}
//	TRACE("\n");
}

int SJMatrix::jacobi(CWnd* p_wnd, SJMatrix &k, SJVector &d)
{
	int n = m_size;
	if(m_size != d.m_size) return -1;
	if(m_size != k.m_size) return -1;

	int j ,iq ,ip , i, nrot;
	float tresh, theta, tau, t, sm, s, h, g, c;

	SJVector b(m_size);
	SJVector z(m_size);

	identity();

	for(ip = 1; ip <= n; ip++) 
	{		
		b.el(ip) = k.el(ip, ip);
		d.el(ip) = k.el(ip, ip);
		z.el(ip) = 0.0f;
	}
	nrot = 0;
	
	for(i = 1; i <= 50; i++) 
	{		
		sm = 0.0f;
			
		for(ip = 1; ip <= n - 1; ip++) 
		{
			for (iq = ip + 1; iq <= n; iq++) sm += sabs(k.el(ip, iq));
		}
		if(sm < 1e-20f) 
		{
			eigsrt(d);
			set_maxval();
			return nrot;
		}
		if(i < 4) tresh = 0.2f * sm / (n * n);
		else tresh = 0.0f;
	  
		for(ip = 1; ip <= n - 1; ip++) 
		{
			for(iq = ip + 1; iq <= n; iq++) 
			{
				g = 100.0f * sabs(k.el(ip, iq));
	      
				if((i > 4) && (sabs(d.el(ip)) + g == sabs(d.el(ip))) && (sabs(d.el(iq)) + g == sabs(d.el(iq)))) 
							
					k.el(ip, iq) = 0.0f;
					
				else if(sabs(k.el(ip, iq)) > tresh) 
				{	
					h = d.el(iq) - d.el(ip);
					if(sabs(h) + g == sabs(h)) t = (k.el(ip, iq) / h);
					else 
					{
						theta = 0.5f * h / (k.el(ip, iq));
						t = 1.0f / (sabs(theta) + sr(1.0f + theta * theta));
						if (theta < 0.0) t = -t;
					}
					c = 1.0f / sr(1.0f + (t * t));
					s = t * c;
					tau = s / (1.0f + c);
						
					h = t * k.el(ip, iq);
						
					z.el(ip) -= h;
					z.el(iq) += h;	
					d.el(ip) -= h;
					d.el(iq) += h;
						
					k.el(ip, iq) = 0.0f;

					for (j = 1; j <= ip - 1; j++)			rotate(k, j, ip, j, iq, tau, s);
					for (j = ip + 1; j <= iq - 1; j++)	rotate(k, ip, j, j, iq, tau, s);
					for (j = iq + 1; j <= n; j++)			rotate(k, ip, j, iq, j, tau, s);
					for (j = 1; j <= n; j++)				rotate(*this, j, ip, j, iq, tau, s);

					++nrot;
				}
			}
		}
		for (ip = 1; ip <= n; ip++) 
		{
			b.el(ip) += z.el(ip);
			d.el(ip) =  b.el(ip);
			z.el(ip) =  0.0;
		}
//		TRACE("\nIteration %d \n", i); 
	}
//	TRACE("\nToo many iterations in routine JACOBI\n"); 
	return nrot;
}

void SJMatrix::rotate(SJMatrix &a, int i, int j, int k, int l, float tau, float s) 
{
	float g, h;
	g = a.el(i, j); 
	h = a.el(k, l); 
	a.el(i, j) = g - s * (h + g * tau);
	a.el(k, l) = h + s * (g - h * tau);
}

void SJMatrix::eigsrt(SJVector &d) 
{ 
	int n = d.m_size;
	if(m_size != n) return;

	int k, j, i;
	float p;

	for(i = 1; i <= n; i++) 
	{
		p = d.el(k = i);

		for (j = i + 1; j <= n; j++) if (d.el(j) <= p) p = d.el(k = j);
            
		if(k != i) 
		{     
			d.el(k) = d.el(i);
			d.el(i) = p;
         for (j = 1; j <= n; j++) 
			{       
				p = el(j, i);
				el(j, i) = el(j, k);
            el(j, k) = p;
			}
		}
	}
}

void SJMatrix::eignrm(SJVector &mass)
{
	float nrm = 0.0f;
	for(int modenum = 1; modenum <= m_size; modenum++)
	{ 
		SJVector eigenmode(*this, modenum);
		SJVector eigenmode2(*this, modenum);
		eigenmode.v_by(mass);
		nrm = eigenmode.by_vt(eigenmode2);
		nrm = 1.0f / sqrtf(fabsf(nrm));
		TRACE("EIGNRM %3i %15.5f \n", modenum, nrm);
		scalecol(modenum, nrm);
	}
	set_maxval();
}

void SJMatrix::scalecol(int colnum, float scalar)
{
	for(int rownum = 1; rownum <= m_size; rownum++) el(rownum, colnum) *= scalar;
}

float SJMatrix::sabs(float in)
{
	return (float)fabs(in);
}

float SJMatrix::sr(float in)
{
	return (float)sqrt(in);
}

float SJMatrix::maxval()
{
	int i, j;
	float max_val = 0.0f;
	float current_val = 0.0f;

	for (i = 1; i < m_size; i++) for (j = 1; j < m_size; j++)
	{ 
		if((float)fabs(el(i, j)) > (float)fabs(max_val)) max_val = el(i, j);
	}
	return max_val;
}

float SJMatrix::maxc(int col)
{
	int i;
	float max_val = 0.0f;
	float current_val = 0.0f;

	for (i = 1; i <= m_size; i++)
	{ 
		if((float)fabs(el(i, col)) > (float)fabs(max_val)) max_val = el(i, col);
	}
	return max_val;
}

float SJMatrix::draw(CPaintDC &dc)
{
	CRect rect;
	dc.GetWindow()->GetClientRect(&rect);

	int dc_size = rect.right;
	int i, j, rval, gval, bval;
	if(m_size <= 0) return 0.0;
	int sqsize = dc_size / m_size;
	float current_val = 0.0f;
	float afmx = (float)fabs(m_fmx);

	for (i = 1; i <= m_size; i++)
	{
		int xp = (sqsize * (i - 1));
		for (j = 1; j <= m_size; j++)
		{		
			int yp = (sqsize * (j - 1));
			if (afmx > 0.0f) 
			{
				current_val = el(i, j);
				if(current_val >= 0.0f)
				{
					rval = (int)((1.0f - (current_val / afmx)) * 255.0f);
					gval = rval;
					bval = 255;
				}
				else
				{
					rval = 255;
					bval = (int)((1 + (current_val / afmx)) * 255.0f);
					gval = bval;
				}
			}
			else 
			{
				rval = 255;
				gval = 255;
				bval = 255;
			}
			CBrush brush;
			brush.CreateSolidBrush(RGB(rval, gval, bval));
			CRect rect(yp, xp, yp + sqsize - 1, xp + sqsize - 1);
			dc.FillRect(&rect, &brush);
			brush.DeleteObject();
		}
	}
	return m_fmx;
}

