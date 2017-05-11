#pragma once

#include "SJVec3.h"

class SJRotation;
class SJBLine;

typedef float f4x4[4][4];

class SJMat3
{
public:
   
	SJMat3();
   SJMat3(float a11, float a12, float a13, float a14,
          float a21, float a22, float a23, float a24,
          float a31, float a32, float a33, float a34,
          float a41, float a42, float a43, float a44);

   SJMat3(const f4x4 &m);
	SJMat3(SJMat3* p_mat);

   void                 set_value(const f4x4 &m);
   
	void                 set_value(float a11, float a12, float a13, float a14,
										   float a21, float a22, float a23, float a24, 
                                 float a31, float a32, float a33, float a34, 
                                 float a41, float a42, float a43, float a44);

   void                 get_value(f4x4 &m) const;
	const f4x4&          get_value() const;
	void						get_value(SJRotation* rotation);
   void                 identity();
   void                 setScale(float s);
   void                 setScale(const SJVec3 &s);
   void                 setTranslate(const SJVec3 &t);

   void                 setTransform(const SJVec3 &t, 
		                               const SJRotation &r, 
												 const SJVec3 &s);

   void                 setTransform(const SJVec3 &t, 
		                               const SJRotation &r, 
												 const SJVec3 &s, 
												 const SJRotation &so);

   void                 setTransform(const SJVec3 &translation, 
		                               const SJRotation &rotation,
                                     const SJVec3 &scaleFactor, 
												 const SJRotation &scaleOrientation, 
												 const SJVec3 &center);

   void                 getTransform(SJVec3 &t, 
		                               SJRotation &r, 
												 SJVec3 &s, 
												 SJRotation &so) const;

   float                det3(int r1, 
		                       int r2, 
									  int r3, 
									  int c1, 
									  int c2, 
									  int c3) const;

   float                det3() const;
   float                det4() const;

   bool                 factor(SJMat3 &r, 
										 SJVec3 &s, 
										 SJMat3 &u, 
										 SJVec3 &t, 
										 SJMat3 &proj) const;

   SJMat3					inverse() const;
   bool                 LUDecomposition(int index[4], float &d);
   void                 LUBackSubstitution(int index[4], float b[4]) const;
   SJMat3					transpose() const;
   SJMat3&					multRight(const SJMat3 &m);
	SJMat3&					by(const SJMat3 &b);
   SJMat3&					multLeft(const SJMat3 &m);
   void                 multMatrixVec(const SJVec3 &src, SJVec3 &dst) const;
   void                 multVecMatrix(const SJVec3 &src, SJVec3 &dst) const;
   void                 multDirMatrix(const SJVec3 &src, SJVec3 &dst) const;
	void						by(const SJVec3 &src, SJVec3 &dst) const;
   void                 multLineMatrix(SJBLine* src, SJBLine* dst);
   void                 print(FILE *fp) const;
   operator             float*();
   operator             f4x4&();
   float*               operator [](int i);
   const float*         operator [](int i) const;
   SJMat3&					operator =(const SJMat3 &m);
   SJMat3&					operator =(const SJRotation &q);
   void						getAdjoint(SJMat3&) const;

	SJMat3 &operator *= (const SJMat3 &m);

	void operator = (const f4x4 &f);  

protected:

	float matrix[4][4];
};