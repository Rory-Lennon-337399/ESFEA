
#pragma once

#include "fstream.h"

class SJRotation
{
public:

   SJRotation();
   SJRotation(const float v[4]);
   SJRotation(float q0, float q1, float q2, float q3);
   SJRotation(const SJMat3 &m);
   SJRotation(const SJVec3 &axis, float radians);
   SJRotation(const SJVec3 &rotateFrom, const SJVec3 &rotateTo);

	void get_angle(float &angle);

	void set_angle(float angle);

	void inc_angle(float angle);

   const float* get_value() const;
   void         get_value(float& q0, float& q1, float& q2, float& degrees) const;
   SJRotation&  set_value(float q0, float q1, float q2, float degrees);
   void         get_value(SJVec3 &axis, float &degrees) const;
   void         get_value(SJMat3 &matrix) const;
   SJRotation&  set_value(const float q[4]);
   SJRotation&  set_value(const SJMat3 &m);
   SJRotation&  set_value(const SJVec3 &axis, float degrees);
   SJRotation&  set_value(const SJVec3 &rotateFrom, const SJVec3 &rotateTo);

   SJRotation&          invert();
   SJRotation           inverse() const;
   void                 multVec(const SJVec3 &src, SJVec3 &dst) const;
   void                 scaleAngle(float scaleFactor);
   
   static SJRotation    slerp(const SJRotation &rot0, const SJRotation &rot1, float t);
   static SJRotation    identity();

   float&               operator [](int i);
   const float&         operator [](int i) const;

protected:

   float quaternion[4];
};



