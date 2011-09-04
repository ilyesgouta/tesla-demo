//
// tesla-demo, an OpenGL|ES 1.1 port of Sunflower's original Tesla demo.
//
// Original Tesla code, Copyright (C) 2000 Sunflower
// Linux EGL/X11 port by Ilyes Gouta, ilyes.gouta@gmail.com
//
// Port released under GNU General Public License with permission from
// Konrad Zagorowicz, original developer from Sunflower.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifdef WIN32
#include "stdafx.h"
#endif

#ifndef WIN32
#include <GL/gl.h>
#include <string.h>
#endif

#ifdef WIN32
extern "C" {

static HMODULE hOpenGLDLL = 0;

pfnglAccum glAccum;
pfnglAlphaFunc glAlphaFunc;
pfnglAreTexturesResident glAreTexturesResident;
pfnglArrayElement glArrayElement;
pfnglBegin glBegin;
pfnglBindTexture glBindTexture;
pfnglBitmap glBitmap;
pfnglBlendFunc glBlendFunc;
pfnglCallList glCallList;
pfnglCallLists glCallLists;
pfnglClear glClear;
pfnglClearAccum glClearAccum;
pfnglClearColor glClearColor;
pfnglClearDepth glClearDepth;
pfnglClearIndex glClearIndex;
pfnglClearStencil glClearStencil;
pfnglClipPlane glClipPlane;
pfnglColor3b glColor3b;
pfnglColor3bv glColor3bv;
pfnglColor3d glColor3d;
pfnglColor3dv glColor3dv;
pfnglColor3f glColor3f;
pfnglColor3fv glColor3fv;
pfnglColor3i glColor3i;
pfnglColor3iv glColor3iv;
pfnglColor3s glColor3s;
pfnglColor3sv glColor3sv;
pfnglColor3ub glColor3ub;
pfnglColor3ubv glColor3ubv;
pfnglColor3ui glColor3ui;
pfnglColor3uiv glColor3uiv;
pfnglColor3us glColor3us;
pfnglColor3usv glColor3usv;
pfnglColor4b glColor4b;
pfnglColor4bv glColor4bv;
pfnglColor4d glColor4d;
pfnglColor4dv glColor4dv;
pfnglColor4f glColor4f;
pfnglColor4fv glColor4fv;
pfnglColor4i glColor4i;
pfnglColor4iv glColor4iv;
pfnglColor4s glColor4s;
pfnglColor4sv glColor4sv;
pfnglColor4ub glColor4ub;
pfnglColor4ubv glColor4ubv;
pfnglColor4ui glColor4ui;
pfnglColor4uiv glColor4uiv;
pfnglColor4us glColor4us;
pfnglColor4usv glColor4usv;
pfnglColorMask glColorMask;
pfnglColorMaterial glColorMaterial;
pfnglColorPointer glColorPointer;
pfnglCopyPixels glCopyPixels;
pfnglCopyTexImage1D glCopyTexImage1D;
pfnglCopyTexImage2D glCopyTexImage2D;
pfnglCopyTexSubImage1D glCopyTexSubImage1D;
pfnglCopyTexSubImage2D glCopyTexSubImage2D;
pfnglCullFace glCullFace;
pfnglDeleteLists glDeleteLists;
pfnglDeleteTextures glDeleteTextures;
pfnglDepthFunc glDepthFunc;
pfnglDepthMask glDepthMask;
pfnglDepthRange glDepthRange;
pfnglDisable glDisable;
pfnglDisableClientState glDisableClientState;
pfnglDrawArrays glDrawArrays;
pfnglDrawBuffer glDrawBuffer;
pfnglDrawElements glDrawElements;
pfnglDrawPixels glDrawPixels;
pfnglEdgeFlag glEdgeFlag;
pfnglEdgeFlagPointer glEdgeFlagPointer;
pfnglEdgeFlagv glEdgeFlagv;
pfnglEnable glEnable;
pfnglEnableClientState glEnableClientState;
pfnglEnd glEnd;
pfnglEndList glEndList;
pfnglEvalCoord1d glEvalCoord1d;
pfnglEvalCoord1dv glEvalCoord1dv;
pfnglEvalCoord1f glEvalCoord1f;
pfnglEvalCoord1fv glEvalCoord1fv;
pfnglEvalCoord2d glEvalCoord2d;
pfnglEvalCoord2dv glEvalCoord2dv;
pfnglEvalCoord2f glEvalCoord2f;
pfnglEvalCoord2fv glEvalCoord2fv;
pfnglEvalMesh1 glEvalMesh1;
pfnglEvalMesh2 glEvalMesh2;
pfnglEvalPoint1 glEvalPoint1;
pfnglEvalPoint2 glEvalPoint2;
pfnglFeedbackBuffer glFeedbackBuffer;
pfnglFinish glFinish;
pfnglFlush glFlush;
pfnglFogf glFogf;
pfnglFogfv glFogfv;
pfnglFogi glFogi;
pfnglFogiv glFogiv;
pfnglFrontFace glFrontFace;
pfnglFrustum glFrustum;
pfnglGenLists glGenLists;
pfnglGenTextures glGenTextures;
pfnglGetBooleanv glGetBooleanv;
pfnglGetClipPlane glGetClipPlane;
pfnglGetDoublev glGetDoublev;
pfnglGetError glGetError;
pfnglGetFloatv glGetFloatv;
pfnglGetIntegerv glGetIntegerv;
pfnglGetLightfv glGetLightfv;
pfnglGetLightiv glGetLightiv;
pfnglGetMapdv glGetMapdv;
pfnglGetMapfv glGetMapfv;
pfnglGetMapiv glGetMapiv;
pfnglGetMaterialfv glGetMaterialfv;
pfnglGetMaterialiv glGetMaterialiv;
pfnglGetPixelMapfv glGetPixelMapfv;
pfnglGetPixelMapuiv glGetPixelMapuiv;
pfnglGetPixelMapusv glGetPixelMapusv;
pfnglGetPointerv glGetPointerv;
pfnglGetPolygonStipple glGetPolygonStipple;
pfnglGetString glGetString;
pfnglGetTexEnvfv glGetTexEnvfv;
pfnglGetTexEnviv glGetTexEnviv;
pfnglGetTexGendv glGetTexGendv;
pfnglGetTexGenfv glGetTexGenfv;
pfnglGetTexGeniv glGetTexGeniv;
pfnglGetTexImage glGetTexImage;
pfnglGetTexLevelParameterfv glGetTexLevelParameterfv;
pfnglGetTexLevelParameteriv glGetTexLevelParameteriv;
pfnglGetTexParameterfv glGetTexParameterfv;
pfnglGetTexParameteriv glGetTexParameteriv;
pfnglHint glHint;
pfnglIndexd glIndexd;
pfnglIndexdv glIndexdv;
pfnglIndexf glIndexf;
pfnglIndexfv glIndexfv;
pfnglIndexi glIndexi;
pfnglIndexiv glIndexiv;
pfnglIndexMask glIndexMask;
pfnglIndexPointer glIndexPointer;
pfnglIndexs glIndexs;
pfnglIndexsv glIndexsv;
pfnglIndexub glIndexub;
pfnglIndexubv glIndexubv;
pfnglInitNames glInitNames;
pfnglInterleavedArrays glInterleavedArrays;
pfnglIsEnabled glIsEnabled;
pfnglIsList glIsList;
pfnglIsTexture glIsTexture;
pfnglLightf glLightf;
pfnglLightfv glLightfv;
pfnglLighti glLighti;
pfnglLightiv glLightiv;
pfnglLightModelf glLightModelf;
pfnglLightModelfv glLightModelfv;
pfnglLightModeli glLightModeli;
pfnglLightModeliv glLightModeliv;
pfnglLineStipple glLineStipple;
pfnglLineWidth glLineWidth;
pfnglListBase glListBase;
pfnglLoadIdentity glLoadIdentity;
pfnglLoadMatrixd glLoadMatrixd;
pfnglLoadMatrixf glLoadMatrixf;
pfnglLoadName glLoadName;
pfnglLogicOp glLogicOp;
pfnglMap1d glMap1d;
pfnglMap1f glMap1f;
pfnglMap2d glMap2d;
pfnglMap2f glMap2f;
pfnglMapGrid1d glMapGrid1d;
pfnglMapGrid1f glMapGrid1f;
pfnglMapGrid2d glMapGrid2d;
pfnglMapGrid2f glMapGrid2f;
pfnglMaterialf glMaterialf;
pfnglMaterialfv glMaterialfv;
pfnglMateriali glMateriali;
pfnglMaterialiv glMaterialiv;
pfnglMatrixMode glMatrixMode;
pfnglMultMatrixd glMultMatrixd;
pfnglMultMatrixf glMultMatrixf;
pfnglNewList glNewList;
pfnglNormal3b glNormal3b;
pfnglNormal3bv glNormal3bv;
pfnglNormal3d glNormal3d;
pfnglNormal3dv glNormal3dv;
pfnglNormal3f glNormal3f;
pfnglNormal3fv glNormal3fv;
pfnglNormal3i glNormal3i;
pfnglNormal3iv glNormal3iv;
pfnglNormal3s glNormal3s;
pfnglNormal3sv glNormal3sv;
pfnglNormalPointer glNormalPointer;
pfnglOrtho glOrtho;
pfnglPassThrough glPassThrough;
pfnglPixelMapfv glPixelMapfv;
pfnglPixelMapuiv glPixelMapuiv;
pfnglPixelMapusv glPixelMapusv;
pfnglPixelStoref glPixelStoref;
pfnglPixelStorei glPixelStorei;
pfnglPixelTransferf glPixelTransferf;
pfnglPixelTransferi glPixelTransferi;
pfnglPixelZoom glPixelZoom;
pfnglPointSize glPointSize;
pfnglPolygonMode glPolygonMode;
pfnglPolygonOffset glPolygonOffset;
pfnglPolygonStipple glPolygonStipple;
pfnglPopAttrib glPopAttrib;
pfnglPopClientAttrib glPopClientAttrib;
pfnglPopMatrix glPopMatrix;
pfnglPopName glPopName;
pfnglPrioritizeTextures glPrioritizeTextures;
pfnglPushAttrib glPushAttrib;
pfnglPushClientAttrib glPushClientAttrib;
pfnglPushMatrix glPushMatrix;
pfnglPushName glPushName;
pfnglRasterPos2d glRasterPos2d;
pfnglRasterPos2dv glRasterPos2dv;
pfnglRasterPos2f glRasterPos2f;
pfnglRasterPos2fv glRasterPos2fv;
pfnglRasterPos2i glRasterPos2i;
pfnglRasterPos2iv glRasterPos2iv;
pfnglRasterPos2s glRasterPos2s;
pfnglRasterPos2sv glRasterPos2sv;
pfnglRasterPos3d glRasterPos3d;
pfnglRasterPos3dv glRasterPos3dv;
pfnglRasterPos3f glRasterPos3f;
pfnglRasterPos3fv glRasterPos3fv;
pfnglRasterPos3i glRasterPos3i;
pfnglRasterPos3iv glRasterPos3iv;
pfnglRasterPos3s glRasterPos3s;
pfnglRasterPos3sv glRasterPos3sv;
pfnglRasterPos4d glRasterPos4d;
pfnglRasterPos4dv glRasterPos4dv;
pfnglRasterPos4f glRasterPos4f;
pfnglRasterPos4fv glRasterPos4fv;
pfnglRasterPos4i glRasterPos4i;
pfnglRasterPos4iv glRasterPos4iv;
pfnglRasterPos4s glRasterPos4s;
pfnglRasterPos4sv glRasterPos4sv;
pfnglReadBuffer glReadBuffer;
pfnglReadPixels glReadPixels;
pfnglRectd glRectd;
pfnglRectdv glRectdv;
pfnglRectf glRectf;
pfnglRectfv glRectfv;
pfnglRecti glRecti;
pfnglRectiv glRectiv;
pfnglRects glRects;
pfnglRectsv glRectsv;
pfnglRenderMode glRenderMode;
pfnglRotated glRotated;
pfnglRotatef glRotatef;
pfnglScaled glScaled;
pfnglScalef glScalef;
pfnglScissor glScissor;
pfnglSelectBuffer glSelectBuffer;
pfnglShadeModel glShadeModel;
pfnglStencilFunc glStencilFunc;
pfnglStencilMask glStencilMask;
pfnglStencilOp glStencilOp;
pfnglTexCoord1d glTexCoord1d;
pfnglTexCoord1dv glTexCoord1dv;
pfnglTexCoord1f glTexCoord1f;
pfnglTexCoord1fv glTexCoord1fv;
pfnglTexCoord1i glTexCoord1i;
pfnglTexCoord1iv glTexCoord1iv;
pfnglTexCoord1s glTexCoord1s;
pfnglTexCoord1sv glTexCoord1sv;
pfnglTexCoord2d glTexCoord2d;
pfnglTexCoord2dv glTexCoord2dv;
pfnglTexCoord2f glTexCoord2f;
pfnglTexCoord2fv glTexCoord2fv;
pfnglTexCoord2i glTexCoord2i;
pfnglTexCoord2iv glTexCoord2iv;
pfnglTexCoord2s glTexCoord2s;
pfnglTexCoord2sv glTexCoord2sv;
pfnglTexCoord3d glTexCoord3d;
pfnglTexCoord3dv glTexCoord3dv;
pfnglTexCoord3f glTexCoord3f;
pfnglTexCoord3fv glTexCoord3fv;
pfnglTexCoord3i glTexCoord3i;
pfnglTexCoord3iv glTexCoord3iv;
pfnglTexCoord3s glTexCoord3s;
pfnglTexCoord3sv glTexCoord3sv;
pfnglTexCoord4d glTexCoord4d;
pfnglTexCoord4dv glTexCoord4dv;
pfnglTexCoord4f glTexCoord4f;
pfnglTexCoord4fv glTexCoord4fv;
pfnglTexCoord4i glTexCoord4i;
pfnglTexCoord4iv glTexCoord4iv;
pfnglTexCoord4s glTexCoord4s;
pfnglTexCoord4sv glTexCoord4sv;
pfnglTexCoordPointer glTexCoordPointer;
pfnglTexEnvf glTexEnvf;
pfnglTexEnvfv glTexEnvfv;
pfnglTexEnvi glTexEnvi;
pfnglTexEnviv glTexEnviv;
pfnglTexGend glTexGend;
pfnglTexGendv glTexGendv;
pfnglTexGenf glTexGenf;
pfnglTexGenfv glTexGenfv;
pfnglTexGeni glTexGeni;
pfnglTexGeniv glTexGeniv;
pfnglTexImage1D glTexImage1D;
pfnglTexImage2D glTexImage2D;
pfnglTexParameterf glTexParameterf;
pfnglTexParameterfv glTexParameterfv;
pfnglTexParameteri glTexParameteri;
pfnglTexParameteriv glTexParameteriv;
pfnglTexSubImage1D glTexSubImage1D;
pfnglTexSubImage2D glTexSubImage2D;
pfnglTranslated glTranslated;
pfnglTranslatef glTranslatef;
pfnglVertex2d glVertex2d;
pfnglVertex2dv glVertex2dv;
pfnglVertex2f glVertex2f;
pfnglVertex2fv glVertex2fv;
pfnglVertex2i glVertex2i;
pfnglVertex2iv glVertex2iv;
pfnglVertex2s glVertex2s;
pfnglVertex2sv glVertex2sv;
pfnglVertex3d glVertex3d;
pfnglVertex3dv glVertex3dv;
pfnglVertex3f glVertex3f;
pfnglVertex3fv glVertex3fv;
pfnglVertex3i glVertex3i;
pfnglVertex3iv glVertex3iv;
pfnglVertex3s glVertex3s;
pfnglVertex3sv glVertex3sv;
pfnglVertex4d glVertex4d;
pfnglVertex4dv glVertex4dv;
pfnglVertex4f glVertex4f;
pfnglVertex4fv glVertex4fv;
pfnglVertex4i glVertex4i;
pfnglVertex4iv glVertex4iv;
pfnglVertex4s glVertex4s;
pfnglVertex4sv glVertex4sv;
pfnglVertexPointer glVertexPointer;
pfnglViewport glViewport;

pfnwglCopyContext dynwglCopyContext;
pfnwglCreateContext dynwglCreateContext;
pfnwglCreateLayerContext dynwglCreateLayerContext;
pfnwglDeleteContext dynwglDeleteContext;
pfnwglGetCurrentContext dynwglGetCurrentContext;
pfnwglGetCurrentDC dynwglGetCurrentDC;
pfnwglGetProcAddress dynwglGetProcAddress;
pfnwglMakeCurrent dynwglMakeCurrent;
pfnwglShareLists dynwglShareLists;
pfnwglSwapBuffers dynwglSwapBuffers;
pfnwglUseFontBitmapsA dynwglUseFontBitmapsA;
pfnwglUseFontBitmapsW dynwglUseFontBitmapsW;

pfnwglGetPixelFormat dynwglGetPixelFormat;
pfnwglSetPixelFormat dynwglSetPixelFormat;
pfnwglDescribePixelFormat dynwglDescribePixelFormat;
pfnwglChoosePixelFormat dynwglChoosePixelFormat;


static int nInitMode = 0;

void WINAPI
SafeProc(void)
{
 OutputDebugString("GL function called after deintialization\n");
 while (1);
}

static PROC
GetGLProcAddr(char *pszProcName)
{
 if (nInitMode)
    return (PROC)SafeProc;
 else
    return GetProcAddress(hOpenGLDLL, pszProcName);
}

static PROC
GetEXProcAddr(char *pszProcName)
{
 
 if (nInitMode)
    return (PROC)SafeProc;
 else
    return dynwglGetProcAddress(pszProcName);
}

#define GETADDR(type, var, name) var = (type)GetGLProcAddr(name)
#define GETEXADDR(type, var, name) var = (type)GetEXProcAddr(name)

static void SetProcs(void)
{
GETADDR(pfnglAccum,glAccum,"glAccum");
GETADDR(pfnglAlphaFunc,glAlphaFunc,"glAlphaFunc");
GETADDR(pfnglAreTexturesResident,glAreTexturesResident,"glAreTexturesResident");
GETADDR(pfnglArrayElement,glArrayElement,"glArrayElement");
GETADDR(pfnglBegin,glBegin,"glBegin");
GETADDR(pfnglBindTexture,glBindTexture,"glBindTexture");
GETADDR(pfnglBitmap,glBitmap,"glBitmap");
GETADDR(pfnglBlendFunc,glBlendFunc,"glBlendFunc");
GETADDR(pfnglCallList,glCallList,"glCallList");
GETADDR(pfnglCallLists,glCallLists,"glCallLists");
GETADDR(pfnglClear,glClear,"glClear");
GETADDR(pfnglClearAccum,glClearAccum,"glClearAccum");
GETADDR(pfnglClearColor,glClearColor,"glClearColor");
GETADDR(pfnglClearDepth,glClearDepth,"glClearDepth");
GETADDR(pfnglClearIndex,glClearIndex,"glClearIndex");
GETADDR(pfnglClearStencil,glClearStencil,"glClearStencil");
GETADDR(pfnglClipPlane,glClipPlane,"glClipPlane");
GETADDR(pfnglColor3b,glColor3b,"glColor3b");
GETADDR(pfnglColor3bv,glColor3bv,"glColor3bv");
GETADDR(pfnglColor3d,glColor3d,"glColor3d");
GETADDR(pfnglColor3dv,glColor3dv,"glColor3dv");
GETADDR(pfnglColor3f,glColor3f,"glColor3f");
GETADDR(pfnglColor3fv,glColor3fv,"glColor3fv");
GETADDR(pfnglColor3i,glColor3i,"glColor3i");
GETADDR(pfnglColor3iv,glColor3iv,"glColor3iv");
GETADDR(pfnglColor3s,glColor3s,"glColor3s");
GETADDR(pfnglColor3sv,glColor3sv,"glColor3sv");
GETADDR(pfnglColor3ub,glColor3ub,"glColor3ub");
GETADDR(pfnglColor3ubv,glColor3ubv,"glColor3ubv");
GETADDR(pfnglColor3ui,glColor3ui,"glColor3ui");
GETADDR(pfnglColor3uiv,glColor3uiv,"glColor3uiv");
GETADDR(pfnglColor3us,glColor3us,"glColor3us");
GETADDR(pfnglColor3usv,glColor3usv,"glColor3usv");
GETADDR(pfnglColor4b,glColor4b,"glColor4b");
GETADDR(pfnglColor4bv,glColor4bv,"glColor4bv");
GETADDR(pfnglColor4d,glColor4d,"glColor4d");
GETADDR(pfnglColor4dv,glColor4dv,"glColor4dv");
GETADDR(pfnglColor4f,glColor4f,"glColor4f");
GETADDR(pfnglColor4fv,glColor4fv,"glColor4fv");
GETADDR(pfnglColor4i,glColor4i,"glColor4i");
GETADDR(pfnglColor4iv,glColor4iv,"glColor4iv");
GETADDR(pfnglColor4s,glColor4s,"glColor4s");
GETADDR(pfnglColor4sv,glColor4sv,"glColor4sv");
GETADDR(pfnglColor4ub,glColor4ub,"glColor4ub");
GETADDR(pfnglColor4ubv,glColor4ubv,"glColor4ubv");
GETADDR(pfnglColor4ui,glColor4ui,"glColor4ui");
GETADDR(pfnglColor4uiv,glColor4uiv,"glColor4uiv");
GETADDR(pfnglColor4us,glColor4us,"glColor4us");
GETADDR(pfnglColor4usv,glColor4usv,"glColor4usv");
GETADDR(pfnglColorMask,glColorMask,"glColorMask");
GETADDR(pfnglColorMaterial,glColorMaterial,"glColorMaterial");
GETADDR(pfnglColorPointer,glColorPointer,"glColorPointer");
GETADDR(pfnglCopyPixels,glCopyPixels,"glCopyPixels");
GETADDR(pfnglCopyTexImage1D,glCopyTexImage1D,"glCopyTexImage1D");
GETADDR(pfnglCopyTexImage2D,glCopyTexImage2D,"glCopyTexImage2D");
GETADDR(pfnglCopyTexSubImage1D,glCopyTexSubImage1D,"glCopyTexSubImage1D");
GETADDR(pfnglCopyTexSubImage2D,glCopyTexSubImage2D,"glCopyTexSubImage2D");
GETADDR(pfnglCullFace,glCullFace,"glCullFace");
GETADDR(pfnglDeleteLists,glDeleteLists,"glDeleteLists");
GETADDR(pfnglDeleteTextures,glDeleteTextures,"glDeleteTextures");
GETADDR(pfnglDepthFunc,glDepthFunc,"glDepthFunc");
GETADDR(pfnglDepthMask,glDepthMask,"glDepthMask");
GETADDR(pfnglDepthRange,glDepthRange,"glDepthRange");
GETADDR(pfnglDisable,glDisable,"glDisable");
GETADDR(pfnglDisableClientState,glDisableClientState,"glDisableClientState");
GETADDR(pfnglDrawArrays,glDrawArrays,"glDrawArrays");
GETADDR(pfnglDrawBuffer,glDrawBuffer,"glDrawBuffer");
GETADDR(pfnglDrawElements,glDrawElements,"glDrawElements");
GETADDR(pfnglDrawPixels,glDrawPixels,"glDrawPixels");
GETADDR(pfnglEdgeFlag,glEdgeFlag,"glEdgeFlag");
GETADDR(pfnglEdgeFlagPointer,glEdgeFlagPointer,"glEdgeFlagPointer");
GETADDR(pfnglEdgeFlagv,glEdgeFlagv,"glEdgeFlagv");
GETADDR(pfnglEnable,glEnable,"glEnable");
GETADDR(pfnglEnableClientState,glEnableClientState,"glEnableClientState");
GETADDR(pfnglEnd,glEnd,"glEnd");
GETADDR(pfnglEndList,glEndList,"glEndList");
GETADDR(pfnglEvalCoord1d,glEvalCoord1d,"glEvalCoord1d");
GETADDR(pfnglEvalCoord1dv,glEvalCoord1dv,"glEvalCoord1dv");
GETADDR(pfnglEvalCoord1f,glEvalCoord1f,"glEvalCoord1f");
GETADDR(pfnglEvalCoord1fv,glEvalCoord1fv,"glEvalCoord1fv");
GETADDR(pfnglEvalCoord2d,glEvalCoord2d,"glEvalCoord2d");
GETADDR(pfnglEvalCoord2dv,glEvalCoord2dv,"glEvalCoord2dv");
GETADDR(pfnglEvalCoord2f,glEvalCoord2f,"glEvalCoord2f");
GETADDR(pfnglEvalCoord2fv,glEvalCoord2fv,"glEvalCoord2fv");
GETADDR(pfnglEvalMesh1,glEvalMesh1,"glEvalMesh1");
GETADDR(pfnglEvalMesh2,glEvalMesh2,"glEvalMesh2");
GETADDR(pfnglEvalPoint1,glEvalPoint1,"glEvalPoint1");
GETADDR(pfnglEvalPoint2,glEvalPoint2,"glEvalPoint2");
GETADDR(pfnglFeedbackBuffer,glFeedbackBuffer,"glFeedbackBuffer");
GETADDR(pfnglFinish,glFinish,"glFinish");
GETADDR(pfnglFlush,glFlush,"glFlush");
GETADDR(pfnglFogf,glFogf,"glFogf");
GETADDR(pfnglFogfv,glFogfv,"glFogfv");
GETADDR(pfnglFogi,glFogi,"glFogi");
GETADDR(pfnglFogiv,glFogiv,"glFogiv");
GETADDR(pfnglFrontFace,glFrontFace,"glFrontFace");
GETADDR(pfnglFrustum,glFrustum,"glFrustum");
GETADDR(pfnglGenLists,glGenLists,"glGenLists");
GETADDR(pfnglGenTextures,glGenTextures,"glGenTextures");
GETADDR(pfnglGetBooleanv,glGetBooleanv,"glGetBooleanv");
GETADDR(pfnglGetClipPlane,glGetClipPlane,"glGetClipPlane");
GETADDR(pfnglGetDoublev,glGetDoublev,"glGetDoublev");
GETADDR(pfnglGetError,glGetError,"glGetError");
GETADDR(pfnglGetFloatv,glGetFloatv,"glGetFloatv");
GETADDR(pfnglGetIntegerv,glGetIntegerv,"glGetIntegerv");
GETADDR(pfnglGetLightfv,glGetLightfv,"glGetLightfv");
GETADDR(pfnglGetLightiv,glGetLightiv,"glGetLightiv");
GETADDR(pfnglGetMapdv,glGetMapdv,"glGetMapdv");
GETADDR(pfnglGetMapfv,glGetMapfv,"glGetMapfv");
GETADDR(pfnglGetMapiv,glGetMapiv,"glGetMapiv");
GETADDR(pfnglGetMaterialfv,glGetMaterialfv,"glGetMaterialfv");
GETADDR(pfnglGetMaterialiv,glGetMaterialiv,"glGetMaterialiv");
GETADDR(pfnglGetPixelMapfv,glGetPixelMapfv,"glGetPixelMapfv");
GETADDR(pfnglGetPixelMapuiv,glGetPixelMapuiv,"glGetPixelMapuiv");
GETADDR(pfnglGetPixelMapusv,glGetPixelMapusv,"glGetPixelMapusv");
GETADDR(pfnglGetPointerv,glGetPointerv,"glGetPointerv");
GETADDR(pfnglGetPolygonStipple,glGetPolygonStipple,"glGetPolygonStipple");
GETADDR(pfnglGetString,glGetString,"glGetString");
GETADDR(pfnglGetTexEnvfv,glGetTexEnvfv,"glGetTexEnvfv");
GETADDR(pfnglGetTexEnviv,glGetTexEnviv,"glGetTexEnviv");
GETADDR(pfnglGetTexGendv,glGetTexGendv,"glGetTexGendv");
GETADDR(pfnglGetTexGenfv,glGetTexGenfv,"glGetTexGenfv");
GETADDR(pfnglGetTexGeniv,glGetTexGeniv,"glGetTexGeniv");
GETADDR(pfnglGetTexImage,glGetTexImage,"glGetTexImage");
GETADDR(pfnglGetTexLevelParameterfv,glGetTexLevelParameterfv,"glGetTexLevelParameterfv");
GETADDR(pfnglGetTexLevelParameteriv,glGetTexLevelParameteriv,"glGetTexLevelParameteriv");
GETADDR(pfnglGetTexParameterfv,glGetTexParameterfv,"glGetTexParameterfv");
GETADDR(pfnglGetTexParameteriv,glGetTexParameteriv,"glGetTexParameteriv");
GETADDR(pfnglHint,glHint,"glHint");
GETADDR(pfnglIndexd,glIndexd,"glIndexd");
GETADDR(pfnglIndexdv,glIndexdv,"glIndexdv");
GETADDR(pfnglIndexf,glIndexf,"glIndexf");
GETADDR(pfnglIndexfv,glIndexfv,"glIndexfv");
GETADDR(pfnglIndexi,glIndexi,"glIndexi");
GETADDR(pfnglIndexiv,glIndexiv,"glIndexiv");
GETADDR(pfnglIndexMask,glIndexMask,"glIndexMask");
GETADDR(pfnglIndexPointer,glIndexPointer,"glIndexPointer");
GETADDR(pfnglIndexs,glIndexs,"glIndexs");
GETADDR(pfnglIndexsv,glIndexsv,"glIndexsv");
GETADDR(pfnglIndexub,glIndexub,"glIndexub");
GETADDR(pfnglIndexubv,glIndexubv,"glIndexubv");
GETADDR(pfnglInitNames,glInitNames,"glInitNames");
GETADDR(pfnglInterleavedArrays,glInterleavedArrays,"glInterleavedArrays");
GETADDR(pfnglIsEnabled,glIsEnabled,"glIsEnabled");
GETADDR(pfnglIsList,glIsList,"glIsList");
GETADDR(pfnglIsTexture,glIsTexture,"glIsTexture");
GETADDR(pfnglLightf,glLightf,"glLightf");
GETADDR(pfnglLightfv,glLightfv,"glLightfv");
GETADDR(pfnglLighti,glLighti,"glLighti");
GETADDR(pfnglLightiv,glLightiv,"glLightiv");
GETADDR(pfnglLightModelf,glLightModelf,"glLightModelf");
GETADDR(pfnglLightModelfv,glLightModelfv,"glLightModelfv");
GETADDR(pfnglLightModeli,glLightModeli,"glLightModeli");
GETADDR(pfnglLightModeliv,glLightModeliv,"glLightModeliv");
GETADDR(pfnglLineStipple,glLineStipple,"glLineStipple");
GETADDR(pfnglLineWidth,glLineWidth,"glLineWidth");
GETADDR(pfnglListBase,glListBase,"glListBase");
GETADDR(pfnglLoadIdentity,glLoadIdentity,"glLoadIdentity");
GETADDR(pfnglLoadMatrixd,glLoadMatrixd,"glLoadMatrixd");
GETADDR(pfnglLoadMatrixf,glLoadMatrixf,"glLoadMatrixf");
GETADDR(pfnglLoadName,glLoadName,"glLoadName");
GETADDR(pfnglLogicOp,glLogicOp,"glLogicOp");
GETADDR(pfnglMap1d,glMap1d,"glMap1d");
GETADDR(pfnglMap1f,glMap1f,"glMap1f");
GETADDR(pfnglMap2d,glMap2d,"glMap2d");
GETADDR(pfnglMap2f,glMap2f,"glMap2f");
GETADDR(pfnglMapGrid1d,glMapGrid1d,"glMapGrid1d");
GETADDR(pfnglMapGrid1f,glMapGrid1f,"glMapGrid1f");
GETADDR(pfnglMapGrid2d,glMapGrid2d,"glMapGrid2d");
GETADDR(pfnglMapGrid2f,glMapGrid2f,"glMapGrid2f");
GETADDR(pfnglMaterialf,glMaterialf,"glMaterialf");
GETADDR(pfnglMaterialfv,glMaterialfv,"glMaterialfv");
GETADDR(pfnglMateriali,glMateriali,"glMateriali");
GETADDR(pfnglMaterialiv,glMaterialiv,"glMaterialiv");
GETADDR(pfnglMatrixMode,glMatrixMode,"glMatrixMode");
GETADDR(pfnglMultMatrixd,glMultMatrixd,"glMultMatrixd");
GETADDR(pfnglMultMatrixf,glMultMatrixf,"glMultMatrixf");
GETADDR(pfnglNewList,glNewList,"glNewList");
GETADDR(pfnglNormal3b,glNormal3b,"glNormal3b");
GETADDR(pfnglNormal3bv,glNormal3bv,"glNormal3bv");
GETADDR(pfnglNormal3d,glNormal3d,"glNormal3d");
GETADDR(pfnglNormal3dv,glNormal3dv,"glNormal3dv");
GETADDR(pfnglNormal3f,glNormal3f,"glNormal3f");
GETADDR(pfnglNormal3fv,glNormal3fv,"glNormal3fv");
GETADDR(pfnglNormal3i,glNormal3i,"glNormal3i");
GETADDR(pfnglNormal3iv,glNormal3iv,"glNormal3iv");
GETADDR(pfnglNormal3s,glNormal3s,"glNormal3s");
GETADDR(pfnglNormal3sv,glNormal3sv,"glNormal3sv");
GETADDR(pfnglNormalPointer,glNormalPointer,"glNormalPointer");
GETADDR(pfnglOrtho,glOrtho,"glOrtho");
GETADDR(pfnglPassThrough,glPassThrough,"glPassThrough");
GETADDR(pfnglPixelMapfv,glPixelMapfv,"glPixelMapfv");
GETADDR(pfnglPixelMapuiv,glPixelMapuiv,"glPixelMapuiv");
GETADDR(pfnglPixelMapusv,glPixelMapusv,"glPixelMapusv");
GETADDR(pfnglPixelStoref,glPixelStoref,"glPixelStoref");
GETADDR(pfnglPixelStorei,glPixelStorei,"glPixelStorei");
GETADDR(pfnglPixelTransferf,glPixelTransferf,"glPixelTransferf");
GETADDR(pfnglPixelTransferi,glPixelTransferi,"glPixelTransferi");
GETADDR(pfnglPixelZoom,glPixelZoom,"glPixelZoom");
GETADDR(pfnglPointSize,glPointSize,"glPointSize");
GETADDR(pfnglPolygonMode,glPolygonMode,"glPolygonMode");
GETADDR(pfnglPolygonOffset,glPolygonOffset,"glPolygonOffset");
GETADDR(pfnglPolygonStipple,glPolygonStipple,"glPolygonStipple");
GETADDR(pfnglPopAttrib,glPopAttrib,"glPopAttrib");
GETADDR(pfnglPopClientAttrib,glPopClientAttrib,"glPopClientAttrib");
GETADDR(pfnglPopMatrix,glPopMatrix,"glPopMatrix");
GETADDR(pfnglPopName,glPopName,"glPopName");
GETADDR(pfnglPrioritizeTextures,glPrioritizeTextures,"glPrioritizeTextures");
GETADDR(pfnglPushAttrib,glPushAttrib,"glPushAttrib");
GETADDR(pfnglPushClientAttrib,glPushClientAttrib,"glPushClientAttrib");
GETADDR(pfnglPushMatrix,glPushMatrix,"glPushMatrix");
GETADDR(pfnglPushName,glPushName,"glPushName");
GETADDR(pfnglRasterPos2d,glRasterPos2d,"glRasterPos2d");
GETADDR(pfnglRasterPos2dv,glRasterPos2dv,"glRasterPos2dv");
GETADDR(pfnglRasterPos2f,glRasterPos2f,"glRasterPos2f");
GETADDR(pfnglRasterPos2fv,glRasterPos2fv,"glRasterPos2fv");
GETADDR(pfnglRasterPos2i,glRasterPos2i,"glRasterPos2i");
GETADDR(pfnglRasterPos2iv,glRasterPos2iv,"glRasterPos2iv");
GETADDR(pfnglRasterPos2s,glRasterPos2s,"glRasterPos2s");
GETADDR(pfnglRasterPos2sv,glRasterPos2sv,"glRasterPos2sv");
GETADDR(pfnglRasterPos3d,glRasterPos3d,"glRasterPos3d");
GETADDR(pfnglRasterPos3dv,glRasterPos3dv,"glRasterPos3dv");
GETADDR(pfnglRasterPos3f,glRasterPos3f,"glRasterPos3f");
GETADDR(pfnglRasterPos3fv,glRasterPos3fv,"glRasterPos3fv");
GETADDR(pfnglRasterPos3i,glRasterPos3i,"glRasterPos3i");
GETADDR(pfnglRasterPos3iv,glRasterPos3iv,"glRasterPos3iv");
GETADDR(pfnglRasterPos3s,glRasterPos3s,"glRasterPos3s");
GETADDR(pfnglRasterPos3sv,glRasterPos3sv,"glRasterPos3sv");
GETADDR(pfnglRasterPos4d,glRasterPos4d,"glRasterPos4d");
GETADDR(pfnglRasterPos4dv,glRasterPos4dv,"glRasterPos4dv");
GETADDR(pfnglRasterPos4f,glRasterPos4f,"glRasterPos4f");
GETADDR(pfnglRasterPos4fv,glRasterPos4fv,"glRasterPos4fv");
GETADDR(pfnglRasterPos4i,glRasterPos4i,"glRasterPos4i");
GETADDR(pfnglRasterPos4iv,glRasterPos4iv,"glRasterPos4iv");
GETADDR(pfnglRasterPos4s,glRasterPos4s,"glRasterPos4s");
GETADDR(pfnglRasterPos4sv,glRasterPos4sv,"glRasterPos4sv");
GETADDR(pfnglReadBuffer,glReadBuffer,"glReadBuffer");
GETADDR(pfnglReadPixels,glReadPixels,"glReadPixels");
GETADDR(pfnglRectd,glRectd,"glRectd");
GETADDR(pfnglRectdv,glRectdv,"glRectdv");
GETADDR(pfnglRectf,glRectf,"glRectf");
GETADDR(pfnglRectfv,glRectfv,"glRectfv");
GETADDR(pfnglRecti,glRecti,"glRecti");
GETADDR(pfnglRectiv,glRectiv,"glRectiv");
GETADDR(pfnglRects,glRects,"glRects");
GETADDR(pfnglRectsv,glRectsv,"glRectsv");
GETADDR(pfnglRenderMode,glRenderMode,"glRenderMode");
GETADDR(pfnglRotated,glRotated,"glRotated");
GETADDR(pfnglRotatef,glRotatef,"glRotatef");
GETADDR(pfnglScaled,glScaled,"glScaled");
GETADDR(pfnglScalef,glScalef,"glScalef");
GETADDR(pfnglScissor,glScissor,"glScissor");
GETADDR(pfnglSelectBuffer,glSelectBuffer,"glSelectBuffer");
GETADDR(pfnglShadeModel,glShadeModel,"glShadeModel");
GETADDR(pfnglStencilFunc,glStencilFunc,"glStencilFunc");
GETADDR(pfnglStencilMask,glStencilMask,"glStencilMask");
GETADDR(pfnglStencilOp,glStencilOp,"glStencilOp");
GETADDR(pfnglTexCoord1d,glTexCoord1d,"glTexCoord1d");
GETADDR(pfnglTexCoord1dv,glTexCoord1dv,"glTexCoord1dv");
GETADDR(pfnglTexCoord1f,glTexCoord1f,"glTexCoord1f");
GETADDR(pfnglTexCoord1fv,glTexCoord1fv,"glTexCoord1fv");
GETADDR(pfnglTexCoord1i,glTexCoord1i,"glTexCoord1i");
GETADDR(pfnglTexCoord1iv,glTexCoord1iv,"glTexCoord1iv");
GETADDR(pfnglTexCoord1s,glTexCoord1s,"glTexCoord1s");
GETADDR(pfnglTexCoord1sv,glTexCoord1sv,"glTexCoord1sv");
GETADDR(pfnglTexCoord2d,glTexCoord2d,"glTexCoord2d");
GETADDR(pfnglTexCoord2dv,glTexCoord2dv,"glTexCoord2dv");
GETADDR(pfnglTexCoord2f,glTexCoord2f,"glTexCoord2f");
GETADDR(pfnglTexCoord2fv,glTexCoord2fv,"glTexCoord2fv");
GETADDR(pfnglTexCoord2i,glTexCoord2i,"glTexCoord2i");
GETADDR(pfnglTexCoord2iv,glTexCoord2iv,"glTexCoord2iv");
GETADDR(pfnglTexCoord2s,glTexCoord2s,"glTexCoord2s");
GETADDR(pfnglTexCoord2sv,glTexCoord2sv,"glTexCoord2sv");
GETADDR(pfnglTexCoord3d,glTexCoord3d,"glTexCoord3d");
GETADDR(pfnglTexCoord3dv,glTexCoord3dv,"glTexCoord3dv");
GETADDR(pfnglTexCoord3f,glTexCoord3f,"glTexCoord3f");
GETADDR(pfnglTexCoord3fv,glTexCoord3fv,"glTexCoord3fv");
GETADDR(pfnglTexCoord3i,glTexCoord3i,"glTexCoord3i");
GETADDR(pfnglTexCoord3iv,glTexCoord3iv,"glTexCoord3iv");
GETADDR(pfnglTexCoord3s,glTexCoord3s,"glTexCoord3s");
GETADDR(pfnglTexCoord3sv,glTexCoord3sv,"glTexCoord3sv");
GETADDR(pfnglTexCoord4d,glTexCoord4d,"glTexCoord4d");
GETADDR(pfnglTexCoord4dv,glTexCoord4dv,"glTexCoord4dv");
GETADDR(pfnglTexCoord4f,glTexCoord4f,"glTexCoord4f");
GETADDR(pfnglTexCoord4fv,glTexCoord4fv,"glTexCoord4fv");
GETADDR(pfnglTexCoord4i,glTexCoord4i,"glTexCoord4i");
GETADDR(pfnglTexCoord4iv,glTexCoord4iv,"glTexCoord4iv");
GETADDR(pfnglTexCoord4s,glTexCoord4s,"glTexCoord4s");
GETADDR(pfnglTexCoord4sv,glTexCoord4sv,"glTexCoord4sv");
GETADDR(pfnglTexCoordPointer,glTexCoordPointer,"glTexCoordPointer");
GETADDR(pfnglTexEnvf,glTexEnvf,"glTexEnvf");
GETADDR(pfnglTexEnvfv,glTexEnvfv,"glTexEnvfv");
GETADDR(pfnglTexEnvi,glTexEnvi,"glTexEnvi");
GETADDR(pfnglTexEnviv,glTexEnviv,"glTexEnviv");
GETADDR(pfnglTexGend,glTexGend,"glTexGend");
GETADDR(pfnglTexGendv,glTexGendv,"glTexGendv");
GETADDR(pfnglTexGenf,glTexGenf,"glTexGenf");
GETADDR(pfnglTexGenfv,glTexGenfv,"glTexGenfv");
GETADDR(pfnglTexGeni,glTexGeni,"glTexGeni");
GETADDR(pfnglTexGeniv,glTexGeniv,"glTexGeniv");
GETADDR(pfnglTexImage1D,glTexImage1D,"glTexImage1D");
GETADDR(pfnglTexImage2D,glTexImage2D,"glTexImage2D");
GETADDR(pfnglTexParameterf,glTexParameterf,"glTexParameterf");
GETADDR(pfnglTexParameterfv,glTexParameterfv,"glTexParameterfv");
GETADDR(pfnglTexParameteri,glTexParameteri,"glTexParameteri");
GETADDR(pfnglTexParameteriv,glTexParameteriv,"glTexParameteriv");
GETADDR(pfnglTexSubImage1D,glTexSubImage1D,"glTexSubImage1D");
GETADDR(pfnglTexSubImage2D,glTexSubImage2D,"glTexSubImage2D");
GETADDR(pfnglTranslated,glTranslated,"glTranslated");
GETADDR(pfnglTranslatef,glTranslatef,"glTranslatef");
GETADDR(pfnglVertex2d,glVertex2d,"glVertex2d");
GETADDR(pfnglVertex2dv,glVertex2dv,"glVertex2dv");
GETADDR(pfnglVertex2f,glVertex2f,"glVertex2f");
GETADDR(pfnglVertex2fv,glVertex2fv,"glVertex2fv");
GETADDR(pfnglVertex2i,glVertex2i,"glVertex2i");
GETADDR(pfnglVertex2iv,glVertex2iv,"glVertex2iv");
GETADDR(pfnglVertex2s,glVertex2s,"glVertex2s");
GETADDR(pfnglVertex2sv,glVertex2sv,"glVertex2sv");
GETADDR(pfnglVertex3d,glVertex3d,"glVertex3d");
GETADDR(pfnglVertex3dv,glVertex3dv,"glVertex3dv");
GETADDR(pfnglVertex3f,glVertex3f,"glVertex3f");
GETADDR(pfnglVertex3fv,glVertex3fv,"glVertex3fv");
GETADDR(pfnglVertex3i,glVertex3i,"glVertex3i");
GETADDR(pfnglVertex3iv,glVertex3iv,"glVertex3iv");
GETADDR(pfnglVertex3s,glVertex3s,"glVertex3s");
GETADDR(pfnglVertex3sv,glVertex3sv,"glVertex3sv");
GETADDR(pfnglVertex4d,glVertex4d,"glVertex4d");
GETADDR(pfnglVertex4dv,glVertex4dv,"glVertex4dv");
GETADDR(pfnglVertex4f,glVertex4f,"glVertex4f");
GETADDR(pfnglVertex4fv,glVertex4fv,"glVertex4fv");
GETADDR(pfnglVertex4i,glVertex4i,"glVertex4i");
GETADDR(pfnglVertex4iv,glVertex4iv,"glVertex4iv");
GETADDR(pfnglVertex4s,glVertex4s,"glVertex4s");
GETADDR(pfnglVertex4sv,glVertex4sv,"glVertex4sv");
GETADDR(pfnglVertexPointer,glVertexPointer,"glVertexPointer");
GETADDR(pfnglViewport,glViewport,"glViewport");

GETADDR(pfnwglCopyContext,dynwglCopyContext,"wglCopyContext");
GETADDR(pfnwglCreateContext,dynwglCreateContext,"wglCreateContext");
GETADDR(pfnwglCreateLayerContext,dynwglCreateLayerContext,"wglCreateLayerContext");
GETADDR(pfnwglDeleteContext,dynwglDeleteContext,"wglDeleteContext");
GETADDR(pfnwglGetCurrentContext,dynwglGetCurrentContext,"wglGetCurrentContext");
GETADDR(pfnwglGetCurrentDC,dynwglGetCurrentDC,"wglGetCurrentDC");
GETADDR(pfnwglGetProcAddress,dynwglGetProcAddress,"wglGetProcAddress");
GETADDR(pfnwglMakeCurrent,dynwglMakeCurrent,"wglMakeCurrent");
GETADDR(pfnwglShareLists,dynwglShareLists,"wglShareLists");
GETADDR(pfnwglSwapBuffers,dynwglSwapBuffers,"wglSwapBuffers");
GETADDR(pfnwglUseFontBitmapsA,dynwglUseFontBitmapsA,"wglUseFontBitmapsA");
GETADDR(pfnwglUseFontBitmapsW,dynwglUseFontBitmapsW,"wglUseFontBitmapsW");

GETADDR(pfnwglGetPixelFormat,dynwglGetPixelFormat,"wglGetPixelFormat");
GETADDR(pfnwglSetPixelFormat,dynwglSetPixelFormat,"wglSetPixelFormat");
GETADDR(pfnwglDescribePixelFormat,dynwglDescribePixelFormat,"wglDescribePixelFormat");
GETADDR(pfnwglChoosePixelFormat,dynwglChoosePixelFormat,"wglChoosePixelFormat");
}

int
dynglLoad(char *pszDllName)
{
 if (hOpenGLDLL != 0)
    {
     return 1;
    }
 putenv("FX_GLIDE_NO_SPLASH=1");
 hOpenGLDLL = LoadLibrary(pszDllName);
 if (hOpenGLDLL == 0)
    {
     return 2;
    }
 nInitMode = 0;
 SetProcs();
 return 0;
}

int
dynglUnload(void)
{
  if (hOpenGLDLL == 0)
     {
      return 1;
     }
 nInitMode = 1;
 SetProcs();
 FreeLibrary(hOpenGLDLL);
 hOpenGLDLL = 0;
 return 0;
}
#endif

int dyngl_GL_EXT_clip_volume_hint = 0;
int dyngl_GL_EXT_texture_env_add = 0;
int dyngl_GL_EXT_texture_env_combine = 0;
int dyngl_GL_NV_texture_env_combine4 = 0;
int dyngl_GL_ARB_multitexture = 0;

#ifdef WIN32
PFNGLMULTITEXCOORD1DARBPROC glMultiTexCoord1dARB;
PFNGLMULTITEXCOORD1DVARBPROC glMultiTexCoord1dvARB;
PFNGLMULTITEXCOORD1FARBPROC glMultiTexCoord1fARB;
PFNGLMULTITEXCOORD1FVARBPROC glMultiTexCoord1fvARB;
PFNGLMULTITEXCOORD1IARBPROC glMultiTexCoord1iARB;
PFNGLMULTITEXCOORD1IVARBPROC glMultiTexCoord1ivARB;
PFNGLMULTITEXCOORD1SARBPROC glMultiTexCoord1sARB;
PFNGLMULTITEXCOORD1SVARBPROC glMultiTexCoord1svARB;
PFNGLMULTITEXCOORD2DARBPROC glMultiTexCoord2dARB;
PFNGLMULTITEXCOORD2DVARBPROC glMultiTexCoord2dvARB;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB;
PFNGLMULTITEXCOORD2IARBPROC glMultiTexCoord2iARB;
PFNGLMULTITEXCOORD2IVARBPROC glMultiTexCoord2ivARB;
PFNGLMULTITEXCOORD2SARBPROC glMultiTexCoord2sARB;
PFNGLMULTITEXCOORD2SVARBPROC glMultiTexCoord2svARB;
PFNGLMULTITEXCOORD3DARBPROC glMultiTexCoord3dARB;
PFNGLMULTITEXCOORD3DVARBPROC glMultiTexCoord3dvARB;
PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB;
PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB;
PFNGLMULTITEXCOORD3IARBPROC glMultiTexCoord3iARB;
PFNGLMULTITEXCOORD3IVARBPROC glMultiTexCoord3ivARB;
PFNGLMULTITEXCOORD3SARBPROC glMultiTexCoord3sARB;
PFNGLMULTITEXCOORD3SVARBPROC glMultiTexCoord3svARB;
PFNGLMULTITEXCOORD4DARBPROC glMultiTexCoord4dARB;
PFNGLMULTITEXCOORD4DVARBPROC glMultiTexCoord4dvARB;
PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB;
PFNGLMULTITEXCOORD4FVARBPROC glMultiTexCoord4fvARB;
PFNGLMULTITEXCOORD4IARBPROC glMultiTexCoord4iARB;
PFNGLMULTITEXCOORD4IVARBPROC glMultiTexCoord4ivARB;
PFNGLMULTITEXCOORD4SARBPROC glMultiTexCoord4sARB;
PFNGLMULTITEXCOORD4SVARBPROC glMultiTexCoord4svARB;
PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
#endif

void
dynglCheckExtensions(void)
{
 if (strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_clip_volume_hint"))
    dyngl_GL_EXT_clip_volume_hint = 1;
 else
    dyngl_GL_EXT_clip_volume_hint = 0;

 if (strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_env_add"))
    dyngl_GL_EXT_texture_env_add = 1;
 else
    dyngl_GL_EXT_texture_env_add = 0;

 if (strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_env_combine"))
    dyngl_GL_EXT_texture_env_combine = 1;
 else
    dyngl_GL_EXT_texture_env_combine = 0;

 if (strstr((char*)glGetString(GL_EXTENSIONS), "GL_NV_texture_env_combine4"))
    dyngl_GL_NV_texture_env_combine4 = 1;
 else
    dyngl_GL_NV_texture_env_combine4 = 0;

 if (strstr((char*)glGetString(GL_EXTENSIONS), "GL_ARB_multitexture"))
    {
     dyngl_GL_ARB_multitexture = 1;
#ifdef WIN32
     GETEXADDR(PFNGLMULTITEXCOORD1DARBPROC, glMultiTexCoord1dARB, "glMultiTexCoord1dARB");
     GETEXADDR(PFNGLMULTITEXCOORD1DVARBPROC, glMultiTexCoord1dvARB, "glMultiTexCoord1dvARB");
     GETEXADDR(PFNGLMULTITEXCOORD1FARBPROC, glMultiTexCoord1fARB, "glMultiTexCoord1fARB");
     GETEXADDR(PFNGLMULTITEXCOORD1FVARBPROC, glMultiTexCoord1fvARB, "glMultiTexCoord1fvARB");
     GETEXADDR(PFNGLMULTITEXCOORD1IARBPROC, glMultiTexCoord1iARB, "glMultiTexCoord1iARB");
     GETEXADDR(PFNGLMULTITEXCOORD1IVARBPROC, glMultiTexCoord1ivARB, "glMultiTexCoord1ivARB");
     GETEXADDR(PFNGLMULTITEXCOORD1SARBPROC, glMultiTexCoord1sARB, "glMultiTexCoord1sARB");
     GETEXADDR(PFNGLMULTITEXCOORD1SVARBPROC, glMultiTexCoord1svARB, "glMultiTexCoord1svARB");
     GETEXADDR(PFNGLMULTITEXCOORD2DARBPROC, glMultiTexCoord2dARB, "glMultiTexCoord2dARB");
     GETEXADDR(PFNGLMULTITEXCOORD2DVARBPROC, glMultiTexCoord2dvARB, "glMultiTexCoord2dvARB");
     GETEXADDR(PFNGLMULTITEXCOORD2FARBPROC, glMultiTexCoord2fARB, "glMultiTexCoord2fARB");
     GETEXADDR(PFNGLMULTITEXCOORD2FVARBPROC, glMultiTexCoord2fvARB, "glMultiTexCoord2fvARB");
     GETEXADDR(PFNGLMULTITEXCOORD2IARBPROC, glMultiTexCoord2iARB, "glMultiTexCoord2iARB");
     GETEXADDR(PFNGLMULTITEXCOORD2IVARBPROC, glMultiTexCoord2ivARB, "glMultiTexCoord2ivARB");
     GETEXADDR(PFNGLMULTITEXCOORD2SARBPROC, glMultiTexCoord2sARB, "glMultiTexCoord2sARB");
     GETEXADDR(PFNGLMULTITEXCOORD2SVARBPROC, glMultiTexCoord2svARB, "glMultiTexCoord2svARB");
     GETEXADDR(PFNGLMULTITEXCOORD3DARBPROC, glMultiTexCoord3dARB, "glMultiTexCoord3dARB");
     GETEXADDR(PFNGLMULTITEXCOORD3DVARBPROC, glMultiTexCoord3dvARB, "glMultiTexCoord3dvARB");
     GETEXADDR(PFNGLMULTITEXCOORD3FARBPROC, glMultiTexCoord3fARB, "glMultiTexCoord3fARB");
     GETEXADDR(PFNGLMULTITEXCOORD3FVARBPROC, glMultiTexCoord3fvARB, "glMultiTexCoord3fvARB");
     GETEXADDR(PFNGLMULTITEXCOORD3IARBPROC, glMultiTexCoord3iARB, "glMultiTexCoord3iARB");
     GETEXADDR(PFNGLMULTITEXCOORD3IVARBPROC, glMultiTexCoord3ivARB, "glMultiTexCoord3ivARB");
     GETEXADDR(PFNGLMULTITEXCOORD3SARBPROC, glMultiTexCoord3sARB, "glMultiTexCoord3sARB");
     GETEXADDR(PFNGLMULTITEXCOORD3SVARBPROC, glMultiTexCoord3svARB, "glMultiTexCoord3svARB");
     GETEXADDR(PFNGLMULTITEXCOORD4DARBPROC, glMultiTexCoord4dARB, "glMultiTexCoord4dARB");
     GETEXADDR(PFNGLMULTITEXCOORD4DVARBPROC, glMultiTexCoord4dvARB, "glMultiTexCoord4dvARB");
     GETEXADDR(PFNGLMULTITEXCOORD4FARBPROC, glMultiTexCoord4fARB, "glMultiTexCoord4fARB");
     GETEXADDR(PFNGLMULTITEXCOORD4FVARBPROC, glMultiTexCoord4fvARB, "glMultiTexCoord4fvARB");
     GETEXADDR(PFNGLMULTITEXCOORD4IARBPROC, glMultiTexCoord4iARB, "glMultiTexCoord4iARB");
     GETEXADDR(PFNGLMULTITEXCOORD4IVARBPROC, glMultiTexCoord4ivARB, "glMultiTexCoord4ivARB");
     GETEXADDR(PFNGLMULTITEXCOORD4SARBPROC, glMultiTexCoord4sARB, "glMultiTexCoord4sARB");
     GETEXADDR(PFNGLMULTITEXCOORD4SVARBPROC, glMultiTexCoord4svARB, "glMultiTexCoord4svARB");
     GETEXADDR(PFNGLACTIVETEXTUREARBPROC, glActiveTextureARB, "glActiveTextureARB");
     GETEXADDR(PFNGLCLIENTACTIVETEXTUREARBPROC, glClientActiveTextureARB, "glClientActiveTextureARB");
#endif
    }
 else
    dyngl_GL_ARB_multitexture = 0;

}

#ifdef WIN32
}
#endif
