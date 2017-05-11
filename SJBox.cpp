#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJBox.h"
#include <Math.h>

SJBox::SJBox()
{
	m_min_vec[0] = 0.0f;
	m_min_vec[1] = 0.0f;
	m_min_vec[2] = 0.0f;

	m_max_vec[0] = 0.0f;
	m_max_vec[1] = 0.0f;
	m_max_vec[2] = 0.0f;
}

SJBox::SJBox(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax)
{
	m_min_vec[0] = xmin;
	m_min_vec[1] = ymin;
	m_min_vec[2] = zmin;

	m_max_vec[0] = xmax;
	m_max_vec[1] = ymax;
	m_max_vec[2] = zmax;
}

SJBox::SJBox(const SJVec3 &min, const SJVec3 &max)
{
	m_min_vec = min;
	m_max_vec = max;
}

SJBox::~SJBox()
{}

const SJVec3& SJBox::get_min()
{
	return m_min_vec;
}

const SJVec3& SJBox::get_max()
{
	return m_max_vec;	
}

SJVec3 SJBox::get_center()
{
	SJVec3 center;

	center[0] = (m_max_vec[0] + m_min_vec[0]) / 2.0f;
	center[1] = (m_max_vec[1] + m_min_vec[1]) / 2.0f;
	center[2] = (m_max_vec[2] + m_min_vec[2]) / 2.0f;

	return center;
}

float SJBox::get_diagonal()
{
	float x_len = get_width();
	float y_len = get_height();
	return (float)sqrt(x_len * x_len + y_len * y_len);
}

float	SJBox::get_width()
{
	return m_max_vec[0] - m_min_vec[0];
}

float	SJBox::get_height()
{
	return m_max_vec[1] - m_min_vec[1];
}

float	SJBox::get_depth()
{
	return m_max_vec[2] - m_min_vec[2];
}

float	SJBox::get_min_dimension()
{
	float mn = min(get_width(), get_height());
	mn = min(mn, get_depth());
	return mn;
}

void SJBox::extend_by(const SJVec3 & point)
{
	m_min_vec[0] = min(m_min_vec[0], point[0]);
	m_min_vec[1] = min(m_min_vec[1], point[1]);
	m_min_vec[2] = min(m_min_vec[2], point[2]);

	m_max_vec[0] = max(m_max_vec[0], point[0]);
	m_max_vec[1] = max(m_max_vec[1], point[1]);
	m_max_vec[2] = max(m_max_vec[2], point[2]);
}

void SJBox::extend_by(const SJBox & box)
{
	m_min_vec[0] = min(m_min_vec[0], box.m_min_vec[0]);
	m_min_vec[1] = min(m_min_vec[1], box.m_min_vec[1]);
	m_min_vec[2] = min(m_min_vec[2], box.m_min_vec[2]);

	m_max_vec[0] = max(m_max_vec[0], box.m_max_vec[0]);
	m_max_vec[1] = max(m_max_vec[1], box.m_max_vec[1]);
	m_max_vec[2] = max(m_max_vec[2], box.m_max_vec[2]);
}

void SJBox::slack_by(float fSlack)
{
	float diagSlack = get_diagonal() * fSlack;

	m_min_vec[0] -= diagSlack;
	m_min_vec[1] -= diagSlack;
	m_min_vec[2] -= diagSlack;

	m_max_vec[0] += diagSlack;
	m_max_vec[1] += diagSlack;
	m_max_vec[2] += diagSlack;
}

void SJBox::set_bounds(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax)
{
	m_min_vec[0] = xmin;
	m_min_vec[1] = ymin;
	m_min_vec[2] = zmin;

	m_max_vec[0] = xmax;
	m_max_vec[1] = ymax;
	m_max_vec[2] = zmax;
}

void SJBox::set_bounds(const SJVec3& min, const SJVec3& max)
{
	m_min_vec = min;
	m_max_vec = max;
}

void SJBox::get_bounds(float& xmin, float& ymin, float& zmin, float& xmax, float& ymax, float& zmax)
{
   xmin = m_min_vec[0];
   ymin = m_min_vec[1];
   zmin = m_min_vec[2];

   xmax = m_max_vec[0];
   ymax = m_max_vec[1];
   zmax = m_max_vec[2];
}

void SJBox::get_bounds(SJVec3& min, SJVec3& max)
{
   min = m_min_vec;
   max = m_max_vec;
}

void SJBox::draw_mod_outline()
{
	float sx = get_min_dimension() / 5.0f;
	float tx = sx * 2.0f;

	float xt, yt, zt;
	float xb, yb, zb;

	m_max_vec.get_value(xt, yt, zt);
	m_min_vec.get_value(xb, yb, zb);

	float xm1 = xb + sx;
	float xm2 = xb + tx;
	float xm3 = xt - tx;
	float xm4 = xt - sx;

	float ym1 = yb + sx;
	float ym2 = yb + tx;
	float ym3 = yt - tx;
	float ym4 = yt - sx;

	float zm1 = zb + sx;
	float zm2 = zb + tx;
	float zm3 = zt - tx;
	float zm4 = zt - sx;

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xm2, yb,  zb);
	::glVertex3d(xm1, yb,  zb);	
	::glVertex3d(xb,  yb,  zm1);
	::glVertex3d(xb,  yb,  zm2);

	::glEnd();
	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xb,  yb,  zm3);
	::glVertex3d(xb,  yb,  zm4);
	::glVertex3d(xm1, yb,   zt);
	::glVertex3d(xm2, yb,   zt);

	::glEnd();
	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xm3, yb,   zt);
	::glVertex3d(xm4, yb,   zt);
	::glVertex3d(xt,  yb,   zm4);
	::glVertex3d(xt,  yb,   zm3);

	::glEnd();
	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xt,  yb,   zm2);
	::glVertex3d(xt,  yb,   zm1);
	::glVertex3d(xm4, yb,   zb);
	::glVertex3d(xm3, yb,   zb);

	::glEnd();

//////////////////////////////////////////////////

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xm2, yt,  zb);
	::glVertex3d(xm1, yt,  zb);	
	::glVertex3d(xb,  yt,  zm1);
	::glVertex3d(xb,  yt,  zm2);

	::glEnd();
	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xb,  yt,  zm3);
	::glVertex3d(xb,  yt,  zm4);
	::glVertex3d(xm1, yt,   zt);
	::glVertex3d(xm2, yt,   zt);

	::glEnd();
	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xm3, yt,   zt);
	::glVertex3d(xm4, yt,   zt);
	::glVertex3d(xt,  yt,   zm4);
	::glVertex3d(xt,  yt,   zm3);

	::glEnd();
	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xt,  yt,   zm2);
	::glVertex3d(xt,  yt,   zm1);
	::glVertex3d(xm4, yt,   zb);
	::glVertex3d(xm3, yt,   zb);

	::glEnd();

//////////////////////////////////////////////////

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xm1,  yb,  zb);
	::glVertex3d(xb,  ym1,  zb);
	::glVertex3d(xb,  ym2,  zb);

	::glEnd();

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xb , ym3,  zb);
	::glVertex3d(xb,  ym4,  zb);
	::glVertex3d(xm1,  yt,  zb);

	::glEnd();

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xm4,  yb,  zb);
	::glVertex3d(xt,  ym1,  zb);
	::glVertex3d(xt,  ym2,  zb);

	::glEnd();

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xt , ym3,  zb);
	::glVertex3d(xt,  ym4,  zb);
	::glVertex3d(xm4,  yt,  zb);

	::glEnd();

//////////////////////////////////////////////////

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xm1,  yb,  zt);
	::glVertex3d(xb,  ym1,  zt);
	::glVertex3d(xb,  ym2,  zt);

	::glEnd();

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xb , ym3,  zt);
	::glVertex3d(xb,  ym4,  zt);
	::glVertex3d(xm1,  yt,  zt);

	::glEnd();

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xm4,  yb,  zt);
	::glVertex3d(xt,  ym1,  zt);
	::glVertex3d(xt,  ym2,  zt);

	::glEnd();

	::glBegin(GL_LINE_STRIP);

	::glVertex3d(xt , ym3,  zt);
	::glVertex3d(xt,  ym4,  zt);
	::glVertex3d(xm4,  yt,  zt);

	::glEnd();

//////////////////////////////////////////////////

	::glBegin(GL_LINES);

	::glVertex3d(xb,  yb,  zm1);
	::glVertex3d(xb, ym1,  zb);

	::glVertex3d(xb,  yb,  zm4);
	::glVertex3d(xb, ym1,  zt);

	::glVertex3d(xb, ym4,  zb);
	::glVertex3d(xb,  yt,  zm1);

	::glVertex3d(xb, ym4,  zt);
	::glVertex3d(xb,  yt,  zm4);

	::glVertex3d(xt,  yb,  zm1);
	::glVertex3d(xt, ym1,  zb);

	::glVertex3d(xt,  yb,  zm4);
	::glVertex3d(xt, ym1,  zt);

	::glVertex3d(xt, ym4,  zb);
	::glVertex3d(xt,  yt,  zm1);

	::glVertex3d(xt, ym4,  zt);
	::glVertex3d(xt,  yt,  zm4);

	::glEnd();
}

void SJBox::draw_outline()
{
	float xt, yt, zt;
	float xb, yb, zb;

	m_max_vec.get_value(xt, yt, zt);
	m_min_vec.get_value(xb, yb, zb);

	float p1[] = { xb, yb, zb };
	float p2[] = { xt, yb, zb };
	float p3[] = { xt, yt, zb };
	float p4[] = { xb, yt, zb };
	float p5[] = { xb, yb, zt };
	float p6[] = { xt, yb, zt };
	float p7[] = { xt, yt, zt };
	float p8[] = { xb, yt, zt };
  
	::glColor3f(1.0f, 1.0f, 1.0f);

	::glBegin(GL_LINES);

	::glVertex3fv(p1);
	::glVertex3fv(p2);

	::glVertex3fv(p2);
	::glVertex3fv(p3);

	::glVertex3fv(p3);
	::glVertex3fv(p4);

	::glVertex3fv(p4);
	::glVertex3fv(p1);

	::glVertex3fv(p1);
	::glVertex3fv(p5);

	::glVertex3fv(p2);
	::glVertex3fv(p6);

	::glVertex3fv(p3);
	::glVertex3fv(p7);

	::glVertex3fv(p4);
	::glVertex3fv(p8);

	::glVertex3fv(p5);
	::glVertex3fv(p6);

	::glVertex3fv(p6);
	::glVertex3fv(p7);

	::glVertex3fv(p7);
	::glVertex3fv(p8);

	::glVertex3fv(p8);
	::glVertex3fv(p5);

	::glEnd();
}
