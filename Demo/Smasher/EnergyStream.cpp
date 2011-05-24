
#include "stdafx.h"
#include "EnergyStream.hpp" 


        static float l_fChangeTime = 15;
        static float l_fChangeTime1 = 25;
        static float l_fChangeTime2 = 38; 
        static float l_fChangeTime2a =46;
        static float l_fChangeTime3 = 58;

/*******************************************************************************************/
CFlareStream::CFlareStream() {

        m_iFlares = 0;
        m_pFlares = 0;
        m_iGLFlareTex = -1;
}
/*******************************************************************************************/
CFlareStream::~CFlareStream() {

        if ( m_iGLFlareTex != -1 ) g_cTexManager.ReleaseTexture( m_iGLFlareTex );
        if ( m_pFlares ) delete[] m_pFlares;
}
/*******************************************************************************************/
void CFlareStream::Init( int iSeed, int iGLFlareTex, CVector& cBasePos, float fSpeed ) {

        m_pFlares = new CVector[iSeed];
        m_iFlares = iSeed;
        m_iGLFlareTex = iGLFlareTex;
        m_fSpeed = fSpeed;

        for ( int i = 0; i != m_iFlares; i++ )
        {
          m_pFlares[i].fX = -800.0f*rand()/RAND_MAX - 1150;
          m_pFlares[i].fY = 10.0f*rand()/RAND_MAX - 20;
          m_pFlares[i].fZ = 10.0f*rand()/RAND_MAX - 20;
          m_pFlares[i] += cBasePos;
        }
}
/*******************************************************************************************/
void CFlareStream::Render( float fTime, CVector& cBaseX, CVector& cBaseY, float fAlpha ) {

        static const l_fFlareSize = 10;

        if ( m_iGLFlareTex == -1 ) return;
        if ( !m_pFlares ) return;

        CVector cFlarePos;

        if ( fTime < l_fChangeTime ) return;

        fTime -= l_fChangeTime;

        glColor4f( 1, 1, 1, fAlpha );
        glBindTexture( GL_TEXTURE_2D, m_iGLFlareTex );

        glBegin( GL_QUADS );

        float fMultipler = 1;

        if ( fTime + l_fChangeTime > l_fChangeTime1 )
        {
          if ( fTime + l_fChangeTime > l_fChangeTime2 )
          {
            fMultipler = 2.5;
          }
          else
            fMultipler = 2;
        }

        char szDbg[256];

        sprintf( szDbg, "mult %f\n", fMultipler );
        OutputDebugString( szDbg );

        for ( int i = 0; i != m_iFlares; i++ )
        {
          cFlarePos.fX = fmod( m_pFlares[i].fX + fTime*m_fSpeed*fMultipler, 800 ) - 400;
          cFlarePos.fY = m_pFlares[i].fY + 2*sin(fTime*7 + m_pFlares[i].fX );
          cFlarePos.fZ = m_pFlares[i].fZ + 2*cos(fTime*7 + i*3.14);

          glTexCoord2f( 0, 0 );
          glVertex3fv( (float*)&(cFlarePos - cBaseX + cBaseY) );
          glTexCoord2f( 1, 0 );
          glVertex3fv( (float*)&(cFlarePos + cBaseX + cBaseY) );
          glTexCoord2f( 1, 1 );
          glVertex3fv( (float*)&(cFlarePos + cBaseX - cBaseY) );
          glTexCoord2f( 0, 1 );
          glVertex3fv( (float*)&(cFlarePos - cBaseX - cBaseY) );
        }

        glEnd();
}
/*******************************************************************************************/




/*******************************************************************************************/
static void PutQuad( CTexel cUVPos ) {

        glTexCoord2f( 0 + cUVPos.fU, 0 + cUVPos.fV );
        glVertex3f( -300, 300, 0 );
        glTexCoord2f( 1 + cUVPos.fU, 0 + cUVPos.fV );
        glVertex3f( 300, 300, 0 );
        glTexCoord2f( 1 + cUVPos.fU, 1 + cUVPos.fV );
        glVertex3f( 300, -300, 0 );
        glTexCoord2f( 0 + cUVPos.fU, 1 + cUVPos.fV );
        glVertex3f( -300, -300, 0 );
}
/*******************************************************************************************/
CEnergyStream::CEnergyStream() {

        m_iGLTex1 = g_cTexManager.LoadTexture( "data/textures/y7.jpg" );
        m_iGLTex2 = g_cTexManager.LoadTexture( "data/textures/y6.jpg" );


        m_pFStreams = new CFlareStream[16];
        m_iFStreams = 16;

        int iFlareTex = g_cTexManager.LoadTexture("data/textures/flare02.jpg");

        m_pFStreams[0].Init( 150, iFlareTex, CVector(0, 50, 0), 300 );
        m_pFStreams[1].Init( 150, iFlareTex, CVector(0, 0, 0), 150 );
        m_pFStreams[2].Init( 150, iFlareTex, CVector(0, 90, 60), 250 );
        m_pFStreams[3].Init( 150, iFlareTex, CVector(0, -100, 30), 160 );
        m_pFStreams[4].Init( 150, iFlareTex, CVector(0, 50, -100), 340 );
        m_pFStreams[5].Init( 150, iFlareTex, CVector(0, -50, 50), 270  );
        m_pFStreams[6].Init( 150, iFlareTex, CVector(0, 100, 50), 180 );
        m_pFStreams[7].Init( 150, iFlareTex, CVector(0, -30, 90), 130 );

        m_pFStreams[8].Init( 150, iFlareTex, CVector(0, 150, 10), 200 );
        m_pFStreams[9].Init( 150, iFlareTex, CVector(0, 100, -100), 210 );
        m_pFStreams[10].Init( 150, iFlareTex, CVector(0, 190, 160), 220 );
        m_pFStreams[11].Init( 150, iFlareTex, CVector(0, -200, 130), 230 );
        m_pFStreams[12].Init( 150, iFlareTex, CVector(0, 150, -200), 240 );
        m_pFStreams[13].Init( 150, iFlareTex, CVector(0, -150, 250), 160 );
        m_pFStreams[14].Init( 150, iFlareTex, CVector(0, 200, 150), 230 );
        m_pFStreams[15].Init( 150, iFlareTex, CVector(0, -130, 190), 250 );
}
/*******************************************************************************************/
CEnergyStream::~CEnergyStream() {

        g_cTexManager.ReleaseTexture( m_iGLTex1 );
        g_cTexManager.ReleaseTexture( m_iGLTex2 );
}
/*******************************************************************************************/
void CEnergyStream::Do( float fTime, float fTimeStart ) {

        fTime -= fTimeStart;

        int i;


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

        glTranslatef( 0, 0, -300 );
        glRotatef( fTime*30, 1, 0, 0 );
        glRotatef( 30*sin(fTime/3) + 10, 0, 0, 1 );

        if ( fTime > l_fChangeTime1 )
        {
          if ( fTime > l_fChangeTime2 )
          {
            glRotatef( 90, 0, 1, 0 );
          }
          else
            glRotatef( 180, 0, 1, 0 );
        }


        glEnable( GL_FOG );
        glFogf( GL_FOG_START, 200 );
        glFogf( GL_FOG_END, 500 );
        glFogf( GL_FOG_MODE, GL_LINEAR );


        glPushMatrix();

        CTexel cUVPos(0, 0);
        float fAlpha = 1;

        if ( fTime > l_fChangeTime )
        {
          cUVPos = CTexel(.1*sin(fTime), fTime/5);
          glBindTexture( GL_TEXTURE_2D, m_iGLTex2 );
          fAlpha = fTime - l_fChangeTime;

          clamp( &fAlpha );

          if ( fTime > l_fChangeTime1 )
          {
            fAlpha *= ( fTime - l_fChangeTime1 );
            clamp( &fAlpha );
            glRotatef( 90, 0, 1, 0 );

            if ( fTime > l_fChangeTime2 )
            {
              fAlpha *= ( fTime - l_fChangeTime2 );
              clamp( &fAlpha );

              if ( fTime > l_fChangeTime3 )
              {
                fAlpha *= ( 1 + l_fChangeTime3 - fTime );
                clamp( &fAlpha );
              }
            }
            else
            {
              fAlpha *= ( l_fChangeTime2 - fTime );
              clamp( &fAlpha );
            }
          }
          else
          {
            fAlpha *= ( l_fChangeTime1 - fTime );
            clamp( &fAlpha );
          }


          glColor4f( 1, 1, 1, fAlpha );
        }
        else
        {
          glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );
          fAlpha = (l_fChangeTime - fTime)*.5;
          clamp( &fAlpha );
          glColor4f( 1, 1, 1, (sin(fTime*2)*.25 + .75)*fAlpha );//(sin(fTime*2)*.5 + 1)*fAlpha );
        }

        if ( fTime > l_fChangeTime )
        {
          for ( i = 0; i != 8; i++ )
          {

            glBegin( GL_QUADS );
              PutQuad( cUVPos );
            glEnd();

            glRotatef( 180/7, 1, 0, 0 );
          }
        }
        else
          for ( i = 0; i != 16; i++ )
          {

            glBegin( GL_QUADS );
              PutQuad( cUVPos );
            glEnd();

            glRotatef( 180/15, 1, 0, 0 );
          }

        glPopMatrix();

        CMatrix cCamera;

        glGetFloatv( GL_MODELVIEW_MATRIX, (float*)cCamera.aMatrix );

        cCamera.Inverse();


        for ( i = 0; i != m_iFStreams; i++ )
        {
          m_pFStreams[i].Render( fTime, cCamera.stBaseX*10, cCamera.stBaseY*10, fAlpha );
        }

        glDisable( GL_FOG );
}
/*******************************************************************************************/

