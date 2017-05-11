#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJBlock.h"

SJBlock::SJBlock(SJPL_POINTS* pl_points, float ae) 
{
	ml_points.add_tail(pl_points);

	float edge	= 1.0f * ae;
	float diag	= 1.0f * ae;

/// SIDES ///////////////
	add_line(1, 2, edge);
	add_line(2, 3, edge);
	add_line(3, 4, edge);
	add_line(4, 1, edge);

/// DIAGONALS ///////////
	add_line(1, 3, diag);
	add_line(2, 4, diag);
}

SJBlock::~SJBlock()
{
	ml_lines.delete_data();
}

void SJBlock::add_line(int i, int j, float ae)
{
	SJPoint* p_p1 = ml_points.get_at(i - 1);
	SJPoint* p_p2 = ml_points.get_at(j - 1);

	SJLine* p_line = new SJLine(p_p1, p_p2, ae);
	ml_lines.add_tail(p_line);
}

void SJBlock::traverse_render(int render_type)
{
	::glDisable(GL_LIGHTING);
	::glEnable(GL_COLOR_MATERIAL);

	int count = 0;
	POS pos = ml_lines.get_head_pos();
	while(pos) 
	{
		count++;
		SJLine* p_line = ml_lines.get_next(pos);
		if(count < 5) p_line->traverse_render(render_type);
	}
}

void SJBlock::traverse_write(ofstream* p_file)
{
	*p_file << "<QUAD ";

	*p_file << "P1=" << dqs << ml_points.get_at(0)->m_num << dqs << " ";
	*p_file << "P2=" << dqs << ml_points.get_at(1)->m_num << dqs << " ";
	*p_file << "P3=" << dqs << ml_points.get_at(2)->m_num << dqs << " ";
	*p_file << "P4=" << dqs << ml_points.get_at(3)->m_num << dqs;

	*p_file << " />" << endl;
}


