#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJVec3.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

SJVec3::SJVec3()
{
   vector[0] = 0.f;     
	vector[1] = 0.f;        
	vector[2] = 0.f;
}

SJVec3::SJVec3(const float v[3])
{
   vector[0] = v[0];
   vector[1] = v[1];
   vector[2] = v[2];
}

SJVec3::SJVec3(float x, float y, float z)
{
   vector[0] = x;
   vector[1] = y;
   vector[2] = z;
}

SJVec3::~SJVec3()
{}

SJVec3 SJVec3::cross(const SJVec3& v) const
{
   return SJVec3((vector[1] * v.vector[2]) - (vector[2] * v.vector[1]),
                  (vector[2] * v.vector[0]) - (vector[0] * v.vector[2]),
                  (vector[0] * v.vector[1]) - (vector[1] * v.vector[0]));
}

float SJVec3::dot(const SJVec3 &v) const
{
   return (vector[0] * v.vector[0] + 
		     vector[1] * v.vector[1] + 
			  vector[2] * v.vector[2]);
}

bool SJVec3::equals(const SJVec3 v, float tolerance) const
{
   return (fabs(vector[0] - v.vector[0]) < fabs(tolerance) && 
			  fabs(vector[1] - v.vector[1]) < fabs(tolerance) && 
			  fabs(vector[2] - v.vector[2]) < fabs(tolerance));
}

const float* SJVec3::get_value() const
{
   return &vector[0];
}

void SJVec3::get_value(float &x, float &y, float &z) const
{
   x = vector[0];
   y = vector[1];
   z = vector[2];
}

float	SJVec3::get_component(int component)
{
	return vector[component];
}

void SJVec3::set_component(int component, float value)
{
	vector[component] = value;
}

float SJVec3::length() const
{
   return float (sqrt(vector[0] * vector[0] + 
						    vector[1] * vector[1] + 
							 vector[2] * vector[2]));
}

float SJVec3::length(const SJVec3 &other_vec) const
{
	float ov_x, ov_y, ov_z;
	float tv_x, tv_y, tv_z;

	float l_x, l_y, l_z;

	other_vec.get_value(ov_x, ov_y, ov_z);
				 get_value(tv_x, tv_y, tv_z);

	l_x = ov_x - tv_x;
	l_y = ov_y - tv_y;
	l_z = ov_z - tv_z;

   return float(sqrt(l_x * l_x + l_y * l_y + l_z * l_z));
}

float SJVec3::angle(const SJVec3 &other_vec) const
{
	return 2.0f * (float)asin(length(other_vec) / 2.0f) * 180.0f / 3.1415926536f;
}

void SJVec3::negate()
{
   vector[0] = -vector[0];
   vector[1] = -vector[1];
   vector[2] = -vector[2];
}

float SJVec3::normalize()
{
   float f = length();
   vector[0] /= f;
   vector[1] /= f;
   vector[2] /= f;
   return f;
}

void SJVec3::check_unity()
{
	if(vector[0] < 0.0f) vector[0] = 0.0f;
	if(vector[1] < 0.0f) vector[1] = 0.0f;
	if(vector[2] < 0.0f) vector[2] = 0.0f;

	if(vector[0] > 1.0f) vector[0] = 1.0f;
	if(vector[1] > 1.0f) vector[1] = 1.0f;
	if(vector[2] > 1.0f) vector[2] = 1.0f;
}

SJVec3& SJVec3::set_value(const SJVec3 &bvec)
{
	set_value(bvec.get_value());

   return *this;
}

SJVec3& SJVec3::set_value(const float v[3])
{
   vector[0] = v[0];
   vector[1] = v[1];
   vector[2] = v[2];
   return *this;
}

SJVec3& SJVec3::set_value(float x, float y, float z)
{
   vector[0] = x;
   vector[1] = y;
   vector[2] = z;
   return *this;
}

float& SJVec3::operator [](int i)
{
   return vector[i];
}

const float& SJVec3::operator [](int i) const
{
   return vector[i];
}

SJVec3& SJVec3::operator =(const SJVec3& vec3f)
{
	set_value(vec3f.get_value());

   return *this;
}

SJVec3& SJVec3::operator *=(float d)
{
   vector[0] *= d;
   vector[1] *= d;
   vector[2] *= d;
   return *this;
}

SJVec3& SJVec3::operator /=(float d)
{
   vector[0] /= d;
   vector[1] /= d;
   vector[2] /= d;
   return *this;
}

SJVec3& SJVec3::operator +=(const SJVec3 &u)
{
   vector[0] += u.vector[0];
   vector[1] += u.vector[1];
   vector[2] += u.vector[2];
   return *this;
}

SJVec3& SJVec3::operator -=(const SJVec3 &u)
{
   vector[0] -= u.vector[0];
   vector[1] -= u.vector[1];
   vector[2] -= u.vector[2];
   return *this;
}

SJVec3 SJVec3::operator -() const
{
   return SJVec3(-vector[0], -vector[1], -vector[2]);
}

void SJVec3::print_coords(ofstream* open_file)
{
	char dqs = '"';

	*open_file << " XF=" << dqs;
	print_float_only(open_file, get_component(0));	
	*open_file << dqs;	
	
	*open_file << " YF=" << dqs;
	print_float_only(open_file, get_component(1));	
	*open_file << dqs;	

	*open_file << " ZF=" << dqs;
	print_float_only(open_file, get_component(2));	
	*open_file << dqs;	
}

void SJVec3::print_float_only(ofstream* open_file, float value)
{
	char szBuffer[15];
	::sprintf(szBuffer, "%15.5f", value);

	for(int i = 0; i < 15; i++)
	{
		if(szBuffer[i] != ' ') *open_file << szBuffer[i];
	}
}

void SJVec3::trace_val()
{
	float x, y, z;
	x = get_component(0);
	y = get_component(1);
	z = get_component(2);
//	TRACE("vec3 %10.5f %10.5f %10.5f\n", x, y, z);
}