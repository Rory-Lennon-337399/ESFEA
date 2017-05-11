#pragma once

#include "SJPointers.h"
#include "fstream.h"
#include "SJMat3.h"
#include "SJBounds.h"

class SJNode;
typedef SJPointers<SJNode*> PL_NODE;

class SJNode  
{
public:

						SJNode();
	virtual			~SJNode();
	virtual void	traverse_render(int render_type);
	virtual void	traverse_bounds(SJBounds &bounds);
	virtual void	traverse_write(ofstream* p_file);
	virtual void	write_to_file(ofstream* p_open_file);
	virtual void	add_child(SJNode* p_node);
	SJNode* 			get_child(int num);
	int				get_num_kids();
	virtual void	delete_data();
	void				print_double_only(ofstream* p_open_file, double value);
	void				write_dependants(ofstream* open_file);

protected:

	PL_NODE			mpl_child_nodes;
};


