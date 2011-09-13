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

#include "FaceMorph.hpp"

#if !defined pi
#define pi 3.1415926535897932384626433832795
#endif

static const float l_fMorphSpeed = .5;

int l_aMorphObj[] = {1, 0, 3, 0 };

const float fR = 90;
const int iVSeg = 8;
const int iHSeg = 8;

static int l_iEnableDisplace = 0;
static int iOldO2 = 0xff;

static float l_fChangeTime3 = 19.5;

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

static CVertex s_Vertex[4] = {
    {0, 1, 0},
    {0, 0, 0},
    {1, 1, 0},
    {1, 0, 0}
};

static CTex s_Texture[4] = {
    {0, 1},
    {0, 0},
    {1, 1},
    {1, 0}
};

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

static inline CVector LerpVector( const Lib3dsVector& cV1, const Lib3dsVector& cV2, float t )
{
    CVector ret;

    ret.fX = (cV2[0] - cV1[0]) * t + cV1[0];
    ret.fY = (cV2[1] - cV1[1]) * t + cV1[1];
    ret.fZ = (cV2[2] - cV1[2]) * t + cV1[2];

    return (ret);
}

CFaceMorph::CFaceMorph()
{
    m_iGLTex1 = g_cTexManager.LoadTexture( "data/textures/y6.jpg" );
    m_iGLTex1a = g_cTexManager.LoadTexture( "data/textures/t1a.jpg" );

    m_iGLTex2 = g_cTexManager.LoadTexture( "data/textures/max_t1.jpg" );
    m_iGLBackTex = g_cTexManager.LoadTexture( "data/textures/y7.jpg" );

    m_iGLTexBlend = g_cTexManager.LoadTexture( "data/textures/blend2.png" );

    m_pScene = lib3ds_file_load( "data/3d/faces.3ds" );

    Lib3dsMesh *object_2 = m_pScene->meshes->next->next;

    m_pMesh = object_2;

    m_iFaces = object_2->faces;

    m_iVertices = object_2->points;
    m_pVertices = new CVector[m_iVertices];
    m_pUV = new CTexel[m_iVertices];
    m_pNormals = new CVector[m_iVertices];
    m_pEnvUV = new CTexel[m_iVertices];

    m_pFaces = new unsigned short[3 * m_iFaces];

    for ( int i = 0; i != m_iFaces; i++ )
    {
        m_pFaces[3 * i + 0] = object_2->faceL[i].points[0];
        m_pFaces[3 * i + 1] = object_2->faceL[i].points[1];
        m_pFaces[3 * i + 2] = object_2->faceL[i].points[2];
    }

    int count = GetMeshCount();

    for ( uint u = 0; u != count; u++ )
    {
        Lib3dsMesh *mesh = GetMesh(u);

        //for (int i = 0; i < mesh->faces; i++)
        //    mesh->faceL[i].smoothing = 0;

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

    /* create tubes */
    m_iTubeVertices = iVSeg * iHSeg;
    m_iTubeFaces = (iVSeg - 1) * (iHSeg - 1) * 2;

    m_pTubeVertices = 0;
    m_pTubeUV = 0;
    m_pTubeFaces = 0;

    {
        m_pTubeVertices = new CVector[m_iTubeVertices];
        m_pTubeUV = new float[2 * m_iTubeVertices];
        m_pTubeFaces = new unsigned short[3 * m_iTubeFaces];

        for ( int v = 0; v != iVSeg; v++ )
        {
            for ( int h = 0; h != iHSeg; h++ )
            {
                m_pTubeVertices[v * iHSeg + h].fX = fR * (float)cos( pi * h * 2 / (iHSeg - 1) );
                m_pTubeVertices[v * iHSeg + h].fY = v * 70.f - (iVSeg - 1) * 35.f;
                m_pTubeVertices[v * iHSeg + h].fZ = fR * (float)sin( pi * h * 2 / (iHSeg - 1) );

                m_pTubeUV[2 * (v * iHSeg + h) + 0] = (float)h / (iHSeg - 1);
                m_pTubeUV[2 * (v * iHSeg + h) + 1] = (float)v / (iVSeg - 1);
            }
        }

        for ( int v = 0; v != iVSeg - 1; v++ )
        {
            for ( int h = 0; h != iHSeg - 1; h++ )
            {
                m_pTubeFaces[6 * (v * (iHSeg - 1) + h) + 0] = v * iHSeg + h;
                m_pTubeFaces[6 * (v * (iHSeg - 1) + h) + 1] = v * iHSeg + h + 1;
                m_pTubeFaces[6 * (v * (iHSeg - 1) + h) + 2] = (v + 1) * iHSeg + h;

                m_pTubeFaces[6 * (v * (iHSeg - 1) + h) + 3] = v * iHSeg + h + 1;
                m_pTubeFaces[6 * (v * (iHSeg - 1) + h) + 4] = (v + 1) * iHSeg + h + 1;
                m_pTubeFaces[6 * (v * (iHSeg - 1) + h) + 5] = (v + 1) * iHSeg + h;
            }
        }
    }
}

Lib3dsMesh* CFaceMorph::GetMesh(int id)
{
    Lib3dsMesh* mesh = m_pScene->meshes;

    for (int i = 0; i < id; i++)
        mesh = mesh->next;

    return (mesh);
}

int CFaceMorph::GetMeshCount()
{
    int count = 0;
    Lib3dsMesh* mesh = m_pScene->meshes;

    while (mesh) {
        count++;
        mesh = mesh->next;
    }

    return (count);
}

CFaceMorph::~CFaceMorph()
{
    if ( m_pVertices )
        delete[] m_pVertices;
    if ( m_pFaces )
        delete[] m_pFaces;
    if ( m_pNormals )
        delete[] m_pNormals;
    if ( m_pEnvUV )
        delete[] m_pEnvUV;
}

void CFaceMorph::Do( float fTime, float fTimeStart )
{
    CVector cN;
    CMatrix cCam;

    fTime -= fTimeStart;

    float fAlpha = 1;

    fAlpha = l_fChangeTime3 - fTime;
    clamp( &fAlpha );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustumf( -12.6f, 12.6f, -12.45f, 12.45f, 1, 1000 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glTranslatef( 2, 0, -13 );
    glRotatef( 20 * sin(fTime), 1, 0, 0 );
    glRotatef( 10 * sin(fTime * .9) - 15, 0, 1, 0 );
    glRotatef( 180, 0, 1, 0 );

    glGetFloatv( GL_MODELVIEW_MATRIX, cCam.m_.aMatrix );
    cCam.m_.sMatrix.stBaseW = CBase(0, 0, 0, 1);

    glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDepthMask( 0 );

    /* some background */
    glColor4f(1, 1, 1, .4 * fAlpha );

    for ( int u = 0; u != 4; u++ )
    {
        RenderTube( 1 + u, 1 + fTime * 10 * u );
    }

    glRotatef( 100, 1, 0, 0 );
    glRotatef( 180, 0, 1, 0 );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustumf( -.6f, .6f, -.45f, .45f, 1, 1000 );

    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glEnable( GL_DEPTH_TEST );
    glDepthMask( 1 );
    glDepthFunc( GL_LEQUAL );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    /* morphing */
    float fT = fmod(fTime * l_fMorphSpeed, 1);

    fT = cos((1 - fT) * 3.14159) * .5 + .5;

    int iO1 = (int)(fmod(fTime * l_fMorphSpeed, 4));
    int iO2 = iO1 + 1 >= 4 ? 0 : iO1 + 1;

    /*
    if ( iO2 != iOldO2 && iO2 == 0 )
    {
    l_iEnableDisplace++;
    iOldO2 = iO2;
    }
    */
    iO1 = l_aMorphObj[iO1];
    iO2 = l_aMorphObj[iO2];

    CVector direction;
    float time = fTime;
    direction.fX = sin(time) - cos(time);
    direction.fY = sin(time) + cos(time);
    direction.Normalize();

    Lib3dsPoint* pV1 = GetMesh(iO1)->pointL;
    Lib3dsPoint* pV2 = GetMesh(iO2)->pointL;

    for ( int i = 0; i != m_iVertices; i++ )
    {
        m_pVertices[i] = LerpVector( pV1[i].pos, pV2[i].pos, fT );

        m_pNormals[i] = LerpVector( m_pMeshNormals[iO1][i], m_pMeshNormals[iO2][i], fT );

        cN = cCam * m_pNormals[i];

        m_pEnvUV[i].fU = cN.fX;
        m_pEnvUV[i].fV = cN.fY;

        /*
        if ( l_iEnableDisplace > 0 )
        {
        #define sqr(x) ((x)*(x))
        float dist = 1 / sqrt(sqr(m_pVertices[i].fX)+sqr(m_pVertices[i].fY)+sqr(m_pVertices[i].fZ));;
        CVector vtr = m_pVertices[i];
        vtr.Normalize();
        float dif = vtr.Dot(direction);
        dif = dif * dif * dif * dif * dif * dif;
        dif *= dif;
        //			dif *= 5;

        m_pVertices[i].fX *= 1+ direction.fX * dif * sin(dist*dif);
        m_pVertices[i].fY *= 1+ direction.fY * dif * cos(dist+dif);
        m_pVertices[i].fZ *= 1+ direction.fZ * dif;// * sin(dist) * cos(dist*0.2*dif);
        }
        */
    }

    glVertexPointer( 3, GL_FLOAT, 0, m_pVertices );

    /* mesh */
    glMatrixMode( GL_TEXTURE );

    glColor4f( 1, 1, 1, 1 * fAlpha );

    glTexCoordPointer( 2, GL_FLOAT, 0, m_pMesh->texelL );
    glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );

    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glLoadIdentity();
    glTranslatef( fTime * .05, fTime * .1, 0 );
    glRotatef( fTime * 30, 0, 0, 1 );

    glDrawElements( GL_TRIANGLES, m_iFaces * 3, GL_UNSIGNED_SHORT, m_pFaces );

    glColor4f( 1, 1, 1, .5 * fAlpha );

    glBindTexture( GL_TEXTURE_2D, m_iGLTex1a );

    glLoadIdentity();
    glTranslatef( fTime * .05, -fTime * .05, 0 );
    glRotatef( -fTime * 20, 0, 0, 1 );

    glDrawElements( GL_TRIANGLES, m_iFaces * 3, GL_UNSIGNED_SHORT, m_pFaces );

    glLoadIdentity();

    /* env */
    glColor4f( 1, 1, 1, 1 * fAlpha );

    glTexCoordPointer( 2, GL_FLOAT, 0, m_pEnvUV );

    glBindTexture( GL_TEXTURE_2D, m_iGLTex2 );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );

    glDrawElements( GL_TRIANGLES, m_iFaces * 3, GL_UNSIGNED_SHORT, m_pFaces );

    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrthof( 0, 1, 0, 1, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glDisable( GL_CULL_FACE );

    glBindTexture( GL_TEXTURE_2D, m_iGLTexBlend );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glColor4f( 1, 1, 1, 1 * fAlpha );

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
    glVertex3f( 0, 0, 0 );
    glTexCoord2f( 1, 0 );
    glVertex3f( 1, 0, 0 );
    glTexCoord2f( 1, 1 );
    glVertex3f( 1, 1, 0 );
    glTexCoord2f( 0, 1 );
    glVertex3f( 0, 1, 0 );

    glEnd();
#endif
}

void CFaceMorph::RenderTube( float fScale, float fAngle0 )
{
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    glEnable( GL_TEXTURE_2D );

    glBindTexture( GL_TEXTURE_2D, m_iGLBackTex );

    glPushMatrix();
    glRotatef( fAngle0, 0, 1, 0 );
    glScalef( fScale, fScale, fScale );

    glVertexPointer( 3, GL_FLOAT, 0, m_pTubeVertices );
    glTexCoordPointer( 2, GL_FLOAT, 0, m_pTubeUV );

    glDrawElements( GL_TRIANGLES, m_iTubeFaces * 3, GL_UNSIGNED_SHORT, m_pTubeFaces );

    glPopMatrix();
}
