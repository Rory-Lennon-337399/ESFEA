#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJSG.h"
#include "SJNodeCam.h"
#include "SJNodePush.h"
#include "SJNodeSwitch.h"
#include "SJNodeMesh.h"
#include "SJNodeTransManip.h"

SJSG::SJSG()
{
	m_root_pod = NULL;
}

SJSG::~SJSG()
{
	delete m_root_pod;
}	

void SJSG::create_tree()
{
	m_root_pod = new SJNode;
	mp_camera = new SJNodeCam;
	m_root_pod->add_child(mp_camera);

	m_scene_root = new SJNodePush;
	m_root_pod->add_child(m_scene_root);
	
	mp_mesh = new SJNodeMesh;
	m_scene_root->add_child(mp_mesh);
}

void SJSG::fit_mesh()
{
//	TRACE("SJSG::fit_mesh\n");
	m_bounds.m_first_pass = TRUE;
	m_root_pod->traverse_bounds(m_bounds);

	mp_camera->fit_mesh();
	mp_mesh->get_maxvs();
}

void SJSG::inc_move(int pane, double x, double y)
{
	prepare_screen_move(pane, x, y);
}

void SJSG::inc_scale(int pane, double x)
{

}

void SJSG::prepare_screen_move(int pane, double& x, double& y)
{
	double region_x, region_y;
	region_x = (double)m_region.get_x();
	region_y = (double)m_region.get_y();

	x = mp_camera->m_width  * (x / region_x);
	y = mp_camera->m_height * (y / region_y);
}

void SJSG::new_file()
{
	mp_mesh->new_file();
}

void SJSG::traverse_render(int render_type)
{
	m_root_pod->traverse_render(render_type);
}

void SJSG::traverse_write(ofstream* p_file)
{
	m_root_pod->traverse_write(p_file);
}