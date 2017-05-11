
#pragma once

#include "SJNodePush.h"
#include "SJSG.h"

class CFileIn : public CStdioFile
{
public:

							CFileIn();
							~CFileIn();
	bool					read_file();

	SJSG*					mp_sg;
	SJPL_POINTS			ml_points;

protected:

	void					add_mesh();
	void					read_params(CString str_params);
	float					extract_float(CString str_input, CString str_after);
	int					extract_int(CString str_input, CString str_after);

	float					string_to_float(CString str);
	int					string_to_int(CString str);
};

