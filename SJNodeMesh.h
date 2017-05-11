#pragma once

#include "SJNode.h"
#include "SJPoint.h"
#include "SJBlock.h"
#include "SJMatrix.h"
#include "SJVector.h"

class SJNodeMesh : public SJNode
{
public:
						SJNodeMesh();
	virtual			~SJNodeMesh();
	virtual void	traverse_render(int render_type);
	virtual void	traverse_bounds(SJBounds &bounds);
	virtual void	traverse_write(ofstream* p_file);
	void				add_point(int select, float x, float y);
	void				add_point(int num, int select, int fix, float x, float y, float px, float py, float lump);
	void				add_block(int point_nums[4]);
	void				add_block(SJPL_POINTS& pl_points);
	int				slot_dofs();
	void				arrange_stiffness();
	void				arrange_mass();
	void				arrange_general();
	void 				arrange_load();
	void				extract_modes();
	void				strut(SJLine* p_line);
	float				sq(float in);
	float				sr3(float in1, float in2, float in3 = 0.0f);
	float				sr2(float in1, float in2);
	void				new_file();
	void				select_point(SJPoint* p_point);
	void				select_all();
	void				copy_nodes(float dx, float dy);
	void				unselect_nodes();
	void				fix();
	void				force(float x, float y);
	void				mass(float lump);
	void				material(float ae);
	void				add_mode_frame(SJVector& mode, float theta);
	void				clear_animate_vecs();
	void				reset_animate();
	float				create_mode_animation(int &modenum);
	BOOL 				next_frame();
	void				run_rk4();
	void				rk4(float* y, int mode);
	void				derivs(float y[], float dydx[], int mode);
	float				get_p(float tau, int mode);
	float				get_frq(int modenum);
	float				get_dp(float tau, int mode);
	void				add_dynamic_frame(SJVector &disps);
	void				get_maxvs();
	void				run_duhamel();
	float				int1(float tau, float wd, float dwsq, float x1wd);
	float				int2(float tau, float wd, float dwsq, float x1wd);
	float				int3(float tau, float wd, float dwsq, float x1wd, float int1f, float int2f);
	float				int4(float tau, float wd, float dwsq, float x1wd, float int1f, float int2f);

	SJBounds			m_local;
	SJMatrix			m_stiff;
	SJMatrix			m_modes;
	SJVector			m_vals;
	SJVector 		m_mass;
	SJVector 		m_gmass;
	SJVector 		m_load;
	SJVector 		m_gload;
	int				m_numdofs;
	int				m_calcstage;
	int				m_int;
	float				m_time;
	float				m_dt;
	float				m_ct;
	float				m_ft;
	float				m_damp;
	float				m_frac;
	float				m_aa;
	float				m_ee;
	float				m_maxp;
	float				m_maxm;

	SJPL_POINTS		ml_points;
	SJPL_BLOCKS		ml_blocks;
};


