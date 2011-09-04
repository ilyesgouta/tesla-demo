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

#include "LinePlane.hpp"
#include "ffd.h"

CLinePlane::CLinePlane()
{
    m_pVertices = 0;
    m_pTexels = 0;
    m_iVertices = 0;
    m_pLines = 0;
    m_iLines = 0;
    m_pFFD = 0;

    m_iGLTexName = g_cTexManager.LoadTexture( "data/textures/y2.jpg" );
    m_iGLFlareName = g_cTexManager.LoadTexture( "data/textures/flare02.jpg" );

    CreateMesh( 16, 16, 256, 256 );

    m_pFFD = new CFFD();
}

CLinePlane::~CLinePlane()
{
    if ( m_pVertices )
        delete[] m_pVertices;
    if ( m_pTexels )
        delete[] m_pTexels;
    if ( m_pLines )
        delete[] m_pLines;
    if ( m_pFFD )
        delete m_pFFD;
}

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

static CVertex s_Vertex[4] = {
    {-1, -1, 0},
    {-1, 1, 0},
    {1, -1, 0},
    {1, 1, 0}
};

static CTex s_Texture[4] = {
    {0, 1},
    {0, 0},
    {1, 1},
    {1, 0}
};

void CLinePlane::Do( float fTime, float fTimeStart )
{
    float fAspect = 480.f / 640.f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustumf(-0.5f, 0.5f, -0.5f * fAspect, 0.5f * fAspect, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef( 0, 0, -350 );

    glRotatef( 30 * sin(fTime), 0, 0, 1 );

    glEnable( GL_TEXTURE_2D );
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    glVertexPointer( 3, GL_FLOAT, 0, m_pVertices );
    glTexCoordPointer( 2, GL_FLOAT, 0, m_pTexels );

    glLineWidth( 2 );
    glDisable( GL_LINE_SMOOTH );
    glColor4f( 1, 1, 1, 1 );

    glBindTexture( GL_TEXTURE_2D, m_iGLTexName );
    glDrawElements( GL_LINES, m_iLines * 2, GL_UNSIGNED_SHORT, m_pLines );

    glTranslatef( 0, 0, 300 );

    glBindTexture( GL_TEXTURE_2D, m_iGLFlareName );

#ifdef GL_VERSION_ES_CM_1_1
    glClientActiveTexture(GL_TEXTURE0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, s_Vertex);
    glTexCoordPointer(2, GL_FLOAT, 0, s_Texture);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
    glBegin( GL_QUADS );

    glTexCoord2f( 0, 0 );
    glVertex3f( -1,  1, 0 );

    glTexCoord2f( 1, 0 );
    glVertex3f(  1,  1, 0 );

    glTexCoord2f( 1, 1 );
    glVertex3f(  1, -1, 0 );

    glTexCoord2f( 0, 1 );
    glVertex3f( -1, -1, 0 );

    glEnd();
#endif
}

void CLinePlane::CreateMesh( int iHRes, int iVRes, float fSizeX, float fSizeY )
{
    int h, v;

    m_iVertices = iHRes * iVRes;
    m_pVertices = new CVector[m_iVertices];
    m_pTexels = new CTexel[m_iVertices];

    m_iLines = iHRes * (iVRes - 1) + (iHRes - 1) * iVRes;
    m_pLines = new unsigned short[2 * m_iLines];

    for ( v = 0; v != iVRes; v++ )
    {
        for ( h = 0; h != iHRes; h++ )
        {
            m_pVertices[v*iHRes + h].fX = fSizeX * h/(iHRes - 1) - fSizeX * .5f;
            m_pVertices[v*iHRes + h].fY = fSizeY * v/(iVRes - 1) - fSizeY * .5f;
            m_pVertices[v*iHRes + h].fZ = 0;
            m_pTexels[v*iHRes + h].fU = (float)h/(iHRes - 1);
            m_pTexels[v*iHRes + h].fV = (float)v/(iVRes - 1);
        }
    }

    unsigned short* pLine = m_pLines;

    for ( v = 0; v != iVRes - 1; v++ )
        for ( h = 0; h != iHRes; h++ )
        {
            pLine[0] = v * iHRes + h;
            pLine[1] = (v + 1) * iHRes + h;
            pLine += 2;
        }

    for ( v = 0; v != iVRes; v++ )
        for ( h = 0; h != iHRes - 1; h++ )
        {
            pLine[0] = v * iHRes + h;
            pLine[1] = v * iHRes + h + 1;
            pLine += 2;
        }
}
