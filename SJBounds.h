
#pragma once

#include "SJMat3.h"
#include "SJBox.h"
#include "SJVec3.h"

class SJBounds  
{
public:

	SJBounds();
	~SJBounds();
	void stretch(SJVec3& point);

	SJBox m_box;
	int m_first_pass;
	SJMat3 m_mat3;
};


