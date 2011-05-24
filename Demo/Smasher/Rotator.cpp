
#include "stdafx.h"
#include "Rotator.hpp"

        static float l_fChangeTime = 8;
        static float l_fChangeTime1 = 16;

        static float l_fChangeTime3 = 26.5;

/******************************************************************************************/
CThing::CThing() {
        
        m_cUVPos = CTexel( 0, 0 );

        m_iGLTexName = g_cTexManager.LoadTexture( "data/textures/y2.jpg" );

        m_iGLLayer1 = g_cTexManager.LoadTexture( "data/textures/cred-saffron01.png" );
        m_iGLLayer2 = g_cTexManager.LoadTexture( "data/textures/cred-yoghurt01.png" );
        m_iGLLayer3 = g_cTexManager.LoadTexture( "data/textures/cred-radixlluvia01.png" );

}
/******************************************************************************************/
CThing::~CThing() {

        g_cTexManager.ReleaseTexture( m_iGLTexName );
}
/******************************************************************************************/
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
/******************************************************************************************/
void CThing::Do( float fTime, float fTimeStart ) {

        fTime -= fTimeStart;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustum( -.6, .6, -.45, .45, 1, 1000 );

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

        glColor4f( 1, 1, 1, (.2 + .1*sin(fTime*2))*fAlpha );

        glPushMatrix();

        for ( int i = 0; i != 8; i++ )
        {
          glRotatef( 5 + sin(fTime + i*10)*10, 0, 0, 1 );
          cUVPos.fU = -( .4*sin(fTime+i*6)+.4*cos(fTime*2+i*4))*.1;
          cUVPos.fV = ( .3*sin(fTime+i*12)+.4*sin(fTime+i*5))*.05;
          glBegin( GL_QUADS );
            PutQuad( cUVPos );
          glEnd();
        }

        glPopMatrix();

        m_cUVPos.fU = -fTime*.1;
        m_cUVPos.fV = fTime*.2;

        cUVPos.fU = 0;
        cUVPos.fV = 0;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( -300, 300, -300, 300, -1, 1 );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        if ( fTime < l_fChangeTime )
        {
          float fa = (l_fChangeTime-fTime)*.3;
          clamp( &fa );
       
          glBindTexture( GL_TEXTURE_2D, m_iGLLayer1 );
          glColor4f( 1, 1, 1, fa*fAlpha );
          glBegin( GL_QUADS );
            PutQuad( cUVPos, 1 );
          glEnd();

          glBindTexture( GL_TEXTURE_2D, m_iGLLayer3 );
          glColor4f( 1, 1, 1, (1-fa)*fAlpha);
          glBegin( GL_QUADS );
            PutQuad( cUVPos, 1 );
          glEnd();
        }
        else
        {
          float fa = (fTime - l_fChangeTime1)*.3;
          clamp( &fa );
      
          glBindTexture( GL_TEXTURE_2D, m_iGLLayer2 );
          glColor4f( 1, 1, 1, fa*fAlpha );
          glBegin( GL_QUADS );
            PutQuad( cUVPos, 1 );
          glEnd();

          glBindTexture( GL_TEXTURE_2D, m_iGLLayer3 );
          glColor4f( 1, 1, 1, (1-fa)*fAlpha);
          glBegin( GL_QUADS );
            PutQuad( cUVPos, 1 );
          glEnd();
        }

        float fBum = 1 - fTime*.5;
        clamp( &fBum );

        if ( fBum > 0 ) 
        {
          glDisable( GL_TEXTURE_2D );
          glBlendFunc( GL_SRC_ALPHA, GL_ONE );
          glColor4f( 1, 1, 1, fBum );

          glBegin( GL_QUADS );
            PutQuad( cUVPos, 1 );
          glEnd();
        }
}
/******************************************************************************************/

