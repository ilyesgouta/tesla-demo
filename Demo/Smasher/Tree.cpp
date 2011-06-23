#ifdef WIN32
#include "stdafx.h"
#endif

#include <GLES/gl.h>

#include "Tree.hpp"

extern CTextureManager g_cTexManager;
extern MainFrame_c* g_pMainFrame;

#define SCENE_NAME "data/3d/kbuu2.3ds"
//#define SCENE_NAME "data/3d/testobj.3ds"

  static float l_fChangeTime = 2;
  static float l_fChangeTime1 = 7;

  static float l_fChangeTime3 = 14;


/********************************************************************************************/
CTree::CTree() {

        m_pScene = 0;

        m_pScene = Load3ds( SCENE_NAME );

        if ( !m_pScene )
        {
          g_pMainFrame->ErrorQuit( "[CTree::CTree] Cant load file %s", SCENE_NAME );
          return;
        }

        m_pVertices = new CVector[m_pScene->objects[0].nvertices];
        m_pUVMap = new CTexel[m_pScene->objects[0].nvertices];
        m_iVertices = m_pScene->objects[0].nvertices;
        m_pFaces = new unsigned short[3*m_pScene->objects[0].nfaces];
        m_iFaces = m_pScene->objects[0].nfaces;

        face_t* pFace = m_pScene->objects[0].faces;
        vertex_t* pVertex = m_pScene->objects[0].vertices;

        uint i;

        for ( i = 0; i != m_pScene->objects[0].nvertices; i++ )
        {
//          m_pVertices[i] = (CVector&)m_pScene->objects[0].vertices[i].vlocal;
          m_pUVMap[i] = (CTexel&)m_pScene->objects[0].vertices[i].wlocal;
        }

        for ( i = 0; i != m_pScene->objects[0].nfaces; i++ )
        {
          m_pFaces[3*i + 0] = ((long)pFace->vertices[0] - (long)pVertex)/sizeof(vertex_t);
          m_pFaces[3*i + 1] = ((long)pFace->vertices[1] - (long)pVertex)/sizeof(vertex_t);
          m_pFaces[3*i + 2] = ((long)pFace->vertices[2] - (long)pVertex)/sizeof(vertex_t);
          pFace++;
        }

        m_iGLTex = g_cTexManager.LoadTexture( "data/textures/t1a.jpg" );
        m_iGLTex1 = g_cTexManager.LoadTexture( "data/textures/max_t3.jpg" );


        m_cFFD.set_vector_table( &m_pScene->objects[0].vertices->vlocal, m_pScene->objects[0].nvertices, sizeof(vertex_t) );
        m_cFFD.set_deform( m_aDeform, 5, 5, 5, 0 );
}
/********************************************************************************************/
CTree::~CTree() {

}
/********************************************************************************************/
float lerp( float a, float b, float t ) {
  
        return (b-a)*t + a;
}
/********************************************************************************************/
void CTree::Do( float fTime, float fTimeStart ) {

        fTime -= fTimeStart;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustumf( -.6f, .6f, -.45f, .45f, 1, 1000 );

        glMatrixMode( GL_TEXTURE );
        glLoadIdentity();
//        glRotatef( fTime*15, 0, 0, 1 );

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


        glColor4f( 1, 1, 1, .2*fAlpha  );

        
        /* make zoom here */

        glTranslatef( 0, 0, -12 );

        

        glRotatef( 5*sin(fTime/3), 0, 0, 1 );
        glRotatef( fTime*10, 0, 1, 0 );

        glBindTexture( GL_TEXTURE_2D, m_iGLTex );

        glEnableClientState( GL_VERTEX_ARRAY );
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
        glDisableClientState( GL_COLOR_ARRAY );

        for ( int z = 0; z != 5; z++ )
        {
          for ( int y = 0; y != 5; y++ )
          {
            for ( int x = 0; x != 5; x++ )
            {
              m_aDeform[z*5*5 + 5*y+ x].fX = (x*4. - 8.f)*(sin(fTime*1.33+y*4)*.2+.8);
              m_aDeform[z*5*5 + 5*y+ x].fY = (y*4. - 8.f)*(cos(fTime*2+x*10)*.2+.8);
              m_aDeform[z*5*5 + 5*y+ x].fZ = (z*4. - 8.f)*(cos(fTime*2.33 +  y*10)*.2 +.8);
            }
          }
        }

        m_cFFD.set_deform( m_aDeform, 5, 5, 5, sizeof(CVector) );

        m_cFFD.calc_spline_deform( m_pVertices, sizeof(CVector) );

        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glVertexPointer( 3, GL_FLOAT, 0, m_pVertices );
        glTexCoordPointer( 2, GL_FLOAT, 0, m_pUVMap );
//        glDrawElements( GL_TRIANGLES, m_iFaces*3, GL_UNSIGNED_INT, m_pFaces );

        glBlendFunc( GL_SRC_ALPHA, GL_ONE );

        glMatrixMode( GL_TEXTURE );
        glLoadIdentity();
        glTranslatef( fTime*.1, fTime*.5, 0 );

        glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );
        glDrawElements( GL_TRIANGLES, m_iFaces*3, GL_UNSIGNED_SHORT, m_pFaces );

        glLoadIdentity();
        glMatrixMode( GL_MODELVIEW );
}
/********************************************************************************************/

