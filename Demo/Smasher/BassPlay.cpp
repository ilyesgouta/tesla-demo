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
