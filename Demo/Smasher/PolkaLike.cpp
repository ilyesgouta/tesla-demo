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

#include "PolkaLike.hpp"

static const float l_fZMax = 300;

static float l_fChangeTime = 10;
static float l_fChangeTime1 = 20;
static float l_fChangeTime3 = 19;

static float l_fTime;

inline void TrackElem_c::Update( float fDelTime )
{
    m_cPosition = m_cPosition + m_cDelPos * fDelTime;
    m_fAnlgeZ += -2 * 1.234f * fDelTime;
}

PolkaLike_c::PolkaLike_c()
{
    Init();
}

PolkaLike_c::~PolkaLike_c()
{
    if ( m_pTracks )
        delete[] m_pTracks;

    g_cTexManager.ReleaseTexture( m_iTexture );
    g_cTexManager.ReleaseTexture( m_iBack );
}

void PolkaLike_c::Init()
{
    int iTracks = 4;
    int iTrackElems = 64;

    m_pTracks = new Track_c[iTracks];
    m_iTracks = iTracks;

    m_pTracks[0].Init( iTrackElems, pi/2.13, pi/3.41 );
    m_pTracks[1].Init( iTrackElems, pi/2.93, pi/1.72 );
    m_pTracks[2].Init( iTrackElems, pi/3.97, pi );
    m_pTracks[3].Init( iTrackElems, pi*1.23, pi*2.17 );

    m_iTexture = g_cTexManager.LoadTexture( "data/textures/polka.png" );
    m_iBack = g_cTexManager.LoadTexture( "data/textures/max_t3.jpg" );
}

void PolkaLike_c::PutQuad( float fZ )
{
#ifdef GL_VERSION_ES_CM_1_1
    m_Vertex[0].x = -1;
    m_Vertex[0].y = -1;
    m_Vertex[0].z = fZ;
    m_Texture[0].s0 = 0; m_Texture[0].t0 = 1;

    m_Vertex[1].x = -1;
    m_Vertex[1].y = 1;
    m_Vertex[1].z = fZ;
    m_Texture[1].s0 = 0; m_Texture[1].t0 = 0;

    m_Vertex[2].x = 1;
    m_Vertex[2].y = -1;
    m_Vertex[2].z = fZ;
    m_Texture[2].s0 = 1; m_Texture[2].t0 = 1;

    m_Vertex[3].x = 1;
    m_Vertex[3].y = 1;
    m_Vertex[3].z = fZ;
    m_Texture[3].s0 = 1; m_Texture[3].t0 = 0;

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#else
    glBegin( GL_QUADS );
    glTexCoord2f( 0, 0 );
    glVertex3f( -1, 1, fZ );
    glTexCoord2f( 1, 0 );
    glVertex3f(  1, 1, fZ );
    glTexCoord2f( 1, 1 );
    glVertex3f( 1, -1, fZ );
    glTexCoord2f( 0, 1 );
    glVertex3f( -1, -1, fZ );
    glEnd();
#endif
}

void PolkaLike_c::Do( float fTime, float fTimeStart )
{
    fTime -= fTimeStart;
    l_fTime = fTime;

    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();
    glFrustumf( -.6f, .6f, -.45f, .45f, 1, l_fZMax );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
    glEnable( GL_TEXTURE_2D );

    glBindTexture( GL_TEXTURE_2D, m_iBack );

    float fAlpha = fTime * .5f;
    clamp( &fAlpha );

    float fCol = .25 * sin(fTime) + .5;

    glColor4f( 1, 1, 1, fCol * fAlpha );

    glClientActiveTexture(GL_TEXTURE0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
    glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);

    for ( int a = 0; a != 16; a++ )
    {
        float fZ = -1.4f;
        glRotatef( 4 * sin(fTime), 0, 1, 0 );
        glRotatef( 5 * fTime, 0, 0, 1 );

        PutQuad( fZ - 1 * a );
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindTexture( GL_TEXTURE_2D, m_iTexture );

    for ( int i = 0; i != m_iTracks; i++ )
        m_pTracks[i].Render( .016, fTime );
}

Track_c::Track_c()
{
    m_pTrackElems = 0;
    m_iTrackElems = 0;

    m_fInitAngleZ = 0;
    m_fInitAngleChange = 0;

    m_cInitPos = CVector(0, 0, 0);
    m_fInitPos = 0;
    m_fInitPosChange = 0;

    m_triBufSize = 32 * 3;
    m_triCurrentIndex = 0;

    m_Vertex = new CVertex[m_triBufSize];
    m_Texture = new CTex[m_triBufSize];
    m_Color = new CColor[m_triBufSize];

    for (int i = 0; i < m_triBufSize; i++)
        m_Color[i].r = m_Color[i].g = m_Color[i].b = 1.0f;
}

void Track_c::Init( int iElems, float fInitAngleChange, float fInitPosChange )
{
    m_iTrackElems = iElems;
    m_pTrackElems = new TrackElem_c[iElems];

    CVector cDelPos( 0, 0, 100 );

    m_fInitAngleChange = fInitAngleChange;
    m_fInitPosChange = fInitPosChange;

    for ( int i = 0; i != m_iTrackElems; i++ )
    {
        m_cInitPos.fX = (float)(10 * cos(m_fInitPos) + 10 * sin(m_fInitPos * 1.32));
        m_cInitPos.fY = (float)(15 * sin(m_fInitPos) + 5 * sin(m_fInitPos * .89) );
        m_cInitPos.fZ = -3 * l_fZMax - (l_fZMax / m_iTrackElems) * i;

        m_pTrackElems[i].Init( m_cInitPos, cDelPos, m_fInitAngleZ );

        m_fInitAngleZ += m_fInitAngleChange * .042f;
        m_fInitPos += m_fInitPosChange * .042f;
    }
}

void Track_c::glPutFace(const CVector& cV1, const CVector& cV2, const CVector& cV3, const CVector& cV4, float alpha)
{
    if (m_triCurrentIndex == m_triBufSize) {
        glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
        glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);
        glColorPointer(4, GL_FLOAT, 0, m_Color);

        glDrawArrays(GL_TRIANGLES, 0, m_triBufSize);

        m_triCurrentIndex = 0;
    } else {
        m_Vertex[m_triCurrentIndex].x = cV1.fX;
        m_Vertex[m_triCurrentIndex].y = cV1.fY;
        m_Vertex[m_triCurrentIndex].z = cV1.fZ;

        m_Texture[m_triCurrentIndex].s0 = 0;
        m_Texture[m_triCurrentIndex].t0 = 1;

        m_Color[m_triCurrentIndex].a = alpha;

        m_triCurrentIndex++;

        m_Vertex[m_triCurrentIndex].x = cV2.fX;
        m_Vertex[m_triCurrentIndex].y = cV2.fY;
        m_Vertex[m_triCurrentIndex].z = cV2.fZ;

        m_Texture[m_triCurrentIndex].s0 = 0;
        m_Texture[m_triCurrentIndex].t0 = 0;

        m_Color[m_triCurrentIndex].a = alpha;

        m_triCurrentIndex++;

        m_Vertex[m_triCurrentIndex].x = cV3.fX;
        m_Vertex[m_triCurrentIndex].y = cV3.fY;
        m_Vertex[m_triCurrentIndex].z = cV3.fZ;

        m_Texture[m_triCurrentIndex].s0 = 1;
        m_Texture[m_triCurrentIndex].t0 = 1;

        m_Color[m_triCurrentIndex].a = alpha;

        m_triCurrentIndex++;

        m_Vertex[m_triCurrentIndex].x = cV3.fX;
        m_Vertex[m_triCurrentIndex].y = cV3.fY;
        m_Vertex[m_triCurrentIndex].z = cV3.fZ;

        m_Texture[m_triCurrentIndex].s0 = 1;
        m_Texture[m_triCurrentIndex].t0 = 1;

        m_Color[m_triCurrentIndex].a = alpha;

        m_triCurrentIndex++;

        m_Vertex[m_triCurrentIndex].x = cV4.fX;
        m_Vertex[m_triCurrentIndex].y = cV4.fY;
        m_Vertex[m_triCurrentIndex].z = cV4.fZ;

        m_Texture[m_triCurrentIndex].s0 = 1;
        m_Texture[m_triCurrentIndex].t0 = 0;

        m_Color[m_triCurrentIndex].a = alpha;

        m_triCurrentIndex++;

        m_Vertex[m_triCurrentIndex].x = cV2.fX;
        m_Vertex[m_triCurrentIndex].y = cV2.fY;
        m_Vertex[m_triCurrentIndex].z = cV2.fZ;

        m_Texture[m_triCurrentIndex].s0 = 0;
        m_Texture[m_triCurrentIndex].t0 = 0;

        m_Color[m_triCurrentIndex].a = alpha;

        m_triCurrentIndex++;
    }
}

void Track_c::glFlushFaces()
{
    glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
    glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);
    glColorPointer(4, GL_FLOAT, 0, m_Color);

    glDrawArrays(GL_TRIANGLES, 0, m_triCurrentIndex);

    m_triCurrentIndex = 0;
}

void Track_c::Render( float fDelTime, float fTime )
{
    CVector cRot(0, 0, 0);
    CVector cRot1(0, 0, 0);

    glLineWidth(2);

#ifdef GL_VERSION_ES_CM_1_1
    glClientActiveTexture(GL_TEXTURE0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
#else
    glBegin( GL_QUADS );
#endif

    float fAlpha = 1;

    for ( int i = 0; i != m_iTrackElems; i++ )
    {
        m_pTrackElems[i].Update( fDelTime );

        cRot.fX = (float)cos( m_pTrackElems[i].m_fAnlgeZ );//*10;
        cRot.fY = (float)sin( m_pTrackElems[i].m_fAnlgeZ );//*5;
        cRot1.fY = -cRot.fX;
        cRot1.fX = cRot.fY;
        cRot.fX *= 5;
        cRot.fY *= 5;

        fAlpha = -m_pTrackElems[i].m_cPosition.fZ / l_fZMax;

        //glColor4f( 1, 1, 1, fAlpha );

#ifdef GL_VERSION_ES_CM_1_1
        CVector v1 = m_pTrackElems[i].m_cPosition - cRot - cRot1;
        CVector v2 = m_pTrackElems[i].m_cPosition + cRot - cRot1;
        CVector v3 = m_pTrackElems[i].m_cPosition - cRot + cRot1;
        CVector v4 = m_pTrackElems[i].m_cPosition + cRot + cRot1;

        glPutFace(v1, v2, v3, v4, fAlpha);
#else
        glTexCoord2f( 0, 0 );
        glVertex3fv( (float*)&(m_pTrackElems[i].m_cPosition + cRot - cRot1) );

        glTexCoord2f( 1, 0 );
        glVertex3fv( (float*)&(m_pTrackElems[i].m_cPosition + cRot + cRot1) );

        glTexCoord2f( 1, 1 );
        glVertex3fv( (float*)&(m_pTrackElems[i].m_cPosition - cRot + cRot1) );

        glTexCoord2f( 0, 1 );
        glVertex3fv( (float*)&(m_pTrackElems[i].m_cPosition - cRot - cRot1) );
#endif

        if ( l_fTime < l_fChangeTime3 )
            if ( m_pTrackElems[i].m_cPosition.fZ > 0 )
            {
                m_pTrackElems[i].m_cPosition.fZ = -l_fZMax;
                m_pTrackElems[i].m_cPosition.fX = m_cInitPos.fX;
                m_pTrackElems[i].m_cPosition.fY = m_cInitPos.fY;
                m_pTrackElems[i].m_fAnlgeZ = m_fInitAngleZ;
            }
    }

    glFlushFaces();

#ifdef GL_VERSION_ES_CM_1_1
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
#else
    glEnd();
#endif

    if ( fTime < l_fChangeTime )
    {
        m_cInitPos.fX = (float)(10 * cos(m_fInitPos) + 10 * sin(m_fInitPos * 1.32));
        m_cInitPos.fY = (float)(15 * sin(m_fInitPos) + 5 * sin(m_fInitPos * .89) );
    }
    else
    if ( fTime < l_fChangeTime1 )
    {
        m_cInitPos.fX = (float)(15 * cos(m_fInitPos) + 15 * sin(m_fInitPos * 2.32));
        m_cInitPos.fY = (float)(30 * sin(m_fInitPos) + 15 * sin(m_fInitPos * 1.89) );
    }
    else
    {
        m_cInitPos.fX = (float)(30 * cos(m_fInitPos) + 15 * sin(m_fInitPos * .72));
        m_cInitPos.fY = (float)(25 * sin(m_fInitPos) + 19 * sin(m_fInitPos * .59) );
    }

    m_cInitPos.fZ = -l_fZMax;

    m_fInitAngleZ += m_fInitAngleChange * fDelTime;
    m_fInitPos += m_fInitPosChange * fDelTime;
}
