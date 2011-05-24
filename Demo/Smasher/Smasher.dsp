# Microsoft Developer Studio Project File - Name="Smasher" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Smasher - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Smasher.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Smasher.mak" CFG="Smasher - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Smasher - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Smasher - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Smasher - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "NDEBUG"
# ADD RSC /l 0x415 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 Zlib.lib PNGLib.lib JPegLib.lib kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows /machine:I386 /libpath:"\Project\PNGLib\Release" /libpath:"\Project\JpegLib\Release" /libpath:"\Project\Zlib\Release"

!ELSEIF  "$(CFG)" == "Smasher - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "_DEBUG"
# ADD RSC /l 0x415 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Zlib.lib PNGLib.lib JPegLib.lib kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"\Project\PNGLib\Debug" /libpath:"\Project\JpegLib\Debug" /libpath:"\Project\Zlib\Debug"

!ENDIF 

# Begin Target

# Name "Smasher - Win32 Release"
# Name "Smasher - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Effects"

# PROP Default_Filter ""
# Begin Group "PolkaLike"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PolkaLike.cpp
# End Source File
# Begin Source File

SOURCE=.\PolkaLike.hpp
# End Source File
# End Group
# Begin Group "SpinZoom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SpinZoom.cpp
# End Source File
# Begin Source File

SOURCE=.\SpinZoom.hpp
# End Source File
# End Group
# Begin Group "Tubes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tubes.cpp
# End Source File
# Begin Source File

SOURCE=.\tubes.hpp
# End Source File
# End Group
# Begin Group "tessellate"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tessellator.cpp
# End Source File
# Begin Source File

SOURCE=.\tessellator.hpp
# End Source File
# End Group
# Begin Group "FFDLinePlane"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LinePlane.cpp
# End Source File
# Begin Source File

SOURCE=.\LinePlane.hpp
# End Source File
# End Group
# Begin Group "Rotator"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Rotator.cpp
# End Source File
# Begin Source File

SOURCE=.\Rotator.hpp
# End Source File
# End Group
# Begin Group "Dragon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Dragon.cpp
# End Source File
# Begin Source File

SOURCE=.\Dragon.hpp
# End Source File
# End Group
# Begin Group "EnergyStream"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EnergyStream.cpp
# End Source File
# Begin Source File

SOURCE=.\EnergyStream.hpp
# End Source File
# End Group
# Begin Group "Tree"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Tree.cpp
# End Source File
# Begin Source File

SOURCE=.\Tree.hpp
# End Source File
# End Group
# Begin Group "ShadeBall"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ShadeBall.cpp
# End Source File
# Begin Source File

SOURCE=.\ShadeBall.hpp
# End Source File
# End Group
# Begin Group "Splines"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Splines.cpp
# End Source File
# Begin Source File

SOURCE=.\Splines.hpp
# End Source File
# End Group
# Begin Group "FaceMorph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FaceMorph.cpp
# End Source File
# Begin Source File

SOURCE=.\FaceMorph.hpp
# End Source File
# End Group
# Begin Group "FFDEnvVector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FFDEnvVector.cpp
# End Source File
# Begin Source File

SOURCE=.\FFDEnvVector.hpp
# End Source File
# End Group
# Begin Group "TC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bands.cpp
# End Source File
# Begin Source File

SOURCE=.\Bands.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Effect.hpp
# End Source File
# End Group
# Begin Group "filters"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ffd.cpp
# End Source File
# Begin Source File

SOURCE=.\ffd.h
# End Source File
# Begin Source File

SOURCE=.\Stuff.cpp
# End Source File
# Begin Source File

SOURCE=.\Stuff.hpp
# End Source File
# End Group
# Begin Group "BassPlay"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BassPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\BassPlay.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\EffManage.cpp
# End Source File
# Begin Source File

SOURCE=.\EffManage.hpp
# End Source File
# Begin Source File

SOURCE=.\Smasher.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TexManager.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\sinus.hpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TexManager.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\demo.rc
# End Source File
# End Group
# Begin Group "Libs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Bass\C\BASS.LIB
# End Source File
# End Group
# End Target
# End Project
