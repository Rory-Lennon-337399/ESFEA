#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJBounds.h"

SJBounds::SJBounds()
{
	m_first_pass = TRUE;
	m_mat3.identity();
}

SJBounds::~SJBounds()
{}

void SJBounds::stretch(SJVec3& point)
{
	if(m_first_pass)
	{		
		m_first_pass = FALSE;
		m_box.set_bounds(point, point);
	}
	else
	{
		m_box.extend_by(point);
	}
}

