
#include "stdafx.h"
#include "BassPlay.hpp"

CBassWrapper g_cBass;

/*******************************************************************************************/
void CALLBACK LoopSync( HSYNC handle, DWORD channel, DWORD data ) {

        BASS_Free();
        PostMessage( g_pMainFrame->GetWindowHandle(), WM_CLOSE, 0, 0 );
}
/*******************************************************************************************/
void CALLBACK Sync( HSYNC handle, DWORD channel, DWORD data ) {

}
/*******************************************************************************************/
CBassWrapper::CBassWrapper() {

        m_dwStartTime = 0;
        m_dwCurTime = 0;
        m_hMP3Strem = 0;
        m_dwPos = 0;
        m_dwLevel = 0;
        m_bMono = false;

        if ( BASS_GetVersion() != MAKELONG(0,7) )
        {
          m_bSoundAvailable = false;
	  return;
	}

	if ( !BASS_Init(-1, 44100, 0, GetForegroundWindow()) )
        {
          m_bSoundAvailable = false;
	  return;
        }

        m_bSoundAvailable = true;
}
/*******************************************************************************************/
CBassWrapper::~CBassWrapper() {

        m_hMP3Strem = 0;
	BASS_Free();
}
/*******************************************************************************************/
bool CBassWrapper::LoadMP3( char* pszFileName ) {

        if ( !m_bSoundAvailable ) return false;

	if ( m_hMP3Strem = BASS_StreamCreateFile(FALSE, pszFileName, 0, 0, 0) )
        {
	  m_bMono = BASS_ChannelGetFlags( m_hMP3Strem )&BASS_SAMPLE_MONO;
	  BASS_ChannelSetSync( m_hMP3Strem, BASS_SYNC_END, 0, &LoopSync );
          BASS_Start();
  	  m_dwStartTime = timeGetTime();
          return true;
	}
        else        
          return false;
}
/*******************************************************************************************/
bool CBassWrapper::PlayMP3() {
      
          if ( !m_hMP3Strem ) return false;

          BASS_StreamPlay( m_hMP3Strem, FALSE, BASS_SAMPLE_LOOP );
          m_dwStartTime = timeGetTime();
          return true;
}
/*******************************************************************************************/
void CBassWrapper::StopMP3() {

        m_hMP3Strem = 0;
	BASS_Free();
}
/*******************************************************************************************/
