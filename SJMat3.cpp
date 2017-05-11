#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJMat3.h"
#include "SJRotation.h"
#include "math.h"

#define deg2rad (3.14159265358979323846f / 180.0f)

SJMat3::SJMat3()
{
   identity();
}

SJMat3::SJMat3(float a11, float a12, float a13, float a14,
                     float a21, float a22, float a23, float a24,
                     float a31, float a32, float a33, float a34,
                     float a41, float a42, float a43, float a44)
{
   matrix[0][0] = a11;  
	matrix[0][1] = a12;     
	matrix[0][2] = a13;     
	matrix[0][3] = a14;

   matrix[1][0] = a21;  
	matrix[1][1] = a22;     
	matrix[1][2] = a23;     
	matrix[1][3] = a24;

   matrix[2][0] = a31;  
	matrix[2][1] = a32;     
	matrix[2][2] = a33;     
	matrix[2][3] = a34;

   matrix[3][0] = a41;  
	matrix[3][1] = a42;     
	matrix[3][2] = a43;     
	matrix[3][3] = a44;
}

SJMat3::SJMat3(const f4x4 &m)
{
	set_value(m);
}

SJMat3::SJMat3(SJMat3* p_mat)
{
	set_value(p_mat->get_value());
}

void SJMat3::set_value(const f4x4 &m)
{
	int i, j;

	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) 
	{ 
		matrix[i][j] = m[i][j];
	}
}

void SJMat3::set_value(float a11, float a12, float a13, float a14,
								  float a21, float a22, float a23, float a24, 
								  float a31, float a32, float a33, float a34, 
                          float a41, float a42, float a43, float a44)
{
   matrix[0][0] = a11; 
	matrix[0][1] = a12; 
	matrix[0][2] = a13; 
	matrix[0][3] = a14;

   matrix[1][0] = a21; 
	matrix[1][1] = a22; 
	matrix[1][2] = a23; 
	matrix[1][3] = a24;

   matrix[2][0] = a31; 
	matrix[2][1] = a32; 
	matrix[2][2] = a33; 
	matrix[2][3] = a34;

   matrix[3][0] = a41; 
	matrix[3][1] = a42; 
	matrix[3][2] = a43; 
	matrix[3][3] = a44;
}

void SJMat3::get_value(SJRotation* rotation) 
{
	float x, y, z, t;
	rotation->get_value(x, y, z, t);

	SJVec3 naxis(x, y, z);
	naxis.normalize();

	float radians = deg2rad * t;

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

void SJMat3::get_value(f4x4 &m) const
{      
	int i, j;

	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) 
	{ 
		m[i][j] = matrix[i][j];
	}
}

const f4x4& SJMat3::get_value() const
{
   return matrix;
}

void SJMat3::identity()
{
	int i, j;

	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) 
	{ 
		matrix[i][j] = 0.0f;
	}
	for (i = 0; i < 4; i++)
	{
		matrix[i][i] = 1.0f;
	}
}

void SJMat3::setScale(float s)
{
   matrix[0][0] = s;    
	matrix[1][1] = s;       
	matrix[2][2] = s;
}

void SJMat3::setScale(const SJVec3 &s)
{
   matrix[0][0] = s[0]; 
	matrix[1][1] = s[1];    
	matrix[2][2] = s[2];
}

void SJMat3::setTranslate(const SJVec3 &t)
{
	identity();

   matrix[0][3] = t[0]; 
	matrix[1][3] = t[1];    
	matrix[2][3] = t[2];
}

void SJMat3::setTransform(const SJVec3&    t, 
                            const SJRotation& r, 
                            const SJVec3&    s)
{
   identity();
   setTranslate(t);
   
   SJMat3 rmat;
   r.get_value(rmat);
   multRight(rmat);
   
   SJMat3 smat;
   smat.setScale(s);
   multRight(smat);
}

void SJMat3::setTransform(const SJVec3&    t, 
                            const SJRotation& r, 
                            const SJVec3&    s, 
                            const SJRotation& so)
{
   identity();
   setTranslate(t);
   
   SJMat3 rmat;
   r.get_value(rmat);
   multRight(rmat);
   
   SJMat3 somat;
   so.get_value(somat);
   multRight(somat);
   
   SJMat3 smat;
   smat.setScale(s);
   multRight(smat);
   
   multRight(somat.inverse());
}

void SJMat3::setTransform(const SJVec3&    t, 
                            const SJRotation& r, 
                            const SJVec3&    s,
                            const SJRotation& so, 
                            const SJVec3&    c)
{
   identity();
   setTranslate(t);
   
   SJMat3 cmat;
   cmat.setTranslate(c);
   multRight(cmat);
   
   SJMat3 rmat;
   r.get_value(rmat);
   multRight(rmat);
   
   SJMat3 somat;
   so.get_value(somat);
   multRight(somat);
   
   SJMat3 smat;
   smat.setScale(s);
   multRight(smat);
   
   multRight(somat.inverse());
   multRight(cmat.inverse());
}

void SJMat3::getTransform(SJVec3 & /*t*/, SJRotation & /*r*/, SJVec3 & /*s*/, SJRotation & /*so*/) const
{}

inline float det2(float a, float b, float c, float d)
{
   return a * d - b * c;
}

float SJMat3::det3(int r1, int r2, int r3, int c1, int c2, int c3) const
{
   return
		
	matrix[r1][c1] * det2(matrix[r2][c2],
	matrix[r3][c2],
	matrix[r2][c3],
	matrix[r3][c3])

 - matrix[r1][c2] * det2(matrix[r2][c1],
	matrix[r3][c1],
	matrix[r2][c3],
	matrix[r3][c3])

 + matrix[r1][c3] * det2(matrix[r2][c1],
   matrix[r3][c1],
	matrix[r2][c2],
	matrix[r3][c2]);
}

float SJMat3::det3() const
{
   return det3(0, 1, 2, 0, 1, 2);
}

float SJMat3::det4() const
{
   return 
		
		  matrix[0][0] * det3(1, 2, 3, 1, 2, 3)
      - matrix[0][1] * det3(1, 2, 3, 0, 2, 3)
      + matrix[0][2] * det3(1, 2, 3, 0, 1, 3)
      - matrix[0][3] * det3(1, 2, 3, 0, 1, 2);
}

bool SJMat3::factor(SJMat3 & /*r*/, 
							 SJVec3  & /*s*/, 
							 SJMat3 & /*u*/, 
							 SJVec3  & /*t*/, 
							 SJMat3 & /*proj*/) const
{
   return true;
}

void SJMat3::getAdjoint(SJMat3& out) const
{
   out.matrix[0][0]  =   det3(1, 2, 3, 1, 2, 3);
   out.matrix[1][0]  = - det3(1, 2, 3, 0, 2, 3);
   out.matrix[2][0]  =   det3(1, 2, 3, 0, 1, 3);
   out.matrix[3][0]  = - det3(1, 2, 3, 0, 1, 2);
                                 
   out.matrix[0][1]  = - det3(0, 2, 3, 1, 2, 3);
   out.matrix[1][1]  =   det3(0, 2, 3, 0, 2, 3);
   out.matrix[2][1]  = - det3(0, 2, 3, 0, 1, 3);
   out.matrix[3][1]  =   det3(0, 2, 3, 0, 1, 2);
                                 
   out.matrix[0][2]  =   det3(0, 1, 3, 1, 2, 3);
   out.matrix[1][2]  = - det3(0, 1, 3, 0, 2, 3);
   out.matrix[2][2]  =   det3(0, 1, 3, 0, 1, 3);
   out.matrix[3][2]  = - det3(0, 1, 3, 0, 1, 2);
                                 
   out.matrix[0][3]  = - det3(0, 1, 2, 1, 2, 3);
   out.matrix[1][3]  =   det3(0, 1, 2, 0, 2, 3);
   out.matrix[2][3]  = - det3(0, 1, 2, 0, 1, 3);
   out.matrix[3][3]  =   det3(0, 1, 2, 0, 1, 2);
}

SJMat3 SJMat3::inverse() const
{
   // Calculate the adjoint matrix
   SJMat3 out;
   getAdjoint(out);
   
   // Scale the adjoint matrix with the determinant 
   // to get the inverse
   float det = det4();
   
	if (det > 0.0f) 
	{
      for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) 
		{	
			out.matrix[i][j] /= det;
		}
   }
   else {
      // Simgular matrix
      out.identity();
   }
   return out;
}

bool SJMat3::LUDecomposition( int /*index*/[4], float & /*d*/ )
{
   return true;
}

void SJMat3::LUBackSubstitution( int /*index*/[4], float /*b*/[4] ) const
{}

SJMat3 SJMat3::transpose() const
{
   return *this;
}

SJMat3& SJMat3::by(const SJMat3 &b)
{
	int i, j, k;

   SJMat3 mt;

	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) 
	{ 
		mt[i][j] = 0.0f;
			
		for (k = 0; k < 4; k++) mt.matrix[i][j] += matrix[i][k] * b.matrix[k][j];  	                                            
   }
   return operator =(mt);
}

SJMat3& SJMat3::multRight(const SJMat3 &b)
{
	int i, j, k;

   SJMat3 mt;

	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) 
	{ 
		mt[i][j] = 0.0f;
			
		for (k = 0; k < 4; k++) mt.matrix[i][j] += matrix[i][k] * b.matrix[k][j];  	                                            
   }
   return operator =(mt);
}

SJMat3& SJMat3::multLeft( const SJMat3& /*b*/ )
{
   SJMat3 mt;

   return operator =(mt);
}

void SJMat3::multMatrixVec(const SJVec3 & src, SJVec3& dst) const
{
   float w =	  src[0] * matrix[3][0] + 
					  src[1] * matrix[3][1] + 
					  src[2] * matrix[3][2] + 
								  matrix[3][3];

   dst.set_value((src[0] * matrix[0][0] +
		           src[1] * matrix[0][1] + 
					  src[2] * matrix[0][2] +
								  matrix[0][3]) / w,

                (src[0] * matrix[1][0] +
					  src[1] * matrix[1][1] +
					  src[2] * matrix[1][2] +
								  matrix[1][3]) / w,

                (src[0] * matrix[2][0] +
					  src[1] * matrix[2][1] +
					  src[2] * matrix[2][2] +
								  matrix[2][3]) / w);
}

void SJMat3::multVecMatrix(const SJVec3 &src, SJVec3 &dst) const
{
   float w = src[0] * matrix[0][3] +
		       src[1] * matrix[1][3] + 
				 src[2] * matrix[2][3] + 
				 1.0f   * matrix[3][3];

   dst[0] = (src[0] * matrix[0][0] + 
		       src[1] * matrix[1][0] + 
				 src[2] * matrix[2][0] + 
				 1.0f   * matrix[3][0]) / w;

   dst[1] = (src[0] * matrix[0][1] + 
		       src[1] * matrix[1][1] + 
				 src[2] * matrix[2][1] + 
				 1.0f   * matrix[3][1]) / w;

   dst[2] = (src[0] * matrix[0][2] + 
		       src[1] * matrix[1][2] + 
				 src[2] * matrix[2][2] + 
				 1.0f   * matrix[3][2]) / w;
}

void SJMat3::by(const SJVec3 &src, SJVec3 &dst) const
{
    float x = matrix[0][0] * src[0] + matrix[0][1] * src[1] + matrix[0][2] * src[2] + matrix[0][3];
    float y = matrix[1][0] * src[0] + matrix[1][1] * src[1] + matrix[1][2] * src[2] + matrix[1][3];
    float z = matrix[2][0] * src[0] + matrix[2][1] * src[1] + matrix[2][2] * src[2] + matrix[2][3];
    float w = matrix[3][0] * src[0] + matrix[3][1] * src[1] + matrix[3][2] * src[2] + matrix[3][3];

    if(w != 0.f) 
	 {
        dst[0] = x / w;
        dst[1] = y / w;
        dst[2] = z / w;
    }
}

void SJMat3::multDirMatrix(const SJVec3& src, SJVec3& dst) const
{
   float w = src[0] * matrix[0][3] + 
		       src[1] * matrix[1][3] + 
				 src[2] * matrix[2][3] + 
				 matrix[3][3];

   dst[0] = (src[0] * matrix[0][0] + 
		       src[1] * matrix[1][0] + 
				 src[2] * matrix[2][0]) / w;

   dst[1] = (src[0] * matrix[0][1] + 
		       src[1] * matrix[1][1] + 
				 src[2] * matrix[2][1]) / w;

   dst[2] = (src[0] * matrix[0][2] + 
		       src[1] * matrix[1][2] + 
				 src[2] * matrix[2][2]) / w;
}

/*
void SJMat3::multLineMatrix(SJBLine* src, SJBLine* dst)
{
   multVecMatrix(src->pos, dst->pos);
   multDirMatrix(src->dir, dst->dir);
}
*/

SJMat3::operator float*()
{
   return &matrix[0][0];
}

SJMat3::operator f4x4&()
{
   return matrix;
}

float* SJMat3::operator [](int i)
{
   return &matrix[i][0];
}

const float* SJMat3::operator [](int i) const
{
   return &matrix[i][0];
}

SJMat3& SJMat3::operator =(const SJMat3 &m)
{
   set_value(m.matrix);
   return *this;
}

void SJMat3::operator =(const f4x4& m)
{
	int i, j;

	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) 
	{ 
		matrix[i][j] = m[i][j];
	}
}

SJMat3& SJMat3::operator *=(const SJMat3 &m)
{
	int i, j, k;

   SJMat3 mt;

	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) 
	{ 
		mt[i][j] = 0.0f;
			
		for (k = 0; k < 4; k++) mt.matrix[i][j] += matrix[i][k] * m.matrix[k][j];  	                                            
   }
   return operator =(mt);
}

void SJMat3::print(FILE* /*fp*/) const
{
//	TRACE("%f %f %f %f\n", matrix[0][0],matrix[0][1],matrix[0][2],matrix[0][3]);
//	TRACE("%f %f %f %f\n", matrix[1][0],matrix[1][1],matrix[1][2],matrix[1][3]);
//	TRACE("%f %f %f %f\n", matrix[2][0],matrix[2][1],matrix[2][2],matrix[2][3]);
//	TRACE("%f %f %f %f\n", matrix[3][0],matrix[3][1],matrix[3][2],matrix[3][3]);
}
