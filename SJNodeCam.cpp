#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJNodeCam.h"

SJNodeCam::SJNodeCam()
{
	mp_sg = &((CESFEA2DApp*)AfxGetApp())->m_sg;
	m_push_back.set_value(0.0f, 0.0f, 0.0f);
	m_scale.set_value(1.0f, 1.0f, 1.0f);
	m_slack = 0.2f;
}

SJNodeCam::~SJNodeCam()
{}

void SJNodeCam::fit_mesh()
{
	short rx, ry;
	mp_sg->m_region.get_value(rx, ry);
	m_aspect_ratio = (float)rx / (float)ry;

	float sx, sy, sz;
	m_scale.get_value(sx, sy, sz);
	m_object_position.set_value(mp_sg->m_bounds.m_box.get_center());

	m_push_back.set_value(0.0f, 0.0f, mp_sg->m_bounds.m_box.get_diagonal());
	m_scale.set_value(1.0f, 1.0f, 1.0f);

	m_near = -mp_sg->m_bounds.m_box.get_diagonal() * 100.0f;
	m_far  =  mp_sg->m_bounds.m_box.get_diagonal() * 100.0f;

	float heightTemp = mp_sg->m_bounds.m_box.get_height();
	float widthTemp = mp_sg->m_bounds.m_box.get_width();
	float ao = widthTemp / heightTemp;

	if(m_aspect_ratio > ao) 
	{
		m_height = heightTemp * (m_slack + 1.0f);
		m_width  = m_height * m_aspect_ratio;
	}
	else 
	{
		m_height = widthTemp * (m_slack + 1.0f) / m_aspect_ratio;
		m_width  = m_height * m_aspect_ratio;
	}

	m_left		= -m_width / 2.0f;
	m_right		=  m_width / 2.0f;

	m_bottom		= -m_height / 2.0f; 
	m_top			=  m_height / 2.0f;
} 

void SJNodeCam::move_camera_delta(float dx, float dy, float /*dz*/)
{
	float x, y, z;
	m_push_back.get_value(x, y, z);
	x += dx;
	y += dy;
	m_push_back.set_value(x, y, z);
}

void SJNodeCam::scale_object(float dx, float dy, float dz)
{
	float x, y, z;
	m_scale.get_value(x, y, z);

	x += (dx / 40.0f);
	y += (dy / 40.0f);
	z += (dz / 40.0f);

	if(x < 0.001f) x = 0.001f;
	if(y < 0.001f) y = 0.001f;
	if(z < 0.001f) z = 0.001f;

	m_scale.set_value(x, y, z);
}

void SJNodeCam::traverse_render(int render_type)
{
	::glMatrixMode(GL_PROJECTION);
	if(render_type != SELECT) ::glLoadIdentity();

	float sx, sy, sz;
	m_scale.get_value(sx, sy, sz);

	::glOrtho(m_left * sx, m_right * sx, m_bottom * sy, m_top * sy, m_near, m_far);

	float x, y, z;
	m_push_back.get_value(x, y, z);
	::glTranslated(-x, -y, -z);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

//	m_scale_factor.get_value(x, y, z);
//	::glScalef(x, y, z);

	m_object_position.get_value(x, y, z);
	::glTranslated(-x, -y, -z);
}

void SJNodeCam::traverse_select(CRect& rect)
{

}

void SJNodeCam::traverse_bounds(SJBounds &bounds)
{	
	SJVec3 axis;
	float cx, cy, cz;
	SJMat3 tempMatrix;

	m_object_position.get_value(cx, cy, cz);
	axis.set_value(cx, cy, cz);
	tempMatrix.setTranslate(axis);
	bounds.m_mat3.by(tempMatrix);

	axis.set_value(-cx, -cy, -cz);
	tempMatrix.setTranslate(axis);
	bounds.m_mat3.by(tempMatrix);
}

