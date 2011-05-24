

#if !defined (_OPEN_GL_HPP_)
#define _OPEN_GL_HPP_

#include "dyngl.h"

class OpenGL_c {

public:
        OpenGL_c();
        virtual ~OpenGL_c();

        /* default: 'opengl32.dll' */
        bool LoadLib( char* pszGLLibraryName );
        bool CreateGLContext( HWND hWindow, int iBitsPerPixel, int iZDepthBits );
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

        HGLRC m_hGLRC;
};

extern OpenGL_c g_cOpenGL;

#endif /*_OPEN_GL_HPP_*/