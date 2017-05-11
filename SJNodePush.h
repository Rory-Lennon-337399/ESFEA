

#pragma once

#include "SJNode.h"

class SJNodePush : public SJNode
{

public:

	SJNodePush();
	virtual void	traverse_render(int render_type);
	virtual void	write_to_file(ofstream* open_file);

protected:

	virtual ~SJNodePush();
};


