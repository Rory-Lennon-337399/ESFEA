
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include <afxadv.h>

//#include <SJBCommon.h>
#include "SJVec3.h"
///////////
const ID_MAIN_SPLIT				= WM_USER + 550;
const ID_CTRL_PANE_BAR			= WM_USER + 551;
const ID_CTRL_CONSOLE			= WM_USER + 552;
///////////
const IDM_ROTATE					= WM_USER + 801;
const IDM_MOVE						= WM_USER + 802;
const IDM_SCALE					= WM_USER + 803;
const IDM_SELECT_POINT			= WM_USER + 804;
const IDM_SELECT_OBJECT			= WM_USER + 805;
const IDM_SELECT_MESH_POINT	= WM_USER + 806;
const IDM_SELECT_MESH_FACE		= WM_USER + 807;
const IDM_SELECT_MESH			= WM_USER + 808;
const IDM_FIX_MESH_POINT		= WM_USER + 809;
const IDM_DRAG_POINT				= WM_USER + 810;
const IDM_MOVE_LOADS				= WM_USER + 811;
const IDM_CHANGE_PERSP			= WM_USER + 812;
const IDM_NEW_POINT				= WM_USER + 813;
const IDM_COLOR_MATERIAL		= WM_USER + 814;
const IDM_SHINE					= WM_USER + 815;
const IDM_MANIP_MOVE				= WM_USER + 816;
const IDM_MANIP_SCALE			= WM_USER + 817;
const IDM_MANIP_ROTATE			= WM_USER + 818;
const IDM_LIGHTS_COLOR			= WM_USER + 819;
const IDM_LIGHTS_POS				= WM_USER + 820;
const IDM_LIGHTS_DIR				= WM_USER + 821;
const IDM_SELECT_LIGHT			= WM_USER + 822;
///////////
const ID_UPDATE_PANES			= WM_USER + 560;
const ID_UPDATE_PANE_NUM		= WM_USER + 561;
const ID_MOUSE_MOVE_PANE		= WM_USER + 571;
const ID_MOUSE_MOVE_INC			= WM_USER + 572;
const ID_MOUSE_DOWN_PANE		= WM_USER + 573;
const ID_MOUSE_UP_PANE			= WM_USER + 574;
const ID_RIGHT_DOWN_PANE		= WM_USER + 575;
const ID_SET_VPR					= WM_USER + 576;
const ID_CHANGE_ROTATION		= WM_USER + 579;
const ID_CHANGE_CAM				= WM_USER + 580;
const ID_PERSPECTIVE				= WM_USER + 581;
const ID_PERSP_MESSAGE			= WM_USER + 582;
const ID_X_Z_PLANE				= WM_USER + 584;
const ID_X_Y_PLANE				= WM_USER + 585;
const ID_FRONT						= WM_USER + 586;
const ID_BACK						= WM_USER + 587;
const ID_TOP						= WM_USER + 588;
const ID_BOTTOM					= WM_USER + 589;
const ID_LEFT						= WM_USER + 590;
const ID_RIGHT						= WM_USER + 591;
const ID_SET_IN_CAM				= WM_USER + 605;
const ID_SET_ALL_IN_CAM			= WM_USER + 606;
const ID_SAFE_FROM_MAIN			= WM_USER + 607;
const ID_DOCK_ED					= WM_USER + 608;
const ID_UNPUSH_CHILDREN		= WM_USER + 700;
const ID_CHANGE_EDITOR			= WM_USER + 750;
const ID_SHOW_FORM				= WM_USER + 751;
const ID_HIDE_FORM				= WM_USER + 752;
const ID_UNPUSH					= WM_USER + 753;
const ID_PUSH						= WM_USER + 754;
const ID_CHILD_UNPUSH			= WM_USER + 761;
const ID_PARENT_UNPUSH			= WM_USER + 762;
const ID_NEW_BLOCK				= WM_USER + 763;
const ID_GROW_SELECTED			= WM_USER + 764;
const ID_UN_SELECT_MESH			= WM_USER + 765;
const ID_SET_MODE					= WM_USER + 800;
const ID_FIX_MORE					= WM_USER + 801;
const ID_THREAD_FINISHED		= WM_USER + 802;
const ID_SET_LOOP					= WM_USER + 803;
const ID_PAUSE						= WM_USER + 804;

const ID_MODAL_BUTTONS			= WM_USER + 850;
const ID_INIT_FORM				= WM_USER + 851;
const ID_SHOW_MODE				= WM_USER + 852;
const ID_ANIMATE					= WM_USER + 853;
const ID_TOGGLE_OUTLINE			= WM_USER + 854;
const ID_CALC_FINISHED			= WM_USER + 855;
const ID_CALC_STARTED			= WM_USER + 856;
const ID_NEW_SCENE				= WM_USER + 900;
const ID_RESIZE_POINTS			= WM_USER + 901;
const ID_CREASE	 				= WM_USER + 902;
const ID_UNCREASE					= WM_USER + 903;
const ID_COLOR_VEC				= WM_USER + 904;
const ID_NEW_SHAPE				= WM_USER + 905;
const ID_SPHERE					= WM_USER + 906;
const ID_CONE						= WM_USER + 907;
const ID_CYLINDER					= WM_USER + 908;
const ID_CUBE						= WM_USER + 909;
const ID_UNSELECT					= WM_USER + 910;
const ID_HIDE_PANEL				= WM_USER + 911;
const ID_SHOW_PANEL				= WM_USER + 912;
const ID_SET_CENTER				= WM_USER + 913;
const ID_CALC_NORMALS			= WM_USER + 914;
const ID_LIGHTS					= WM_USER + 915;
const ID_NEW_LIGHT				= WM_USER + 916;
const IDG_PANEL_SWITCH			= WM_USER + 950;
const IDG_MODAL_BUTTONS			= WM_USER + 951;
const ID_CONSOLE_STATE			= WM_USER + 952;
const ID_BAR_LIGHT				= WM_USER + 953;
const ID_SELECT					= WM_USER + 954;
const ID_DOCK_WIDTH				= WM_USER + 955;
const ID_CLICK_TREE				= WM_USER + 956;
const ID_CLOSE_MATRIX			= WM_USER + 957;
const ID_CHANGE_MODE				= WM_USER + 958;
const ID_UPDATE_DATA				= WM_USER + 959;

#define TO_DIALOG					FALSE
#define FROM_DIALOG				TRUE

#define INTEGRATE_IMPLICIT		0
#define INTEGRATE_EXPLICIT		1

#define IDM_SELECT_ND		   1
#define IDM_CREATE_EL			2
#define IDM_CREATE_ND		   3
#define IDM_SELECT_EL		   4
#define IDM_SCALE					5
#define IDM_PAN					6
#define IDM_FIT				   7
#define IDM_STIFF				   8
#define IDM_MASS					9
#define IDM_MODES				  10
#define IDM_LOAD			     11
#define IDM_MODAL				  12
#define IDM_DYNAMIC			  13

#define PI							3.1415926535897932385f

#define STIFFNESS			1
#define MODES				2
#define DYNAMIC			3

const char dqs = 34;

const CString g_modes[] = 
{
	"",
	"SELECT NODES",
	"CREATE ELEMENTS"
};

#include "SJSG.h"

class CESFEA2DApp : public CWinApp
{
public:

								CESFEA2DApp();

	//{{AFX_VIRTUAL(CESFEA2DApp)
public:
	virtual BOOL			InitInstance();
	virtual CDocument*	OpenDocumentFile(LPCTSTR lpszFileName);
	virtual int				ExitInstance();
	//}}AFX_VIRTUAL

	CString					get_mru_top();
	void						open_file(CString file_path);
	BOOL						save_file(CString file_path);
	void						set_mode(int newmode);
	int						get_mode();

	CFont						m_font;
	CFont						m_font_small;
	SJVec3					m_background_color;
	bool						m_drag_mode;
	SJSG						m_sg;
	HICON						m_app_icon;
	CString					m_last_file;

	//{{AFX_MSG(CESFEA2DApp)
	afx_msg void			OnAppAbout();
	afx_msg void			OnFileOpen();
	afx_msg void			OnFileSave();
	afx_msg void			OnFileSaveAs();
	afx_msg void			OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	int						m_i_manip_mode;
};
