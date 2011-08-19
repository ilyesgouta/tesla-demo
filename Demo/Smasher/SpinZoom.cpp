
//3.5-9
//15-19

#include "stdafx.h"
#include "SpinZoom.hpp"
#include "Stuff.hpp"

static const float l_fBoundMin = -3;
static const float l_fBoundMax = 3;
static const float l_fZMax = 300;


class kdat
{
public:
	float t;
	float v;

	kdat(float a,float b):t(a),v(b){};
};

kdat unrTab[] = { 
	kdat(0,0), kdat(3.3,0), // poczatek, full black
	kdat(6.5, 1), kdat(8,1), // pierwszy widok
	kdat(9,0), kdat(10,0), // black pomiedzy
	kdat(13,1), kdat(15,0), 
	kdat(16,1), 
	kdat(20,0), kdat(22,1), 
	kdat(24,0), kdat(99,0), kdat(99,0), kdat(99,0), kdat(99,0), kdat(99,0)};

	static float l_fChangeTime3 = 19;

/*******************************************************************************************/
static inline void PutQuad() {

        glBegin( GL_QUADS );
          glTexCoord2f( 0, 0 );
          glVertex3f( - 1, 1, 0 );
          glTexCoord2f( 1, 0 );
          glVertex3f( 1, 1, 0 );
          glTexCoord2f( 1, 1 );
          glVertex3f( 1, -1, 0 );
          glTexCoord2f( 0, 1 );
          glVertex3f( -1, -1, 0 );
        glEnd();
}
/*******************************************************************************************/
inline void CSpin::Init( float fAngle0, float fAngleChange, float fScaleChange, CSinWave cSinWave ) {

        m_cPosition.fZ = -((float)rand()/RAND_MAX)*l_fZMax;
        m_cPosition.fX = ((float)rand()/RAND_MAX)*(l_fBoundMax - l_fBoundMin) + l_fBoundMin;
        m_cPosition.fY = ((float)rand()/RAND_MAX)*(l_fBoundMax - l_fBoundMin) + l_fBoundMin;

        m_fAngle = fAngle0;
        m_fAngleChange = fAngleChange;
        m_fScaleChange = fScaleChange;
        m_cSinWave = cSinWave;
}

/*******************************************************************************************/
void CSpin::Render( float fTime ) {
	
	int u;
	CDarkQuads cDarkQuads;
	float timeSpan;
	
	
	//m_cPosition.fZ += .09f;
	
	m_cPosition.fZ = -2;
	m_cPosition.fX = 0;
	m_cPosition.fY = 0;
	
	if ( m_cPosition.fZ > 0 ) 
	{
		m_cPosition.fX = ((float)rand()/RAND_MAX)*(l_fBoundMax - l_fBoundMin) + l_fBoundMin;
		m_cPosition.fY = ((float)rand()/RAND_MAX)*(l_fBoundMax - l_fBoundMin) + l_fBoundMin;
		m_cPosition.fZ -= l_fZMax;
	}
	
	float unrMult;
	float bTime;
	
	for (u=0; u< 100; u++)
		if ((fTime > unrTab[u].t) && (fTime<unrTab[u+1].t))
			break;
		timeSpan = (unrTab[u+1].t-unrTab[u].t);
		bTime = (fTime - unrTab[u].t) / timeSpan;
		unrMult = unrTab[u].v +  (unrTab[u+1].v-unrTab[u].v) * bTime;
		
		//				fprintf(w, "%f %d %f %f\n", fTime, u, bTime, unrMult);
		
        glColor4f( 1, 1, 1, unrMult *0.23 );
		
        glPushMatrix();
        glTranslatef( m_cPosition.fX, m_cPosition.fY, m_cPosition.fZ );
        glRotatef( fTime , 0, 1, 0 );
        glRotatef( fTime*.5123f, 1, 0, 0 );
		
        for ( int i = 0; i != 18; i++ )
        {
			switch (u)
			{
			case 5:
			case 6:
				glRotatef( fTime*3 + 5, 1, -.2f, -.3f );
				glColor4f( 1, 1, 1, unrMult *0.33);
				{
					float uM = sin(bTime*3.14159/2);
					if (unrTab[u+1].v>=unrTab[u].v)
						glScalef( m_fScaleChange * uM, m_fScaleChange, 1 );
					else
						glScalef( m_fScaleChange , m_fScaleChange, 1 );
				}
				break;
			case 7:
			case 8:
				glRotatef( fTime*22 + 5, 1, 0, 0 );
				glRotatef( fTime*2 + 5, 0, 0, 1 );
				glColor4f( 1, 1, 1, unrMult *0.33);
				
				break;
			case 9:
			case 10:
				glRotatef( 10*(float)sin(fTime) + 5, 1, -.2f, .3f );
				glRotatef( 5*(float)cos(fTime) + 10*(float)cos(fTime/2), 0, .5, 1 );
			if (unrTab[u+1].v<unrTab[u].v)
				glScalef( m_fScaleChange * unrMult, m_fScaleChange, 1 );
			else
				glScalef( m_fScaleChange , m_fScaleChange, 1 );

				break;
			default:
				glRotatef( 10*(float)sin(fTime*0.9)+ 5, 1, -.2f, .3f );
			if (unrTab[u+1].v>unrTab[u].v)
				glScalef( m_fScaleChange * unrMult * unrMult, m_fScaleChange, 1 );
			else
				glScalef( m_fScaleChange , m_fScaleChange, 1 );

				break;
			};
			
			//          glRotatef( 5*(float)cos(fTime) + 10*(float)cos(fTime/2), 0, .5, 1 );

			PutQuad();
        }
        glPopMatrix();
		
		switch(u)
		{
		case 5:
		case 6:
			cDarkQuads.Render( 20, CColor(0,0,0.1,0.12));
			break;
		case 7:
		case 8:
			cDarkQuads.Render( 220, CColor(0,0,0.041,0.1));
			break;
			
		default:
			cDarkQuads.Render( 80);
		}
		
}
/*******************************************************************************************/





/*******************************************************************************************/
CSpinZoom::CSpinZoom() {
	
	m_pSpins = 0;
	m_iSpins = 0;
	
	m_iTex1 = g_cTexManager.LoadTexture( "data/textures/sphere.jpg" );
	
	m_pSpins = new CSpin[512];
	m_iSpins = 1;
	
	for ( int i = 0; i != m_iSpins; i++ )
		m_pSpins[i].Init( 0, 5, 1.02f, CSinWave(30.f, 1.23f, 0) );
}
/*******************************************************************************************/
CSpinZoom::~CSpinZoom() {

        if ( m_pSpins ) delete[] m_pSpins;
}
/*******************************************************************************************/
void CSpinZoom::Do( float fTime, float fTimeStart ) {

        m_fTime = fTime - fTimeStart - .1;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustum( -.6f, .6f, -.45f, .45f, 1, l_fZMax );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glEnable( GL_TEXTURE_2D );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glDisable( GL_CULL_FACE );
        glDisable( GL_DEPTH_TEST );
        glDepthMask( 0 );

        glBindTexture( GL_TEXTURE_2D, m_iTex1 );

        for ( int i = 0; i != m_iSpins; i++ )
        {
          m_pSpins[i].Render( m_fTime );
        }

}
/*******************************************************************************************/
