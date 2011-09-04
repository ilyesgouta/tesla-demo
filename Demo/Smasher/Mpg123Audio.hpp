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

#if !defined (_MPG123_PLAY_HPP_)
#define _MPG123_PLAY_HPP_

#include <mpg123.h>
#include <pthread.h>
#include <alsa/asoundlib.h>

class CMpg123Audio {

friend void* decodeThread(void* data);
friend void* outputThread(void* data);

public:
    CMpg123Audio(int nBuffers);
    ~CMpg123Audio();

    bool LoadMP3( char* pszFileName );
    bool PlayMP3();
    void StopMP3();

private:
    mpg123_handle *m_hMPG123;

    long m_rate;
    int m_channels, m_encoding;

    int m_nBuffers;
    int m_outputBufferSize;

    unsigned char** m_buffer;

    bool m_decode;
    pthread_t m_decodeThread;

    snd_pcm_t *m_hPCM;

    bool InitializeDevice();
    int WriteBuffer(unsigned char* buf, int bytes);
    void CloseDevice();
};

extern CMpg123Audio g_cMpg123;

#endif
