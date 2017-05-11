
#pragma once

#include "SJNode.h"
#include "SJVec2s.h"
#include "SJVec3.h"
#include "SJRotation.h"
#include "SJBox.h"

class SJSG;

class SJNodeCam : public SJNode
{
public:

	SJNodeCam();
	virtual ~SJNodeCam();

 	virtual void	fit_mesh();
	virtual void	move_camera_delta(float dx, float dy, float /*dz*/);
	virtual void	scale_object(float dx, float dy, float dz);
	
	SJSG*	mp_sg;	
	
	SJVec3 m_push_back;
	SJVec3 m_object_position;
	SJVec3 m_scale;
 
	SJMat3 m_mat;
	SJVec3 m_center;	           // Center point for scale and rotate
	
	float m_height;
	float m_width;
	float m_left; 
	float m_right;
	float m_top; 
	float m_bottom; 
	float m_near; 
	float m_far;
	float m_aspect_ratio;
	float m_slack;

	void traverse_render(int render_type);
	void traverse_bounds(SJBounds &bounds);
	void traverse_select(CRect& rect);

protected:
};


