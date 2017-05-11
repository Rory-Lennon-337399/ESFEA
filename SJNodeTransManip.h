
#pragma once

#include "SJNode.h"
#include "SJRotation.h"
#include "SJVec2s.h"
#include "SJMat3.h"

class SJNodeTransManip : public SJNode
{
public:

	SJNodeTransManip();
	void change_manip_type(int type);
	void change_rotation_type(int type);
	void inc_x_rotation(float inc);
	void inc_y_rotation(float inc);
	void inc_x_and_y_rotation(float x, float y);
	virtual void traverse_render(int render_type);
	virtual void traverse_bounds(SJBounds &bounds);

	void do_gl_rotations();
	int m_rotation_type;
	int m_view_type;
	SJRotation rotationX;	        
	SJRotation rotationY;	  
	SJMat3 m_mat;
	SJVec3 m_scale;					// Scale factors
	SJVec3 m_center;	           // Center point for scale and rotate

	enum 
	{
		PERSPECTIVE,
		ORTHO,
		X_Z_PLANE,   // Front
		X_Y_PLANE,	 // Top
	};

	enum 
	{
		TRACKBALL,
		BI_AXIAL
	};





protected:

	void	inc_with_trackball(float x, float y);
	virtual ~SJNodeTransManip();


//	virtual void traverse_render(SJTraverseRender* render_traversal);
//	virtual void traverse_matrix(SJTraverseMatrix* matrix_traversal);
//	virtual void traverse_select(SJTraverseSelect* select_traversal);
};
