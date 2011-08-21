
#ifdef WIN32
#include "stdafx.h"
#endif

#define _GNU_SOURCE
#include <time.h>
#include <stdarg.h>

#include "MainFrame.hpp"
#include "OpenGL/OpenGL.hpp"

MainFrame_c* g_pMainFrame = 0;

static void ErrorMessage( char* pszErrorMessage ) {
#ifdef WIN32
      MessageBox( 0, pszErrorMessage, "Error...", MB_ICONERROR );  
#else
    printf("%s\n", pszErrorMessage);
#endif
}

#ifdef WIN32
LRESULT CALLBACK MainWindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
  
        return g_pMainFrame->WindowProc( hWnd, uMsg, wParam, lParam );
}
#endif

#ifdef WIN32
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iShowCmd ) {

        MSG stMsg;

        Start();

        if ( !g_pMainFrame )
        {
          ErrorMessage( "WinMain: Can't create MainFramce_c" );
          return -1;
        }

        if ( g_pMainFrame->GetLastError() )
        {
          ErrorMessage( g_pMainFrame->GetLastErrorMsg() );
          return -1;
        }

        if ( !g_pMainFrame->InitWindow( hInstance ) )
        {
          ErrorMessage( "WinMain: Can't create window" );
          return -1;
        }
  
        while ( true )
        {
          if ( PeekMessage(&stMsg, NULL, 0, 0, PM_REMOVE) )
          {
            if (stMsg.message == WM_QUIT) break;
            TranslateMessage(&stMsg);
            DispatchMessage(&stMsg);
          }
          else
          {
            if ( !g_pMainFrame->GetMessageBased() && g_pMainFrame->GetWindowActive() )
            {
              RedrawWindow( g_pMainFrame->GetWindowHandle(), NULL, NULL, RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_NOERASE );
              WaitMessage();
            }
            else
              WaitMessage();
          }
        }

        if ( g_pMainFrame->GetFullScreen() )
        {
          ChangeDisplaySettings( 0, 0 );
        }

        delete g_pMainFrame;
        g_pMainFrame = 0;

        End();

        return 0;
}
#else
int main(int argc, char** argv)
{
    Start();

    if ( !g_pMainFrame )
    {
      ErrorMessage( "WinMain: Can't create MainFramce_c" );
      return -1;
    }

    if ( g_pMainFrame->GetLastError() )
    {
      ErrorMessage( g_pMainFrame->GetLastErrorMsg() );
      return -1;
    }

    if ( !g_pMainFrame->InitWindow() )
    {
      ErrorMessage( "WinMain: Can't create window" );
      return -1;
    }

    bool m_render = true;
    XEvent ev;

    Display *display = g_pMainFrame->GetDisplay();

    while (m_render)
    {
        if (XPending(display))
        {
            XNextEvent(display, &ev);

            switch(ev.type) {
            /*case ConfigureNotify:
                if (width != ev.xconfigure.width
                        || height != ev.xconfigure.height) {
                    width = ev.xconfigure.width;
                    height = ev.xconfigure.height;
                }
                break;*/
            case ButtonPress:
                m_render = false;
                break;
            default:
                break;
            }
        }

        g_pMainFrame->OnPaint();
        eglSwapBuffers(g_cOpenGL.GetEGLDisplay(), g_cOpenGL.GetEGLSurface());
    }

    XCloseDisplay(display);

    delete g_pMainFrame;
    g_pMainFrame = 0;

    End();

    return 0;
}
#endif

// MAIN FRAME
MainFrame_c::MainFrame_c() {
#ifdef WIN32
        m_hWnd = 0;
#endif
        m_iError = 0;
        m_szErrorMessage[0] = 0;  
        m_bWindowActive = true;
        m_iWindowWidth = 640;
        m_iWindowHeight = 480;
        m_iBitsPerPixel = 16;
        strcpy( m_szWindowName, "default name" );
        m_bFullScreen = false;
        m_bInitDone = false;
        m_bMessageBased = false;
        m_iResourceIcon = 0;
        m_dwWindowStyle = 0;

        m_pTimer = new Timer_c;
        if ( !m_pTimer->InitTimer() ) ErrorQuit( "MainFrame_c::MainFrame_c: Can't init default timer!" );
}

MainFrame_c::~MainFrame_c() {

        if ( m_pTimer ) delete m_pTimer;
        if ( m_iError ) ErrorMessage( m_szErrorMessage );
}

#ifdef WIN32
void MainFrame_c::SetWindowHandle( HWND hWnd ) {
        
        m_hWnd = hWnd;
}
#endif

#ifdef WIN32
HWND MainFrame_c::GetWindowHandle() const {
  
        return m_hWnd;
}
#endif

void MainFrame_c::ErrorQuit( char* pszErrMsg, ... ) {

        va_list        pArgs;

        va_start( pArgs, pszErrMsg );
        vsprintf( m_szErrorMessage, pszErrMsg, pArgs );
        va_end( pArgs );

        m_iError = 1;
}

#ifdef WIN32
bool MainFrame_c::InitWindow( HINSTANCE hInstance ) {

        WNDCLASS    stWndClass;

        m_hInstance = hInstance;

        stWndClass.hInstance =  m_hInstance;
        stWndClass.hCursor = 0;
        stWndClass.hIcon = m_iResourceIcon ? LoadIcon( m_hInstance, MAKEINTRESOURCE(m_iResourceIcon) ) : 0;
        stWndClass.lpfnWndProc = MainWindowProc;
        stWndClass.lpszClassName = "MainFrame_c";
        stWndClass.lpszMenuName = NULL;
        stWndClass.hbrBackground = 0;
        stWndClass.style=CS_OWNDC;
        stWndClass.cbClsExtra = 0;
        stWndClass.cbWndExtra = 0;

        if (!RegisterClass(&stWndClass)) return false;


        /* try to change the screen resolution */
        if ( m_bFullScreen )
        {
          DEVMODE stDevMode;

          memset( &stDevMode, 0, sizeof(DEVMODE) );

          stDevMode.dmSize = sizeof(DEVMODE);
          stDevMode.dmBitsPerPel = m_iBitsPerPixel;
          stDevMode.dmPelsWidth = m_iWindowWidth;
          stDevMode.dmPelsHeight = m_iWindowHeight;
          stDevMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

          if ( DISP_CHANGE_SUCCESSFUL != ChangeDisplaySettings(&stDevMode, CDS_FULLSCREEN) )
          {
            m_bFullScreen = false;
          }
        }

        if ( m_bFullScreen )
        {
          ShowCursor( false );
          m_hWnd = CreateWindowEx(WS_EX_TOPMOST,
                                 "MainFrame_c",
                                 m_szWindowName,
                                 WS_POPUP |
                                 WS_CLIPCHILDREN |
                                 WS_CLIPSIBLINGS |
                                 WS_VISIBLE | m_dwWindowStyle,
                                 0,
                                 0,
                                 m_iWindowWidth,
                                 m_iWindowHeight,
                                 0,
                                 0,
                                 m_hInstance,
                                 0);
        }
        else
        {
          m_hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                                 "MainFrame_c",
                                 m_szWindowName,
                                 WS_OVERLAPPED | WS_CAPTION |  WS_SYSMENU |
                                 WS_POPUP | WS_BORDER |
                                 WS_CLIPCHILDREN |
                                 WS_CLIPSIBLINGS |
                                 WS_VISIBLE | m_dwWindowStyle,
                                 0,
                                 0,
                                 m_iWindowWidth + (GetSystemMetrics(SM_CXSIZEFRAME) - 1)*2,
                                 m_iWindowHeight + GetSystemMetrics(SM_CYCAPTION) + (GetSystemMetrics(SM_CYSIZEFRAME) - 1)*2,
                                 0,
                                 0,
                                 m_hInstance,
                                 0);
        }

        if ( !m_hWnd ) return false;

        SetFocus( m_hWnd );

        if ( !m_bInitDone )
        {
          if ( !OnCreate() || m_iError )
          {
            if ( !m_iError ) ErrorQuit( "MainFrame_c::WindowProc::OnCreate: Unknown error!" );
            PostMessage( m_hWnd, WM_CLOSE, 0, 0 );
          }

          m_bInitDone = true;
        }

        return true;  
}
#else
bool MainFrame_c::InitWindow()
{
    return (m_bInitDone = OnCreate());
}
#endif

#ifdef WIN32
LRESULT MainFrame_c::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
  
        switch ( uMsg )
        {
          case WM_CREATE:
            m_hWnd = hWnd;
            return 0;

          case WM_SETFOCUS:
            return 0;

          case WM_KILLFOCUS:
            return 0;

          case WM_DESTROY:
            if ( !OnDestroy() && !m_iError ) ErrorQuit( "MainFrame_c::WindowProc::OnDestroy: Unknown error!" );
            PostQuitMessage( 0 );
            return 0;

          case WM_PAINT:

            m_pTimer->Update();

            if ( !OnPaint() )
            {
              if ( !m_iError  ) ErrorQuit( "MainFrame_c::WindowProc::OnPain: Unknown error!" );
              PostMessage( hWnd, WM_CLOSE, 0, 0 );
            }

            ValidateRgn( m_hWnd, 0 );

            if ( m_iError ) PostMessage( hWnd, WM_CLOSE, 0, 0 );
            return 0;

          case WM_ACTIVATE:
            int iActive = LOWORD(wParam);

            switch ( iActive )
            {
              case WA_ACTIVE:
              case WA_CLICKACTIVE:
                m_bWindowActive = 1;
                if ( m_bFullScreen )
                {
                  DEVMODE stDevMode;

                  memset( &stDevMode, 0, sizeof(DEVMODE) );

                  stDevMode.dmSize = sizeof(DEVMODE);
                  stDevMode.dmBitsPerPel = m_iBitsPerPixel;
                  stDevMode.dmPelsWidth = m_iWindowWidth;
                  stDevMode.dmPelsHeight = m_iWindowHeight;
                  stDevMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

                  if ( DISP_CHANGE_SUCCESSFUL != ChangeDisplaySettings(&stDevMode, CDS_FULLSCREEN) )
                  {
                    ErrorQuit( "MainFrame_c::WindowProc: Cant restore window!" );
                  }
                }
                break;

              case WA_INACTIVE:
                m_bWindowActive = 0;
                if ( m_bFullScreen )
                {
                  ChangeDisplaySettings( 0, 0 );
                }
                break;
            }
            return 0;
        }

        return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
#endif

// timer
TimerBase_c::TimerBase_c() {

}

TimerBase_c::~TimerBase_c() {

}

Timer_c::Timer_c() {
#ifdef WIN32
    m_liTimeCurrent = 0;
    m_liTimeFreq = 0;
    m_liTimePrev = 0;
    m_liTimeStart = 0;
#endif
    m_fTimeCurrent = 0;
    m_fTimePrev = 0;
    m_fTimeAppStart = 0;
    m_fTimeDelta = 0;

#ifdef WIN32
        if ( !QueryPerformanceFrequency((LARGE_INTEGER*)&m_liTimeFreq) )
        {
          // fix: exit app and tell the user that he doesnt have requested hardware;
        }
#endif
}

Timer_c::~Timer_c() {

}

bool Timer_c::InitTimer() {
#ifdef WIN32
    QueryPerformanceCounter( (LARGE_INTEGER*)&m_liTimeStart );
    m_fTimeAppStart = (float)m_liTimeStart/m_liTimeFreq;
#else
    struct timespec tp;

    clock_gettime(CLOCK_MONOTONIC, &tp);

    m_fTimeAppStart = (tp.tv_sec * 1000.0f + tp.tv_nsec / 1000000.0f) / 1000.0f;
#endif
        return true;
}

void Timer_c::Update() {
#ifdef WIN32
    m_liTimePrev = m_liTimeCurrent;
    QueryPerformanceCounter( (LARGE_INTEGER*)&m_liTimeCurrent );
    m_liTimeCurrent -= m_liTimeStart;

    m_fTimePrev= m_fTimeCurrent;
    m_fTimeCurrent = (float)m_liTimeCurrent/m_liTimeFreq;

    m_fTimeDelta = m_fTimeCurrent - m_fTimePrev;
#else
    struct timespec tp;

    clock_gettime(CLOCK_MONOTONIC, &tp);

    m_fTimePrev = m_fTimeCurrent;
    m_fTimeCurrent = (tp.tv_sec * 1000.0f + tp.tv_nsec / 1000000.0f) / 1000.0f;

    m_fTimeDelta = m_fTimeCurrent - m_fTimePrev;
#endif
}
