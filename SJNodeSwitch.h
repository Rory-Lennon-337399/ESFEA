
#pragma once

#include "SJNode.h"

class SJNodeSwitch : public SJNode
{

public:

	SJNodeSwitch();
	virtual ~SJNodeSwitch();
	virtual void traverse_render(int render_type);
	virtual void traverse_bounds(SJBounds &bounds);

	int m_which_child;
};


