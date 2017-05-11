# Microsoft Developer Studio Project File - Name="ESFEA2D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ESFEA2D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ESFEA2D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ESFEA2D.mak" CFG="ESFEA2D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ESFEA2D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ESFEA2D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ESFEA2D - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release_output"
# PROP Intermediate_Dir "release_intermediate"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib vfw32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ESFEA2D - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "debug_output"
# PROP Intermediate_Dir "debug_intermediate"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ESFEA2D - Win32 Release"
# Name "ESFEA2D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlPaneBar.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\ESFEA2D.cpp
# End Source File
# Begin Source File

SOURCE=.\ESFEA2D.rc
# End Source File
# Begin Source File

SOURCE=.\FileIn.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelAnimate.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelElements.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelLoad.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelModal.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelNodes.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelNum.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelSelectNode.cpp
# End Source File
# Begin Source File

SOURCE=.\PanelTree.cpp
# End Source File
# Begin Source File

SOURCE=.\SejikaSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\SejikaStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\SJBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\SJBounds.cpp
# End Source File
# Begin Source File

SOURCE=.\SJBox.cpp
# End Source File
# Begin Source File

SOURCE=.\SJLine.cpp
# End Source File
# Begin Source File

SOURCE=.\SJMat3.cpp
# End Source File
# Begin Source File

SOURCE=.\SJMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\SJNode.cpp
# End Source File
# Begin Source File

SOURCE=.\SJNodeCam.cpp
# End Source File
# Begin Source File

SOURCE=.\SJNodeMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\SJNodePush.cpp
# End Source File
# Begin Source File

SOURCE=.\SJNodeSwitch.cpp
# End Source File
# Begin Source File

SOURCE=.\SJNodeTransManip.cpp
# End Source File
# Begin Source File

SOURCE=.\SJPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\SJRotation.cpp
# End Source File
# Begin Source File

SOURCE=.\SJSG.cpp
# End Source File
# Begin Source File

SOURCE=.\SJVec2s.cpp
# End Source File
# Begin Source File

SOURCE=.\SJVec3.cpp
# End Source File
# Begin Source File

SOURCE=.\SJVector.cpp
# End Source File
# Begin Source File

SOURCE=.\SJView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ThreadSejika.cpp
# End Source File
# Begin Source File

SOURCE=.\WRITEAVI.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\CtrlPaneBar.h
# End Source File
# Begin Source File

SOURCE=.\DlgMatrix.h
# End Source File
# Begin Source File

SOURCE=.\ESFEA2D.h
# End Source File
# Begin Source File

SOURCE=.\FileIn.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PanelAnimate.h
# End Source File
# Begin Source File

SOURCE=.\PanelBase.h
# End Source File
# Begin Source File

SOURCE=.\PanelElements.h
# End Source File
# Begin Source File

SOURCE=.\PanelLoad.h
# End Source File
# Begin Source File

SOURCE=.\PanelModal.h
# End Source File
# Begin Source File

SOURCE=.\PanelNodes.h
# End Source File
# Begin Source File

SOURCE=.\PanelNum.h
# End Source File
# Begin Source File

SOURCE=.\PanelSelectNode.h
# End Source File
# Begin Source File

SOURCE=.\PanelTree.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SejikaSheet.h
# End Source File
# Begin Source File

SOURCE=.\SejikaStatus.h
# End Source File
# Begin Source File

SOURCE=.\SJBlock.h
# End Source File
# Begin Source File

SOURCE=.\SJBounds.h
# End Source File
# Begin Source File

SOURCE=.\SJBox.h
# End Source File
# Begin Source File

SOURCE=.\SJLine.h
# End Source File
# Begin Source File

SOURCE=.\SJMat3.h
# End Source File
# Begin Source File

SOURCE=.\SJMatrix.h
# End Source File
# Begin Source File

SOURCE=.\SJNode.h
# End Source File
# Begin Source File

SOURCE=.\SJNodeCam.h
# End Source File
# Begin Source File

SOURCE=.\SJNodeMesh.h
# End Source File
# Begin Source File

SOURCE=.\SJNodePush.h
# End Source File
# Begin Source File

SOURCE=.\SJNodeSwitch.h
# End Source File
# Begin Source File

SOURCE=.\SJNodeTransManip.h
# End Source File
# Begin Source File

SOURCE=.\SJPoint.h
# End Source File
# Begin Source File

SOURCE=.\SJPointers.h
# End Source File
# Begin Source File

SOURCE=.\SJRotation.h
# End Source File
# Begin Source File

SOURCE=.\SJSG.h
# End Source File
# Begin Source File

SOURCE=.\SJVec2s.h
# End Source File
# Begin Source File

SOURCE=.\SJVec3.h
# End Source File
# Begin Source File

SOURCE=.\SJVector.h
# End Source File
# Begin Source File

SOURCE=.\SJView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ThreadSejika.h
# End Source File
# Begin Source File

SOURCE=.\WriteAVI.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CURSOR1.CUR
# End Source File
# Begin Source File

SOURCE=.\res\DONUT.BMP
# End Source File
# Begin Source File

SOURCE=.\res\ESFEA2D.ico
# End Source File
# Begin Source File

SOURCE=.\res\ESFEA2D.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ICON2.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Nodrop.cur
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Trck4way.cur
# End Source File
# Begin Source File

SOURCE=.\res\Trckwe.cur
# End Source File
# End Group
# End Target
# End Project
