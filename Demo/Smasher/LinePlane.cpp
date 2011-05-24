
#include "stdafx.h"
#include "LinePlane.hpp"
#include "ffd.h"

/*******************************************************************************************/
CLinePlane::CLinePlane() {

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
/*******************************************************************************************/
CLinePlane::~CLinePlane() {

        if ( m_pVertices ) delete[] m_pVertices;
        if ( m_pTexels ) delete[] m_pTexels;
        if ( m_pLines ) delete[] m_pLines;
        if ( m_pFFD ) delete m_pFFD;
}
/*******************************************************************************************/
void CLinePlane::Do( float fTime, float fTimeStart ) {

        float fAspect = 480.f/640.f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5f, 0.5f, -0.5f*fAspect, 0.5f*fAspect, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

        glTranslatef( 0, 0, -350 );

        glRotatef( 30*sin(fTime), 0, 0, 1 );


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
        glDrawElements( GL_LINES, m_iLines*2, GL_UNSIGNED_INT, m_pLines );

        glTranslatef( 0, 0, 300 );

        glBindTexture( GL_TEXTURE_2D, m_iGLFlareName );
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

}
/*******************************************************************************************/
void CLinePlane::CreateMesh( int iHRes, int iVRes, float fSizeX, float fSizeY ) {

        int h, v;

        m_iVertices = iHRes*iVRes;
        m_pVertices = new CVector[m_iVertices];
        m_pTexels = new CTexel[m_iVertices];

        m_iLines = iHRes*(iVRes - 1) + (iHRes - 1)*iVRes;
        m_pLines = new int[2*m_iLines];

        for ( v = 0; v != iVRes; v++ )
        {
          for ( h = 0; h != iHRes; h++ )
          {
            m_pVertices[v*iHRes + h].fX = fSizeX*h/(iHRes-1) - fSizeX*.5f;
            m_pVertices[v*iHRes + h].fY = fSizeY*v/(iVRes-1) - fSizeY*.5f;
            m_pVertices[v*iHRes + h].fZ = 0;
            m_pTexels[v*iHRes + h].fU = (float)h/(iHRes - 1);
            m_pTexels[v*iHRes + h].fV = (float)v/(iVRes - 1);
          }
        }

        int* pLine = m_pLines;

        for ( v = 0; v != iVRes - 1; v++ )
          for ( h = 0; h != iHRes; h++ )
          {
            pLine[0] = v*iHRes + h;
            pLine[1] = (v + 1)*iHRes + h;
            pLine += 2;
          }

        for ( v = 0; v != iVRes; v++ )
          for ( h = 0; h != iHRes - 1; h++ )
          {
            pLine[0] = v*iHRes + h;
            pLine[1] = v*iHRes + h + 1;
            pLine += 2;
          }
}
/*******************************************************************************************/
