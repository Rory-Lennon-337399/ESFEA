
#pragma once

typedef unsigned long POS;

template<class PTR_TYPE>
class SJPointers 
{
protected:

	class SJPointersNode
	{
	public:

		SJPointersNode* p_next_node;
		PTR_TYPE p_data;

		SJPointersNode()
		{
			p_next_node = NULL;
			p_data = NULL;
		}
		~SJPointersNode() {}; 
	};

public:

	SJPointers();
	SJPointers(int size);
	SJPointers(SJPointers* src_list);
	~SJPointers();

	int  get_count() const;
	int  get_index(PTR_TYPE element);
	bool is_empty() const;

	PTR_TYPE get_head() const;
	PTR_TYPE get_tail() const;

	PTR_TYPE	remove_tail();
	void pop();

	int add_tail(PTR_TYPE new_element);
	int add_tail(SJPointers* pNewList);
	int add_once(PTR_TYPE new_element);
	int add_head(PTR_TYPE new_element);

	void reverse_order();

	void delete_list_nodes();
	void delete_data();
	
	POS  get_head_pos() const;
	POS  get_tail_pos() const;

	PTR_TYPE	get_next(POS &pos) const;
	PTR_TYPE	get_at (int n_index) const;
	PTR_TYPE	get_pos(POS pos) const;

	void set_at(int n_index, PTR_TYPE new_element);
	void set_pos(POS pos, PTR_TYPE new_element);
	void remove_at(POS pos);

	void delete_element(PTR_TYPE element);
	void remove_element(PTR_TYPE element);

	void expand(int num);

	POS insert_before(POS pos, PTR_TYPE new_element);
	POS insert_after (POS pos, PTR_TYPE new_element);

	POS find(PTR_TYPE search_value, POS start_after = NULL) const;
	POS find_pos_at_index(int n_index) const;

	void transfer_from_list(SJPointers* p_src_list);

protected:

	void init();

	SJPointersNode* m_p_node_head;
	SJPointersNode* m_p_node_tail;

	int m_num_nodes;
};

template<class PTR_TYPE>
SJPointers<PTR_TYPE>::SJPointers()
{
	init();
}

template<class PTR_TYPE>
SJPointers<PTR_TYPE>::SJPointers(int size)
{
	init();
	expand(size);	
}

template<class PTR_TYPE>
SJPointers<PTR_TYPE>::SJPointers(SJPointers* src_list)
{
	init();
	add_tail(src_list);
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::init()
{
	m_num_nodes = 0;
	m_p_node_head = NULL;
	m_p_node_tail = NULL;
}

template<class PTR_TYPE>
SJPointers<PTR_TYPE>::~SJPointers()
{
	delete_list_nodes();
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::delete_data()
{
	if(m_num_nodes <= 0) return;

	PTR_TYPE p_arg;
	POS pos;

	pos = (POS)m_p_node_head;
	while(pos)
	{
		p_arg = get_next(pos);
		delete p_arg;
	} 
	delete_list_nodes();
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::delete_list_nodes()
{
	if(m_num_nodes <= 0) return;

	SJPointersNode* p_d_node;

	POS pos = (POS) m_p_node_head;
	while(pos)
	{
		p_d_node = (SJPointersNode*)pos;
		get_next(pos);
		if(p_d_node != NULL) delete p_d_node;
	}
	init();
}

template<class PTR_TYPE>
int SJPointers<PTR_TYPE>::add_tail(PTR_TYPE new_element)
{
	SJPointersNode* p_new_node = new SJPointersNode;
	p_new_node->p_data = new_element;

	if (m_p_node_tail != NULL) m_p_node_tail->p_next_node = p_new_node;
	else m_p_node_head = p_new_node;

	m_p_node_tail = p_new_node;

	return m_num_nodes++;
}

template<class PTR_TYPE>
int SJPointers<PTR_TYPE>::add_tail(SJPointers* pNewList)
{
	POS pos = pNewList->get_head_pos();
	while(pos != NULL) add_tail(pNewList->get_next(pos));

	return m_num_nodes;
}

template<class PTR_TYPE>
int SJPointers<PTR_TYPE>::add_head(PTR_TYPE new_element)
{
	SJPointersNode* p_new_node = new SJPointersNode;
	p_new_node->p_data = new_element;

	if (m_p_node_head != NULL) p_new_node->p_next_node = m_p_node_head;
	else m_p_node_tail = p_new_node;	

	m_p_node_head = p_new_node;

	return m_num_nodes++;
}

template<class PTR_TYPE>
int SJPointers<PTR_TYPE>::add_once(PTR_TYPE new_element)
{
	if(new_element == NULL) return;

	SJPointersNode* p_node = m_p_node_head;
	for (; p_node != NULL; p_node = p_node->p_next_node)
	{	
		if(p_node->p_data == new_element) return;
	}
	add_tail(new_element);

	return m_num_nodes;
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::reverse_order()
{
	SJPointers<PTR_TYPE> pl_dummy;

	SJPointersNode* p_node = m_p_node_head;
	for (; p_node != NULL; p_node = p_node->p_next_node)
	{	
		pl_dummy.add_head(p_node->p_data);
	}
	transfer_from_list(&pl_dummy);
}

template<class PTR_TYPE>
 void SJPointers<PTR_TYPE>::transfer_from_list(SJPointers* p_src_list)
{
	delete_list_nodes();	
	add_tail(p_src_list);
}

template<class PTR_TYPE>
 PTR_TYPE SJPointers<PTR_TYPE>::get_next(POS& pos) const // return *POS++
{ 
	SJPointersNode* p_node = (SJPointersNode*)pos;
	pos = (POS)(p_node->p_next_node);
	return p_node->p_data; 
}

template<class PTR_TYPE>
PTR_TYPE	SJPointers<PTR_TYPE>::remove_tail()
{
	if(m_num_nodes <= 0) return;

	SJPointersNode* p_old_tail = m_p_node_tail;
	SJPointersNode* p_new_tail = (SJPointersNode*)find_pos_at_index(m_num_nodes - 2);

	if(p_new_tail != NULL) p_new_tail->p_next_node = NULL;
	m_p_node_tail = p_new_tail;

	if(p_old_tail != NULL)
	{
		delete p_old_tail;
	}
	m_num_nodes--;
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::pop()
{
	if(m_num_nodes <= 0) return;

	SJPointersNode* p_old_tail = m_p_node_tail;
	SJPointersNode* p_new_tail = (SJPointersNode*)find_pos_at_index(m_num_nodes - 2);

	if(p_new_tail != NULL) p_new_tail->p_next_node = NULL;
	m_p_node_tail = p_new_tail;

	if(p_old_tail != NULL)
	{
		delete p_old_tail->p_data;	
		delete p_old_tail;
	}
	m_num_nodes--;
}

template<class PTR_TYPE>
int SJPointers<PTR_TYPE>::get_count() const
{ 
	return m_num_nodes; 
}

template<class PTR_TYPE>
int  SJPointers<PTR_TYPE>::get_index(PTR_TYPE p_element)
{
	int index = 0;
	PTR_TYPE p_list_element;

	POS pos = (POS)m_p_node_head;
	while(pos)
	{
		p_list_element = get_next(pos);
		if (p_list_element == p_element) return index;
		index++;
	} 
	return 0;
}

template<class PTR_TYPE>
bool SJPointers<PTR_TYPE>::is_empty() const
{ 
	return m_num_nodes == 0; 
}

template<class PTR_TYPE>
PTR_TYPE SJPointers<PTR_TYPE>::get_head() const
{ 
	if(m_p_node_head == NULL) return NULL;
	return m_p_node_head->p_data; 
}

template<class PTR_TYPE>
PTR_TYPE SJPointers<PTR_TYPE>::get_tail() const
{ 
	if(m_p_node_tail == NULL) return NULL;
	return m_p_node_tail->p_data; 
}

template<class PTR_TYPE>
POS SJPointers<PTR_TYPE>::get_head_pos() const
{ 
	return (POS) m_p_node_head; 
}

template<class PTR_TYPE>
POS SJPointers<PTR_TYPE>::get_tail_pos() const
{ 
	return (POS) m_p_node_tail; 
}

template<class PTR_TYPE>
PTR_TYPE SJPointers<PTR_TYPE>::get_at(int n_index) const
{ 
	if (n_index >= m_num_nodes || n_index < 0) return NULL;  // went too far

	SJPointersNode* p_node = m_p_node_head;
	while(n_index--)
	{
		p_node = p_node->p_next_node;
	}
	return p_node->p_data;
}

template<class PTR_TYPE>
PTR_TYPE SJPointers<PTR_TYPE>::get_pos(POS rPOS) const
{ 
	SJPointersNode* p_node = (SJPointersNode*) (rPOS);
	return p_node->p_data; 
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::set_pos(POS pos, PTR_TYPE new_element)
{ 
	SJPointersNode* p_node = (SJPointersNode*) pos;
	p_node->p_data = new_element; 
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::set_at(int n_index, PTR_TYPE new_element)
{ 
	if(n_index < 0) return;

	expand(n_index + 1);

	SJPointersNode* p_node = m_p_node_head;
	while(n_index--)
	{
		p_node = p_node->p_next_node;
	}
	p_node->p_data = new_element;
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::expand(int num)
{ 
	for(int i = m_num_nodes; i < num; i++) add_tail((PTR_TYPE)NULL);
}

template<class PTR_TYPE>
POS SJPointers<PTR_TYPE>::insert_before(POS pos, PTR_TYPE new_element)
{
	if (POS == NULL) return AddHead(new_element); // insert before nothing -> head of the list

	// Insert it before POS
	SJPointersNode* pOldNode = (SJPointersNode*) POS;
	SJPointersNode* p_new_node = new SJPointersNode;
	p_new_node->p_data = new_element;

	m_p_node_head = p_new_node;

	return (POS) p_new_node;
}

template<class PTR_TYPE>
POS SJPointers<PTR_TYPE>::insert_after(POS pos, PTR_TYPE new_element)
{
	if (POS == NULL) return add_tail(new_element); // insert after nothing -> tail of the list

	SJPointersNode* pOldNode = (SJPointersNode*) POS;
	SJPointersNode* p_new_node = new SJPointersNode;
	p_new_node->p_data = new_element;

	m_p_node_tail = p_new_node;

	pOldNode->p_next_node = p_new_node;
	return (POS) p_new_node;
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::remove_at(POS pos)
{
	SJPointersNode* pOldNode = (SJPointersNode*) POS;
	if(pOldNode == m_p_node_head)
	{
		m_p_node_head = pOldNode->p_next_node;
	}
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::remove_element(PTR_TYPE element)
{
	SJPointersNode* p_current_node = m_p_node_head;
	SJPointersNode* p_current_node_m1 = NULL;

	while(p_current_node != NULL)
	{
		if(p_current_node->p_data == element) 
		{
			if(p_current_node_m1 != NULL) 
			{
				p_current_node_m1->p_next_node = p_current_node->p_next_node;
			}
			if(p_current_node == m_p_node_head)
			{
				m_p_node_head = m_p_node_head->p_next_node;
			}
			if(p_current_node == m_p_node_tail)
			{
				if(p_current_node_m1 != NULL) 
				{
					m_p_node_tail = p_current_node_m1;
					m_p_node_tail->p_next_node = NULL;
				}
				else m_p_node_tail = m_p_node_head = NULL;
			}
			delete p_current_node;
			m_num_nodes--;
			return;
		}
		p_current_node_m1 = p_current_node;
		p_current_node = p_current_node->p_next_node;
	}
}

template<class PTR_TYPE>
void SJPointers<PTR_TYPE>::delete_element(PTR_TYPE element)
{
	remove_element(element);
	delete element;
}

template<class PTR_TYPE>
POS SJPointers<PTR_TYPE>::find_pos_at_index(int n_index) const
{
	if (n_index >= m_num_nodes || n_index < 0) return NULL;  // went too far

	SJPointersNode* p_node = m_p_node_head;
	while(n_index--)
	{
		p_node = p_node->p_next_node;
	}
	return (POS)p_node;
}

template<class PTR_TYPE>
POS SJPointers<PTR_TYPE>::find(PTR_TYPE search_value, POS start_after) const
{
	SJPointersNode* p_node = (SJPointersNode*) start_after;
	if (p_node == NULL)
	{
		p_node = m_p_node_head;  // start at head
	}
	else
	{
		p_node = p_node->p_next_node;  // start after the one specified
	}

	for (; p_node != NULL; p_node = p_node->p_next_node)
	{	
		if (p_node->p_data == search_value) return (POS)p_node;
	}
	return NULL;
}

