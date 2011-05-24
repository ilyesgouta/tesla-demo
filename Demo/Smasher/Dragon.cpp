
#include "stdafx.h"
#include "Dragon.hpp"

#define FILE_DRAGON "data/3d/dragon.3ds"

/*******************************************************************************************/
CDragon::CDragon() {

        m_pScene = Load3ds( FILE_DRAGON );

        if ( !m_pScene )
        {
          g_pMainFrame->ErrorQuit( "[CDragon::CDragon] Cant load file: %s\n", FILE_DRAGON );
        }

        m_pMorphedVertices = new CVector[m_pScene->objects[0].nvertices];
        m_pMorphedFaces = new int[3*m_pScene->objects[0].nfaces];

        face_t* pFace = m_pScene->objects[0].faces;
        vertex_t* pVertex = m_pScene->objects[0].vertices;

        for ( uint i = 0; i != m_pScene->objects[0].nfaces; i++ )
        {
          m_pMorphedFaces[3*i + 0] = ((int)pFace->vertices[0] - (int)pVertex)/sizeof(vertex_t);
          m_pMorphedFaces[3*i + 1] = ((int)pFace->vertices[1] - (int)pVertex)/sizeof(vertex_t);
          m_pMorphedFaces[3*i + 2] = ((int)pFace->vertices[2] - (int)pVertex)/sizeof(vertex_t);
          pFace++;
        }
}
/*******************************************************************************************/
CDragon::~CDragon() {

        if ( m_pScene )
        {
          // fix: free scene 
        }

        if ( m_pMorphedFaces ) delete[] m_pMorphedFaces;
        if ( m_pMorphedVertices ) delete[] m_pMorphedVertices;
}
/*******************************************************************************************/
static inline CVector LerpVertex( vertex_t& cV1, vertex_t& cV2, float t ) {

        CVector& v1 = (CVector&)cV1.vlocal;
        CVector& v2 = (CVector&)cV2.vlocal;

        return (v2 - v1)*t + v1;
}
/*******************************************************************************************/
void CDragon::Do( float fTime, float fTimeStart ) {

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustum( -.6f, .6f, -.45f, .45f, 1, 1000 );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glEnable( GL_TEXTURE_2D );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glDisable( GL_CULL_FACE );
        glDisable( GL_DEPTH_TEST );
        glDepthMask( 0 );

        glDisable( GL_TEXTURE_2D );

        glTranslatef( 0, 5, -30 );
        glRotatef( 35, 1, 0, 0 );
        glRotatef( -110, 0, 1, 0 );
        glRotatef( 10*sin(fTime), 1, 0, 0 );



        glColor4f( .1, .3, .4, .05 );
        glLineWidth( 2 );


        float fT = fmod(fTime, 1);

        int iO1 = (int)(fmod(fTime, 5));
        int iO2 = iO1 + 1 >= 5 ? 0 : iO1 + 1;       

  
        object_t* pO1 = &m_pScene->objects[iO1];
        object_t* pO2 = &m_pScene->objects[iO2];


        for ( uint i = 0; i != pO1->nvertices; i++ )
        {
          m_pMorphedVertices[i] = LerpVertex( pO1->vertices[i], pO2->vertices[i], fT );
        }

        glEnableClientState( GL_VERTEX_ARRAY );
        glDisableClientState( GL_TEXTURE_COORD_ARRAY );
        glDisableClientState( GL_COLOR_ARRAY );


        glVertexPointer( 3, GL_FLOAT, 0, m_pMorphedVertices );
        glDrawElements( GL_LINE_LOOP, pO1->nfaces*3, GL_UNSIGNED_INT, m_pMorphedFaces );


        



        
/*
        glBegin( GL_LINES );

        for ( uint i = 0; i != pObject->nfaces; i++ )
        {
          glVertex3fv( (float*)&pFace->vertices[0]->vlocal );
          glVertex3fv( (float*)&pFace->vertices[1]->vlocal );
          glVertex3fv( (float*)&pFace->vertices[1]->vlocal );
          glVertex3fv( (float*)&pFace->vertices[2]->vlocal );
          glVertex3fv( (float*)&pFace->vertices[2]->vlocal );
          glVertex3fv( (float*)&pFace->vertices[0]->vlocal );

          pFace++;
        }

        glEnd();
*/
}
/*******************************************************************************************/

