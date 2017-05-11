#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJNodeTransManip.h"
#include "SJBounds.h"

SJNodeTransManip::SJNodeTransManip()
{
	rotationX.set_value(1.0f, 0.0f, 0.0f, 0.0f);
	rotationY.set_value(0.0f, 1.0f, 0.0f, 0.0f);	
	m_scale.set_value(1.0f, 1.0f, 1.0f);
	m_center.set_value(0.0f, 0.0f, 0.0f);

	m_rotation_type	= BI_AXIAL;
	m_view_type			= PERSPECTIVE;
}

SJNodeTransManip::~SJNodeTransManip()
{}

void SJNodeTransManip::do_gl_rotations()
{
	SJVec3 axis;
	float angle;

	switch(m_rotation_type)
	{
	case(BI_AXIAL):

		rotationY.get_value(axis, angle);
		::glRotated(angle, axis[0], axis[1], axis[2]);

		rotationX.get_value(axis, angle);
		::glRotated(angle, axis[0], axis[1], axis[2]);

	break;
	case(TRACKBALL):

		::glMultMatrixf((float*)m_mat.get_value());

	break;
	}
}

void SJNodeTransManip::traverse_render(int render_type)
{
	float cx, cy, cz;
	m_center.get_value(cx, cy, cz);
	::glTranslated(-cx, -cy, -cz);
	do_gl_rotations();
	::glTranslated(cx, cy, cz);
}

void SJNodeTransManip::traverse_bounds(SJBounds &bounds)
{
	SJRotation bRotation;
	
	SJVec3 axis;
	float cx, cy, cz, x, y, z, angle;

	SJMat3 tempMatrix;
	m_center.get_value(cx, cy, cz);
	axis.set_value(-cx, -cy, -cz);
	tempMatrix.setTranslate(axis);
	bounds.m_mat3.by(tempMatrix);

	switch(m_rotation_type)
	{
	case(BI_AXIAL):

		rotationY.get_value(x, y, z, angle);
		bRotation.set_value(x, y, z, angle);
		bRotation.get_value(tempMatrix);
		bounds.m_mat3.by(tempMatrix);

		rotationX.get_value(x, y, z, angle);
		bRotation.set_value(x, y, z, angle);
		bRotation.get_value(tempMatrix);
		bounds.m_mat3.by(tempMatrix);
	
	break;
	case(TRACKBALL):

		bounds.m_mat3.by(m_mat);

	break;
	}
	axis.set_value(cx, cy, cz);
	tempMatrix.setTranslate(axis);
	bounds.m_mat3.by(tempMatrix);
}

void SJNodeTransManip::inc_x_rotation(float inc)
{
	float x, y, z, angle;
	rotationX.get_value(x, y, z, angle);
	angle += inc;
	rotationX.set_value(1.0f, 0.0f, 0.0f, angle);	
}

void SJNodeTransManip::inc_y_rotation(float inc)
{
	float x, y, z, angle;
	rotationY.get_value(x, y, z, angle);
	angle += inc;
	rotationY.set_value(0.0f, 1.0f, 0.0f, angle);		
}

void SJNodeTransManip::inc_with_trackball(float x, float y)
{
	SJRotation t_rotation;
	SJMat3  t_matrix;

	t_rotation.set_value(1.0f, 0.0f, 0.0f, y);
	t_rotation.get_value(t_matrix);
	m_mat.by(t_matrix);

	t_rotation.set_value(0.0f, 1.0f, 0.0f, x);
	t_rotation.get_value(t_matrix);
	m_mat.by(t_matrix);
}

void SJNodeTransManip::inc_x_and_y_rotation(float x, float y)
{
	x /= 4.0f;
	y /= 4.0f;

	switch(m_view_type)
	{
	case(PERSPECTIVE):
	case(ORTHO):

		switch(m_rotation_type)
		{
		case(BI_AXIAL):
			inc_x_rotation(x);
			inc_y_rotation(y);
		break;
		case(TRACKBALL):
			inc_with_trackball(-y, -x);
		break;
		}

	case(X_Z_PLANE):
	case(X_Y_PLANE):

		inc_y_rotation(y);

	break;
	}
}

void SJNodeTransManip::change_manip_type(int type)
{
/*

	if(m_view_type == type) return;
	else m_view_type = type;

	switch(type)
	{
		case(IDB_ORTHO):
			rotationX.set_value(1.0f, 0.0f, 0.0f, 0.0f);
		break;
		case(X_Z_PLANE):
			rotationX.set_value(1.0f, 0.0f, 0.0f, 0.0f);
			change_rotation_type(BI_AXIAL);
		break;
		case(X_Y_PLANE):
			rotationX.set_value(1.0f, 0.0f, 0.0f, 90.0f);
			change_rotation_type(BI_AXIAL);
		break;
	}
	rotationX.get_value(m_mat);
*/
}

void SJNodeTransManip::change_rotation_type(int type)
{
	if(m_rotation_type == type) return;
	else m_rotation_type = type;

	rotationX.set_value(1.0f, 0.0f, 0.0f, 0.0f);
	rotationY.set_value(0.0f, 1.0f, 0.0f, 0.0f);	

	switch(m_rotation_type)
	{
	case(BI_AXIAL):

	break;
	case(TRACKBALL):

		rotationX.get_value(m_mat);

	break;
	}
}