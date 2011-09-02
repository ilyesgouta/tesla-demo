//
// Alsa output module for libmpg123, based on code from the original mpg123 package.
//
// Copyright 2006-8 by the mpg123 project - free software under the terms of the LGPL 2.1
// see COPYING and AUTHORS files in distribution or http://mpg123.org
//

#include "Mpg123Audio.hpp"

#include <stdio.h>

#include <iostream>

using namespace std;

CMpg123Audio g_cMpg123(2);

static const struct {
    snd_pcm_format_t alsa;
    int mpg123;
} format_map[] = {
    { SND_PCM_FORMAT_S16,    MPG123_ENC_SIGNED_16   },
    { SND_PCM_FORMAT_U16,    MPG123_ENC_UNSIGNED_16 },
    { SND_PCM_FORMAT_U8,     MPG123_ENC_UNSIGNED_8  },
    { SND_PCM_FORMAT_S8,     MPG123_ENC_SIGNED_8    },
    { SND_PCM_FORMAT_A_LAW,  MPG123_ENC_ALAW_8      },
    { SND_PCM_FORMAT_MU_LAW, MPG123_ENC_ULAW_8      },
    { SND_PCM_FORMAT_S32,    MPG123_ENC_SIGNED_32   },
    { SND_PCM_FORMAT_U32,    MPG123_ENC_UNSIGNED_32 },
    { SND_PCM_FORMAT_FLOAT,  MPG123_ENC_FLOAT_32    },
    { SND_PCM_FORMAT_FLOAT64, MPG123_ENC_FLOAT_64   }
};
#define NUM_FORMATS (sizeof format_map / sizeof format_map[0])

static void error_ignorer(const char *file, int line, const char *function, int err, const char *fmt,...)
{
}

bool CMpg123Audio::InitializeDevice()
{
    snd_pcm_hw_params_t *hw = NULL;
    snd_pcm_sw_params_t *sw = NULL;

    snd_pcm_uframes_t buffer_size;
    snd_pcm_uframes_t period_size;

    unsigned int rate;
    int i;

    snd_lib_error_set_handler(error_ignorer);

    if (snd_pcm_open(&m_hPCM, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0)
        return -1;

    snd_pcm_hw_params_alloca(&hw);
    if (snd_pcm_hw_params_any(m_hPCM, hw) < 0) {
        cout << "InitializeDevice(): no configuration available\n";
        return false;
    }

    if (snd_pcm_hw_params_set_access(m_hPCM, hw, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
        cout << "InitializeDevice(): device does not support interleaved access\n";
        return false;
    }

    int format = m_encoding;
    for (i = 0; i < NUM_FORMATS; ++i) {
        if (format == format_map[i].mpg123) {
            format = format_map[i].alsa;
            break;
        }
    }

    if (format == SND_PCM_FORMAT_UNKNOWN) {
        cout << "InitializeDevice(): invalid sample format " << format << "\n";
        return false;
    }

    if (snd_pcm_hw_params_set_format(m_hPCM, hw, (snd_pcm_format_t)format) < 0) {
        cout << "InitializeDevice(): cannot set format " << snd_pcm_format_name((snd_pcm_format_t)format) << "\n";
        return false;
    }

    cout << "SND_PCM format: " << snd_pcm_format_name((snd_pcm_format_t)format) << "\n";

    if (snd_pcm_hw_params_set_channels(m_hPCM, hw, m_channels) < 0) {
        cout << "InitializeDevice(): cannot set " << m_channels << "channels\n";
        return false;
    }

    cout << "SND_PCM channles: " << m_channels << "\n";

    rate = m_rate;
    if (snd_pcm_hw_params_set_rate_near(m_hPCM, hw, &rate, NULL) < 0) {
        cout << "InitializeDevice(): cannot set rate " << rate << "\n";
        return false;
    }

    if (rate != m_rate) {
        cout << "InitializeDevice(): rate " << m_rate << " not available!\n";
        return false;
    }

    cout << "SND_PCM sampling rate: " << m_rate << "\n";

    buffer_size = m_outputBufferSize;
    if (snd_pcm_hw_params_set_buffer_size_near(m_hPCM, hw, &buffer_size) < 0) {
        cout << "InitializeDevice(): cannot set buffer size\n";
        return false;
    }

    cout << "SND_PCM buffer size: " << buffer_size << "\n";

    period_size = buffer_size / 4;
    if (snd_pcm_hw_params_set_period_size_near(m_hPCM, hw, &period_size, NULL) < 0) {
        cout << "InitializeDevice(): cannot set period size\n";
        return false;
    }

    cout << "SND_PCM period size: " << period_size << "\n";

    if (snd_pcm_hw_params(m_hPCM, hw) < 0) {
        cout << "InitializeDevice(): cannot set hw params\n";
        return false;
    }

    snd_pcm_sw_params_alloca(&sw);
    if (snd_pcm_sw_params_current(m_hPCM, sw) < 0) {
        cout << "InitializeDevice(): cannot get sw params\n";
        return false;
    }

    if (snd_pcm_sw_params_set_start_threshold(m_hPCM, sw, 0) < 0) {
        cout << "InitializeDevice(): cannot set start threshold\n";
        return false;
    }

    if (snd_pcm_sw_params_set_avail_min(m_hPCM, sw, 2048) < 0) {
        cout << "InitializeDevice(): cannot set min available\n";
        return false;
    }

    if (snd_pcm_sw_params(m_hPCM, sw) < 0) {
        cout << "InitializeDevice(): cannot set sw params\n";
        return false;
    }

    return true;
}

int CMpg123Audio::WriteBuffer(unsigned char *buf, int bytes)
{
    snd_pcm_uframes_t frames;
    snd_pcm_sframes_t written;

    frames = snd_pcm_bytes_to_frames(m_hPCM, bytes);
    written = snd_pcm_writei(m_hPCM, buf, frames);

    if (written == -EINTR) /* interrupted system call */
        written = 0;
    else
        if (written == -EPIPE) { /* underrun */
            if (snd_pcm_prepare(m_hPCM) >= 0)
                written = snd_pcm_writei(m_hPCM, buf, frames);
        }

    if (written >= 0)
        return snd_pcm_frames_to_bytes(m_hPCM, written);
    else
    {
        if (snd_pcm_state(m_hPCM) == SND_PCM_STATE_SUSPENDED)
        {
            snd_pcm_resume(m_hPCM);
            if (snd_pcm_state(m_hPCM) == SND_PCM_STATE_SUSPENDED)
                return -1;
        }
        return 0;
    }
}

void CMpg123Audio::CloseDevice()
{
    snd_pcm_drop(m_hPCM);
    snd_pcm_prepare(m_hPCM);

    if (m_hPCM != NULL)
    {
        if (snd_pcm_state(m_hPCM) == SND_PCM_STATE_RUNNING)
            snd_pcm_drain(m_hPCM);

        snd_pcm_close(m_hPCM);
    }
}

CMpg123Audio::CMpg123Audio(int nBuffers = 2)
{
    m_hMPG123 = 0;

    m_rate = m_channels = m_encoding = 0;

    m_nBuffers = nBuffers;
    m_outputBufferSize = 0;

    m_buffer = new unsigned char*[nBuffers];
}

CMpg123Audio::~CMpg123Audio()
{
    if (m_hMPG123)
        mpg123_delete(m_hMPG123);

    m_hMPG123 = 0;

    mpg123_exit();

    delete [] m_buffer;
}

void* decodeThread(void* data)
{
    CMpg123Audio* Mpg123Audio = (CMpg123Audio*)data;

    size_t decoded_bytes;
    int index = 0;

    while (Mpg123Audio->m_decode)
    {
        snd_pcm_wait(Mpg123Audio->m_hPCM, 1000);

        int frames = snd_pcm_avail_update(Mpg123Audio->m_hPCM);

        int bytes = snd_pcm_frames_to_bytes(Mpg123Audio->m_hPCM, frames);
        int buffer_size = bytes > Mpg123Audio->m_outputBufferSize ? Mpg123Audio->m_outputBufferSize : bytes;

        mpg123_read(Mpg123Audio->m_hMPG123, Mpg123Audio->m_buffer[index], buffer_size, &decoded_bytes);

        Mpg123Audio->WriteBuffer(Mpg123Audio->m_buffer[index], decoded_bytes);

        if (++index >= Mpg123Audio->m_nBuffers)
            index = 0;
    }

    return NULL;
}

bool CMpg123Audio::LoadMP3( char* pszFileName )
{
    int ret = 0;

    if ((ret = mpg123_init())) {
        cout << "libmpg123 error: " << mpg123_plain_strerror(ret) << "\n";
        return false;
    }

    m_hMPG123 = mpg123_new(NULL, NULL);

    mpg123_param(m_hMPG123, MPG123_FLAGS, MPG123_FORCE_STEREO, 0);
    mpg123_param(m_hMPG123, MPG123_FORCE_RATE, 44100, 0);

    const char **decoders = mpg123_supported_decoders();

    while (*decoders)
        cout << "suppported MP3 decoder: " << *decoders++ << "\n";

    if (mpg123_open(m_hMPG123, pszFileName)) {
        cout << "libmpg123 error: " << mpg123_strerror(m_hMPG123) << "\n";
        return false;
    }

    mpg123_getformat(m_hMPG123, &m_rate, &m_channels, &m_encoding);

    cout << "MP3 stream's rate: " << m_rate << ", channels: " << m_channels << ", encoding: " << m_encoding << "\n";

    if (mpg123_decoder(m_hMPG123, "generic")) {
        cout << "libmpg123 error: " << mpg123_strerror(m_hMPG123) << "\n";
        return false;
    }

    m_outputBufferSize = mpg123_safe_buffer();

    InitializeDevice();

    return true;
}

bool CMpg123Audio::PlayMP3()
{
    if (!m_hMPG123)
        return false;

    for (int i = 0; i < m_nBuffers; i++)
        m_buffer[i] = new unsigned char[m_outputBufferSize];

    m_decode = true;

    pthread_create(&m_decodeThread, NULL, decodeThread, (void*)this);

    return true;
}

void CMpg123Audio::StopMP3()
{
    m_decode = false;

    pthread_join(m_decodeThread, NULL);

    CloseDevice();

    for (int i = 0; i < m_nBuffers; i++)
        delete [] m_buffer[i];
}
