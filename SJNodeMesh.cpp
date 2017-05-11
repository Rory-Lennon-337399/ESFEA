#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJNodeMesh.h"
#include "SJPoint.h"
#include "math.h"

SJNodeMesh::SJNodeMesh() 
{
	m_numdofs = 0;
	m_calcstage = 0;
	m_damp = 0.1f;
	m_time = 5.0f;
	m_dt = 0.005f;
	m_ct = 0.0f;
	m_frac = 0.5f;
	m_ft = 2.0f;
	m_maxp = 0.0;
	m_maxm = 0.0;
	m_aa = 0.0f;
	m_ee = 0.0f;
}

SJNodeMesh::~SJNodeMesh()
{
	ml_points.delete_data();
	ml_blocks.delete_data();
}

void SJNodeMesh::traverse_render(int render_type)
{
	POS pos;

	GLfloat vec2[] = { 0.5f, 0.5f, 0.5f, 0.0f };
	::glMaterialfv(GL_FRONT, GL_DIFFUSE, vec2);
	::glMaterialfv(GL_FRONT, GL_AMBIENT, vec2);

//	::glColor3d(1.0, 1.0, 1.0);
//	::glLineWidth(1.0f);

	if(render_type != ANIMATE)
	{
		pos = ml_points.get_head_pos();
		while(pos) ml_points.get_next(pos)->traverse_render(m_maxp, m_maxm);
	}
	::glDisable(GL_LIGHTING);	
//	::glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	::glEnable(GL_LINE_SMOOTH);

	pos = ml_blocks.get_head_pos();
	while(pos) ml_blocks.get_next(pos)->traverse_render(render_type);

//	TRACE("SJNodeMesh::traverse_render force %8.4f mass %8.4f\n", m_maxp, m_maxm);	
}

void SJNodeMesh::select_all()
{
	SJPoint* p_next;
	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_next = ml_points.get_next(pos);
//		if(p_next->get_fix() == 0) p_next->m_selection = 1;
		p_next->m_selection = 1;
	}
}

void SJNodeMesh::select_point(SJPoint* p_point)
{
	SJPoint* p_next;

	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_next = ml_points.get_next(pos);
		if(p_next == p_point) p_next->m_selection = 1;
	}
}

void SJNodeMesh::traverse_write(ofstream* p_file)
{
	*p_file << "<?xml version=" << dqs << "1.0" << dqs << "?>" << endl;

	*p_file << "<PARAMETERS";

	*p_file << " DAMP=";
	*p_file << dqs << m_damp << dqs;

	*p_file << " FRAC=";
	*p_file << dqs << m_frac << dqs;

	*p_file << " INT=";
	*p_file << dqs << m_int << dqs;

	*p_file << " AA=";
	*p_file << dqs << m_aa << dqs;

	*p_file << " EE=";
	*p_file << dqs << m_ee << dqs;

	*p_file << " TIME=";
	*p_file << dqs << m_time << dqs;

	*p_file << " DT=";
	*p_file << dqs << m_dt << dqs;
	
	*p_file << " FT=";
	*p_file << dqs << m_ft << dqs;

	*p_file << " />" << endl;

	*p_file << "<MESH>" << endl;

	POS pos = ml_points.get_head_pos();
	while(pos) ml_points.get_next(pos)->traverse_write(p_file);

	pos = ml_blocks.get_head_pos();
	while(pos) ml_blocks.get_next(pos)->traverse_write(p_file);

	*p_file << "</MESH>" << endl;
}

void SJNodeMesh::new_file()
{
	m_numdofs = 0;
	ml_points.delete_data();
	ml_blocks.delete_data();
}

void SJNodeMesh::add_point(int select, float x, float y)
{
	int num = ml_points.get_count() + 1;
	add_point(num, select, FALSE, x, y, 0.0, 0.0, 1.0);
}

void SJNodeMesh::add_point(int num, int select, int fix, float x, float y, float px, float py, float lump)
{
	SJPoint* p_point = new SJPoint(num, x, y, 0.0f, lump);
	p_point->m_load.set_value(px, py, 0.0f);
	p_point->m_selection = select;
	p_point->fix(fix);
	ml_points.set_at(num -1, p_point);
}

void SJNodeMesh::traverse_bounds(SJBounds &bounds)
{
	SJVec3 global;
	SJVec3 current_point;

	m_local.m_first_pass = TRUE;

	SJPoint* p_point;
	POS pos = ml_points.get_head_pos();
	while(pos)
	{
		p_point = ml_points.get_next(pos);
		current_point.set_value(p_point->get_value());
		bounds.m_mat3.by(current_point, global);
		bounds.stretch(global);
		m_local.stretch(current_point);
	}
}

void SJNodeMesh::add_block(SJPL_POINTS& pl_points)
{
	SJBlock* p_block = new SJBlock(&pl_points, m_aa * m_ee);	
	ml_blocks.add_tail(p_block);
}

void SJNodeMesh::add_block(int point_nums[4])
{
	SJPL_POINTS pl_points;
	for (int i = 0; i < 4; i++) pl_points.add_tail(ml_points.get_at(point_nums[i] - 1));
	SJBlock* p_block = new SJBlock(&pl_points, m_aa * m_ee);	
	ml_blocks.add_tail(p_block);
}

void SJNodeMesh::copy_nodes(float dx, float dy)
{
	SJPoint* p_next;
	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_next = ml_points.get_next(pos);
		if(p_next->m_selection == 1) 
		{
			p_next->m_selection = 0;
			add_point(2, p_next->get_component(0) + dx, p_next->get_component(1) + dy);
		}
	}
	pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_next = ml_points.get_next(pos);
		if(p_next->m_selection == 2) p_next->m_selection = 1;
	}
}

void SJNodeMesh::unselect_nodes()
{
	POS pos = ml_points.get_head_pos();
	while(pos) ml_points.get_next(pos)->m_selection = 0;
}

void SJNodeMesh::fix()
{
	SJPoint* p_next;
	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_next = ml_points.get_next(pos);
		if(p_next->m_selection == 1)
		{
			p_next->m_selection = 0;
			p_next->fix(1);
		}
	}
}

void SJNodeMesh::get_maxvs()
{
	float forcex = 0.0f;
	float forcey = 0.0f;
	float mass = 0.0f;
	m_maxp = 0.0f;
	m_maxm = 0.0f;
	SJPoint* p_next;
	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_next = ml_points.get_next(pos);
		forcex = p_next->m_load.get_component(0);
		forcey = p_next->m_load.get_component(1);

//		TRACE("SJNodeMesh::get_maxvs forcex %8.4f forcey %8.4f\n", forcex, forcey);

		mass = p_next->m_lump;
		if((float)fabs((double)forcex) > m_maxp) m_maxp = (float)fabs((double)forcex);
		if((float)fabs((double)forcey) > m_maxp) m_maxp = (float)fabs((double)forcey);
		if(mass > m_maxm) m_maxm = mass;
	}
	m_maxp = m_local.m_box.get_diagonal() * 0.1f / m_maxp;

//	TRACE("SJNodeMesh::get_maxvs m_maxp %8.4f m_maxm %8.4f\n", m_maxp, m_maxm);	
}

void SJNodeMesh::force(float x, float y)
{
	SJPoint* p_next;
	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_next = ml_points.get_next(pos);
		if(p_next->m_selection == 1)
		{
			p_next->fix(0);
			p_next->m_load.set_value(x, y, 0.0f);
		}
	}
	get_maxvs();
}

void SJNodeMesh::mass(float lump)
{
	SJPoint* p_next;
	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_next = ml_points.get_next(pos);

		if(p_next->m_selection == 1)
		{
//			TRACE("SJNodeMesh::mass %10.5f\n", lump);

//			p_next->fix(0);
			p_next->m_lump = lump;
		}
	}
	get_maxvs();
	m_calcstage = 0;
}

void SJNodeMesh::material(float ae)
{
	SJBlock* p_block;
	SJLine* p_line;

	POS pos = ml_blocks.get_head_pos();
	while(pos)
	{
		p_block = ml_blocks.get_next(pos);

		POS pos2 = p_block->ml_lines.get_head_pos();
		while(pos2)
		{
			p_line = p_block->ml_lines.get_next(pos2);
			p_line->m_ae = ae;
		}
	}
	m_calcstage = 0;
}

int SJNodeMesh::slot_dofs()
{
	int dof_slot = 0;
	SJPoint* p_point;

	POS pos = ml_points.get_head_pos();
	while(pos)
	{
		p_point = ml_points.get_next(pos);

		if(!p_point->get_fix())
		{
			p_point->m_dof[0] = ++dof_slot;
			p_point->m_dof[1] = ++dof_slot;
		}
		else
		{
			p_point->m_dof[0] = 0;
			p_point->m_dof[1] = 0;
		}
	}
	if(dof_slot < 1) dof_slot = 1;
	return dof_slot;
}

void SJNodeMesh::arrange_stiffness()
{
	if(m_calcstage >= STIFFNESS) return;

	TRACE("ARRANGE STIFFNESS\n");

	m_numdofs = slot_dofs();
	m_stiff.size(m_numdofs);

	SJBlock* p_block;
	SJLine* p_line;

	POS pos = ml_blocks.get_head_pos();
	while(pos)
	{
		p_block = ml_blocks.get_next(pos);

		POS pos2 = p_block->ml_lines.get_head_pos();
		while(pos2)
		{
			p_line = p_block->ml_lines.get_next(pos2);
			strut(p_line);
		}
	}
	m_stiff.set_maxval();
	arrange_mass();

	m_calcstage = STIFFNESS;
}

void SJNodeMesh::arrange_mass()
{
	TRACE("ARRANGE MASS\n");

	m_mass.size(m_numdofs);

	int dof = 0;
	SJPoint* p_point;
	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_point = ml_points.get_next(pos);
		if(p_point->get_fix() <= 0)
		{
			m_mass.el(p_point->m_dof[0]) = p_point->m_lump;
			m_mass.el(p_point->m_dof[1]) = p_point->m_lump;
		}
	}
	SJVector mi(m_mass);
//	mi.trace_vector();
	mi.sqrt();
	mi.invert();
//	mi.trace_vector();

	m_stiff.by_vt(m_mass);
	m_stiff.v_by(m_mass);
}

float SJNodeMesh::create_mode_animation(int &modenum)
{
	TRACE("CREATE MODE ANIMATION\n");

	extract_modes();

	if(modenum < 1) modenum = 1;
	if(modenum > m_numdofs) modenum = m_numdofs;

	float w = get_frq(modenum) * (2.0f * PI);

	clear_animate_vecs();
	SJVector mode(m_modes, modenum);
	if(m_modes.m_fmx != 0.0f) mode.scale(1.0f / m_modes.m_fmx); 

	float lim = 10.0f;
	float step = 0.05f;
	float theta = 0.0f;
	for(float time = 0; time <= lim; time += step)
	{
		add_mode_frame(mode, sinf(w * time));
	}
	return get_frq(modenum);
}

void SJNodeMesh::add_mode_frame(SJVector& mode, float theta)
{
	int disp = 0;
	float dx, dy;
	SJVec3 vec;

	float size = m_local.m_box.get_diagonal() / 10.0f;

	POS pos_p = ml_points.get_head_pos();
	while(pos_p)
	{
		SJPoint* p_point = ml_points.get_next(pos_p);

		if(p_point->get_fix() < 1)
		{
			dx = mode.el(++disp);
			dy = mode.el(++disp);

//			TRACE("SJNodeMesh::add_mode_frame %10.5f\n", dx);

			vec.set_value(dx * size * theta, dy * size * theta, 0.0);
			p_point->add_animate(vec);
		}
	}
}

void SJNodeMesh::clear_animate_vecs()
{
	POS pos = ml_points.get_head_pos();
	while(pos) ml_points.get_next(pos)->clear_animate();
}

void SJNodeMesh::reset_animate()
{
	POS pos = ml_points.get_head_pos();
	while(pos) ml_points.get_next(pos)->reset_animate();
}

BOOL SJNodeMesh::next_frame()
{
	SJPoint* p_point = NULL;
	BOOL keepgoing = TRUE;
	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_point = ml_points.get_next(pos);
		if(p_point->get_fix() > 0) continue;
		keepgoing = p_point->next_frame();
		if(keepgoing == FALSE) return FALSE;
	}
	return TRUE;
}

void SJNodeMesh::extract_modes()
{
	if(m_calcstage < STIFFNESS) arrange_stiffness();
	if(m_calcstage >= MODES) return;

	TRACE("EXTRACT MOODES\n");

	m_modes.size(m_numdofs);
	m_vals.size(m_numdofs);
	m_modes.jacobi(NULL, m_stiff, m_vals);
//	SJVector id(m_numdofs);
//	id.set_val(1.0f);

	SJVector mi(m_mass);
//	mi.sqrt();
	mi.invert();
	m_modes.eignrm(mi);
//	m_modes.eignrm(m_mass);
	m_calcstage = MODES;
}

void SJNodeMesh::arrange_general()
{
	TRACE("ARRANGE GENERAL\n");

	m_gload.size(m_numdofs);
	m_gmass.size(m_numdofs);

	for(int modenum = 1; modenum <= m_numdofs; modenum++)
	{
		SJVector eigenmode(m_modes, modenum);
		m_gload.el(modenum) = m_load.by_vt(eigenmode);
		m_gmass.el(modenum) = m_mass.by_vt(eigenmode);
	}
	m_gload.trace_vector();
	m_gmass.trace_vector();
}

void SJNodeMesh::strut(SJLine* p_line)
{
	float x1, y1, z1;
	float x2, y2, z2;

	SJPoint* p_p1;
	SJPoint* p_p2;

	p_p1 = p_line->mp_p1;
	p_p2 = p_line->mp_p2;

	p_p1->get_value(x1, y1, z1);
	p_p2->get_value(x2, y2, z2);

	int s1 = p_p1->m_dof[0];
	int s2 = p_p1->m_dof[1];

	int s3 = p_p2->m_dof[0];
	int s4 = p_p2->m_dof[1];

	float x = x2 - x1;
	float y = y2 - y1;
	float len = sr2(x, y);

	float cx = x / len;
	float sy = y / len;

//	TRACE("SJNodeMesh::strut %8.4f \n", p_line->m_ae);

	float eaol = p_line->m_ae / len;

//////
	m_stiff.el(s1, s1) +=  eaol * cx * cx;
	m_stiff.el(s1, s2) +=  eaol * cx * sy;

	m_stiff.el(s2, s1) +=  eaol * cx * sy;
	m_stiff.el(s2, s2) +=  eaol * sy * sy;
//////
	m_stiff.el(s1, s3) += -eaol * cx * cx;
	m_stiff.el(s1, s4) += -eaol * cx * sy;

	m_stiff.el(s2, s3) += -eaol * cx * sy;
	m_stiff.el(s2, s4) += -eaol * sy * sy;
//////
	m_stiff.el(s3, s1) += -eaol * cx * cx;
	m_stiff.el(s3, s2) += -eaol * cx * sy;

	m_stiff.el(s4, s1) += -eaol * cx * sy;
	m_stiff.el(s4, s2) += -eaol * sy * sy;
//////
	m_stiff.el(s3, s3) +=  eaol * cx * cx;
	m_stiff.el(s3, s4) +=  eaol * cx * sy;

	m_stiff.el(s4, s3) +=  eaol * cx * sy;
	m_stiff.el(s4, s4) +=  eaol * sy * sy;
//////
}

float SJNodeMesh::sq(float in)
{
	return in * in;
}

float SJNodeMesh::sr2(float in1, float in2)
{
	return sqrtf(sq(in1) + sq(in2));
}

float SJNodeMesh::sr3(float in1, float in2, float in3)
{
	return sqrtf(sq(in1) + sq(in2) + sq(in3));
}

void SJNodeMesh::arrange_load()
{
	m_load.size(m_numdofs);

	int dof = 0;
	SJPoint* p_point;
	POS pos = ml_points.get_head_pos();
	while(pos) 
	{
		p_point = ml_points.get_next(pos);
		if(p_point->get_fix() <= 0)
		{
			m_load.el(p_point->m_dof[0]) = p_point->m_load.get_component(0) * -1.0f;
			m_load.el(p_point->m_dof[1]) = p_point->m_load.get_component(1) * -1.0f;
		}
	}
}

void SJNodeMesh::run_rk4()
{
	extract_modes();
	if(m_calcstage >= DYNAMIC) return;

	TRACE("RUN RK4\n");

	clear_animate_vecs();
	arrange_load();
	arrange_general();

	if(m_dt <= 0.0f) return;
	if(m_time <= 0.0f) return;
	if(m_frac <= 0.0f) return;

	int num_frames = (int)(m_time / m_dt);
	int frac_eigs = (int)((float)m_numdofs * m_frac);

	m_ct = 0.0f;
	float fm = 0.0f;
	int mode, i, j, step;

	float yin[3];
	for (i = 0; i < 3; i++) yin[i] = 0.0f;

	SJVector u1(m_numdofs);
	SJVector u2(m_numdofs);
	SJVector u3(m_numdofs);

	for(step = 0; step < num_frames; step++) // time = t
	{ 
		for(mode = 1; mode <= frac_eigs; mode++) // mode
		{			
			yin[1] = u2.el(mode);
			yin[2] = u3.el(mode);
			rk4(yin, mode); 
			for (j = 1; j <= m_numdofs; j++) u1.el(j) += m_modes.el(j, mode) * yin[1];				
			u2.el(mode) = yin[1];
			u3.el(mode) = yin[2];
		}	
		fm = (float)fmod((double)m_ct, 0.05);
		if(fm < m_dt) 
		{
			add_dynamic_frame(u1);
			TRACE("FRAME\n");
		}
		TRACE("time %10.5f\n", m_ct);
		m_ct += m_dt;	
	}
	m_calcstage = DYNAMIC;
}

void SJNodeMesh::rk4(float* y, int mode) 
{
	int i;
	float xh, hh, h6;

	hh = m_dt / 2.0f;
	h6 = m_dt / 6.0f;
	xh = m_ct + hh;

	float dym[3];
	float dyt[3];
	float yt[3];
	float dydx[3];

	for(i = 0; i < 3; i++)
	{
		dym[i]	= 0.0f;
		dyt[i]	= 0.0f;
		yt[i]		= 0.0f;
		dydx[i]	= 0.0f;
	}

	derivs(yt, dydx, mode);
	for(i = 1; i <= 2; i++) yt[i] = y[i] + hh * dydx[i];
	derivs(yt, dyt, mode);
	for(i = 1; i <= 2; i++) yt[i] = y[i] + hh * dyt[i];
	derivs(yt, dym, mode);

	for(i = 1; i <= 2; i++) 
	{
		yt[i] = y[i] + m_dt * dym[i];
		dym[i] += dyt[i];
	}
	derivs(yt, dyt, mode);

	for(i = 1; i <= 2; i++) y[i] = y[i] + h6 * (dydx[i] + dyt[i] + 2.0f * dym[i]);
}

void SJNodeMesh::derivs(float y[], float dydx[], int mode) 
{
	float w = sqrtf(m_vals.el(mode));
	dydx[1] = y[2];
	dydx[2] = ((get_dp(m_ct, mode)) - (2.0f * m_damp * w * y[2]) - (w * w * y[1]));
}

float	SJNodeMesh::get_p(float tau, int mode)
{
	if(tau <= m_ft)
	{
		float p = (1.0f - cosf(2.0f * PI * tau / m_ft)) / 2.0f;
		float r = p * m_gload.el(mode);
//		TRACE("SJNodeMesh::get_p time %8.4f		r %15.8f\n", tau, r);
		return r;  // / m_gmass.el(mode);
	}
	return 0.0f;	
}

float SJNodeMesh::get_dp(float tau, int mode)
{
	if(tau > m_ft) return 0.0f;
	float r = get_p(tau, mode) - get_p(tau - m_dt, mode);	
	if(mode == 1) TRACE("SJNodeMesh::get_dp	 time %8.4f	 mode %2i 	r %15.8f\n", tau, mode, r);
	return r;		
}

float	SJNodeMesh::get_frq(int modenum)
{
	return sqrtf(m_vals.el(modenum)) / (2.0f * PI);
}

void SJNodeMesh::add_dynamic_frame(SJVector &disps)
{
	SJVec3 vec;
	float x, y;
	POS pos_p = ml_points.get_head_pos();
	while(pos_p)
	{
		SJPoint* p_point = ml_points.get_next(pos_p);

		if(p_point->get_fix() <= 0)
		{
			x = disps.el(p_point->m_dof[0]);
			y = disps.el(p_point->m_dof[1]);
			vec.set_value(x, y, 0.0f);
			p_point->add_animate(vec);
		}
	}
}

void SJNodeMesh::run_duhamel()
{
	extract_modes();
	if(m_calcstage >= DYNAMIC) return;

	TRACE("RUN DUHAMEL\n");

	clear_animate_vecs();
	arrange_load();
	arrange_general();

	if(m_dt <= 0.0f) return;
	if(m_time <= 0.0f) return;
	if(m_frac <= 0.0f) return;

	int step, modenum;
	int num_frames = (int)(m_time / m_dt);
	int frac_eigs = (int)((float)m_numdofs * m_frac);

	BOOL  drawstep = FALSE;		
	float omega		= 0.0f;
	float wd			= 0.0f;
	float x1wd		= 0.0f;
	float dwsq		= 0.0f;
	float AI			= 0.0f;
	float BI			= 0.0f;
	float VS			= 0.0f; 
	float VC			= 0.0f; 
	float dfti		= 0.0f; 
	float ft			= 0.0f; 
	float G			= 0.0f; 
	float Y			= 0.0f; 

	SJVector u1(m_numdofs);
	SJVector ATI(m_numdofs);
	SJVector BTI(m_numdofs);

	m_ct = 0.0f;
	for(step = 0; step < num_frames; step++) 
	{ 
		m_ct += m_dt;
		if(fmodf(m_ct, 0.05f) < m_dt) 
		{
			drawstep = TRUE;
			u1.clear();
		}
		else drawstep = FALSE;

		for(modenum = 1; modenum <= frac_eigs; modenum++) 
		{		
			omega = sqrtf(m_vals.el(modenum));
//			crit = 2 * sqrtf(m_vals.el(mode);	
			wd = omega * sqrtf(1.0f - (m_damp * m_damp));
			x1wd = omega * m_damp;
			dwsq = powf(x1wd, 2.0f) + powf(wd, 2.0f);

			AI = int1(m_ct, wd, dwsq, x1wd) - int1(m_ct - m_dt, wd, dwsq, x1wd);
			BI = int2(m_ct, wd, dwsq, x1wd) - int2(m_ct - m_dt, wd, dwsq, x1wd);
			VS = int3(m_ct, wd, dwsq, x1wd, AI, BI) - int3(m_ct - m_dt, wd, dwsq, x1wd, AI, BI);
			VC = int4(m_ct, wd, dwsq, x1wd, AI, BI) - int4(m_ct - m_dt, wd, dwsq, x1wd, AI, BI);

			dfti = get_dp(m_ct, modenum);
			ft = dfti / m_dt;
			G = get_p(m_ct - m_dt, modenum) - ((m_ct - m_dt) * ft);
//			G = ((m_ct - m_dt) * ft);

			AI *= G;
			AI += (ft * VC);
			ATI.el(modenum) += AI;

			BI *= G;
			BI += (ft * VS);
			BTI.el(modenum) += BI;

			if(drawstep)
			{
				Y = expf(-x1wd * m_ct) * ((ATI.el(modenum) * sinf(wd * m_ct)) - (BTI .el(modenum) * cosf(wd * m_ct))) / 
					wd;
				if(modenum < 20) TRACE("m_ct %10.5f     mode %4i     Y %20.5f\n", m_ct, modenum, Y);
				SJVector eigenmode(m_modes, modenum);
				eigenmode.scale(Y);
				u1.add(eigenmode);
			}
		}	
		if(drawstep) 
		{
			add_dynamic_frame(u1);
			TRACE("\nFRAME\n\n");
		}
	}
	m_calcstage = DYNAMIC;
}

float	SJNodeMesh::int1(float tau, float wd, float dwsq, float x1wd)
{
	return expf(x1wd * tau) * ((x1wd * cosf(wd * tau)) + (wd * sinf(wd * tau))) / dwsq;
}

float	SJNodeMesh::int2(float tau, float wd, float dwsq, float x1wd)
{
	return expf(x1wd * tau) * ((x1wd * sinf(wd * tau)) - (wd * cosf(wd * tau))) / dwsq;
}

float	SJNodeMesh::int3(float tau, float wd, float dwsq, float x1wd, float int1f, float int2f)
{
	return ((tau - (x1wd / dwsq)) * int2f) + (wd * int1f / dwsq);
}

float	SJNodeMesh::int4(float tau, float wd, float dwsq, float x1wd, float int1f, float int2f)
{
	return ((tau - (x1wd / dwsq)) * int1f) - (wd * int2f / dwsq);
}