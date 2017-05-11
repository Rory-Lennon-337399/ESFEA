#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJVec3.h"
#include "SJMat3.h"
#include "SJRotation.h"
#include <math.h>

#define deg2rad (3.14159265358979323846f/180.0f)

SJRotation::SJRotation()
{
   set_value(SJVec3(0.f, 0.f, 1.f), 0.f);
}

SJRotation::SJRotation(const float v[4])
{
   set_value(v);
}

SJRotation::SJRotation(float q0, float q1, float q2, float q3)
{
   set_value(q0, q1, q2, q3);
}

SJRotation::SJRotation(const SJMat3 &m)
{
   set_value(m);
}

SJRotation::SJRotation(const SJVec3 &axis, float degrees)
{
   set_value(axis, degrees);
}

SJRotation::SJRotation(const SJVec3 &rotateFrom, const SJVec3 &rotateTo)
{
   set_value(rotateFrom, rotateTo);
}

SJRotation& SJRotation::set_value(const float q[4])
{
	quaternion[0] = q[0];
	quaternion[1] = q[1];
	quaternion[2] = q[2];
	quaternion[3] = q[3];
   return *this;
}

SJRotation& SJRotation::set_value(float q0, float q1, float q2, float q3)
{
   quaternion[0] = q0;  
	quaternion[1] = q1;     
	quaternion[2] = q2; 
	quaternion[3] = q3;
   return *this;
}

SJRotation& SJRotation::set_value(const SJVec3& axis, float degrees)
{
	quaternion[0] = axis[0];
	quaternion[1] = axis[1];
	quaternion[2] = axis[2];
	quaternion[3] = degrees;
	return *this;
}

const float* SJRotation::get_value() const
{
   return &quaternion[0];
}

void SJRotation::get_value(float &q0, float &q1, float &q2, float &q3) const
{
   q0 = quaternion[0];  
	q1 = quaternion[1];     
	q2 = quaternion[2];     
	q3 = quaternion[3];
}

void SJRotation::get_angle(float &angle)
{
	angle = quaternion[3];	
}

void SJRotation::set_angle(float angle)
{
	quaternion[3] = angle;	
}

void SJRotation::inc_angle(float angle)
{
	quaternion[3] += angle;	
}

void SJRotation::get_value(SJVec3& axis, float& degrees) const
{
   axis[0] = quaternion[0];  
	axis[1] = quaternion[1];     
	axis[2] = quaternion[2]; 
	degrees = quaternion[3];	
}

void SJRotation::get_value(SJMat3 &matrix) const
{
	SJVec3 naxis(quaternion[0], quaternion[1], quaternion[2]);
	naxis.normalize();

	float radians = deg2rad * quaternion[3];

//	float degsTemp = (float)fmod(quaternion[3], 360.0);
//	if(degsTemp < 0.f) degsTemp += 360.0f;
//	float radians = M_PI * degsTemp / 180.0f;

	float sint = sinf(radians);
   float cost = cosf(radians);
   float ux   = naxis[0];
   float ux2  = ux * ux;
   float uy   = naxis[1];
   float uy2  = uy * uy;
   float uz   = naxis[2];
   float uz2  = uz * uz;

	matrix[0][0] = (float)(ux2 + cost * (1 - ux2));
	matrix[0][1] = (float)(ux * uy * (1 - cost) - uz * sint);
	matrix[0][2] = (float)(uz * ux * (1 - cost) + uy * sint);
	matrix[0][3] = 0.f;
	matrix[1][0] = (float)(ux * uy * (1 - cost) + uz * sint);
	matrix[1][1] = (float)(uy2 + cost * (1 - uy2));
	matrix[1][2] = (float)(uy * uz * (1 - cost) - ux * sint);
	matrix[1][3] = 0.f;
	matrix[2][0] = (float)(uz * ux * (1 - cost) - uy * sint);
	matrix[2][1] = (float)(uy * uz * (1 - cost) + ux * sint);
	matrix[2][2] = (float)(uz2 + cost * (1 - uz2));
	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = 1.f;
}

SJRotation& SJRotation::set_value(const SJMat3& m)
{
   float tr, s;
   int i, j, k;
   const int nxt[3] = { 1, 2, 0 };
   
   tr = m[0][0] + m[1][1] + m[2][2];
   
   if ( tr > 0.0 )
      {
         s = sqrtf(tr + 1.0f);
         quaternion[3] = float (s * 0.5f);
         s = 0.5f / s;
         
         quaternion[0] = float ( ( m[1][2] - m[2][1] ) * s );
         quaternion[1] = float ( ( m[2][0] - m[0][2] ) * s );
         quaternion[2] = float ( ( m[0][1] - m[1][0] ) * s );
      }
   else
      {
         i = 0;
         if ( m[1][1] > m[0][0] )
            i = 1;
         
         if ( m[2][2] > m[i][i] )
            i = 2;
         
         j = nxt[i];
         k = nxt[j];
         
         s = sqrtf((m[i][j] - (m[j][j] + m[k][k])) + 1.0f);
         
         quaternion[i] = float (s * 0.5f);
         s = 0.5f / s;
         
         quaternion[3] = float ( ( m[j][k] - m[k][j] ) * s );
         quaternion[j] = float ( ( m[i][j] + m[j][i] ) * s );
         quaternion[k] = float ( ( m[i][k] + m[k][i] ) * s );
      }
   
   return *this;
}

SJRotation& SJRotation::set_value(const SJVec3& rotateFrom, 
                                 const SJVec3& rotateTo)
{
	SJVec3 from(rotateFrom);  
	from.normalize();
	SJVec3 to(rotateTo);      
	to.normalize();
	SJVec3 axis = from.cross(to);

	float radsin  = float(sqrt((1 - from.dot(to)) / 2));
 	quaternion[0] = float(radsin * axis[0]);
 	quaternion[1] = float(radsin * axis[1]);
 	quaternion[2] = float(radsin * axis[2]);
 	quaternion[3] = float(sqrt((1 + from.dot(to)) / 2));
	return *this;
}

SJRotation& SJRotation::invert()
{
   SJVec3 axis;
   float   radians;
   get_value(axis,radians);
   set_value(axis,-radians);
   return *this;
}

SJRotation SJRotation::inverse() const
{
   SJVec3 axis;
   float   radians;
   get_value(axis,radians);
   return SJRotation(axis,-radians);
}

void SJRotation::multVec(const SJVec3& src, SJVec3 & dst) const
{

   SJMat3 mat;
   get_value(mat);
   mat.multVecMatrix(src, dst);
}

void SJRotation::scaleAngle( float scaleFactor )
{
	SJVec3 axis;
	float   radians;

	get_value(axis, radians);
	set_value(axis, radians * scaleFactor);
}

SJRotation SJRotation::slerp( const SJRotation & /*rot0*/, const SJRotation & /*rot1*/, float /*t*/ )
{
   return SJRotation();
}

SJRotation SJRotation::identity()
{
   static SJRotation ident(SJVec3(0.f, 0.f, 1.f), 0.f);
   return ident;
}

float& SJRotation::operator [](int i)
{
   return quaternion[i];
}

const float& SJRotation::operator [](int i) const
{
   return quaternion[i];
}
