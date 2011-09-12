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

#include "FFDEnvVector.hpp"
#include "Stuff.hpp"

#define SCENE_OBJ_START 0

static float l_fChangeTime3 = 18.3;

extern CTextureManager g_cTexManager;

static inline CVector LerpVertex( vertex_t& cV1, vertex_t& cV2, float t )
{
    CVector& v1 = (CVector&)cV1.vlocal;
    CVector& v2 = (CVector&)cV2.vlocal;

    return (v2 - v1)*t + v1;
}

static inline CVector LerpNormal( vertex_t& cV1, vertex_t& cV2, float t )
{
    CVector& v1 = (CVector&)cV1.wlocal;
    CVector& v2 = (CVector&)cV2.wlocal;

    return (v2 - v1)*t + v1;
}

CFFDEnv::CFFDEnv()
{
    m_iGLTex1 = g_cTexManager.LoadTexture( "data/textures/max_t3.jpg" );
    m_iGLTex2 = g_cTexManager.LoadTexture( "data/textures/gothickiemura02.jpg" );
    m_iGLTexBlend = g_cTexManager.LoadTexture( "data/textures/blend.tga" );

    m_pScene = lib3ds_file_load( "data/3d/meta.3ds" );

    Lib3dsMesh *mesh = m_pScene->meshes;

    // will seek to the latest asset into the .3ds file which has well defined texels
    while (!mesh->texelL)
        mesh = mesh->next;

    m_iFaces = mesh->faces;

    m_pFaces = new unsigned short[3 * m_iFaces];

    m_iVertices = mesh->points;

    m_pVertices = new CVector[m_iVertices];
    m_pNormals = new CVector[m_iVertices];
    m_pUV = new CTexel[m_iVertices];
    m_pEnvUV = new CTexel[m_iVertices];

    for ( long i = 0; i != m_iFaces; i++ )
    {
        m_pFaces[3 * i + 0] = mesh->faceL[i].points[0];
        m_pUV[m_pFaces[3 * i + 0]].fU = mesh->texelL[m_pFaces[3 * i + 0]][0];
        m_pUV[m_pFaces[3 * i + 0]].fV = mesh->texelL[m_pFaces[3 * i + 0]][1];

        m_pFaces[3 * i + 1] = mesh->faceL[i].points[1];
        m_pUV[m_pFaces[3 * i + 1]].fU = mesh->texelL[m_pFaces[3 * i + 1]][0];
        m_pUV[m_pFaces[3 * i + 1]].fV = mesh->texelL[m_pFaces[3 * i + 1]][1];

        m_pFaces[3 * i + 2] = mesh->faceL[i].points[2];
        m_pUV[m_pFaces[3 * i + 2]].fU = mesh->texelL[m_pFaces[3 * i + 2]][0];
        m_pUV[m_pFaces[3 * i + 2]].fV = mesh->texelL[m_pFaces[3 * i + 2]][1];
    }

    int count = GetMeshCount();

    for ( uint u = 0; u != count; u++ )
    {
        Lib3dsMesh *mesh = GetMesh(u);

        for (int i = 0; i < mesh->faces; i++)
            mesh->faceL[i].smoothing = 1;

        m_pMeshNormals[u] = new Lib3dsVector[m_iVertices];

        Lib3dsVector* normals = new Lib3dsVector[3 * mesh->faces];
        lib3ds_mesh_calculate_normals(mesh, normals);

        for (int i = 0; i < mesh->faces; i++) {
            memcpy(&m_pMeshNormals[u][mesh->faceL[i].points[0]], &normals[3 * i + 0], sizeof(Lib3dsVector));
            memcpy(&m_pMeshNormals[u][mesh->faceL[i].points[1]], &normals[3 * i + 1], sizeof(Lib3dsVector));
            memcpy(&m_pMeshNormals[u][mesh->faceL[i].points[2]], &normals[3 * i + 2], sizeof(Lib3dsVector));
        }

        delete [] normals;
    }

    m_Vertex[0].x = 0;
    m_Vertex[0].y = 1;
    m_Vertex[0].z = 0;
    m_Texture[0].s0 = 0; m_Texture[0].t0 = 1;

    m_Vertex[1].x = 0;
    m_Vertex[1].y = 0;
    m_Vertex[1].z = 0;
    m_Texture[1].s0 = 0; m_Texture[1].t0 = 0;

    m_Vertex[2].x = 1;
    m_Vertex[2].y = 1;
    m_Vertex[2].z = 0;
    m_Texture[2].s0 = 1; m_Texture[2].t0 = 1;

    m_Vertex[3].x = 1;
    m_Vertex[3].y = 0;
    m_Vertex[3].z = 0;
    m_Texture[3].s0 = 1; m_Texture[3].t0 = 0;
}

CFFDEnv::~CFFDEnv()
{
    if ( m_pVertices ) delete[] m_pVertices;
    if ( m_pNormals ) delete[] m_pNormals;
    if ( m_pFaces ) delete[] m_pFaces;
}

Lib3dsMesh* CFFDEnv::GetMesh(int id)
{
    Lib3dsMesh* mesh = m_pScene->meshes;

    for (int i = 0; i < id; i++)
        mesh = mesh->next;

    return (mesh);
}

int CFFDEnv::GetMeshCount()
{
    int count = 0;
    Lib3dsMesh* mesh = m_pScene->meshes;

    while (mesh) {
        count++;
        mesh = mesh->next;
    }

    return (count);
}

static inline CVector LerpVector( const Lib3dsVector& cV1, const Lib3dsVector& cV2, float t )
{
    CVector ret;

    ret.fX = (cV2[0] - cV1[0]) * t + cV1[0];
    ret.fY = (cV2[1] - cV1[1]) * t + cV1[1];
    ret.fZ = (cV2[2] - cV1[2]) * t + cV1[2];

    return (ret);
}

void CFFDEnv::Do( float fTime, float fTimeStart )
{
    fTime -= fTimeStart;
    CMatrix cCamRot;
    CTexel cUV;
    CVector cN;
    int i;

    float fAlpha = 1 - fTime + l_fChangeTime3;
    clamp( &fAlpha );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustumf( -.6f, .6f, -.45f, .45f, 1, 1000 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_CULL_FACE );
    glEnable( GL_DEPTH_TEST );
    glDepthMask( 1 );
    glCullFace( GL_BACK );
    glDepthFunc( GL_LEQUAL );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    glTranslatef( 0, 0, -30 );
    /*
    glRotatef( fTime*30, 0, 1, 0 );
    glRotatef( fTime*40, 1, 0, 0 );
    glRotatef( fTime*45, 0, 0, 1 );
    */
    glRotatef( 15*sin(fTime), 0, 1, 0 );
    glRotatef( fTime*45, 0, 0, 1 );
    glRotatef( 90, 1, 0, 0 );

    glGetFloatv( GL_MODELVIEW_MATRIX, cCamRot.m_.aMatrix );
    cCamRot.m_.sMatrix.stBaseW = CBase(0, 0, 0, 1);

    glRotatef( 90, 1, 0, 0 );
    glRotatef( 180, 0, 1, 0 );

    /* calc morphing */
    float fT = fmod(fTime * .5, 1);

    fT = cos((1 - fT) * 3.14159) * .5 + .5;

    int iO1 = (int)(fmod(fTime * .5, 6));
    int iO2 = iO1 + 1 >= 6 ? 0 : iO1 + 1;

    Lib3dsPoint* pV1 = GetMesh(iO1)->pointL;
    Lib3dsPoint* pV2 = GetMesh(iO2)->pointL;

    for ( i = 0; i != m_iVertices; i++ )
    {
        m_pVertices[i] = LerpVector( pV1[i].pos, pV2[i].pos, fT );
        m_pNormals[i] = LerpVector( m_pMeshNormals[iO1][i], m_pMeshNormals[iO2][i], fT );

        /* calc envmap */
        cN = cCamRot * m_pNormals[i];

        m_pEnvUV[i].fU = cN.fX * .5 + .5;
        m_pEnvUV[i].fV = cN.fY * .5 + .5;
    }

    glVertexPointer( 3, GL_FLOAT, 0, m_pVertices );

    /* mesh */
    glBindTexture( GL_TEXTURE_2D, m_iGLTex2 );
    glTexCoordPointer( 2, GL_FLOAT, 0, m_pUV );
    glColor4f( 1, 1, 1, 1 * fAlpha );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDrawElements( GL_TRIANGLES, m_iFaces * 3, GL_UNSIGNED_SHORT, m_pFaces );

    /* env */
    glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );
    glTexCoordPointer( 2, GL_FLOAT, 0, m_pEnvUV );
    glColor4f( 1, 1, 1, 1 * fAlpha );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
    //glDrawElements( GL_TRIANGLES, m_iFaces * 3, GL_UNSIGNED_SHORT, m_pFaces );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrthof( 0, 1, 0, 1, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glDisable( GL_CULL_FACE );

    glBindTexture( GL_TEXTURE_2D, m_iGLTexBlend );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glColor4f( 1, 1, 1, 1*fAlpha );

#ifdef GL_VERSION_ES_CM_1_1
    glClientActiveTexture(GL_TEXTURE0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
    glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
    glBegin( GL_QUADS );

    glTexCoord2f( 0, 0 );
    glVertex3f( 0, 0, 0 );

    glTexCoord2f( 1, 0 );
    glVertex3f( 1, 0, 0 );

    glTexCoord2f( 1, 1 );
    glVertex3f( 1, 1, 0 );

    glTexCoord2f( 0, 1 );
    glVertex3f( 0, 1, 0 );

    glEnd();
#endif

    CDarkQuads cQ;

    CColor cCol(0, 0, 0, .3);

    cCol.fA *= sin(fTime);

    cQ.Render( sin(fTime)*40 + 50, cCol );
}
