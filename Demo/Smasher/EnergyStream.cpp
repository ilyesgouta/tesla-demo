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

#ifdef WIN32
#include "stdafx.h"
#endif

#include "EnergyStream.hpp" 

static float l_fChangeTime = 15;
static float l_fChangeTime1 = 25;
static float l_fChangeTime2 = 38;
static float l_fChangeTime2a = 46;
static float l_fChangeTime3 = 58;

CFlareStream::CFlareStream()
{
    m_iFlares = 0;
    m_pFlares = 0;
    m_iGLFlareTex = -1;
}

CFlareStream::~CFlareStream()
{
    if ( m_iGLFlareTex != -1 ) g_cTexManager.ReleaseTexture( m_iGLFlareTex );
    if ( m_pFlares ) delete[] m_pFlares;
}

void CFlareStream::Init( int iSeed, int iGLFlareTex, const CVector& cBasePos, float fSpeed )
{
    m_pFlares = new CVector[iSeed];
    m_iFlares = iSeed;
    m_iGLFlareTex = iGLFlareTex;
    m_fSpeed = fSpeed;

    for ( int i = 0; i != m_iFlares; i++ )
    {
        m_pFlares[i].fX = -800.0f * rand() / RAND_MAX - 1150;
        m_pFlares[i].fY = 10.0f * rand() / RAND_MAX - 20;
        m_pFlares[i].fZ = 10.0f * rand() / RAND_MAX - 20;
        m_pFlares[i] = m_pFlares[i] + cBasePos;
    }
}

void CFlareStream::Render( float fTime, CVector& cBaseX, CVector& cBaseY, float fAlpha )
{
    static const int l_fFlareSize = 10;

    if ( m_iGLFlareTex == -1 ) return;
    if ( !m_pFlares ) return;

    CVector cFlarePos;

    if ( fTime < l_fChangeTime ) return;

    fTime -= l_fChangeTime;

    glColor4f( 1, 1, 1, fAlpha );
    glBindTexture( GL_TEXTURE_2D, m_iGLFlareTex );

#ifdef GL_VERSION_ES_CM_1_1
    glClientActiveTexture(GL_TEXTURE0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
#else
    glBegin( GL_QUADS );
#endif

    float fMultipler = 1;

    if ( fTime + l_fChangeTime > l_fChangeTime1 )
    {
        if ( fTime + l_fChangeTime > l_fChangeTime2 )
        {
            fMultipler = 2.5;
        }
        else
            fMultipler = 2;
    }

#ifdef WIN32
    char szDbg[256];

    sprintf( szDbg, "mult %f\n", fMultipler );
    OutputDebugString( szDbg );
#endif

    for ( int i = 0; i != m_iFlares; i++ )
    {
        cFlarePos.fX = fmod( m_pFlares[i].fX + fTime * m_fSpeed * fMultipler, 800 ) - 400;
        cFlarePos.fY = m_pFlares[i].fY + 2 * sin(fTime * 7 + m_pFlares[i].fX );
        cFlarePos.fZ = m_pFlares[i].fZ + 2 * cos(fTime * 7 + i * 3.14);

#ifdef GL_VERSION_ES_CM_1_1
        m_Vertex[0].x = (cFlarePos - cBaseX - cBaseY).fX;
        m_Vertex[0].y = (cFlarePos - cBaseX - cBaseY).fY;
        m_Vertex[0].z = (cFlarePos - cBaseX - cBaseY).fZ;
        m_Texture[0].s0 = 0; m_Texture[0].t0 = 1;

        m_Vertex[1].x = (cFlarePos - cBaseX + cBaseY).fX;
        m_Vertex[1].y = (cFlarePos - cBaseX + cBaseY).fY;
        m_Vertex[1].z = (cFlarePos - cBaseX + cBaseY).fZ;
        m_Texture[1].s0 = 0; m_Texture[1].t0 = 0;

        m_Vertex[2].x = (cFlarePos + cBaseX - cBaseY).fX;
        m_Vertex[2].y = (cFlarePos + cBaseX - cBaseY).fY;
        m_Vertex[2].z = (cFlarePos + cBaseX - cBaseY).fZ;
        m_Texture[2].s0 = 1; m_Texture[2].t0 = 1;

        m_Vertex[3].x = (cFlarePos + cBaseX + cBaseY).fX;
        m_Vertex[3].y = (cFlarePos + cBaseX + cBaseY).fY;
        m_Vertex[3].z = (cFlarePos + cBaseX + cBaseY).fZ;
        m_Texture[3].s0 = 1; m_Texture[3].t0 = 0;

        glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
        glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#else
        glTexCoord2f( 0, 0 );
        glVertex3fv( (float*)&(cFlarePos - cBaseX + cBaseY) );
        glTexCoord2f( 1, 0 );
        glVertex3fv( (float*)&(cFlarePos + cBaseX + cBaseY) );
        glTexCoord2f( 1, 1 );
        glVertex3fv( (float*)&(cFlarePos + cBaseX - cBaseY) );
        glTexCoord2f( 0, 1 );
        glVertex3fv( (float*)&(cFlarePos - cBaseX - cBaseY) );
#endif
    }

#ifdef GL_VERSION_ES_CM_1_1
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
    glEnd();
#endif
}

void CEnergyStream::PutQuad( CTexel cUVPos )
{
#ifdef GL_VERSION_ES_CM_1_1
    m_Vertex[0].x = -300;
    m_Vertex[0].y = -300;
    m_Vertex[0].z = 0;
    m_Texture[0].s0 = 0 + cUVPos.fU; m_Texture[0].t0 = 1 + cUVPos.fV;

    m_Vertex[1].x = -300;
    m_Vertex[1].y = 300;
    m_Vertex[1].z = 0;
    m_Texture[1].s0 = 0 + cUVPos.fU; m_Texture[1].t0 = 0 + cUVPos.fV;

    m_Vertex[2].x = 300;
    m_Vertex[2].y = -300;
    m_Vertex[2].z = 0;
    m_Texture[2].s0 = 1 + cUVPos.fU; m_Texture[2].t0 = 1 + cUVPos.fV;

    m_Vertex[3].x = 300;
    m_Vertex[3].y = 300;
    m_Vertex[3].z = 0;
    m_Texture[3].s0 = 1 + cUVPos.fU; m_Texture[3].t0 = 0 + cUVPos.fV;

    glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
    glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#else
    glTexCoord2f( 0 + cUVPos.fU, 0 + cUVPos.fV );
    glVertex3f( -300, 300, 0 );
    glTexCoord2f( 1 + cUVPos.fU, 0 + cUVPos.fV );
    glVertex3f( 300, 300, 0 );
    glTexCoord2f( 1 + cUVPos.fU, 1 + cUVPos.fV );
    glVertex3f( 300, -300, 0 );
    glTexCoord2f( 0 + cUVPos.fU, 1 + cUVPos.fV );
    glVertex3f( -300, -300, 0 );
#endif
}

CEnergyStream::CEnergyStream()
{
    m_iGLTex1 = g_cTexManager.LoadTexture( "data/textures/y7.jpg" );
    m_iGLTex2 = g_cTexManager.LoadTexture( "data/textures/y6.jpg" );

    m_pFStreams = new CFlareStream[16];
    m_iFStreams = 16;

    int iFlareTex = g_cTexManager.LoadTexture("data/textures/flare02.jpg");

    m_pFStreams[0].Init( 50, iFlareTex, CVector(0, 50, 0), 300 );
    m_pFStreams[1].Init( 50, iFlareTex, CVector(0, 0, 0), 150 );
    m_pFStreams[2].Init( 50, iFlareTex, CVector(0, 90, 60), 250 );
    m_pFStreams[3].Init( 50, iFlareTex, CVector(0, -100, 30), 160 );
    m_pFStreams[4].Init( 50, iFlareTex, CVector(0, 50, -100), 340 );
    m_pFStreams[5].Init( 50, iFlareTex, CVector(0, -50, 50), 270  );
    m_pFStreams[6].Init( 50, iFlareTex, CVector(0, 100, 50), 180 );
    m_pFStreams[7].Init( 50, iFlareTex, CVector(0, -30, 90), 130 );

    m_pFStreams[8].Init( 50, iFlareTex, CVector(0, 150, 10), 200 );
    m_pFStreams[9].Init( 50, iFlareTex, CVector(0, 100, -100), 210 );
    m_pFStreams[10].Init( 50, iFlareTex, CVector(0, 190, 160), 220 );
    m_pFStreams[11].Init( 50, iFlareTex, CVector(0, -200, 130), 230 );
    m_pFStreams[12].Init( 50, iFlareTex, CVector(0, 150, -200), 240 );
    m_pFStreams[13].Init( 50, iFlareTex, CVector(0, -150, 250), 160 );
    m_pFStreams[14].Init( 50, iFlareTex, CVector(0, 200, 150), 230 );
    m_pFStreams[15].Init( 50, iFlareTex, CVector(0, -130, 190), 250 );
}

CEnergyStream::~CEnergyStream()
{
    g_cTexManager.ReleaseTexture( m_iGLTex1 );
    g_cTexManager.ReleaseTexture( m_iGLTex2 );
}

void CEnergyStream::Do( float fTime, float fTimeStart )
{
    fTime -= fTimeStart;

    int i;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustumf( -.6f, .6f, -.45f, .45f, 1, 1000 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDepthMask( 0 );

    glTranslatef( 0, 0, -300 );
    glRotatef( fTime*30, 1, 0, 0 );
    glRotatef( 30*sin(fTime/3) + 10, 0, 0, 1 );

    if ( fTime > l_fChangeTime1 )
    {
        if ( fTime > l_fChangeTime2 )
        {
            glRotatef( 90, 0, 1, 0 );
        }
        else
            glRotatef( 180, 0, 1, 0 );
    }

    glEnable( GL_FOG );
    glFogf( GL_FOG_START, 200 );
    glFogf( GL_FOG_END, 500 );
    glFogf( GL_FOG_MODE, GL_LINEAR );

    glPushMatrix();

    CTexel cUVPos(0, 0);
    float fAlpha = 1;

    if ( fTime > l_fChangeTime )
    {
        cUVPos = CTexel(.1*sin(fTime), fTime/5);
        glBindTexture( GL_TEXTURE_2D, m_iGLTex2 );
        fAlpha = fTime - l_fChangeTime;

        clamp( &fAlpha );

        if ( fTime > l_fChangeTime1 )
        {
            fAlpha *= ( fTime - l_fChangeTime1 );
            clamp( &fAlpha );
            glRotatef( 90, 0, 1, 0 );

            if ( fTime > l_fChangeTime2 )
            {
                fAlpha *= ( fTime - l_fChangeTime2 );
                clamp( &fAlpha );

                if ( fTime > l_fChangeTime3 )
                {
                    fAlpha *= ( 1 + l_fChangeTime3 - fTime );
                    clamp( &fAlpha );
                }
            }
            else
            {
                fAlpha *= ( l_fChangeTime2 - fTime );
                clamp( &fAlpha );
            }
        }
        else
        {
            fAlpha *= ( l_fChangeTime1 - fTime );
            clamp( &fAlpha );
        }

        glColor4f( 1, 1, 1, fAlpha );
    }
    else
    {
        glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );
        fAlpha = (l_fChangeTime - fTime)*.5;
        clamp( &fAlpha );
        glColor4f( 1, 1, 1, (sin(fTime*2)*.25 + .75)*fAlpha );//(sin(fTime*2)*.5 + 1)*fAlpha );
    }

    if ( fTime > l_fChangeTime )
    {
        for ( i = 0; i != 4; i++ )
        {
#ifdef GL_VERSION_ES_CM_1_1
            glClientActiveTexture(GL_TEXTURE0);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
#else
            glBegin( GL_QUADS );
#endif

            PutQuad( cUVPos );
#ifdef GL_VERSION_ES_CM_1_1
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
            glEnd();
#endif
            glRotatef( 180/3, 1, 0, 0 );
        }
    }
    else
        for ( i = 0; i != 8; i++ )
        {
#ifdef GL_VERSION_ES_CM_1_1
            glClientActiveTexture(GL_TEXTURE0);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
#else
            glBegin( GL_QUADS );
#endif
            PutQuad( cUVPos );
#ifdef GL_VERSION_ES_CM_1_1
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
            glEnd();
#endif
            glRotatef( 180/7, 1, 0, 0 );
        }

    glPopMatrix();

    CMatrix cCamera;

    glGetFloatv( GL_MODELVIEW_MATRIX, (float*)cCamera.m_.aMatrix );

    cCamera.Inverse();


    for ( i = 0; i != m_iFStreams; i++ )
    {
        CVector v1 = (cCamera.m_.sMatrix.stBaseX * 10);
        CVector v2 = (cCamera.m_.sMatrix.stBaseY * 10);
        m_pFStreams[i].Render( fTime, v1, v2, fAlpha );
    }

    glDisable( GL_FOG );
}
