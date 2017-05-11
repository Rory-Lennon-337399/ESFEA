#include "stdafx.h"
#include "ESFEA2D.h"
#include "FileIn.h"
#include "SJPointers.h"

#include "SJNode.h"
#include "SJNodePush.h"
#include "SJNodeTransManip.h"
#include "SJNodeMesh.h"

CFileIn::CFileIn()
{
	mp_sg = &((CESFEA2DApp*)AfxGetApp())->m_sg;
}

CFileIn::~CFileIn()
{}

	// find character starting at left, -1 if not found
//	int Find(TCHAR ch) const;
	// find character starting at right
//	int ReverseFind(TCHAR ch) const;
	// find character starting at zero-based index and going right
//	int Find(TCHAR ch, int nStart) const;
	// find first instance of any character in passed string
//	int FindOneOf(LPCTSTR lpszCharSet) const;
	// find first instance of substring
//	int Find(LPCTSTR lpszSub) const;
	// find first instance of substring starting at zero-based index
//	int Find(LPCTSTR lpszSub, int nStart) const;

bool CFileIn::read_file()
{
	CString single_line;
	bool valid = false;

	while(ReadString(single_line))
	{
		valid = true;
		single_line.MakeUpper();

		if(single_line.Find("<PARAMETERS") >= 0) read_params(single_line);
		if(single_line.Find("<MESH>") >= 0) add_mesh();
	}
	return valid;
}

void CFileIn::read_params(CString str_params)
{
	mp_sg->mp_mesh->m_damp	= extract_float(str_params, "DAMP");
	mp_sg->mp_mesh->m_frac	= extract_float(str_params, "FRAC");
	mp_sg->mp_mesh->m_time	= extract_float(str_params, "TIME");
	mp_sg->mp_mesh->m_dt		= extract_float(str_params, "DT");
	mp_sg->mp_mesh->m_ft		= extract_float(str_params, "FT");
	mp_sg->mp_mesh->m_aa		= extract_float(str_params, "AA");
	mp_sg->mp_mesh->m_ee		= extract_float(str_params, "EE");
	mp_sg->mp_mesh->m_int	= extract_float(str_params, "INT");
}

void CFileIn::add_mesh()
{
	CString single_line;
	void* void_void = (void*)-1;

	while(ReadString(single_line))
	{
		single_line.MakeUpper();

		SJPL_POINTS pl_points;

		if(single_line.Find("<NODE") >= 0) 
		{
			int num		= extract_int(single_line,		"NUMBER");
			float xx		= extract_float(single_line,	"XX");
			float yy		= extract_float(single_line,	"YY");
//			float fz		= extract_float(single_line,	"ZF");
			float xf		= extract_float(single_line,	"XF");
			float yf		= extract_float(single_line,	"YF");
//			float pz		= extract_float(single_line,	"ZP");
			int fix		= extract_int(single_line,		"FIX");
			float lump	= extract_float(single_line,	"LUMP");
			mp_sg->mp_mesh->add_point(num, FALSE, fix, xx, yy, xf, yf, lump);
		}
		if(single_line.Find("<QUAD") >= 0) 
		{
			int point_nums[4];
			point_nums[0] = extract_int(single_line, "P1");
			point_nums[1] = extract_int(single_line, "P2");
			point_nums[2] = extract_int(single_line, "P3");
			point_nums[3] = extract_int(single_line, "P4");

			mp_sg->mp_mesh->add_block(point_nums);
		}
	}
}

float CFileIn::string_to_float(CString str)
{
	if(str.GetLength() <= 0) return 0.0f;
	if(str.GetLength() >= 100) return 0.0f;

	LPTSTR p_chars = str.GetBuffer(0);
	float ret_float = (float)atof(p_chars);
	str.ReleaseBuffer();
	return ret_float;
}

int CFileIn::string_to_int(CString str)
{
	if(str.GetLength() <= 0) return 0;
	if(str.GetLength() >= 100) return 0;

	LPTSTR p_chars = str.GetBuffer(0);
	int ret_int = atoi(p_chars);
	str.ReleaseBuffer();

   return ret_int;
}

float CFileIn::extract_float(CString str_input, CString str_after)
{
	int pos_char = str_input.Find(str_after);
	if(pos_char <= 0) return 0.0f;
	int dqs_pos_1 = str_input.Find(dqs, pos_char);
	int dqs_pos_2 = str_input.Find(dqs, dqs_pos_1 + 1);
	return string_to_float(str_input.Mid(dqs_pos_1 + 1, dqs_pos_2 - dqs_pos_1 - 1));
}

int CFileIn::extract_int(CString str_input, CString str_after)
{
	int pos_char = str_input.Find(str_after);
	if(pos_char <= 0) return 0;
	int dqs_pos_1 = str_input.Find(dqs, pos_char);
	int dqs_pos_2 = str_input.Find(dqs, dqs_pos_1 + 1);
	return string_to_int(str_input.Mid(dqs_pos_1 + 1, dqs_pos_2 - dqs_pos_1 - 1));
}

