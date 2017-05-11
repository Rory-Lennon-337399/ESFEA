
#pragma once

#include "SJPointers.h"
#include "fstream.h"

class SJVec3
{
public:
							SJVec3();
							SJVec3(const float v[3]);
							SJVec3(float x, float y, float z);
							~SJVec3();

	void					print_coords(ofstream* open_file);
	void					print_float_only(ofstream* open_file, float value);
   SJVec3				cross(const SJVec3 &v) const;
   float					dot(const SJVec3 &v) const;
   bool					equals(const SJVec3 v, float tolerance) const;
   
   const float*		get_value() const;
   void              get_value(float &x, float &y, float &z) const;
	float					get_component(int component);
	void					set_component(int component, float value);

   float					length() const;
	float					length(const SJVec3 &bvec) const;
   void              negate();
   float					normalize();
 
	float					angle(const SJVec3 &bvec) const;
	void					check_unity();
	void					trace_val();

	SJVec3&				set_value(const SJVec3 &bvec);
   SJVec3&				set_value(const float v[3]);
   SJVec3&				set_value(float x, float y, float z);
   SJVec3&				set_value(const SJVec3 &barycentic, const SJVec3 &v0, const SJVec3 &v1, const SJVec3 &v2);
   
   float&				operator [](int i);
   const float&		operator [](int i) const;

	SJVec3&				operator =(const SJVec3& vec3f);
   SJVec3&				operator *=(float d);
   SJVec3&				operator /=(float d);
   SJVec3&				operator +=(const SJVec3 &u);
   SJVec3&				operator -=(const SJVec3 &u);
   SJVec3				operator -() const;
   
protected:

   float				vector[3];
};

typedef SJPointers<SJVec3*> SJPL_VEC3;

