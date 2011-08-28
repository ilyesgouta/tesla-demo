
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
#ifndef WIN32
        m_display = 0;
#endif

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
#include <X11/Xutil.h>

static EGLConfig eglWConfig[8];

static int cIdx = 0, wIdx = 0;

bool OpenGL_c::CreateGLContext( Display* display, int iBitsPerPixel, int iZDepthBits )
{
    int ret;

    if ( !m_bGLLibLoaded )
        return false;

    if ( m_bGLContextCreated )
        return false;

    EGLint retConfigs = 0;

    EGLint targetAttribList[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE
    };

    m_eglDisplay = eglGetDisplay(display);

    EGLint eglMajor, eglMinor;

    if (!eglInitialize(m_eglDisplay, &eglMajor, &eglMinor))
        return false;

    printf("EGL version %d.%d\n", eglMajor, eglMinor);

    if (!eglChooseConfig(m_eglDisplay, targetAttribList, eglWConfig, sizeof(eglWConfig), &retConfigs))
        return false;

    if (!retConfigs)
        return false;
    else
        printf("found %d configurations.\n", retConfigs);

    EGLint vid;

    if (!eglGetConfigAttrib(m_eglDisplay, eglWConfig[0], EGL_NATIVE_VISUAL_ID, &vid))
        return false;

    printf("X visual id: 0x%02x\n", vid);

    XVisualInfo *visInfo, visTemplate;
    int num_visuals;

    visTemplate.visualid = vid;
    visInfo = XGetVisualInfo(display, VisualIDMask, &visTemplate, &num_visuals);

    if (!visInfo)
        return false;

    int scrnum = DefaultScreen(display);
    Window root = RootWindow(display, scrnum);

    XSetWindowAttributes attr;
    unsigned long mask;

    attr.background_pixel = 0;
    attr.border_pixel = 0;
    attr.colormap = XCreateColormap(display, root, visInfo->visual, AllocNone);
    attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    m_window = XCreateWindow(display, root, 0, 0, 1280, 720, 0, visInfo->depth, InputOutput, visInfo->visual, mask, &attr);

    if (!m_window)
        return false;

    {
       XSizeHints sizehints;
       sizehints.x = 0;
       sizehints.y = 0;
       sizehints.width  = 1280;
       sizehints.height = 720;
       sizehints.flags = USSize | USPosition;
       XSetNormalHints(display, m_window, &sizehints);
       XSetStandardProperties(display, m_window, "tesla-demo", "tesla-demo",
                               None, (char **)NULL, 0, &sizehints);
    }

    XSelectInput(display, m_window, ButtonPressMask | StructureNotifyMask | KeyPressMask );
    XMapWindow(display, m_window);

    eglBindAPI(EGL_OPENGL_ES_API);

    m_hGLRC = eglCreateContext(m_eglDisplay, eglWConfig[0], EGL_NO_CONTEXT, NULL);

    if ( m_hGLRC )
    {
        m_surface = eglCreateWindowSurface(m_eglDisplay, eglWConfig[0], m_window, NULL);

        if (!m_surface)
            return false;

        ret = (eglMakeCurrent(m_eglDisplay, m_surface, m_surface, m_hGLRC) == true);
        dynglCheckExtensions();
    }

    if ( ret ) {
        m_display = display;
        m_bGLContextCreated = true;
    }

    return ret;
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
    eglMakeCurrent( m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
    eglDestroyContext( m_display, m_hGLRC );
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
