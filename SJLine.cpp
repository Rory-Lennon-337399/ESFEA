#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJLine.h"

SJLine::SJLine(SJPoint* p_p1, SJPoint* p_p2, float ae) 
{
	m_ae = ae;
	mp_p1 = p_p1;
	mp_p2 = p_p2;
}

SJLine::~SJLine()
{}

void SJLine::traverse_render(int render_type)
{
	::glColor3d(0.0, 0.0, 1.0);

	SJVec3 vec1;
	SJVec3 vec2;

	if(render_type == RENDER)
	{
		vec1.set_value(mp_p1->get_value());
		vec2.set_value(mp_p2->get_value());
	}
	if(render_type == ANIMATE)
	{
		vec1.set_value(mp_p1->get_animate());
		vec2.set_value(mp_p2->get_animate());
		vec1.trace_val();
	}

	::glBegin(GL_LINES);
		::glVertex3fv(vec1.get_value());
		::glVertex3fv(vec2.get_value());
	::glEnd();
}

