#ifdef WIN32
#include "stdafx.h"
#endif

#include <stdlib.h>

#include "Bands.hpp"

static float frand(void)
{
 return (float)rand() / (float)RAND_MAX;
}

CBand::CBand(float fNewBandWidth,
             float fNewSF)
{
    int nS;

#ifdef GL_VERSION_ES_CM_1_1
    glGenBuffers(1, &vertexBuffer);
#endif

    fBandWidth = fNewBandWidth;
    fSpeedFactor = fNewSF;

    for (nS = 0; nS <= BAND_SEGMENTS; nS++)
    {
        aPts[nS][0].fX = 0.0f;
        aPts[nS][0].fY = 0.0f;
        aPts[nS][0].fZ = BAND_NEAR_PLANE + (BAND_FAR_PLANE - BAND_NEAR_PLANE) * nS / (BAND_SEGMENTS+1);
        aPts[nS][1].fX = 0.0f;
        aPts[nS][1].fY = 0.0f;
        aPts[nS][1].fZ = BAND_NEAR_PLANE + (BAND_FAR_PLANE - BAND_NEAR_PLANE) * nS / (BAND_SEGMENTS+1);
        aAngles[nS] = 0.0f;
        aDraw[nS] = 0;
    }
}

CBand::~CBand()
{
#ifdef GL_VERSION_ES_CM_1_1
    glDeleteBuffers(1, &vertexBuffer);
#endif
}

void
CBand::Render(float fAlpha)
{ 
    int nS;
 
#ifdef GL_VERSION_ES_CM_1_1
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertex), m_Vertex, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(CBandVertex), &m_Vertex[0] + offsetof(CBandVertex, x));

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(CBandVertex), &m_Vertex[0] + offsetof(CBandVertex, r));

    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(CBandVertex), &m_Vertex[0] + offsetof(CBandVertex, s0));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#else
    glBegin(GL_QUADS);
    for (nS = 0; nS < BAND_SEGMENTS; nS++)
        if (aDraw[nS])
        {
            float fA;
            fA = fAlpha * (1.0 - ((float)nS / (float)BAND_SEGMENTS));

            glColor4f(1.0, 1.0, 1.0, fA);

            glTexCoord2f(0.0f, 0.0f);
            glVertex3fv(&(aPts[nS    ][0].fX));

            glTexCoord2f(1.0f, 0.0f);
            glVertex3fv(&(aPts[nS    ][1].fX));

            glTexCoord2f(1.0f, 1.0f);
            glVertex3fv(&(aPts[nS + 1][1].fX));

            glTexCoord2f(0.0f, 1.0f);
            glVertex3fv(&(aPts[nS + 1][0].fX));
        }
    glEnd();
#endif
}

void
CBand::Move(float fMove)
{
    int nS;
 
    fMove *= fSpeedFactor;
    for (nS = 0; nS < BAND_SEGMENTS; nS++)
    {
        aPts[nS][0].fZ += fMove;
        aPts[nS][1].fZ += fMove;
    }

    while (aPts[1][0].fZ > BAND_NEAR_PLANE)
    {
        for (nS = 0; nS < BAND_SEGMENTS; nS++)
        {
            aPts[nS][0] = aPts[nS+1][0];
            aPts[nS][1] = aPts[nS+1][1];
            aAngles[nS] = aAngles[nS+1];
            aDraw[nS] = aDraw[nS+1];
        }

        float fX, fY;
        fX = frand() - 0.5;
        fY = frand() - 0.5;
        float fA = frand() - 0.5f;
        fA *= 2.0f;
        float fR = 1.0 + 0.3 * frand();

        aDraw[BAND_SEGMENTS] = 1;
        aAngles[BAND_SEGMENTS] = aAngles[BAND_SEGMENTS-1] + fA;
        aAngles[BAND_SEGMENTS] = fmod(aAngles[BAND_SEGMENTS], 2.0 * 355.0 / 113.0);

        aPts[BAND_SEGMENTS][0].fX = fX + sin(aAngles[BAND_SEGMENTS]) * fR;
        aPts[BAND_SEGMENTS][0].fY = fY + cos(aAngles[BAND_SEGMENTS]) * fR;
        //aPts[BAND_SEGMENTS][0].fZ = aPts[BAND_SEGMENTS-1][0].fZ + (BAND_FAR_PLANE - BAND_NEAR_PLANE) / BAND_SEGMENTS;
        aPts[BAND_SEGMENTS][0].fZ = BAND_FAR_PLANE;

        aPts[BAND_SEGMENTS][1].fX = fX + sin(aAngles[BAND_SEGMENTS] + fBandWidth) * fR;
        aPts[BAND_SEGMENTS][1].fY = fY + cos(aAngles[BAND_SEGMENTS] + fBandWidth) * fR;
        //aPts[BAND_SEGMENTS][1].fZ = aPts[BAND_SEGMENTS-1][1].fZ + (BAND_FAR_PLANE - BAND_NEAR_PLANE) / BAND_SEGMENTS;
        aPts[BAND_SEGMENTS][1].fZ = BAND_FAR_PLANE;
    }
}

CBands::CBands(int nNewBands)
{
    nBands = nNewBands;
    int nB;
 
    aBands = new CBand *[nBands];
    for (nB = 0; nB < nBands; nB++)
        aBands[nB] = new CBand(0.1f + 0.2f * frand(), 1.0f + 1.0 * frand());

    nTex = g_cTexManager.LoadTexture("data/textures/polka.png", 1);

#if 0
    glGenTextures(1, &nTex);
    CTGA *pTGA = new CTGA("Effect.TGA");
    glBindTexture(GL_TEXTURE_2D, nTex);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 3,
                 pTGA->nWidth,
                 pTGA->nHeight,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 (GLvoid *)(pTGA->pBody));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    delete pTGA;
#endif
    fLastTime = -1.0;
}

CBands::~CBands()
{
    int nB;
    for (nB = 0; nB < nBands; nB++)
        delete aBands[nB];
    delete[] aBands;
}

void 
CBands::Render(void)
{
    int nB;

    glBindTexture(GL_TEXTURE_2D, nTex);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    //glColor3f(0.1, 0.1, 0.5);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDisable(GL_DEPTH_TEST);

#if 0
    glEnable(GL_FOG);
    float aFogColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 0.0f/*-0.5 * (BAND_NEAR_PLANE + BAND_FAR_PLANE)*/);
    glFogf(GL_FOG_END, -BAND_FAR_PLANE);
    glFogfv(GL_FOG_COLOR, aFogColor);
#endif

    float fAlpha = 1.0;
    if (fLastTime >= 69.0 && fLastTime < 69.0 + 1.0)
    {
        fAlpha = fLastTime - 69.0;
    }
    else
    if (fLastTime >= 84.0 && fLastTime < 84.0 + 1.0)
    {
        fAlpha = 1.0 - (fLastTime - 84.0);
    }

    for (nB = 0; nB < nBands; nB++)
    {
        aBands[nB]->Render(fAlpha);
    }
}

void 
CBands::Move(float fMove)
{
    int nB;

    for (nB = 0; nB < nBands; nB++)
        aBands[nB]->Move(fMove);
}

void
CBands::Do(float fTime, float fTimeStart)
{
    float fDelta;

    if (fLastTime < 0.0)
    {
        fDelta = 0.0f;
    }
    else
    {
        fDelta = fTime - fLastTime;
    }

    fLastTime = fTime;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustumf(-0.5, 0.5,
               -0.375, 0.375,
               -BAND_NEAR_PLANE, -BAND_FAR_PLANE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(fTime * 50.0, 0.0, 0.0, 1.0);
    glRotatef(20.0 * sin(fTime*1.0), 1.0, 0.0, 0.0);
    glRotatef(20.0 * sin(fTime*2.0), 0.0, 1.0, 0.0);

    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);

    Move(fDelta * 10.0);
    Render();
}
