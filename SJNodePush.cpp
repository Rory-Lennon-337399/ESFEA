#include "stdafx.h"
#include "ESFEA2D.h"
#include "SJNodePush.h"

SJNodePush::SJNodePush() 
{}

SJNodePush::~SJNodePush()
{
//	TRACE("~SJNodePush() size %d pointer %d\n", sizeof(SJNodePush), this);
}

void SJNodePush::traverse_render(int render_type)
{
	::glPushMatrix();
		SJNode::traverse_render(render_type);
 	::glPopMatrix();   
}

void SJNodePush::write_to_file(ofstream* open_file)
{
	*open_file << "<PUSH>" << endl;
	write_dependants(open_file);
	*open_file << "</PUSH>" << endl;
}
