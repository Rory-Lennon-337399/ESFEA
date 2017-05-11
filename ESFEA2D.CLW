; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "esfea2d.h"
LastPage=0

ClassCount=19
Class1=CChildView
Class2=CPanelModal
Class3=CCtrlPaneBar
Class4=CDlgMatrix
Class5=CESFEA2DApp
Class6=CAboutDlg
Class7=CMainFrame
Class8=CPanelAnimate
Class9=CPanelBase
Class10=CPanelElements
Class11=CPanelLoad
Class12=CPanelNodes
Class13=CPanelNum
Class14=CPanelSelectNode
Class15=CPanelTree
Class16=CSejikaSheet
Class17=CSejikaStatus
Class18=SJView
Class19=CThreadSejika

ResourceCount=12
Resource1=IDP_LOAD (English (U.S.))
Resource2=IDP_NODES (English (U.S.))
Resource3=IDP_SEL_ND (English (U.S.))
Resource4=IDP_ANIMATE (English (U.S.))
Resource5=IDD_PANEL_TREE (English (U.S.))
Resource6=IDD_ABOUTBOX (English (U.S.))
Resource7=IDR_MAINFRAME (English (U.S.))
Resource8=IDD_PANEL_NUM (English (U.S.))
Resource9=IDP_MODAL (English (U.S.))
Resource10=IDD_MATRIX (English (U.S.))
Resource11=IDP_ELEMENTS (English (U.S.))
Resource12=IDR_CAMERA_MENU (English (U.S.))

[CLS:CChildView]
Type=0
BaseClass=CWnd
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp

[CLS:CPanelModal]
Type=0
BaseClass=CPanelBase
HeaderFile=CPanelModal.h
ImplementationFile=PanelModal.cpp

[CLS:CCtrlPaneBar]
Type=0
BaseClass=CWnd
HeaderFile=CtrlPaneBar.h
ImplementationFile=CtrlPaneBar.cpp

[CLS:CDlgMatrix]
Type=0
BaseClass=CDialog
HeaderFile=DlgMatrix.h
ImplementationFile=DlgMatrix.cpp

[CLS:CESFEA2DApp]
Type=0
BaseClass=CWinApp
HeaderFile=ESFEA2D.H
ImplementationFile=ESFEA2D.CPP

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ESFEA2D.CPP
ImplementationFile=ESFEA2D.CPP
LastObject=CAboutDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CPanelAnimate]
Type=0
BaseClass=CPanelBase
HeaderFile=PanelAnimate.h
ImplementationFile=PanelAnimate.cpp

[CLS:CPanelBase]
Type=0
BaseClass=CDialog
HeaderFile=PanelBase.h
ImplementationFile=PanelBase.cpp

[CLS:CPanelElements]
Type=0
BaseClass=CPanelBase
HeaderFile=PanelElements.h
ImplementationFile=PanelElements.cpp

[CLS:CPanelLoad]
Type=0
BaseClass=CPanelBase
HeaderFile=PanelLoad.h
ImplementationFile=PanelLoad.cpp

[CLS:CPanelNodes]
Type=0
BaseClass=CPanelBase
HeaderFile=PanelNodes.h
ImplementationFile=PanelNodes.cpp

[CLS:CPanelNum]
Type=0
BaseClass=CPanelBase
HeaderFile=PanelNum.h
ImplementationFile=PanelNum.cpp

[CLS:CPanelSelectNode]
Type=0
BaseClass=CPanelBase
HeaderFile=PanelSelectNode.h
ImplementationFile=PanelSelectNode.cpp

[CLS:CPanelTree]
Type=0
BaseClass=CDialog
HeaderFile=PanelTree.h
ImplementationFile=PanelTree.cpp

[CLS:CSejikaSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=SejikaSheet.h
ImplementationFile=SejikaSheet.cpp

[CLS:CSejikaStatus]
Type=0
BaseClass=CStatusBar
HeaderFile=SejikaStatus.h
ImplementationFile=SejikaStatus.cpp

[CLS:SJView]
Type=0
BaseClass=CWnd
HeaderFile=SJView.h
ImplementationFile=SJView.cpp

[CLS:CThreadSejika]
Type=0
BaseClass=CWinThread
HeaderFile=ThreadSejika.h
ImplementationFile=ThreadSejika.cpp

[DLG:IDP_ANIMATE]
Type=1
Class=CPanelModal

[DLG:IDD_MATRIX]
Type=1
Class=CDlgMatrix

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDP_ELEMENTS]
Type=1
Class=CPanelElements

[DLG:IDP_LOAD]
Type=1
Class=CPanelLoad

[DLG:IDP_NODES]
Type=1
Class=CPanelNodes

[DLG:IDD_PANEL_NUM]
Type=1
Class=CPanelNum

[DLG:IDP_SEL_ND]
Type=1
Class=CPanelSelectNode

[DLG:IDD_PANEL_TREE]
Type=1
Class=CPanelTree

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_APP_ABOUT
CommandCount=7

[DLG:IDD_PANEL_NUM (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,button,1342177287

[DLG:IDD_MATRIX (English (U.S.))]
Type=1
Class=?
ControlCount=0

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDB_DONUT,static,1342177294
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDP_SEL_ND (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,button,1342177287
Control2=IDC_UNSEL_NODE,button,1342242816
Control3=IDC_SEL_ALL,button,1342242816

[DLG:IDP_NODES (English (U.S.))]
Type=1
Class=?
ControlCount=12
Control1=IDE_X,edit,1350631426
Control2=IDE_Y,edit,1350631426
Control3=IDC_INPUT_1,static,1342308352
Control4=IDC_INPUT_2,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_CREATE,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDE_DX,edit,1350631426
Control9=IDE_DY,edit,1350631426
Control10=IDC_INPUT_3,static,1342308352
Control11=IDC_INPUT_4,static,1342308352
Control12=IDC_COPY,button,1342242816

[DLG:IDD_PANEL_TREE (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_TREE,SysTreeView32,1342242850

[DLG:IDP_LOAD (English (U.S.))]
Type=1
Class=?
ControlCount=18
Control1=IDC_STATIC,button,1342177287
Control2=IDC_FIX,button,1342242816
Control3=IDE_FX,edit,1350631426
Control4=IDE_FY,edit,1350631426
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_APPLY,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDE_FT,edit,1350631426
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_MASS,button,1342242816
Control16=IDE_MASS,edit,1350631426
Control17=IDC_INPUT_5,static,1342308352
Control18=IDC_STATIC,static,1342308352

[DLG:IDP_ELEMENTS (English (U.S.))]
Type=1
Class=?
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_MAT,button,1342242816
Control3=IDE_AREA,edit,1350631426
Control4=IDC_INPUT_5,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDE_ELAST,edit,1350631426
Control7=IDC_INPUT_6,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDP_ANIMATE (English (U.S.))]
Type=1
Class=?
ControlCount=19
Control1=IDC_DYNAMIC,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDE_DAMP,edit,1350631426
Control5=IDC_STATIC,static,1342308352
Control6=IDC_RESET,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDE_TIME,edit,1350631426
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDE_DT,edit,1350631426
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDE_FRAC,edit,1350631426
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,button,1342177287
Control17=IDR_IMPLICIT,button,1342177284
Control18=IDC_STATIC,button,1342177287
Control19=IDR_EXPLICIT,button,1342177289

[DLG:IDP_MODAL (English (U.S.))]
Type=1
Class=?
ControlCount=13
Control1=65535,button,1342177287
Control2=IDE_MODENUM,edit,1350631554
Control3=65535,static,1342308352
Control4=IDC_ANIMATE_MODE,button,1342242816
Control5=IDC_SPIN,msctls_updown32,1342177312
Control6=IDE_EIGVAL,edit,1342253186
Control7=65535,static,1342308352
Control8=65535,static,1342308352
Control9=IDE_NDOFS,edit,1342253186
Control10=65535,static,1342308352
Control11=IDE_PERIOD,edit,1342253186
Control12=65535,static,1342308352
Control13=65535,static,1342308352

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
Command11=ID_CONTEXT_HELP
Command12=ID_HELP
CommandCount=12

[MNU:IDR_CAMERA_MENU (English (U.S.))]
Type=1
Class=?
CommandCount=0

