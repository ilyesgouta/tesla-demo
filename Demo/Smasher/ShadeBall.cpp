
#include "stdafx.h"
#include "ShadeBall.hpp"

#if !defined pi
#define pi 3.1415926535897932384626433832795
#endif

class CTime {

public:

      CTime() {
        t = 0, v = 0;
      }

      CTime( float t0, float v0 ) {
        t = t0;
        v = v0;
      }


      float t, v;
};

CTime l_aTimes[] = {
  CTime( 0, 0 ),
  CTime( 1.5, 1 ),
  CTime( 5, 1 ),
  CTime( 7, 0 ),
  CTime( 9, 1 ),
  CTime( 14.5, 1 ), 
  CTime( 16, 0 ),
  CTime( 18.0, 1 ),
  CTime( 20, 1 ),
  CTime( 24, 0 )
};

int l_iTimes = sizeof(l_aTimes)/sizeof(CTime);

float KeyVal( float fTime ) {
  
        for ( int i = 0; i != l_iTimes-1; i++ )
        {
          if ( fTime >= l_aTimes[i].t && fTime < l_aTimes[i+1].t )
          {
            return (l_aTimes[i+1].v - l_aTimes[i].v)*((fTime-l_aTimes[i].t)/(l_aTimes[i+1].t-l_aTimes[i].t)) + l_aTimes[i].v;
          }
        }

        return 0;
}

/*******************************************************************************************/
static void PutQuad( CTexel cUVPos, float fScale = 1 ) {

        glTexCoord2f( 0 + cUVPos.fU, 0 + cUVPos.fV );
        glVertex3f( -300*fScale, 300*fScale, 0 );
        glTexCoord2f( 1 + cUVPos.fU, 0 + cUVPos.fV );
        glVertex3f( 300*fScale, 300*fScale, 0 );
        glTexCoord2f( 1 + cUVPos.fU, 1 + cUVPos.fV );
        glVertex3f( 300*fScale, -300*fScale, 0 );
        glTexCoord2f( 0 + cUVPos.fU, 1 + cUVPos.fV );
        glVertex3f( -300*fScale, -300*fScale, 0 );
}
/*******************************************************************************************/
CShadeBall::CShadeBall() {

        m_iGLTex = g_cTexManager.LoadTexture( "data/textures/gothickiemura02.jpg" );
        m_iGLLayer1 = g_cTexManager.LoadTexture( "data/textures/kalatus1-01.png" );

        m_pVertices = 0;
        m_pFaces = 0;
        m_pUV = 0;
        m_iFaces = 0;
        m_iVertices = 0;

        MakeSphere();
}
/*******************************************************************************************/
CShadeBall::~CShadeBall() {

        g_cTexManager.ReleaseTexture( m_iGLTex );
}
/*******************************************************************************************/
void CShadeBall::MakeSphere() {

  const float fR = 20;
  const int iVSeg = 13;
  const int iHSeg = 13;

          m_iVertices = iVSeg*iHSeg;
          m_iFaces = (iVSeg - 1)*(iHSeg - 1)*2;

          m_pVertices = new CVector[m_iVertices];
          m_pUV = new CTexel[m_iVertices];
          m_pFaces = new int[3*m_iFaces];

          for ( int v = 0; v != iVSeg; v++ )
          {
            for ( int h = 0; h != iHSeg; h++ )
            {
              m_pVertices[v*iHSeg + h].fX = fR*(float)cos( pi*h*2/(iHSeg-1) )*sin( pi*v/(iVSeg-1) );
              m_pVertices[v*iHSeg + h].fY = fR*cos( pi*v/(iVSeg-1) );//((float)v/iHSeg)*fR*2 - fR;
              m_pVertices[v*iHSeg + h].fZ = fR*(float)sin( pi*h*2/(iHSeg-1) )*sin( pi*v/(iVSeg-1) );

              m_pUV[v*iHSeg + h].fU = (float)h/(iHSeg-1);
              m_pUV[v*iHSeg + h].fV = (float)v/(iVSeg-1);
            }
          }

          for ( v = 0; v != iVSeg - 1; v++ )
          {
            for ( int h = 0; h != iHSeg - 1; h++ )
            {
              m_pFaces[6*(v*(iHSeg-1) + h) + 0] = v*iHSeg + h;
              m_pFaces[6*(v*(iHSeg-1) + h) + 1] = v*iHSeg + h + 1;
              m_pFaces[6*(v*(iHSeg-1) + h) + 2] = (v+1)*iHSeg + h;

              m_pFaces[6*(v*(iHSeg-1) + h) + 3] = v*iHSeg + h + 1;
              m_pFaces[6*(v*(iHSeg-1) + h) + 4] = (v+1)*iHSeg + h + 1;
              m_pFaces[6*(v*(iHSeg-1) + h) + 5] = (v+1)*iHSeg + h;
            }
          }

}
/*******************************************************************************************/
void CShadeBall::Do( float fTime, float fTimeStart ) {

        fTime -= fTimeStart;

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

        glTranslatef( 0, 0, -500 );

        float fAlpha = KeyVal( fTime );
        clamp( &fAlpha );

        glEnableClientState( GL_VERTEX_ARRAY );
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
        glDisableClientState( GL_COLOR_ARRAY );

        glBindTexture( GL_TEXTURE_2D, m_iGLTex );

        glVertexPointer( 3, GL_FLOAT, 0, m_pVertices );
        glTexCoordPointer( 2, GL_FLOAT, 0, m_pUV );

        glEnable( GL_CULL_FACE );
        glCullFace( GL_FRONT );


        float t = fTime, alpha;

        for ( int i = 0; i != 20; i++ )
        {
          alpha = 1 - (float)i/12;

          glPushMatrix();

          glRotatef( t*40 + 20*sin(t), 0, 1, 0 );
          glRotatef( t*60 + 30*sin(t*1.2) + 20*sin(t*2.1), 0, 0, 1 );
          glRotatef( t*50, 1, 0, 0 );
          glScalef( alpha*20 + .5, alpha*20 + .5, alpha*20 + .5 );

          glColor4f( 1, 1, 1, .3*alpha*fAlpha );
          glDrawElements( GL_TRIANGLES, m_iFaces*3, GL_UNSIGNED_INT, m_pFaces );

          glPopMatrix();

          t -= 0.014*(8*sin(fTime) + 12);
        }

        glCullFace( GL_BACK );
        glDisable( GL_CULL_FACE );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( -300, 300, -300, 300, -1, 1 );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();


        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glBindTexture( GL_TEXTURE_2D, m_iGLLayer1 );
        glColor4f( 1, 1, 1, fAlpha );
        glBegin( GL_QUADS );
          PutQuad( CTexel(0, 0), 1 );
        glEnd();

}
/*******************************************************************************************/


