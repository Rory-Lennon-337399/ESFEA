#pragma once

#include "SJPoint.h"

class SJLine 
{

public:

	SJLine(SJPoint* p_p1, SJPoint* p_p2, float ae);
	~SJLine();
	virtual void traverse_render(int render_type);

	float m_ae;
	SJPoint* mp_p1;
	SJPoint* mp_p2;
};

typedef SJPointers<SJLine*> SJPL_LINES;