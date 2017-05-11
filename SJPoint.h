#pragma once

#include "SJVec3.h"

class SJPoint : public SJVec3
{
// Constructor/destructor
public:


							SJPoint(int num, float x, float y, float z, float mass);
							~SJPoint();
	virtual void		traverse_write(ofstream* p_file);
	virtual void		traverse_render(float force, float mass);
	virtual void		init();
	virtual void		adjust_point_size(bool resize_method, float scale, float new_size);
	virtual void		draw_point(SJVec3* p_vec, float force, float mass);
	virtual void		draw_load(float force);
	virtual void		clear_animate();
	void					add_animate(SJVec3& disp);
   const float*		get_animate() const;
	virtual void		reset_animate();
	int					slot_dofs();
	float					sq(float in);
	float					sr(float in);
	float					sr3(float in1, float in2, float in3 = 0.0f);
	void					write_float(ofstream* p_file, float val);
	BOOL 					next_frame();
	void 					fix(int i);
	int 					get_fix();

	int					m_num;
	float					m_point_size;
	int					m_dof[3];
	SJVec3				m_load;
	int					m_selection;
	float					m_lump;

protected:

							SJPoint();
							SJPoint(const float v[3]);

	int					m_fix;
	POS					m_pos;
	virtual	void		set_colors(float m);
	SJPL_VEC3			m_animate_vecs;
};

typedef SJPointers<SJPoint*> SJPL_POINTS;