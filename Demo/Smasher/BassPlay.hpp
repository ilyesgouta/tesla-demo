

#if !defined (_BASS_PLAY_HPP_)
#define _BASS_PLAY_HPP_

#include "../../Bass/C/Bass.h"

class CBassWrapper {

public:
        CBassWrapper();
        ~CBassWrapper();

        bool IsSoundAvailable() const {
          return m_bSoundAvailable;
        }

        bool LoadMP3( char* pszFileName );
        bool PlayMP3();
        void StopMP3();

protected:


        DWORD m_dwStartTime;
        DWORD m_dwCurTime;
        DWORD m_dwPos;
        DWORD m_dwLevel;
        BOOL m_bMono;

        HSTREAM m_hMP3Strem;

        bool m_bSoundAvailable;

};

extern CBassWrapper g_cBass;

#endif 