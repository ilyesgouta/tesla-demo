// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* main frame */
#include "../../MainFrame/MainFrame.hpp"

/* gl wrapper */
#include "../../OpenGL/OpenGL.hpp"

/* 3d types */
#include "../../base3d/base3d.hpp"

/* texture manager */
#include "TexManager.hpp"

/* 3ds support */
#include "../../3dlib/3dlib.h"
#include "../../Load3ds/load3ds.h"

#pragma warning ( disable : 4305 )
#pragma warning ( disable : 4244 )

#pragma comment ( lib, "winmm.lib" )


// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
