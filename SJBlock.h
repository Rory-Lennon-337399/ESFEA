#pragma once

#include "SJPoint.h"
#include "SJLine.h"

class SJBlock 
{

public:

	SJBlock(SJPL_POINTS* pl_points, float ae);
	~SJBlock();
	void add_line(int i, int j, float ae);
	virtual void traverse_render(int render_type);
	virtual void traverse_write(ofstream* p_file);

	SJPL_POINTS ml_points;
	SJPL_LINES ml_lines;
};

typedef SJPointers<SJBlock*> SJPL_BLOCKS;