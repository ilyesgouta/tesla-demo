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