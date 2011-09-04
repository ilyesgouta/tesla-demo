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

#include "Rotator.hpp"

static float l_fChangeTime = 8;
static float l_fChangeTime1 = 16;

static float l_fChangeTime3 = 26.5;

CThing::CThing()
{
    m_cUVPos = CTexel( 0, 0 );

    m_iGLTexName = g_cTexManager.LoadTexture( "data/textures/y2.jpg" );

    m_iGLLayer1 = g_cTexManager.LoadTexture( "data/textures/cred-saffron01.png" );
    m_iGLLayer2 = g_cTexManager.LoadTexture( "data/textures/cred-yoghurt01.png" );
    m_iGLLayer3 = g_cTexManager.LoadTexture( "data/textures/cred-radixlluvia01.png" );
}

CThing::~CThing()
{
    g_cTexManager.ReleaseTexture( m_iGLTexName );
}

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

static void PutQuad( CTexel cUVPos, float fScale = 1 )
{
#ifdef GL_VERSION_ES_CM_1_1
    CVertex vertex[4];
    CTex texture[4];

    glClientActiveTexture(GL_TEXTURE0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    vertex[0].x = -300 * fScale;
    vertex[0].y = -300 * fScale;
    vertex[0].z = 0;
    texture[0].s0 = 0 + cUVPos.fU; texture[0].t0 = 1 + cUVPos.fV;

    vertex[1].x = -300 * fScale;
    vertex[1].y = 300 * fScale;
    vertex[1].z = 0;
    texture[1].s0 = 0 + cUVPos.fU; texture[1].t0 = 0 + cUVPos.fV;

    vertex[2].x = 300 * fScale;
    vertex[2].y = -300 * fScale;
    vertex[2].z = 0;
    texture[2].s0 = 1 + cUVPos.fU; texture[2].t0 = 1 + cUVPos.fV;

    vertex[3].x = 300 * fScale;
    vertex[3].y = 300 * fScale;
    vertex[3].z = 0;
    texture[3].s0 = 1 + cUVPos.fU; texture[3].t0 = 0 + cUVPos.fV;

    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glTexCoordPointer(2, GL_FLOAT, 0, texture);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
    glTexCoord2f( 0 + cUVPos.fU, 0 + cUVPos.fV );
    glVertex3f( -300 * fScale, 300 * fScale, 0 );

    glTexCoord2f( 1 + cUVPos.fU, 0 + cUVPos.fV );
    glVertex3f( 300 * fScale, 300 * fScale, 0 );

    glTexCoord2f( 1 + cUVPos.fU, 1 + cUVPos.fV );
    glVertex3f( 300 * fScale, -300 * fScale, 0 );

    glTexCoord2f( 0 + cUVPos.fU, 1 + cUVPos.fV );
    glVertex3f( -300 * fScale, -300 * fScale, 0 );
#endif
}

void CThing::Do( float fTime, float fTimeStart )
{
    fTime -= fTimeStart;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustumf( -.6, .6, -.45, .45, 1, 1000 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0, 80, -250 );
    glRotatef( -60, 1, 0, 0 );
    glRotatef( fTime*10, 0, 0, 1 );

    glEnable( GL_TEXTURE_2D );
    glDisable( GL_CULL_FACE );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
    glDisable( GL_DEPTH_TEST );

    CTexel cUVPos;

    glBindTexture( GL_TEXTURE_2D, m_iGLTexName  );

    float fAlpha = fTime;
    clamp( &fAlpha );

    if ( fTime > l_fChangeTime3 )
    {
        fAlpha = 1 + l_fChangeTime3 - fTime;
    }
    else
        fAlpha = 1;

    glColor4f( 1, 1, 1, (.2 + .1 * sin(fTime * 2)) * fAlpha );

    glPushMatrix();

    for ( int i = 0; i != 8; i++ )
    {
        glRotatef( 5 + sin(fTime + i * 10) * 10, 0, 0, 1 );

        cUVPos.fU = -( .4 * sin(fTime + i * 6) + .4 * cos(fTime * 2 + i * 4)) * .1;
        cUVPos.fV = ( .3 * sin(fTime + i * 12) + .4 * sin(fTime + i * 5)) * .05;
#ifdef GL_VERSION_ES_CM_1_1
#else
        glBegin( GL_QUADS );
        PutQuad( cUVPos );
        glEnd();
#endif
    }

    glPopMatrix();

    m_cUVPos.fU = -fTime * .1;
    m_cUVPos.fV = fTime * .2;

    cUVPos.fU = 0;
    cUVPos.fV = 0;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrthof( -300, 300, -300, 300, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    if ( fTime < l_fChangeTime )
    {
        float fa = (l_fChangeTime - fTime) * .3;
        clamp( &fa );

        glBindTexture( GL_TEXTURE_2D, m_iGLLayer1 );
        glColor4f( 1, 1, 1, fa * fAlpha );

#ifdef GL_VERSION_ES_CM_1_1
        PutQuad( cUVPos, 1 );
#else
        glBegin( GL_QUADS );
        PutQuad( cUVPos, 1 );
        glEnd();
#endif
        glBindTexture( GL_TEXTURE_2D, m_iGLLayer3 );
        glColor4f( 1, 1, 1, (1 - fa) * fAlpha);

#ifdef GL_VERSION_ES_CM_1_1
        PutQuad( cUVPos, 1 );
#else
        glBegin( GL_QUADS );
        PutQuad( cUVPos, 1 );
        glEnd();
#endif
    }
    else
    {
        float fa = (fTime - l_fChangeTime1) * .3;
        clamp( &fa );

        glBindTexture( GL_TEXTURE_2D, m_iGLLayer2 );
        glColor4f( 1, 1, 1, fa * fAlpha );

#ifdef GL_VERSION_ES_CM_1_1
        PutQuad( cUVPos, 1 );
#else
        glBegin( GL_QUADS );
        PutQuad( cUVPos, 1 );
        glEnd();
#endif

        glBindTexture( GL_TEXTURE_2D, m_iGLLayer3 );
        glColor4f( 1, 1, 1, (1 - fa) * fAlpha);

#ifdef GL_VERSION_ES_CM_1_1
        PutQuad( cUVPos, 1 );
#else
        glBegin( GL_QUADS );
        PutQuad( cUVPos, 1 );
        glEnd();
#endif
    }

    float fBum = 1 - fTime*.5;
    clamp( &fBum );

    if ( fBum > 0 )
    {
        glDisable( GL_TEXTURE_2D );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glColor4f( 1, 1, 1, fBum );

#ifdef GL_VERSION_ES_CM_1_1
        PutQuad( cUVPos, 1 );
#else
        glBegin( GL_QUADS );
        PutQuad( cUVPos, 1 );
        glEnd();
#endif
    }
}
