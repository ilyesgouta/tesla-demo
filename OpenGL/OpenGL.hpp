

#if !defined (_OPEN_GL_HPP_)
#define _OPEN_GL_HPP_

#ifdef WIN32
#include <windows.h>
#else
#include <X11/X.h>
#include <EGL/egl.h>

#include <GLES/gl.h>
#endif

#ifdef WIN32
#include "Dyngl.h"
#else
int dynglLoad(char *pszDllName);
int dynglUnload(void);
void dynglCheckExtensions(void);
#endif

class OpenGL_c {

public:
        OpenGL_c();
        virtual ~OpenGL_c();

        /* default: 'opengl32.dll' */
        bool LoadLib( char* pszGLLibraryName );
#ifdef WIN32
        bool CreateGLContext( HWND hWindow, int iBitsPerPixel, int iZDepthBits );
#else
        bool CreateGLContext( Display* display, int iBitsPerPixel, int iZDepthBits );
#endif
        void DestroyGLContext();

        /* dont call this on window messages with gl context created!
         * becouse every message is passed thru the gl dll */
        bool UnloadLib();

        int UploadTexture( void* pRawData, int iTWidth, int iTHeight, int iBPP, int iCreateMipMaps = 0 );

protected:

        int m_iGLWindowWidth;
        int m_iGLWindowHeight;
        int m_iGLWindowBPP;

        bool m_bGLContextCreated;
        bool m_bGLLibLoaded;

#if WIN32
        HGLRC m_hGLRC;
#else
        EGLContext m_hGLRC;
        Display *m_display;
        Window m_window;
        EGLSurface m_surface;
        EGLDisplay m_eglDisplay;
#endif
};

extern OpenGL_c g_cOpenGL;

#endif /*_OPEN_GL_HPP_*/
