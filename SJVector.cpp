#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJVector.h"
#include "SJMatrix.h"
#include "math.h"

SJVector::SJVector()
{
	m_data = NULL;
	m_size = 0;
}

SJVector::SJVector(int sz)
{
	m_data = NULL;
	size(sz);
}

SJVector::SJVector(SJMatrix &bm, int column)
{
	m_data = NULL;
	size(bm.m_size);
	for (int i = 1; i <= m_size; i++) el(i) = bm.el(i, column);
}

SJVector::SJVector(SJVector &v)
{
	m_data = NULL;
	size(v.m_size);
	copy(v);
}

void SJVector::size(int sz)
{
	m_size = sz;
	delete[] m_data;
	m_data = NULL;
	if(m_size > 0) 
	{
		m_data = new float[m_size + 2];
		clear();
	}
}

SJVector::~SJVector()
{
	delete[] m_data;
}

float &SJVector::el(int i) 
{
	return m_data[i + 1];
}

void SJVector::clear()
{
	for (int i = 0; i < (m_size + 2); i++) m_data[i] = 0.0f;
}

void SJVector::copy(SJVector &bv)
{
	if(m_size != bv.m_size) return;
	for (int i = 1; i <= m_size; i++) 
	{
		el(i) = bv.el(i);
	}
}

float SJVector::by_vt(SJVector &vec) 
{
 	float returnval = 0.0f;
 	for (int i = 1; i <= m_size; i++) returnval += el(i) * vec.el(i);
 	return returnval;              
} 

void SJVector::v_by(SJVector &v) 
{
 	for (int i = 1; i <= m_size; i++) el(i) = el(i) * v.el(i);           
} 

void SJVector::vt_by(SJMatrix &m)
{
	SJVector tv(*this);
	clear();
	int i, j;
	for (i = 1; i <= m_size; i++) for (j = 1; j <= m_size; j++) el(i) += tv.el(j) * m.el(j, i); 
}

void SJVector::set_val(float val)
{
	for (int i = 1; i <= m_size; i++) el(i) = val;
}

void SJVector::scale(float scalar)
{
	for (int i = 1; i <= m_size; i++) el(i) *= scalar;
}
	
void SJVector::add(SJVector &v)
{
	for (int i = 1; i <= m_size; i++) el(i) += v.el(i);
}

void SJVector::trace_vector()
{
	int i;

	int out_size = m_size;
	if(out_size > 14) out_size = 14;

	for (i = 0; i < out_size; i++) 
	{
		TRACE("%10.2i", i);
	}

	TRACE("\n");

	for (i = 0; i < out_size; i++)
	{
		TRACE(" "); 
		TRACE("%8.2e", el(i)); 
	}
	TRACE("\n");
}

void SJVector::invert()
{
	for(int i = 1; i <= m_size; i++) 
	{
		if(el(i) != 0.0f)
		{
			el(i) = 1.0f / el(i);
		}
	}
}

void SJVector::sqrt()
{
	for(int i = 1; i <= m_size; i++) 
	{
		if(el(i) != 0.0f)
		{
			el(i) = sqrtf(el(i));
		}
	}
}