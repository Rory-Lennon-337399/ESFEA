#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJNodeSwitch.h"

SJNodeSwitch::SJNodeSwitch() 
{
	m_which_child = 0;
}

SJNodeSwitch::~SJNodeSwitch()
{
//	TRACE("~SJNodeSwitch() size %d pointer %d\n", sizeof(SJNodeSwitch), this);
}

void SJNodeSwitch::traverse_render(int render_type)
{
	SJNode* p_node = (SJNode*)mpl_child_nodes.get_at(m_which_child);
	p_node->traverse_render(render_type);
}

void SJNodeSwitch::traverse_bounds(SJBounds &bounds)
{
	SJNode* p_node = (SJNode*)mpl_child_nodes.get_at(m_which_child);
	p_node->traverse_bounds(bounds);
}

