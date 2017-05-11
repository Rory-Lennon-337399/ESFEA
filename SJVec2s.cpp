#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJVec2s.h"

SJVec2s::SJVec2s()
{
   vector[0] = 0;   
	vector[1] = 0;
}

SJVec2s::SJVec2s(const short v[2])
{
   vector[0] = v[0];
   vector[1] = v[1];
}

SJVec2s::SJVec2s(short x, short y)
{
   vector[0] = x;
   vector[1] = y;
}

long SJVec2s::dot(const SJVec2s &v) const
{
   return ((long)vector[0] * (long)v.vector[0] + (long)vector[1] * (long)v.vector[1]);
}

const short* SJVec2s::get_value() const
{
   return &vector[0];
}

void SJVec2s::get_value(short &x, short &y) const
{
   x = vector[0];       
	y = vector[1];
}

void SJVec2s::negate()
{
   vector[0] = -vector[0];
   vector[1] = -vector[1];
}

SJVec2s& SJVec2s::set_value(const short v[2])
{
   vector[0] = v[0];
   vector[1] = v[1];
   return *this;
}

SJVec2s& SJVec2s::set_value(short x, short y)
{
   vector[0] = x;
   vector[1] = y;
   return *this;
}

short& SJVec2s::operator [](int i)
{
   return vector[i];
}

const short& SJVec2s::operator [](int i) const
{
   return vector[i];
}

SJVec2s& SJVec2s::operator *=(int d)
{
   vector[0] *= d;
   vector[1] *= d;
   return *this;
}

SJVec2s& SJVec2s::operator *=(double d)
{
   vector[0] = (short)(vector[0] * d);
   vector[1] = (short)(vector[1] * d);
   return *this;
}

SJVec2s& SJVec2s::operator /=(int d)
{
   vector[0] /= d;
   vector[1] /= d;
   return *this;
}

SJVec2s& SJVec2s::operator /=(double d)
{
   vector[0] = (short)(vector[0] / d);
   vector[1] = (short)(vector[1] / d);
   return *this;
}

SJVec2s& SJVec2s::operator +=(const SJVec2s &u)
{
   vector[0] += u.vector[0];
   vector[1] += u.vector[1];
   return *this;
}

SJVec2s& SJVec2s::operator -=(const SJVec2s &u)
{
   vector[0] -= u.vector[0];
   vector[1] -= u.vector[1];
   return *this;
}

SJVec2s SJVec2s::operator -() const
{
   return SJVec2s(-vector[0], -vector[1]);
}

short	SJVec2s::get_x()
{
	return vector[0];
}
	
short SJVec2s::get_y()
{
	return vector[1];
}

