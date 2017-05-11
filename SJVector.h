#pragma once

class SJMatrix;

class SJVector
{
public:
				SJVector();
				SJVector(int size);
				SJVector(SJMatrix &bm, int column);
				SJVector(SJVector &v);
				~SJVector();
	void		size(int size);
	float		&el(int i);
	void		clear();
	void		trace_vector();
	void		copy(SJVector &bv);
	void		invert();
	void		sqrt();
	float		by_vt(SJVector &vec);
	void		v_by(SJVector &v);
	void		set_val(float val);
	void		vt_by(SJMatrix &v);
	void		scale(float scalar);
	void		add(SJVector &v);
	int		m_size;

protected:

	float*	m_data;
};

