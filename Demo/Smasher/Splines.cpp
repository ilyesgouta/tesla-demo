//
// tesla-demo, an OpenGL|ES 1.1 port of Sunflower's original Tesla demo.
//
// Original Tesla code, Copyright (C) 2000 Sunflower
// Linux EGL/X11 port by Ilyes Gouta, ilyes.gouta@gmail.com
//
// Port released under GNU General Public License with permission from
// Konrad Zagorowicz, original developer from Sunflower.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifdef WIN32
#include "stdafx.h"
#endif

#include "Splines.hpp"

#if !defined pi
#define pi 3.1415926535897932384626433832795
#endif

float l_fChangeTime3 = 19.5;

static inline float calc_cathmull(float fA, float fB, float fC, float fD, float fT)
{
    register float   fa, fb, fc;

    fa = 0.5f * (3 * fB + fD - fA -3 * fC);
    fb = fA + 2 * fC - 0.5f * (5 * fB + fD);
    fc = 0.5f * (fC - fA);

    return(fT * fT * fT * fa + fT * fT * fb + fT * fc + fB);
}

void CSplineTrail::Init( int iGLTex, int iTailLen, CVector cXSin, CVector cYSin, CVector cZSin )
{
    m_iGLTex = iGLTex;
    m_iTailLen = iTailLen;

    m_cXSinParams = cXSin;
    m_cYSinParams = cYSin;
    m_cZSinParams = cZSin;
}

void CSplineTrail::Render( float fTime )
{
    CMatrix cCam;

    float fAlpha = 1;

    glGetFloatv( GL_MODELVIEW_MATRIX, cCam.m_.aMatrix );

    cCam.Inverse();

    CVector& cX = cCam.m_.sMatrix.stBaseX;
    CVector& cY = cCam.m_.sMatrix.stBaseY;
    CVector cPos;

    glBlendFunc(GL_SRC_COLOR, GL_ONE);//_MINUS_SRC_ALPHA);
    glBindTexture( GL_TEXTURE_2D, m_iGLTex );

#ifdef GL_VERSION_ES_CM_1_1
    glClientActiveTexture(GL_TEXTURE0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
#else
    glBegin( GL_QUADS );
#endif

    float t = fTime;

    cX *= 10;
    cY *= 10;

    for ( int i = 0; i != m_iTailLen; i++ )
    {
        cPos.fX = sin(t * m_cXSinParams.fX) * m_cXSinParams.fZ + sin(t * m_cXSinParams.fY + 1) * m_cXSinParams.fZ;
        cPos.fY = sin(t * m_cYSinParams.fX) * m_cYSinParams.fZ + sin(t * m_cYSinParams.fY + 1) * m_cYSinParams.fZ;
        cPos.fZ = sin(t * m_cZSinParams.fX) * m_cZSinParams.fZ + sin(t * m_cZSinParams.fY + 1) * m_cZSinParams.fZ;

        fAlpha = 1 - (float)i/m_iTailLen;
        clamp( &fAlpha );

        fAlpha *= fAlpha; fAlpha *= fAlpha;

        glColor4f( 1*fAlpha, 1*fAlpha, .9*fAlpha, fAlpha );

        float k = sin(fAlpha * 3.14 + 5);//t );

        glColor4f( 1, 1, .9, .1 * fAlpha );

        if (t > 3)
        {
            float q = t - 3;
            clamp(&q);

            k = 1 - q + q * k;
        } else k = 1;

#ifdef GL_VERSION_ES_CM_1_1
        m_Vertex[0].x = (cPos - cX - cY).fX;
        m_Vertex[0].y = (cPos - cX - cY).fY;
        m_Vertex[0].z = (cPos - cX - cY).fZ;
        m_Texture[0].s0 = 0; m_Texture[0].t0 = 1;

        m_Vertex[1].x = ((cPos - cX + cY)*k).fX;
        m_Vertex[1].y = ((cPos - cX + cY)*k).fY;
        m_Vertex[1].z = ((cPos - cX + cY)*k).fZ;
        m_Texture[1].s0 = 0; m_Texture[1].t0 = 0;

        m_Vertex[2].x = ((cPos + cX - cY)*k).fX;
        m_Vertex[2].y = ((cPos + cX - cY)*k).fY;
        m_Vertex[2].z = ((cPos + cX - cY)*k).fZ;
        m_Texture[2].s0 = 1; m_Texture[2].t0 = 1;

        m_Vertex[3].x = ((cPos + cX + cY)*k).fX;
        m_Vertex[3].y = ((cPos + cX + cY)*k).fY;
        m_Vertex[3].z = ((cPos + cX + cY)*k).fZ;
        m_Texture[3].s0 = 1; m_Texture[3].t0 = 0;

        glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
        glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#else
        glTexCoord2f( 0, 0 );
        glVertex3fv( (float*)&((cPos - cX + cY)*k) );
        glTexCoord2f( 1, 0 );
        glVertex3fv( (float*)&((cPos + cX + cY)*k) );
        glTexCoord2f( 1, 1 );
        glVertex3fv( (float*)&((cPos + cX - cY)*k) );
        glTexCoord2f( 0, 1 );
        glVertex3fv( (float*)&(cPos - cX - cY) );
#endif
        t -= 0.036;
    }

#ifdef GL_VERSION_ES_CM_1_1
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
    glEnd();
#endif
}

CSplines::CSplines()
{
    m_iFlareGLTex = g_cTexManager.LoadTexture( "data/textures/flare02.jpg" );
    //m_iFlareGLTex = g_cTexManager.LoadTexture( "data/textures/spheresmall.png" );
    m_iGLTex = g_cTexManager.LoadTexture( "data/textures/sphere.jpg" );

    m_pSplines = new CSplineTrail[16];
    m_iSplines = 16;

    m_pSplines[0].Init( m_iFlareGLTex, 64, CVector(1.2, 2.3, 100), CVector(2.3, 2.13, 100), CVector(1.32, 2.16, 100) );
    m_pSplines[1].Init( m_iFlareGLTex, 64, CVector(2.122, 1.3, 80), CVector(3.3, 1.13, 100), CVector(2.43, 1.26, 100) );
    m_pSplines[2].Init( m_iFlareGLTex, 64, CVector(1.32, 1.14, 100), CVector(2.35, 2.223, 100), CVector(1.132, 2.416, 100) );
    m_pSplines[3].Init( m_iFlareGLTex, 64, CVector(1.52, 2.23, 50), CVector(1.63, 2.613, 100), CVector(1.42, 3.06, 100) );
    m_pSplines[4].Init( m_iFlareGLTex, 64, CVector(2.256, 2.23, 100), CVector(1.03, 1.213, 100), CVector(1.532, 2.216, 70) );
    m_pSplines[5].Init( m_iFlareGLTex, 64, CVector(2.2, 1.3, 50), CVector(1.73, 2.413, 120), CVector(1.332, 2.916, 100) );
    m_pSplines[6].Init( m_iFlareGLTex, 64, CVector(4.2, 1.3, 100), CVector(1.3, 1.13, 100), CVector(2.32, 2.16, 150) );
    m_pSplines[7].Init( m_iFlareGLTex, 64, CVector(1.22, 0.93, 80), CVector(0.9, 1.913, 80), CVector(1.32, 2.16, 110) );

    m_pSplines[8].Init( m_iFlareGLTex, 64, CVector(1.12, 2.3, 140), CVector(2.3, -2.13, 130), CVector(1.32, -2.16, 150) );
    m_pSplines[9].Init( m_iFlareGLTex, 64, CVector(-2.212, 1.3, 160), CVector(3.3, 1.13, -150), CVector(-2.43, 1.26, 140) );
    m_pSplines[10].Init( m_iFlareGLTex, 64, CVector(1.23, -1.14, 200), CVector(2.35, -2.223, 150), CVector(1.132, 2.416, -120) );
    m_pSplines[11].Init( m_iFlareGLTex, 64, CVector(1.25, 2.23, 100), CVector(1.63, -2.613, 100), CVector(-1.42, -3.06, 160) );
    m_pSplines[12].Init( m_iFlareGLTex, 64, CVector(-2.25, 2.23, 200), CVector(1.03, 1.213, -150), CVector(1.532, 2.216, 140) );
    m_pSplines[13].Init( m_iFlareGLTex, 64, CVector(2.2, -1.3, 100), CVector(-1.73, 2.413, 190), CVector(-1.332, 2.916, 200) );
    m_pSplines[14].Init( m_iFlareGLTex, 64, CVector(3.62, 2.3, 150), CVector(1.3, -1.13, -120), CVector(2.32, -2.16, 150) );
    m_pSplines[15].Init( m_iFlareGLTex, 64, CVector(1.22, -0.93, 160), CVector(0.9, -1.913, 120), CVector(-1.32, 2.16, 210) );

    MakeSphere();
}

CSplines::~CSplines()
{
    g_cTexManager.ReleaseTexture( m_iFlareGLTex );

    if ( m_pSplines ) delete[] m_pSplines;

    if ( m_pVertices ) delete[] m_pVertices;
    if ( m_pFaces ) delete[] m_pFaces;
    if ( m_pUV ) delete[] m_pUV;
}

void CSplines::MakeSphere()
{
    const float fR = 600;
    const int iVSeg = 10;
    const int iHSeg = 10;

    m_iVertices = iVSeg*iHSeg;
    m_iFaces = (iVSeg - 1)*(iHSeg - 1)*2;

    m_pVertices = new CVector[m_iVertices];
    m_pUV = new CTexel[m_iVertices];
    m_pFaces = new unsigned short[3*m_iFaces];

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

    for ( int v = 0; v != iVSeg - 1; v++ )
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

void CSplines::Do( float fTime, float fTimeStart )
{
    fTime -= fTimeStart;

    float fAspect = 480/640.;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustumf(-3.1f, 3.1f, -3.1f*fAspect, 3.1f*fAspect, 1.0f, 2300.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
    glDepthFunc(GL_LEQUAL);

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glEnable( GL_TEXTURE_2D );

    glTranslatef( 0, 0, -500 );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    glBindTexture( GL_TEXTURE_2D, m_iGLTex );

    glVertexPointer( 3, GL_FLOAT, 0, m_pVertices );
    glTexCoordPointer( 2, GL_FLOAT, 0, m_pUV );

    glRotatef( fTime*15, 0, 1, 0 );
    glRotatef( 90*sin(fTime/2)+90*sin(fTime*.9), 0, 0, 1 );

    glPushMatrix();

    glColor4f( 1, 1, 1, .3 + .1*sin(fTime*2) );

    for ( int i = 0; i != 8; i++ )
    {
        glRotatef( 6*fTime*i, 0, 1, 0 );
        glRotatef( 5, 0, 0, 1 );
        glScalef( 1.1, 1.1, 1.1 );
        glDrawElements( GL_TRIANGLES, m_iFaces*3, GL_UNSIGNED_SHORT, m_pFaces );
    }

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustumf(-0.5f, .5f, -.5f*fAspect, .5f*fAspect, 1.0f, 2300.0f);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    float tr = 0;
    if (fTime>3)
    {
        tr = fTime-3;
        tr*=0.3;
        clamp(&tr);
        tr*=180;
    }

    glTranslatef( tr, 0, -500 );
    glRotatef( fTime*15, 0, 1, 0 );
    glRotatef( 90*sin(fTime/2)+90*sin(fTime*.9), 0, 0, 1 );

    for ( int i = 0; i != m_iSplines; i++ )
    {
        m_pSplines[i].Render( fTime );
    }
}
