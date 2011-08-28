
#ifdef WIN32
#include "stdafx.h"
#endif

#include "tubes.hpp"
#include "sinus.hpp"

#define TUBE_U 6
#define TUBE_V 8

static float l_fChangeTime1 = 6.6666666666666666666666666666667;
static float l_fChangeTime2 = 13.333333333333333333333333333333;
static float l_fChangeTime3 = 19.0;

const float fR = 90;
const int iVSeg = 8;
const int iHSeg = 8;

CTubes::CTubes()
{
    CMultiTexData aMultiTex[2];
    CMatrix cMatrix;

    m_pSObject = new CSplinedObject;

    m_iGLTex1 = g_cTexManager.LoadTexture( "data/textures/t1b.jpg" );
    m_iGLTex1a = g_cTexManager.LoadTexture( "data/textures/t1b.jpg" );
    m_iGLTex2 = g_cTexManager.LoadTexture( "data/textures/face.jpg" );

    aMultiTex[0].m_fAlpha = 1.0f;
    aMultiTex[0].m_nGLTexName = &m_iGLTex1;
    aMultiTex[0].m_nMaterial = 1;

    aMultiTex[1].m_fAlpha = 1.0f;
    aMultiTex[1].m_nGLTexName = &m_iGLTex1;
    aMultiTex[1].m_nMaterial = 2;

    m_pSObject->SetMultiTexData(aMultiTex, 2);

    cMatrix.Identity();
    m_pSObject->SetMatrix(cMatrix);

    m_pSObject->SetSeed(4, 6);

    m_pTable = new CObjectNode[TUBE_U*TUBE_V];

    m_pSObject->AddTable( m_pTable, TUBE_U, TUBE_V );
    m_pSObject->CloseTableU();

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

        for ( int v = 0; v != iVSeg - 1; v++ )
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

#if GL_VERSION_ES_CM_1_1
    m_Vertex[0].x = -10;
    m_Vertex[0].y = -10;
    m_Vertex[0].z = -30;
    m_Texture[0].s0 = 0; m_Texture[0].t0 = 1;

    m_Vertex[1].x = -10;
    m_Vertex[1].y = 10;
    m_Vertex[1].z = -30;
    m_Texture[1].s0 = 0; m_Texture[1].t0 = 0;

    m_Vertex[2].x = 10;
    m_Vertex[2].y = -10;
    m_Vertex[2].z = -30;
    m_Texture[2].s0 = 1; m_Texture[2].t0 = 1;

    m_Vertex[3].x = 10;
    m_Vertex[3].y = 10;
    m_Vertex[3].z = -30;
    m_Texture[3].s0 = 1; m_Texture[3].t0 = 0;
#endif
}

CTubes::~CTubes()
{
    if (m_pTable) delete[] m_pTable;
    if (m_pSObject) delete m_pSObject;

    g_cTexManager.ReleaseTexture( m_iGLTex1 );
    g_cTexManager.ReleaseTexture( m_iGLTex1a );
    g_cTexManager.ReleaseTexture( m_iGLTex2 );
}

void CTubes::Do( float fTime, float fTimeStart )
{
    m_fTime = fTime - fTimeStart;

    float fAspect = 480.f/640.f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustumf(-0.5f, 0.5f, -0.5f*fAspect, 0.5f*fAspect, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float fAlpha;

    if ( m_fTime > l_fChangeTime1 )
    {
        fAlpha = m_fTime - l_fChangeTime1;
        clamp( &fAlpha );

        if ( m_fTime > l_fChangeTime2 )
        {
            fAlpha = m_fTime - l_fChangeTime2;
            clamp( &fAlpha );

            if ( m_fTime > l_fChangeTime3 )
            {
                fAlpha *= 1 + l_fChangeTime3 - m_fTime ;
                clamp( &fAlpha );
            }
        }
        else
        {
            fAlpha *= l_fChangeTime2 - m_fTime;
            clamp( &fAlpha );
        }
    }
    else
    {
        fAlpha = l_fChangeTime1 - m_fTime;
        clamp( &fAlpha );
    }

    glColor4f( 1, 1, 1, .15f*fAlpha );

    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, m_iGLTex2 );

#if GL_VERSION_ES_CM_1_1
    glClientActiveTexture(GL_TEXTURE0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
    glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
    glBegin( GL_QUADS );
    glTexCoord2f( 0, 0 );
    glVertex3f( -10, 10, -30 );
    glTexCoord2f( 1, 0 );
    glVertex3f(  10, 10, -30);
    glTexCoord2f( 1, 1 );
    glVertex3f(  10,-10, -30 );
    glTexCoord2f( 0, 1 );
    glVertex3f( -10,-10, -30 );
    glEnd();
#endif

    glTranslatef( 0, 0, -420 );
    glRotatef( 40*sin(m_fTime/2), 1, 0, 0 );
    glRotatef( 30 + 20*sin(m_fTime/2), 0, 0, 1 );

    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
    glDepthFunc(GL_LEQUAL);

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    CMatrix cView;
    CMatrix cProjection;
    cView.Identity();

    m_pSObject->EnableNormals();

    MakeTubes( fAlpha );

    glColor4f( 1, 1, 1, (sin(m_fTime*5)*.05f + .15f)*fAlpha );

    if ( m_fTime > l_fChangeTime1 )
    {
        if ( m_fTime > l_fChangeTime2 )
        {
            glRotatef( 90, 0, 0, 1 );
            glRotatef( 180, 1, 0, 0 );
        }
        else
            glRotatef( 90, 0, 0, 1 );
    }

    for ( int x = 0; x != 8; x++ )
        RenderTube( 1 + x*.4f, 10*m_fTime*x );

    m_pSObject->Render(cView, cProjection);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
}

void CTubes::RenderTube( float fScale, float fAngle0 ) 
{
        glEnableClientState( GL_VERTEX_ARRAY );
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
        glDisableClientState( GL_COLOR_ARRAY );

        glEnable( GL_TEXTURE_2D );

        if ( m_fTime > l_fChangeTime1 )
        {
          if ( m_fTime > l_fChangeTime2 )
          {
            glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );
          }
          else
            glBindTexture( GL_TEXTURE_2D, m_iGLTex1a );
        }
        else
          glBindTexture( GL_TEXTURE_2D, m_iGLTex1 );

        glPushMatrix();
        glRotatef( fAngle0, 0, 1, 0 );
        glScalef( fScale, fScale, fScale );


        glVertexPointer( 3, GL_FLOAT, 0, m_pTubeVertices );
        glTexCoordPointer( 2, GL_FLOAT, 0, m_pTubeUV );
        glDrawElements( GL_TRIANGLES, m_iTubeFaces*3, GL_UNSIGNED_SHORT, m_pTubeFaces );

        glPopMatrix();
}

void CTubes::MakeTubes( float fAlpha ) {

        CNodeData cData;
        float fR = 60;

        CSinPulse cPulse1( 40, 60, 2.14f, 0 );
        CSinPulse cPulseU( -10, 20, 0.9f, 0 );

        for (int v = 0; v != TUBE_V; v++)
        {
          fR = cPulse1.Calculate( m_fTime*v*.55f );

          for (int u = 0; u != TUBE_U; u++)
          {
            fR += cPulseU.Calculate( m_fTime*v*2*(float)pi*u/TUBE_U*.4f );

            cData.m_cColor = CColor( 1, 1, 1, .6f*fAlpha );

            cData.m_cPosition.fX = fR*(float)cos(((float)u*2*pi)/TUBE_U);
            cData.m_cPosition.fY = (v*140 - (TUBE_V-1)*70.0f);
            cData.m_cPosition.fZ = fR*(float)sin(((float)u*2*pi)/TUBE_U);
            cData.m_cTexel.fU = (float)u/TUBE_U + m_fTime*.1f;
            cData.m_cTexel.fV = (float)v/TUBE_V*1.5f - m_fTime*.3f;

            m_pTable[u + v*TUBE_U].SetData(cData);
          }
        }
}
