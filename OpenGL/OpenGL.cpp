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

#include <stdio.h>
#include <string.h>

#include "OpenGL.hpp"

OpenGL_c g_cOpenGL;

OpenGL_c::OpenGL_c() {

        m_iGLWindowWidth = 0;
        m_iGLWindowHeight = 0;
        m_iGLWindowBPP = 0;
        m_bGLContextCreated = false;
        m_bGLLibLoaded = false;
        m_hGLRC = 0;
}

OpenGL_c::~OpenGL_c() {

        DestroyGLContext();
        UnloadLib();
}

bool OpenGL_c::LoadLib( char* pszGLLibraryName ) {
#ifdef WIN32
        if ( !pszGLLibraryName )
            return false;

        if ( dynglLoad(pszGLLibraryName) != 0 )
            return false;
#endif
        m_bGLLibLoaded = true;
        return true;
}

bool OpenGL_c::UnloadLib() {

    if ( m_bGLContextCreated )
    {
        DestroyGLContext();
    }

    if ( m_bGLLibLoaded )
    {
#ifdef WIN32
        if ( dynglUnload() != 0 )
            return false;
#endif
        m_bGLLibLoaded = false;
        return true;
    }
    else
        return false;
}

#ifdef WIN32
bool OpenGL_c::CreateGLContext( HWND hWindow, int iBitsPerPixel, int iZDepthBits ) {

        if ( !m_bGLLibLoaded ) return false;
        if ( m_bGLContextCreated ) return false;

	int nPixelFormat;
        bool iResult = 1;
        PIXELFORMATDESCRIPTOR stPFD;

        HDC hDC = GetDC( hWindow );

	memset( &stPFD, 0, sizeof(PIXELFORMATDESCRIPTOR) );
	stPFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	stPFD.nVersion = 1;
	stPFD.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	stPFD.iPixelType = PFD_TYPE_RGBA;
	stPFD.cColorBits = iBitsPerPixel;
	stPFD.cDepthBits = iZDepthBits;
	stPFD.iLayerType = PFD_MAIN_PLANE;

	nPixelFormat = ChoosePixelFormat( hDC,&stPFD );

        if ( nPixelFormat )
        {
          if ( SetPixelFormat(hDC, nPixelFormat, &stPFD) )
          {
            m_hGLRC = dynwglCreateContext( hDC );
            if ( m_hGLRC )
            { 
              if ( !dynwglMakeCurrent(hDC, m_hGLRC) ) iResult = 0;
              
              dynglCheckExtensions();
            }
            else
              iResult = 0;
          }
          else
            iResult = 0;
        }
        else
          iResult = 0;

        ReleaseDC( hWindow, hDC );

        if ( iResult )
          m_bGLContextCreated = true;

        return iResult;
}
#else

static EGLConfig g_defaultConfig;
static EGLConfig eglWConfig[8];

static int cIdx = 0, wIdx = 0;

bool OpenGL_c::CreateGLContext( int iBitsPerPixel, int iZDepthBits )
{
    DFBResult ret;
    bool result = false;

    int argc = 1;
    char** argv = NULL;

    DFBSurfaceDescription desc;

    //if ( !m_bGLLibLoaded )
    //    return false;

    if ( m_bGLContextCreated )
        return false;

    EGLint retConfigs = 0;

    ret = DirectFBInit(&argc, &argv);
    if (ret) {
         return ret;
    }

    ret = DirectFBCreate(&g_pDFBMain);
    if (ret) {
         return -1;
    }

    g_pDFBMain->SetCooperativeLevel(g_pDFBMain, DFSCL_EXCLUSIVE);

    memset(&desc, 0, sizeof(desc));

    desc.flags = DSDESC_CAPS;
    desc.caps = (DFBSurfaceCapabilities)(DSCAPS_PRIMARY | DSCAPS_DOUBLE);

    ret = g_pDFBMain->CreateSurface(g_pDFBMain, &desc, &pPrimarySurface);
    if (ret) {
         return -2;
    }

    pPrimarySurface->Clear(pPrimarySurface, 255, 0, 0, 255);
    pPrimarySurface->Flip(pPrimarySurface, NULL, DSFLIP_BLIT);

    EGLint major, minor;
    int i, numConfigs = 8;

    m_eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if (m_eglDisplay == EGL_NO_DISPLAY)
        return -1;

    if (eglInitialize(m_eglDisplay, &major, &minor) == EGL_FALSE)
        return -2;

    printf("EGL successfully initialized!\n");

    eglBindAPI(EGL_OPENGL_ES_API);

    EGLint attribList[] =
    {
        EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES_BIT,
        EGL_SURFACE_TYPE,       EGL_WINDOW_BIT,
        EGL_RED_SIZE,           8,
        EGL_BLUE_SIZE,          8,
        EGL_GREEN_SIZE,         8,
        EGL_ALPHA_SIZE,         8,
        EGL_NONE
    };

    if (eglChooseConfig(m_eglDisplay, attribList, eglWConfig, 8, &numConfigs) == EGL_FALSE)
        return -3;

    printf("num configs available: %d\n", numConfigs);

    for (i = 0; i < numConfigs; i++)
    {
        int red, green, blue, alpha, rendertype;

        eglGetConfigAttrib(m_eglDisplay, eglWConfig[i], EGL_RED_SIZE, &red);
        eglGetConfigAttrib(m_eglDisplay, eglWConfig[i], EGL_GREEN_SIZE, &green);
        eglGetConfigAttrib(m_eglDisplay, eglWConfig[i], EGL_BLUE_SIZE, &blue);
        eglGetConfigAttrib(m_eglDisplay, eglWConfig[i], EGL_ALPHA_SIZE, &alpha);

        eglGetConfigAttrib(m_eglDisplay, eglWConfig[i], EGL_RENDERABLE_TYPE, &rendertype);

        if ((red == 8) && (blue == 8) && (green == 8) && (alpha == 8) &&
            ((rendertype & EGL_OPENGL_ES_BIT) == EGL_OPENGL_ES_BIT))
            break;
    }

    if (i == numConfigs)
        return -4;

    g_defaultConfig = eglWConfig[i];

    eglBindAPI(EGL_OPENGL_ES_API);

    m_hGLRC = eglCreateContext(m_eglDisplay, g_defaultConfig, EGL_NO_CONTEXT, NULL);

    if ( m_hGLRC )
    {
        printf("successfully created an EGL context.\n");
        m_surface = eglCreateWindowSurface(m_eglDisplay, g_defaultConfig, pPrimarySurface, NULL);

        if (!m_surface)
            return false;

        result = (eglMakeCurrent(m_eglDisplay, m_surface, m_surface, m_hGLRC) == true);
        dynglCheckExtensions();
    }

    if ( result )
        m_bGLContextCreated = true;

    return result;
}
#endif

void OpenGL_c::DestroyGLContext() {

        if ( !m_bGLContextCreated )
            return;

        if ( !m_bGLLibLoaded )
            return;

        m_bGLContextCreated = false;

#ifdef WIN32
	dynwglMakeCurrent( 0, 0 );
	dynwglDeleteContext( m_hGLRC );
#else
    eglMakeCurrent( m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
    eglDestroyContext( m_eglDisplay, m_hGLRC );
#endif
}

int OpenGL_c::UploadTexture( void* pRawData, int iTWidth, int iTHeight, int iBPP, int iCreateMipMaps ) {


        if ( !m_bGLContextCreated ) return -1;
        if ( !m_bGLLibLoaded ) return -1;
        
        unsigned int iGLTexName;
        glGenTextures( 1, &iGLTexName );

        int iLev = 0;
        int iChannels = iBPP >> 3;
        unsigned int x, y;

        class rgb_t {
          public:
          unsigned char r, g, b;
        };

        class rgba_t {
          public:
            unsigned char r, g, b, a;
        };

        unsigned char* pGrayMap1;
        unsigned char* pGrayMap2;
        rgb_t* pRGBMap1;
        rgb_t* pRGBMap2;
        rgba_t* pRGBAMap1;
        rgba_t* pRGBAMap2;
        
        glBindTexture( GL_TEXTURE_2D, iGLTexName );
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


        if ( iChannels == 3 ) 
        {
          glTexImage2D( GL_TEXTURE_2D, iLev, GL_RGB, iTWidth, iTHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pRawData );
          pRGBMap1 = (rgb_t*)pRawData;
        }
        else if ( iChannels == 4 ) 
        {
          glTexImage2D( GL_TEXTURE_2D, iLev, GL_RGBA, iTWidth, iTHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pRawData );
          pRGBAMap1 = (rgba_t*)pRawData;
        }
        else if ( iChannels == 1 ) 
        {
          glTexImage2D( GL_TEXTURE_2D, iLev, GL_LUMINANCE, iTWidth, iTHeight, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pRawData );
          pGrayMap1 = (unsigned char*)pRawData;
        }        
        else return -1;

        if ( !iCreateMipMaps )
        {
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        }
        else
        {
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

          iLev++;
          iTWidth /= 2; iTHeight /= 2;

          while ( iTWidth >= 1 || iTHeight >= 1 )
          {
            switch ( iChannels )
            {
              case 1:
                pGrayMap2 = new unsigned char[iTWidth*iTHeight];
                break;

              case 3:
                pRGBMap2 = new rgb_t[iTWidth*iTHeight];
                for ( y = 0; y != (unsigned)iTHeight; y++ )
                {
                  for ( x = 0; x != (unsigned)iTWidth; x++ )
                  {
                    pRGBMap2[y*iTWidth + x].r = (pRGBMap1[y*2*iTWidth*2 + x*2].r + 
                                                pRGBMap1[y*2*iTWidth*2 + x*2 + 1].r +
                                                pRGBMap1[y*2*iTWidth*2 + x*2 + 1 + iTWidth*2].r +
                                                pRGBMap1[y*2*iTWidth*2 + x*2 + iTWidth*2].r)/4;

                    pRGBMap2[y*iTWidth + x].g = (pRGBMap1[y*2*iTWidth*2 + x*2].g + 
                                                pRGBMap1[y*2*iTWidth*2 + x*2 + 1].g +
                                                pRGBMap1[y*2*iTWidth*2 + x*2 + 1 + iTWidth*2].g +
                                                pRGBMap1[y*2*iTWidth*2 + x*2 + iTWidth*2].g)/4;

                    pRGBMap2[y*iTWidth + x].b = (pRGBMap1[y*2*iTWidth*2 + x*2].b + 
                                                pRGBMap1[y*2*iTWidth*2 + x*2 + 1].b +
                                                pRGBMap1[y*2*iTWidth*2 + x*2 + 1 + iTWidth*2].b +
                                                pRGBMap1[y*2*iTWidth*2 + x*2 + iTWidth*2].b)/4;
                  }
                }

                glTexImage2D( GL_TEXTURE_2D, iLev, iChannels, iTWidth, iTHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pRGBMap2 );
                if ( iLev > 1 ) delete[] pRGBMap1;
                pRGBMap1 = pRGBMap2;
                break;

              case 4:
                pRGBAMap2 = new rgba_t[iTWidth*iTHeight];

                for ( y = 0; y != (unsigned)iTHeight; y++ )
                {
                  for ( x = 0; x != (unsigned)iTWidth; x++ )
                  {
                    pRGBAMap2[y*iTWidth + x].r = (pRGBAMap1[y*2*iTWidth*2 + x*2].r + 
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + 1].r +
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + 1 + iTWidth*2].r +
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + iTWidth*2].r)/4;

                    pRGBAMap2[y*iTWidth + x].g = (pRGBAMap1[y*2*iTWidth*2 + x*2].g + 
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + 1].g +
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + 1 + iTWidth*2].g +
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + iTWidth*2].g)/4;

                    pRGBAMap2[y*iTWidth + x].b = (pRGBAMap1[y*2*iTWidth*2 + x*2].b + 
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + 1].b +
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + 1 + iTWidth*2].b +
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + iTWidth*2].b)/4;

                    pRGBAMap2[y*iTWidth + x].a = (pRGBAMap1[y*2*iTWidth*2 + x*2].a + 
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + 1].a +
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + 1 + iTWidth*2].a +
                                                 pRGBAMap1[y*2*iTWidth*2 + x*2 + iTWidth*2].a)/4;
                  }
                }

                glTexImage2D( GL_TEXTURE_2D, iLev, iChannels, iTWidth, iTHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pRGBAMap2 );
                if ( iLev > 1 ) delete[] pRGBAMap1;
                pRGBAMap1 = pRGBAMap2;
                break;
            }

            iLev++;
            iTWidth /= 2; iTHeight /= 2;
            if ( iTWidth == 0 && iTHeight == 0 ) break;
            if ( iTWidth == 0 ) iTWidth = 1;
            if ( iTHeight == 0 ) iTHeight = 1;

          }
        }

        return iGLTexName;
}
