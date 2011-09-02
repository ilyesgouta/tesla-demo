
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
