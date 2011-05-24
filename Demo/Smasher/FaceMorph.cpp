
#include "stdafx.h"
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

/*******************************************************************************************/
static inline CVector LerpVertex( vertex_t& cV1, vertex_t& cV2, float t ) {

        CVector& v1 = (CVector&)cV1.vlocal;
        CVector& v2 = (CVector&)cV2.vlocal;

        return (v2 - v1)*t + v1;
}
/*******************************************************************************************/
static inline CVector LerpNormal( vertex_t& cV1, vertex_t& cV2, float t ) {

        CVector& v1 = (CVector&)cV1.wlocal;
        CVector& v2 = (CVector&)cV2.wlocal;

        return (v2 - v1)*t + v1;
}
/*******************************************************************************************/
CFaceMorph::CFaceMorph() {

        m_iGLTex1 = g_cTexManager.LoadTexture( "data/textures/y6.jpg" );
        m_iGLTex1a = g_cTexManager.LoadTexture( "data/textures/t1a.jpg" );

        m_iGLTex2 = g_cTexManager.LoadTexture( "data/textures/max_t1.jpg" );
        m_iGLBackTex = g_cTexManager.LoadTexture( "data/textures/y7.jpg" );

        m_iGLTexBlend = g_cTexManager.LoadTexture( "data/textures/blend2.png" );


        m_pScene = Load3ds( "data/3d/faces.3ds" );

        face_t* pFace = m_pScene->objects[2].faces;
        m_iFaces = m_pScene->objects[2].nfaces;

        m_iVertices = m_pScene->objects[2].nvertices;
        m_pVertices = new CVector[m_iVertices];
        m_pUV = new CTexel[m_iVertices];
        m_pNormals = new CVector[m_iVertices];
        m_pEnvUV = new CTexel[m_iVertices];

        vertex_t* pVertices = m_pScene->objects[2].vertices;

        m_pFaces = new int[3*m_iFaces];

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


        
        for ( uint u = 0; u != m_pScene->nobjects; u++ )
        {
          pVertices = m_pScene->objects[u].vertices;
          
          for ( i = 0; (uint)i != m_pScene->objects[u].nvertices; i++ )
          {
            pVertices->vlocal = pVertices->vglobal;
            pVertices++;
          }
        }

        /* create tubes */
        m_iTubeVertices = iVSeg*iHSeg;
        m_iTubeFaces = (iVSeg - 1)*(iHSeg - 1)*2;

        m_pTubeVertices = 0;
        m_pTubeUV = 0;
        m_pTubeFaces = 0;

        {
          m_pTubeVertices = new CVector[m_iTubeVertices];
          m_pTubeUV = new float[2*m_iTubeVertices];
          m_pTubeFaces = new int[3*m_iTubeFaces];

          for ( int v = 0; v != iVSeg; v++ )
          {
            for ( int h = 0; h != iHSeg; h++ )
            {
              m_pTubeVertices[v*iHSeg + h].fX = fR*(float)cos( pi*h*2/(iHSeg-1) );
              m_pTubeVertices[v*iHSeg + h].fY = v*70.f - (iVSeg-1)*35.f;
              m_pTubeVertices[v*iHSeg + h].fZ = fR*(float)sin( pi*h*2/(iHSeg-1) );

              m_pTubeUV[2*(v*iHSeg + h) + 0] = (float)h/(iHSeg-1);
              m_pTubeUV[2*(v*iHSeg + h) + 1] = (float)v/(iVSeg-1);
            }
          }

          for ( v = 0; v != iVSeg - 1; v++ )
          {
            for ( int h = 0; h != iHSeg - 1; h++ )
            {
              m_pTubeFaces[6*(v*(iHSeg-1) + h) + 0] = v*iHSeg + h;
              m_pTubeFaces[6*(v*(iHSeg-1) + h) + 1] = v*iHSeg + h + 1;
              m_pTubeFaces[6*(v*(iHSeg-1) + h) + 2] = (v+1)*iHSeg + h;

              m_pTubeFaces[6*(v*(iHSeg-1) + h) + 3] = v*iHSeg + h + 1;
              m_pTubeFaces[6*(v*(iHSeg-1) + h) + 4] = (v+1)*iHSeg + h + 1;
              m_pTubeFaces[6*(v*(iHSeg-1) + h) + 5] = (v+1)*iHSeg + h;
            }
          }
        }
}
/*******************************************************************************************/
CFaceMorph::~CFaceMorph() {

        if ( m_pVertices ) delete[] m_pVertices;
        if ( m_pFaces ) delete[] m_pFaces;
        if ( m_pNormals ) delete[] m_pNormals;
        if ( m_pEnvUV ) delete[] m_pEnvUV;
}
/*******************************************************************************************/
void CFaceMorph::Do( float fTime, float fTimeStart ) {

        CVector cN;
        CMatrix cCam;

        fTime -= fTimeStart;

        float fAlpha = 1;

        fAlpha = l_fChangeTime3 - fTime;
        clamp( &fAlpha );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustum( -12.6f, 12.6f, -12.45f, 12.45f, 1, 1000 );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glTranslatef( 2, 0, -13 );
        glRotatef( 20*sin(fTime), 1, 0, 0 );
        glRotatef( 10*sin(fTime*.9) - 15, 0, 1, 0 );
        glRotatef( 180, 0, 1, 0 );
        glGetFloatv( GL_MODELVIEW_MATRIX, cCam.aMatrix );
        cCam.stBaseW = CBase(0, 0, 0, 1);

        glEnable( GL_TEXTURE_2D );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glDisable( GL_CULL_FACE );
        glDisable( GL_DEPTH_TEST );
        glDepthMask( 0 );

        /* some background */
        glColor4f(1, 1, 1, .4*fAlpha );

        for ( int u = 0; u != 4; u++ )
        {
          RenderTube( 1 + u, 1 + fTime*10*u );
        }
        
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustum( -.6f, .6f, -.45f, .45f, 1, 1000 );


        glEnable( GL_CULL_FACE );
        glCullFace( GL_FRONT );
        glEnable( GL_DEPTH_TEST );
        glDepthMask( 1 );
        glDepthFunc( GL_LEQUAL );


        glEnableClientState( GL_VERTEX_ARRAY );
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
        glDisableClientState( GL_COLOR_ARRAY );


        /* morphing */
        float fT = fmod(fTime*l_fMorphSpeed, 1);

        fT = cos((1-fT)*3.14159)*.5 + .5;

        int iO1 = (int)(fmod(fTime*l_fMorphSpeed, 4));
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

        vertex_t* pV1 = m_pScene->objects[iO1].vertices;
        vertex_t* pV2 = m_pScene->objects[iO2].vertices;

        for ( int i = 0; i != m_iVertices; i++ )
        {
          m_pVertices[i] = LerpVertex( pV1[i], pV2[i], fT );
          m_pNormals[i] = LerpNormal( pV1[i], pV2[i], fT );
          cN = cCam*m_pNormals[i];
          m_pEnvUV[i].fU = cN.fX*.5 + .5;
          m_pEnvUV[i].fV = cN.fY*.5 + .5;

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
        glColor4f( 1, 1, 1, 1*fAlpha );
        glTexCoordPointer( 2, GL_FLOAT, 0, m_pUV );
        glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glLoadIdentity();
        glTranslatef( fTime*.05, fTime*.1, 0 );
        glRotatef( fTime*30, 0, 0, 1 );
        glDrawElements( GL_TRIANGLES, m_iFaces*3, GL_UNSIGNED_INT, m_pFaces );
        glColor4f( 1, 1, 1, .5*fAlpha );
        glBindTexture( GL_TEXTURE_2D, m_iGLTex1a );
        glLoadIdentity();
        glTranslatef( fTime*.05, -fTime*.05, 0 );
        glRotatef( -fTime*20, 0, 0, 1 );
        glDrawElements( GL_TRIANGLES, m_iFaces*3, GL_UNSIGNED_INT, m_pFaces );
        glLoadIdentity();

        /* env */
        glColor4f( 1, 1, 1, 1*fAlpha );
        glTexCoordPointer( 2, GL_FLOAT, 0, m_pEnvUV );
        glBindTexture( GL_TEXTURE_2D, m_iGLTex2 );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glDrawElements( GL_TRIANGLES, m_iFaces*3, GL_UNSIGNED_INT, m_pFaces );

        glLoadIdentity();
        glMatrixMode( GL_MODELVIEW );

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

}
/*******************************************************************************************/
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
        glDrawElements( GL_TRIANGLES, m_iTubeFaces*3, GL_UNSIGNED_INT, m_pTubeFaces );

        glPopMatrix();
}
/*******************************************************************************************/




