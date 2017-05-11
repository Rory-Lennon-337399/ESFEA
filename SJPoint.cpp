#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJPoint.h"

#define HIGHLIGHT true
#define NOT_HIGHLIGHT false

SJPoint::SJPoint() : SJVec3()
{
	init();
}

SJPoint::SJPoint(const float v[3]) : SJVec3(v)
{
	init();
}

SJPoint::SJPoint(int num, float x, float y, float z, float mass) : SJVec3(x, y, z)
{
	init();
	m_num = num;
	m_lump = mass;
}

SJPoint::~SJPoint()
{
	m_animate_vecs.delete_data();
}

void SJPoint::init()
{
	for(int i = 0; i < 3; i++) m_dof[i] = 0;
	m_pos				= NULL;
	m_selection		= 0;
	m_point_size	= 0.1f;
	m_fix				= 0;
}

void SJPoint::fix(int i)
{
	if(i >= 1) 
	{
		m_fix = 1;
		m_load.set_value(0.0f, 0.0f, 0.0f);
	}
	else 
	{
		m_fix = 0;
	}
}

int SJPoint::get_fix()
{
	return m_fix;
}

void SJPoint::adjust_point_size(bool resize_method, float scale, float new_size)
{
	if(resize_method)
	{
		if(m_point_size <= 0.0f) m_point_size = new_size * scale;
		else
		{
			m_point_size = min(m_point_size, new_size * scale);
		}
	}
	else m_point_size = max(m_point_size, new_size * scale);
}

void SJPoint::set_colors(float m)
{
//	TRACE("SJPoint::set_colors mass %8.4f\n", m);

	if(m_selection == 1) 
	{
		::glColor3f(1.0f, 1.0f, 1.0f);
		return;
	}
	float shade = 0.0f;
	if(m == 0.0f) shade = 0.0f;
	else shade = 0.25f + (0.75f * m_lump / m);

//	TRACE("mass %8.4f shade %8.4f\n", mass, shade);	

	if(m_fix == 0) ::glColor3f(0.0f, shade, 0.0f);
	else ::glColor3f(1.0f, 0.0f, 0.0f);
} 

void SJPoint::traverse_render(float force, float mass)
{
	draw_point((SJVec3*)this, force, mass);
}

void SJPoint::traverse_write(ofstream* p_file)
{
	*p_file << "<NODE ";
	*p_file << " NUMBER=" << dqs << m_num << dqs;
	*p_file << " XX=";
	write_float(p_file, get_component(0));
	*p_file << " YY=";
	write_float(p_file, get_component(1));
	*p_file << " LUMP=";
	write_float(p_file, m_lump);
	*p_file << " FIX=" << dqs << m_fix << dqs;

	if(m_load.get_component(0) != 0.0f) 
	{
		*p_file << " XF=";
		write_float(p_file, m_load.get_component(0));
	}
	if(m_load.get_component(1) != 0.0f) 
	{
		*p_file << " YF=";
		write_float(p_file, m_load.get_component(1));
	}
	*p_file << " />" << endl;
}

void SJPoint::write_float(ofstream* p_file, float val)
{
	char dqs = 34;
	*p_file << dqs;

//	char szBuffer[10];
//	::sprintf(szBuffer, "%10.3f", val);
//	*p_file << szBuffer;
	*p_file << val;
//	for(int i = 0; i < 10; i++)
//	{
//		if(szBuffer[i] != ' ') *p_file << szBuffer[i];
//	}
	*p_file << dqs;
}

void SJPoint::draw_point(SJVec3* p_vec, float force, float mass)
{
//	TRACE("SJPoint::draw_point force %8.4f mass %8.4f\n", force, mass);

	::glPushMatrix();

		GLint p_this = (GLint)this;
		::glLoadName(p_this);	

		float sx, sy, sz;
		get_value(sx, sy, sz);
		::glTranslated(sx, sy, sz);

		::glEnable(GL_COLOR_MATERIAL);
		::glEnable(GL_LIGHTING);
		
		set_colors(mass);

		GLUquadric* qobj = ::gluNewQuadric();
		::gluQuadricDrawStyle(qobj, GLU_FILL);
		::gluQuadricOrientation(qobj, GLU_OUTSIDE);
		::gluQuadricNormals(qobj, GLU_SMOOTH);
		::gluSphere(qobj, m_point_size, 10, 12);

	::glPopMatrix();

	draw_load(force);
}

void SJPoint::draw_load(float force)
{
	float scale = force;
	if(scale <= 0.0f) scale = 1.0f;

	SJVec3 load_pos(m_load);
	load_pos *= force;
	load_pos += *this;

//	::glLineWidth(1.5f);
	::glColor3f(1.0f, 0.0f, 0.0f);

	::glDisable(GL_LIGHTING);	

//	trace_val();
//	m_load.trace_val();
//	load_pos.trace_val();

//	TRACE("\n");

	::glBegin(GL_LINES);

		::glVertex3fv(get_value());
		::glVertex3fv(load_pos.get_value());

	::glEnd();
}

void SJPoint::reset_animate()
{
	m_pos = NULL;
}

void SJPoint::clear_animate()
{
	m_animate_vecs.delete_data();
	m_pos = NULL;
}

void SJPoint::add_animate(SJVec3& disp)
{
//	TRACE("SJPoint::add_animate %i\n", m_animate_vecs.get_count());

	SJVec3* p_new_vec;
	p_new_vec = new SJVec3(get_value());
	*p_new_vec +=(disp);
	m_animate_vecs.add_tail(p_new_vec);
}

BOOL SJPoint::next_frame()
{
	if(m_pos == NULL) m_pos = m_animate_vecs.get_head_pos();

//	TRACE("SJPoint::next_frame %i\n", m_animate_vecs.get_count());

	if(m_pos == NULL) return FALSE;
	else 
	{
		m_animate_vecs.get_next(m_pos);
		if(m_pos != NULL) return TRUE;
		else return FALSE;
	}
}

const float* SJPoint::get_animate() const
{
	if(m_pos == NULL) return get_value();
	else return m_animate_vecs.get_pos(m_pos)->get_value();
}



