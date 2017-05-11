#pragma once

#include "SJVec3.h"

class SJBox
{

public:

	SJBox();
	SJBox(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);
	SJBox(const SJVec3 &min, const SJVec3 &max);
	~SJBox();

	void				draw_outline();
	void				draw_mod_outline();

	const SJVec3  &get_min();
	const SJVec3  &get_max();

	SJVec3			get_center();
	float				get_diagonal();
	float				get_height();
	float				get_width();
	float				get_depth();
	float				get_min_dimension();

	void				extend_by(const SJVec3 & point);
	void				extend_by(const SJBox & box);
	void				slack_by(float fSlack);

	void				set_bounds(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);
	void				set_bounds(const SJVec3 & min, const SJVec3 & max);

	void				get_bounds(float & xmin, float & ymin, float & zmin, float & xmax, float & ymax, float & zmax);
	void				get_bounds(SJVec3 & min, SJVec3 & max);

protected:

	SJVec3			m_min_vec;
	SJVec3			m_max_vec;
};

