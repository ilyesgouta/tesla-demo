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

#include "Tree.hpp"

#include <stdlib.h>

extern CTextureManager g_cTexManager;
extern MainFrame_c* g_pMainFrame;

#define SCENE_NAME "data/3d/kbuu2.3ds"
//#define SCENE_NAME "data/3d/testobj.3ds"

static float l_fChangeTime = 2;
static float l_fChangeTime1 = 7;

static float l_fChangeTime3 = 14;

CTree::CTree()
{
    m_pScene = 0;

    m_pScene = lib3ds_file_load( SCENE_NAME );

    if ( !m_pScene )
    {
        g_pMainFrame->ErrorQuit( "[CTree::CTree] Cant load file %s", SCENE_NAME );
        return;
    }

    int nvertices = m_pScene->meshes->points;
    int nfaces = m_pScene->meshes->faces;

    m_pVertices = new CVector[nvertices];
    m_pDestVertices = new CVector[nvertices];

    m_pUVMap = new CTexel[nvertices];
    m_iVertices = nvertices;
    m_pFaces = new unsigned short[3 * nfaces];
    m_iFaces = nfaces;

    uint i;

    for ( i = 0; i != nvertices; i++ ) {
        m_pVertices[i] = m_pScene->meshes->pointL[i].pos;
        m_pUVMap[i].fU = (float)rand() / RAND_MAX;
        m_pUVMap[i].fV = (float)rand() / RAND_MAX;
    }

    for ( i = 0; i != nfaces; i++ )
    {
        m_pFaces[3 * i + 0] = m_pScene->meshes->faceL[i].points[0];
        m_pFaces[3 * i + 1] = m_pScene->meshes->faceL[i].points[1];
        m_pFaces[3 * i + 2] = m_pScene->meshes->faceL[i].points[2];
    }

    m_iGLTex = g_cTexManager.LoadTexture( "data/textures/t1a.jpg" );
    m_iGLTex1 = g_cTexManager.LoadTexture( "data/textures/max_t3.jpg" );

    m_cFFD.set_vector_table( m_pVertices, nvertices, sizeof(CVector) );
    m_cFFD.set_deform( m_aDeform, 5, 5, 5, 0 );
}

CTree::~CTree()
{
}

float lerp( float a, float b, float t )
{
    return (b - a) * t + a;
}

void CTree::Do( float fTime, float fTimeStart )
{
    fTime -= fTimeStart;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustumf( -.6f, .6f, -.45f, .45f, 1, 1000 );

    glMatrixMode( GL_TEXTURE );
    glLoadIdentity();
    //glRotatef( fTime*15, 0, 0, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDepthMask( 0 );

    //glColor4f( .1, .4, .1, 1 );

    float fAlpha;

    if ( fTime > l_fChangeTime3 )
    {
        fAlpha = 1 + l_fChangeTime3 - fTime;
    }
    else
    {
        fAlpha = fTime*.5;
        clamp( &fAlpha );
    }

    glColor4f( 1, 1, 1, .2 * fAlpha  );

    /* make zoom here */

    glTranslatef( 0, 0, -12 );

    glRotatef( 5 * sin(fTime / 3), 0, 0, 1 );
    glRotatef( fTime * 10, 0, 1, 0 );

    glRotatef( 90, 1, 0, 0 );
    glRotatef( 180, 0, 1, 0 );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    for ( int z = 0; z != 5; z++ )
    {
        for ( int y = 0; y != 5; y++ )
        {
            for ( int x = 0; x != 5; x++ )
            {
                m_aDeform[z * 5 * 5 + 5 * y+ x].fX = (x * 4. - 8.f)*(sin(fTime * 1.33 + y * 4) * .2 + .8);
                m_aDeform[z * 5 * 5 + 5 * y+ x].fY = (y * 4. - 8.f)*(cos(fTime * 2 + x * 10) * .2 + .8);
                m_aDeform[z * 5 * 5 + 5 * y+ x].fZ = (z * 4. - 8.f)*(cos(fTime * 2.33 +  y * 10) * .2 + .8);
            }
        }
    }

    m_cFFD.set_deform( m_aDeform, 5, 5, 5, sizeof(CVector) );

    m_cFFD.calc_spline_deform( m_pDestVertices, sizeof(CVector) );

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glBindTexture( GL_TEXTURE_2D, m_iGLTex );

    glVertexPointer( 3, GL_FLOAT, 0, m_pDestVertices );
    glTexCoordPointer( 2, GL_FLOAT, 0, m_pUVMap );

    glDrawElements( GL_TRIANGLES, m_iFaces * 3, GL_UNSIGNED_SHORT, m_pFaces );

    glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    glMatrixMode( GL_TEXTURE );
    glLoadIdentity();
    glTranslatef( fTime * .1, fTime * .5, 0 );

    glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );
    glDrawElements( GL_TRIANGLES, m_iFaces * 3, GL_UNSIGNED_SHORT, m_pFaces );

    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
}
