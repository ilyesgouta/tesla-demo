
#include <stdio.h>
#include <string.h>

#include "OpenGL.hpp"

OpenGL_c g_cOpenGL;

/*******************************************************************************************/
OpenGL_c::OpenGL_c() {

        m_iGLWindowWidth = 0;
        m_iGLWindowHeight = 0;
        m_iGLWindowBPP = 0;
        m_bGLContextCreated = false;
        m_bGLLibLoaded = false;
        m_hGLRC = 0;
#ifndef WIN32
        m_display = 0;
#endif

}
/*******************************************************************************************/
OpenGL_c::~OpenGL_c() {

        DestroyGLContext();
        UnloadLib();
}
/*******************************************************************************************/
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
/*******************************************************************************************/
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
/*******************************************************************************************/
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
#include <X11/Xutil.h>

bool OpenGL_c::CreateGLContext( Display* display, int iBitsPerPixel, int iZDepthBits )
{
    if ( !m_bGLLibLoaded )
        return false;

    if ( m_bGLContextCreated )
        return false;

    XVisualInfo visual_template, *visuals = NULL;
    int iResult = 0, count = 0;

    memset(&visual_template, 0, sizeof(visual_template));

    visual_template.bits_per_rgb = iBitsPerPixel;
    visual_template.depth = iZDepthBits;

    visuals = XGetVisualInfo(display, VisualDepthMask | VisualBitsPerRGBMask, &visual_template, &count);

    if (!count)
        return 0;

    m_hGLRC = glXCreateContext(display, &(visuals[0]), NULL, true);

    if ( m_hGLRC )
    {
        iResult = (glXMakeCurrent(display, 0/*drawable*/, m_hGLRC) == true);
        dynglCheckExtensions();
    }

    if (visuals)
        XFree(visuals);

    if ( iResult ) {
        m_display = display;
        m_bGLContextCreated = true;
    }

    return iResult;
}
#endif
/*******************************************************************************************/
void OpenGL_c::DestroyGLContext() {

        if ( !m_bGLContextCreated ) return;
        if ( !m_bGLLibLoaded ) return;

        m_bGLContextCreated = false;

#ifdef WIN32
	dynwglMakeCurrent( 0, 0 );
	dynwglDeleteContext( m_hGLRC );
#else
    glXMakeCurrent( m_display, 0, 0 );
    glXDestroyContext( m_display, m_hGLRC );
#endif
}
/*******************************************************************************************/
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
          glTexImage2D( GL_TEXTURE_2D, iLev, iChannels, iTWidth, iTHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pRawData );
          pRGBMap1 = (rgb_t*)pRawData;
        }
        else if ( iChannels == 4 ) 
        {
          glTexImage2D( GL_TEXTURE_2D, iLev, iChannels, iTWidth, iTHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pRawData );
          pRGBAMap1 = (rgba_t*)pRawData;
        }
        else if ( iChannels == 1 ) 
        {
          glTexImage2D( GL_TEXTURE_2D, iLev, iChannels, iTWidth, iTHeight, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pRawData );
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
/*******************************************************************************************/


