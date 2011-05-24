
#include "stdafx.h"
#include "FFDEnvVector.hpp"

#include "Stuff.hpp"


#define SCENE_OBJ_START 0


static float l_fChangeTime3 = 18.3;



/******************************************************************************************/
static inline CVector LerpVertex( vertex_t& cV1, vertex_t& cV2, float t ) {

        CVector& v1 = (CVector&)cV1.vlocal;
        CVector& v2 = (CVector&)cV2.vlocal;

        return (v2 - v1)*t + v1;
}
/******************************************************************************************/
static inline CVector LerpNormal( vertex_t& cV1, vertex_t& cV2, float t ) {

        CVector& v1 = (CVector&)cV1.wlocal;
        CVector& v2 = (CVector&)cV2.wlocal;

        return (v2 - v1)*t + v1;
}
/******************************************************************************************/
CFFDEnv::CFFDEnv() {

        m_iGLTex1 = g_cTexManager.LoadTexture( "data/textures/max_t3.jpg" );
        m_iGLTex2 = g_cTexManager.LoadTexture( "data/textures/gothickiemura02.jpg" );
        m_iGLTexBlend = g_cTexManager.LoadTexture( "data/textures/blend.tga" );
        m_pScene = Load3ds( "data/3d/meta.3ds" );

        face_t* pFace = m_pScene->objects[SCENE_OBJ_START].faces;
        m_iFaces = m_pScene->objects[SCENE_OBJ_START].nfaces;
        m_pFaces = new int[3*m_iFaces];

        m_iVertices = m_pScene->objects[SCENE_OBJ_START].nvertices;
        m_pVertices = new CVector[m_iVertices];
        m_pNormals = new CVector[m_iVertices];
        m_pUV = new CTexel[m_iVertices];
        m_pEnvUV = new CTexel[m_iVertices];

        vertex_t* pVertices = m_pScene->objects[SCENE_OBJ_START].vertices;


        for ( int i = 0; i != m_iFaces; i++ )
        {
          m_pFaces[3*i + 0] = ((int)pFace[i].vertices[0] - (int)pVertices)/sizeof(vertex_t);
          m_pUV[m_pFaces[3*i + 0]].fU = pFace[i].maptexel[0]->u;
          m_pUV[m_pFaces[3*i + 0]].fV = pFace[i].maptexel[0]->v;

          m_pFaces[3*i + 1] = ((int)pFace[i].vertices[1] - (int)pVertices)/sizeof(vertex_t);
          m_pUV[m_pFaces[3*i + 1]].fU = pFace[i].maptexel[1]->u;
          m_pUV[m_pFaces[3*i + 1]].fV = pFace[i].maptexel[1]->v;

          m_pFaces[3*i + 2] = ((int)pFace[i].vertices[2] - (int)pVertices)/sizeof(vertex_t);
          m_pUV[m_pFaces[3*i + 2]].fU = pFace[i].maptexel[2]->u;
          m_pUV[m_pFaces[3*i + 2]].fV = pFace[i].maptexel[2]->v;
        }

        int u = SCENE_OBJ_START;

        pVertices = m_pScene->objects[u].vertices;
        
        for ( i = 0; (uint)i != m_pScene->objects[u].nvertices; i++ )
        {
          m_pVertices[i] = (CVector&)pVertices[i].vlocal;
          m_pNormals[i] = ((CVector&)pVertices[i].wlocal);
        }
}
/*******************************************************************************************/
CFFDEnv::~CFFDEnv() {

        if ( m_pVertices ) delete[] m_pVertices;
        if ( m_pNormals ) delete[] m_pNormals;
        if ( m_pFaces ) delete[] m_pFaces;
}
/*******************************************************************************************/
void CFFDEnv::Do( float fTime, float fTimeStart ) {

        fTime -= fTimeStart;
        CMatrix cCamRot;
        CTexel cUV;
        CVector cN;
        int i;

        float fAlpha = 1 - fTime + l_fChangeTime3;
        clamp( &fAlpha );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustum( -.6f, .6f, -.45f, .45f, 1, 1000 );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glEnable( GL_TEXTURE_2D );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable( GL_CULL_FACE );
        glEnable( GL_DEPTH_TEST );
        glDepthMask( 1 );
        glCullFace( GL_FRONT );
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

        glGetFloatv( GL_MODELVIEW_MATRIX, cCamRot.aMatrix );
        cCamRot.stBaseW = CBase(0, 0, 0, 1);

        /* calc morphing */
        float fT = fmod(fTime*.5, 1);

        fT = cos((1-fT)*3.14159)*.5 + .5;

        int iO1 = (int)(fmod(fTime*.5, 6));
        int iO2 = iO1 + 1 >= 6 ? 0 : iO1 + 1;       
  
        object_t* pO1 = &m_pScene->objects[iO1];
        object_t* pO2 = &m_pScene->objects[iO2];

        for ( i = 0; i != m_iVertices; i++ )
        {
          m_pVertices[i] = LerpVertex( pO1->vertices[i], pO2->vertices[i], fT );
          m_pNormals[i] = LerpNormal( pO1->vertices[i], pO2->vertices[i], fT );
        }


        /* calc envmap */
        for ( i = 0; i != m_iVertices; i++ )
        {
          cN = cCamRot*m_pNormals[i];
          m_pEnvUV[i].fU = cN.fX*.5 + .5;
          m_pEnvUV[i].fV = cN.fY*.5 + .5;
        }

        glVertexPointer( 3, GL_FLOAT, 0, m_pVertices );

        /* mesh */
        glBindTexture( GL_TEXTURE_2D, m_iGLTex2 );
        glTexCoordPointer( 2, GL_FLOAT, 0, m_pUV );
        glColor4f( 1, 1, 1, 1*fAlpha );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glDrawElements( GL_TRIANGLES, m_iFaces*3, GL_UNSIGNED_INT, m_pFaces );

        /* env */
        glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );
        glTexCoordPointer( 2, GL_FLOAT, 0, m_pEnvUV );
        glColor4f( 1, 1, 1, 1*fAlpha );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glDrawElements( GL_TRIANGLES, m_iFaces*3, GL_UNSIGNED_INT, m_pFaces );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0, 1, 0, 1, -1, 1 );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glDisable( GL_CULL_FACE );

        glBindTexture( GL_TEXTURE_2D, m_iGLTexBlend );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glColor4f( 1, 1, 1, 1*fAlpha );
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


        CDarkQuads cQ;

        CColor cCol(0, 0, 0, .3);

        cCol.fA *= sin(fTime);

        cQ.Render( sin(fTime)*40 + 50, cCol );
}
/*******************************************************************************************/




