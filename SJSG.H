
#pragma once

#include "SJVec3.h"
#include "SJNodeMesh.h"
#include "SJNodeCam.h"

class SJNode;
class SJNodeCam;
class SJNodePush;
class SJNodeSwitch;

#define RENDER		1
#define SELECT		2
#define ANIMATE	3

class SJSG
{
public:
					SJSG();
					~SJSG();

	void			new_file();
	void			create_tree();
	void			prepare_screen_move(int pane, double& x, double& y);
	void			traverse_render(int render_type);
	void			traverse_write(ofstream* p_file);
	void			fit_mesh();
	void			inc_move(int pane, double x, double y);
	void			inc_scale(int pane, double x);

	SJNodePush*	m_scene_root;
	SJNode*		m_root_pod;
	SJNodeCam*	mp_camera;
	SJNodeMesh* mp_mesh;

	SJBounds		m_bounds;
	SJVec2s		m_region;
};

