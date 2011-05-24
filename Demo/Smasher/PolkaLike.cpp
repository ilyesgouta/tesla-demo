
#include "stdafx.h"
#include "PolkaLike.hpp"

static const float l_fZMax = 300;


        static float l_fChangeTime = 10;
        static float l_fChangeTime1 = 20;


        static float l_fChangeTime3 = 19;



static float l_fTime;

/*******************************************************************************************/
inline void TrackElem_c::Update( float fDelTime ) {

          m_cPosition += m_cDelPos*fDelTime;
          m_fAnlgeZ += -2*1.234f*fDelTime;
}
/*******************************************************************************************/






/*******************************************************************************************/
PolkaLike_c::PolkaLike_c() {

        Init();
}
/*******************************************************************************************/
PolkaLike_c::~PolkaLike_c() {

        if ( m_pTracks ) delete[] m_pTracks;

        g_cTexManager.ReleaseTexture( m_iTexture );
        g_cTexManager.ReleaseTexture( m_iBack );
}
/*******************************************************************************************/
void PolkaLike_c::Init() {

        int iTracks = 4;
        int iTrackElems = 128;

        m_pTracks = new Track_c[iTracks];
        m_iTracks = iTracks;

        m_pTracks[0].Init( iTrackElems, pi/2.13, pi/3.41 );
        m_pTracks[1].Init( iTrackElems, pi/2.93, pi/1.72 );
        m_pTracks[2].Init( iTrackElems, pi/3.97, pi );
        m_pTracks[3].Init( iTrackElems, pi*1.23, pi*2.17 );

        m_iTexture = g_cTexManager.LoadTexture( "data/textures/polka.png" );
        m_iBack = g_cTexManager.LoadTexture( "data/textures/max_t3.jpg" );
}
/*******************************************************************************************/
void PutQuad( float fZ ) {

        glBegin( GL_QUADS );
          glTexCoord2f( 0, 0 );
          glVertex3f( -1, 1, fZ );
          glTexCoord2f( 1, 0 );
          glVertex3f(  1, 1, fZ );
          glTexCoord2f( 1, 1 );
          glVertex3f( 1, -1, fZ );
          glTexCoord2f( 0, 1 );
          glVertex3f( -1, -1, fZ );
        glEnd();
}
/*******************************************************************************************/
void PolkaLike_c::Do( float fTime, float fTimeStart ) {

        fTime -= fTimeStart;
        l_fTime = fTime;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustum( -.6f, .6f, -.45f, .45f, 1, l_fZMax );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glEnable(GL_BLEND);
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glEnable( GL_TEXTURE_2D );
       
        glBindTexture( GL_TEXTURE_2D, m_iBack );

        float fAlpha = fTime*.5f;
        clamp( &fAlpha );

        float fCol = .25*sin(fTime) + .5;

        glColor4f( 1, 1, 1, fCol*fAlpha );

        for ( int a = 0; a != 16; a++ )
        {
          float fZ = -1.4f;
          glRotatef( 4*sin(fTime), 0, 1, 0 );
          glRotatef( 5*fTime, 0, 0, 1 );
          PutQuad( fZ - 1*a );
        }

        glBindTexture( GL_TEXTURE_2D, m_iTexture );
        for ( int i = 0; i != m_iTracks; i++ ) m_pTracks[i].Render( .016, fTime );

}
/*******************************************************************************************/









/*******************************************************************************************/
void Track_c::Init( int iElems, float fInitAngleChange, float fInitPosChange ) {

        m_iTrackElems = iElems;
        m_pTrackElems = new TrackElem_c[iElems];

        CVector cDelPos( 0, 0, 100 );

        m_fInitAngleChange = fInitAngleChange;
        m_fInitPosChange = fInitPosChange;

        for ( int i = 0; i != m_iTrackElems; i++ )
        { 
          m_cInitPos.fX = (float)(10*cos(m_fInitPos) + 10*sin(m_fInitPos*1.32));
          m_cInitPos.fY = (float)(15*sin(m_fInitPos) + 5*sin(m_fInitPos*.89) );
          m_cInitPos.fZ = -3*l_fZMax - (l_fZMax/m_iTrackElems)*i;

          m_pTrackElems[i].Init( m_cInitPos, cDelPos, m_fInitAngleZ );

          m_fInitAngleZ += m_fInitAngleChange*.042f;
          m_fInitPos += m_fInitPosChange*.042f;
        }
}
/*******************************************************************************************/
void Track_c::Render( float fDelTime, float fTime ) {

        CVector cRot(0, 0, 0);
        CVector cRot1(0, 0, 0);

        glLineWidth(2);
        glBegin( GL_QUADS );

        float fAlpha = 1;

        for ( int i = 0; i != m_iTrackElems; i++ )
        {
          m_pTrackElems[i].Update( fDelTime );

          cRot.fX = (float)cos( m_pTrackElems[i].m_fAnlgeZ );//*10;
          cRot.fY = (float)sin( m_pTrackElems[i].m_fAnlgeZ );//*5;
          cRot1.fY = -cRot.fX;
          cRot1.fX = cRot.fY;
          cRot.fX *= 5;
          cRot.fY *= 5;

          fAlpha = -m_pTrackElems[i].m_cPosition.fZ/l_fZMax + .2;

          glColor4f( 1, 1, 1, fAlpha );

          glTexCoord2f( 0, 0 );
          glVertex3fv( (float*)&(m_pTrackElems[i].m_cPosition + cRot - cRot1) );

          glTexCoord2f( 1, 0 );
          glVertex3fv( (float*)&(m_pTrackElems[i].m_cPosition + cRot + cRot1) );

          glTexCoord2f( 1, 1 );
          glVertex3fv( (float*)&(m_pTrackElems[i].m_cPosition - cRot + cRot1) );

          glTexCoord2f( 0, 1 );
          glVertex3fv( (float*)&(m_pTrackElems[i].m_cPosition - cRot - cRot1) );

          if ( l_fTime < l_fChangeTime3 )
          if ( m_pTrackElems[i].m_cPosition.fZ > 0 )
          {
            m_pTrackElems[i].m_cPosition.fZ = -l_fZMax;
            m_pTrackElems[i].m_cPosition.fX = m_cInitPos.fX;
            m_pTrackElems[i].m_cPosition.fY = m_cInitPos.fY;
            m_pTrackElems[i].m_fAnlgeZ = m_fInitAngleZ;
          }
        }

        glEnd();

        if ( fTime < l_fChangeTime )
        {
          m_cInitPos.fX = (float)(10*cos(m_fInitPos) + 10*sin(m_fInitPos*1.32));
          m_cInitPos.fY = (float)(15*sin(m_fInitPos) + 5*sin(m_fInitPos*.89) );
        }
        else
        if ( fTime < l_fChangeTime1 )
        {
          m_cInitPos.fX = (float)(15*cos(m_fInitPos) + 15*sin(m_fInitPos*2.32));
          m_cInitPos.fY = (float)(30*sin(m_fInitPos) + 15*sin(m_fInitPos*1.89) );
        }
        else
        {
          m_cInitPos.fX = (float)(30*cos(m_fInitPos) + 15*sin(m_fInitPos*.72));
          m_cInitPos.fY = (float)(25*sin(m_fInitPos) + 19*sin(m_fInitPos*.59) );
        }

        m_cInitPos.fZ = -l_fZMax;

        m_fInitAngleZ += m_fInitAngleChange*fDelTime;
        m_fInitPos += m_fInitPosChange*fDelTime;
}
/*******************************************************************************************/






