
#ifdef WIN32
#include "stdafx.h"
#endif

#include "resource.h"

#ifdef WIN32
#include "Vfw.h"
#pragma comment( lib, "Vfw32.lib" )
#endif

//#include "BassPlay.hpp"

#include "OpenGL/OpenGL.hpp"

#include "EffManage.hpp"

#if 0
#include "LinePlane.hpp"
#include "Dragon.hpp"
#endif

#include "SpinZoom.hpp"
#include "ShadeBall.hpp"
#include "Splines.hpp"
#include "Bands.hpp"
#include "FFDEnvVector.hpp"
#include "EnergyStream.hpp"
#include "tubes.hpp"
#include "PolkaLike.hpp"
#include "Tree.hpp"
#include "FaceMorph.hpp"
//#include "ScrewBolt.hpp"
#include "Rotator.hpp"

CEffManager* g_pEffManage = 0;

static bool l_bFirstRenderFrame = true;
static float l_fFirstFrameTime = 0;

class CResolution {

public:
        CResolution() {
          m_iWidth = 0;
          m_iHeight = 0;
          m_iBPP = 0;
        }

        uint m_iWidth;
        uint m_iHeight;
        uint m_iBPP;
};

static int l_iResolutions;
static CResolution l_aResolutions[256];
static int l_iCurResSelection = 0;
static int l_bFullScreen = true;

#if 0
static int l_bMakeAVI = true;
static float l_fAVITime = 0;

/* avi crap */

BITMAPINFO stBitmapIn;
BITMAPINFO stBitmapOut;

static PAVIFILE pAVIFile = 0;
static PAVISTREAM pAVIStream = 0;
static AVISTREAMINFO stAVIStreamInfo;
static BITMAPINFOHEADER biNew; 
static HBITMAP hAVIBitmap = 0;
static HDC hAVIDC = 0;
static int* pAVIBuffer = 0;
static int lAVIStreamSize = 0;

static int iAVIWidth = 720;
static int iAVIHeight = 576;

/* codecs */
HIC hic;
COMPVARS stCompVars;
static ICINFO l_aCodecs[64];
static int l_iCodecs = 0;
#endif

class CDemoFrame : public MainFrame_c {

public:
        CDemoFrame() {}
        virtual ~CDemoFrame() {}
#ifdef WIN32
        virtual LRESULT WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
#endif
};

#ifdef WIN32
void EnumVideoModes()
{
        int iDevMode, iRes;
        DEVMODE stDevMode;

        l_iResolutions = 0;
        memset( l_aResolutions, 0, sizeof(l_aResolutions) );

        iDevMode = 0;

        while ( true ) 
        {
          memset( &stDevMode, 0, sizeof(DEVMODE) );
          stDevMode.dmSize = sizeof(DEVMODE);

          if ( !EnumDisplaySettings(0, iDevMode, &stDevMode) )
          {
            break;
          }
          else
          {
            for (iRes = 0; iRes < l_iResolutions; iRes++)
            {
              if ( stDevMode.dmPelsWidth == l_aResolutions[iRes].m_iWidth
                   && stDevMode.dmPelsHeight == l_aResolutions[iRes].m_iHeight
                   && stDevMode.dmBitsPerPel == l_aResolutions[iRes].m_iBPP ) break;
            }

            if ( iRes == l_iResolutions )
            if ( stDevMode.dmPelsWidth >= 640 && 
                 stDevMode.dmPelsHeight >= 480 && 
                 stDevMode.dmBitsPerPel > 8 )
            {
              l_aResolutions[l_iResolutions].m_iWidth = stDevMode.dmPelsWidth;
              l_aResolutions[l_iResolutions].m_iHeight = stDevMode.dmPelsHeight;
              l_aResolutions[l_iResolutions].m_iBPP = stDevMode.dmBitsPerPel;

              l_iResolutions++;
            }     

            iDevMode++;
          }
        }
}

int CALLBACK DemoDialogProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

        switch ( uMsg )
        { 
          case WM_INITDIALOG: 
          {
            EnumVideoModes();

            for ( int i = 0; i != l_iResolutions; i++ )
            {
              char szText[256];
              sprintf( szText, "%dx%dx%d", l_aResolutions[i].m_iWidth, l_aResolutions[i].m_iHeight, l_aResolutions[i].m_iBPP );
              SendDlgItemMessage( hDlg, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)szText );
            }

            SendDlgItemMessage( hDlg, IDC_COMBO1, CB_SETCURSEL, 0, 0 );
            CheckDlgButton( hDlg, IDC_CHECK1, 0 );
            CheckDlgButton( hDlg, IDC_CHECK2, 1 );
            return 0;
          }

          case WM_COMMAND:
          {
            switch ( LOWORD(wParam) )
            {
              case IDOK:
              {
                l_iCurResSelection = SendDlgItemMessage( hDlg, IDC_COMBO1, CB_GETCURSEL, 0, 0 );
                l_bFullScreen = IsDlgButtonChecked( hDlg, IDC_CHECK1 );
                l_bMakeAVI = IsDlgButtonChecked( hDlg, IDC_CHECK2 );
                EndDialog( hDlg, 1 );
                return 1;
              }

              case IDCANCEL:
                EndDialog( hDlg, 0 );
                return 1;

              default:
                return 0;
            }
          }


          default:
            return 0;        
        }
}
#endif

void Start()
{
#ifdef WIN32
    if ( !DialogBox(0, MAKEINTRESOURCE(IDD_DIALOG1), 0, DemoDialogProc) ) ExitProcess(0);

    if ( l_bMakeAVI )
    {
      AVIFileInit();

      if ( AVIFileOpen( &pAVIFile, "tesla.avi", OF_WRITE | OF_CREATE, 0 ) != 0 )
      {
        MessageBox( 0, "[Start] Cant create tesla.avi file", "Error...", MB_ICONERROR );
        return ;
      }

      memset( &stBitmapIn, 0, sizeof(stBitmapIn) );
      stBitmapIn.bmiHeader.biSize = sizeof(stBitmapIn.bmiHeader);
      stBitmapIn.bmiHeader.biWidth = iAVIWidth;
      stBitmapIn.bmiHeader.biHeight = iAVIHeight;
      stBitmapIn.bmiHeader.biPlanes = 1;
      stBitmapIn.bmiHeader.biBitCount = 24;
      stBitmapIn.bmiHeader.biCompression = BI_RGB;

      memset( &stCompVars, 0, sizeof(stCompVars) );
      stCompVars.cbSize = sizeof(stCompVars);

      int res = ICCompressorChoose( 0, 0, &stBitmapIn, 0, &stCompVars, "select compressor" );

      if ( !res ) ExitProcess( 0 );

      memset( &stBitmapOut, 0, sizeof(stBitmapOut) );

      if ( ICERR_OK != ICCompressGetFormat(stCompVars.hic, &stBitmapIn.bmiHeader, &stBitmapOut.bmiHeader) )
      {
        MessageBox( 0, "[Start] ICCompressGetFormat failed!", "Error...", MB_ICONERROR );
        return;
      }

      memset( &stAVIStreamInfo, 0, sizeof(stAVIStreamInfo) );

      RECT stRect;

      stRect.left = 0;
      stRect.top = 0;
      stRect.right = iAVIWidth;
      stRect.bottom = iAVIHeight;

      stAVIStreamInfo.fccType = streamtypeVIDEO;
      stAVIStreamInfo.fccHandler = mmioFOURCC( 'M', 'S','V', 'C' );
      stAVIStreamInfo.dwScale = 1;
      stAVIStreamInfo.dwRate = 25;
      stAVIStreamInfo.dwQuality = 10000;
      stAVIStreamInfo.rcFrame = stRect;
      strcpy( stAVIStreamInfo.szName, "Tesla by Sunflower..." );

      if ( AVIFileCreateStream(pAVIFile, &pAVIStream, &stAVIStreamInfo) != 0 )
      {
        MessageBox( 0, "[Start] Cant create AVI file stream!", "Error...", MB_ICONERROR );
        return;
      }

      if ( AVIStreamSetFormat(pAVIStream, 0, &stBitmapOut, sizeof(stBitmapOut)) != 0 )
      {
        MessageBox( 0, "[Start] Cant set AVI fromat", "Error...", MB_ICONERROR );
        return;
      }

      if ( !ICSeqCompressFrameStart(&stCompVars, &stBitmapIn) )
      {
        MessageBox( 0, "[Start] Cant initialize compressor!", "Error...", MB_ICONERROR );
        return;
      }
    }
#endif

    g_pMainFrame = new CDemoFrame;
    g_pMainFrame->SetWindowName( "Tesla" );
    g_pMainFrame->SetFullScreen( l_bFullScreen ? 1 : 0 );

#ifdef WIN32
    if ( !l_bMakeAVI )
    {
      g_pMainFrame->m_iWindowWidth = l_aResolutions[l_iCurResSelection].m_iWidth;
      g_pMainFrame->m_iWindowHeight = l_aResolutions[l_iCurResSelection].m_iHeight;
      g_pMainFrame->m_iBitsPerPixel = l_aResolutions[l_iCurResSelection].m_iBPP;
    }
    else
    {
      g_pMainFrame->m_iWindowWidth = iAVIWidth;
      g_pMainFrame->m_iWindowHeight = iAVIHeight;
      g_pMainFrame->m_iBitsPerPixel = 32;
    }
#else
    g_pMainFrame->m_iWindowWidth = 1280;
    g_pMainFrame->m_iWindowHeight = 720;
    g_pMainFrame->m_iBitsPerPixel = 32;
#endif
}

void End() {

        g_cOpenGL.UnloadLib();
}

bool MainFrame_c::OnCreate()
{
    if ( !g_cOpenGL.LoadLib("opengl32.dll") )
    {
      ErrorQuit( "[MainFrame_c::OnCreate] Cant load opengl32.dll" );
      return false;
    }

    m_display = XOpenDisplay(NULL);
    int iResult = g_cOpenGL.CreateGLContext( m_display, m_iBitsPerPixel, 32 );

    if ( !iResult )
    {
      strcpy( m_szErrorMessage, "[MainFrame_c::OnCreate] Cant init OpenGL context!\n" );
      m_iError = 1;
      return false;
    }

/*
    if ( !FAOpenArchive("data.pak") )
    {
      ErrorQuit( "[MainFrame_c::OnCreate] Cant open data file!\n" );
      return false;
    }
*/

#ifdef WIN32
    if ( l_bMakeAVI )
    {
      HDC hDC = GetDC( m_hWnd );
      hAVIDC = CreateCompatibleDC( hDC );
      hAVIBitmap = CreateDIBSection( hAVIDC, &stBitmapIn, DIB_RGB_COLORS, (void**)&pAVIBuffer, 0, 0 );
      ReleaseDC( m_hWnd, hDC );
    }
#endif
    g_pEffManage = new CEffManager();

    g_pEffManage->AddEffect( new CSpinZoom(), 0, 24.5 );
    //g_pEffManage->AddEffect( new CScrewBolt(), 5, 24.5 );
    g_pEffManage->AddEffect( new CShadeBall(), 24.5, 48.5 );
    g_pEffManage->AddEffect( new CSplines(), 48.5, 67.7 );
    g_pEffManage->AddEffect( new CFFDEnv(), 67.7, 87 );
    g_pEffManage->AddEffect( new CBands(), 69, 85 );
    g_pEffManage->AddEffect( new CEnergyStream(), 87, 145 );
    g_pEffManage->AddEffect( new CTubes(), 145, 165 );
    g_pEffManage->AddEffect( new PolkaLike_c(), 165, 203 );
    g_pEffManage->AddEffect( new CTree(), 165 + 21, 201 );
    g_pEffManage->AddEffect( new CFaceMorph(), 203, 222.5 );
    g_pEffManage->AddEffect( new CThing(), 222.5, 254 );

    //if ( !l_bMakeAVI ) g_cBass.LoadMP3( "tournesol.mp3" );

    return true;
}

bool MainFrame_c::OnDestroy()
{
#ifdef WIN32
    if ( !l_bMakeAVI ) g_cBass.StopMP3();
    else
    {
      ICSeqCompressFrameEnd( &stCompVars );

      if ( pAVIStream )
        AVIStreamRelease( pAVIStream );

      if ( pAVIFile )
        AVIFileRelease( pAVIFile );

      AVIFileExit();
    }
#endif
    if ( g_pEffManage ) delete g_pEffManage;
    g_cOpenGL.DestroyGLContext();
    return true;
}

bool MainFrame_c::OnPaint()
{
#ifdef WIN32
    PAINTSTRUCT stPaint;

    if ( l_bFirstRenderFrame )
    {
      l_fFirstFrameTime = m_pTimer->GetCurTime();
      l_bFirstRenderFrame = false;
      if ( !l_bMakeAVI ) g_cBass.PlayMP3();
    }

    HDC hDC = BeginPaint( m_hWnd, &stPaint );
    glClearColor( 0, 0, 0, 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( l_bMakeAVI )
    {
      g_pEffManage->PlayEffects( l_fAVITime );

      l_fAVITime += 1/25.; // about 30 fps

      if ( l_fAVITime > 254 )
        PostMessage( g_pMainFrame->GetWindowHandle(), WM_CLOSE, 0, 0 );
    }
    else
      g_pEffManage->PlayEffects( m_pTimer->GetCurTime() - l_fFirstFrameTime );


    if ( l_bMakeAVI )
    {
      void* pCompressedData;
      BOOL bKeyFrame;
      LONG iMaxSize = iAVIWidth*iAVIHeight*3;

      glReadBuffer( GL_BACK );
      glReadPixels( 0, 0, iAVIWidth, iAVIHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pAVIBuffer );

      pCompressedData = ICSeqCompressFrame( &stCompVars, 0, pAVIBuffer, &bKeyFrame, &iMaxSize );

      if ( !pCompressedData )
      {
        ErrorQuit( "[MainFrame_c::OnPaint] Cant compress frame!\n" );
        return false;
      }

      if ( AVIStreamWrite(pAVIStream, lAVIStreamSize, 1, pCompressedData, iMaxSize, AVIIF_KEYFRAME, NULL, NULL) != 0 )
      {
        ErrorQuit( "[MainFrame_c::OnPaint] Cant write to avi stream!\n" );
        return false;
      }

      lAVIStreamSize++;
    }

    SwapBuffers( hDC );
    EndPaint( m_hWnd, &stPaint );
#else
    m_pTimer->Update();

    if ( l_bFirstRenderFrame )
    {
      l_fFirstFrameTime = m_pTimer->GetCurTime();
      l_bFirstRenderFrame = false;
      //if ( !l_bMakeAVI ) g_cBass.PlayMP3();
    }

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glViewport(0, 0, 1280, 720);

    g_pEffManage->PlayEffects( m_pTimer->GetCurTime() - l_fFirstFrameTime );
#endif
    return true;
}

#ifdef WIN32
LRESULT CDemoFrame::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

        switch ( uMsg )
        {
          case WM_KEYDOWN:
          {
            switch ( wParam )
            {
              case VK_ESCAPE: 
                g_cBass.StopMP3();
                PostMessage( m_hWnd, WM_CLOSE, 0, 0 );
                return 0;

              case VK_UP:
              {
                
              } return 0;

              case VK_DOWN:
              {
                
              } return 0;
            }
          }

          default:
            return MainFrame_c::WindowProc( hWnd, uMsg, wParam, lParam );
        }
}
#endif
