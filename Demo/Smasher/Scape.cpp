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

#include "Scape.hpp"

#include "MainFrame/MainFrame.hpp"

#include "TerrainGen.hpp"

#define MAP_FILE "data/textures/map.raw"

CVector l_aTrack[] = 
{
  CVector( 400, 0, 500 ),
  CVector( 500, 0, 500 ),
  CVector( 600, 0, 600 ),
  CVector( 700, 0, 610 ),
  CVector( 750, 0, 700 ),
  CVector( 760, 0, 800 ),
  CVector( 780, 0, 900 ),
  CVector( 900, 0, 900 ),
  CVector(1000, 0, 950 )
};

int l_iTracks = sizeof(l_aTrack)/sizeof(CVector);

static inline float calc_cathmull(float* destv, float fA, float fB, float fC, float fD, float fT)
{
    register float   fa, fb, fc;

    fa = 0.5f * (3 * fB + fD - fA - 3 * fC);
    fb = fA + 2 * fC - 0.5f * (5 * fB + fD);
    fc = 0.5f * (fC - fA);

    destv[0] = 3 * fT * fT * fa + 2 * fT * fb + fc;

    return(fT * fT * fT * fa + fT * fT * fb + fT * fc + fB);
}

CScape::CScape()
{
    m_pTerrain = new CTerrain();

    if ( !m_pTerrain->LoadRawMap(MAP_FILE) )
    {
        g_pMainFrame->ErrorQuit( "[CScape::CScape] Cant load file %s\n", MAP_FILE );
        return;
    }
}

CScape::~CScape()
{
    if ( m_pTerrain )
        delete m_pTerrain;
}

void CScape::Do( float fTime, float fTimeStart )
{
    fTime -= fTimeStart;

    CCamera cCam;
    CMatrix cMat;

    CColor cFogCol(0, 0, 0, 0);
    glEnable( GL_FOG );
    glFogf( GL_FOG_START, 180 );
    glFogf( GL_FOG_END, 300 );
    glFogf( GL_FOG_MODE, GL_LINEAR );
    glFogfv( GL_FOG_COLOR, (float*)&cFogCol );

    cMat.Identity();

    CVector cPos, cV, cU(0, 1, 0), cR;

    float t = fmod( fTime/10, 1 );
    int iSeg = fmod( fTime/10, l_iTracks );

    cPos.fX = calc_cathmull( &cV.fX, l_aTrack[iSeg].fX, l_aTrack[(iSeg+1)%l_iTracks].fX, l_aTrack[(iSeg+2)%l_iTracks].fX, l_aTrack[(iSeg+3)%l_iTracks].fX, t );
    cPos.fY = calc_cathmull( &cV.fY, l_aTrack[iSeg].fY, l_aTrack[(iSeg+1)%l_iTracks].fY, l_aTrack[(iSeg+2)%l_iTracks].fY, l_aTrack[(iSeg+3)%l_iTracks].fY, t );
    cPos.fZ = calc_cathmull( &cV.fZ, l_aTrack[iSeg].fZ, l_aTrack[(iSeg+1)%l_iTracks].fZ, l_aTrack[(iSeg+2)%l_iTracks].fZ, l_aTrack[(iSeg+3)%l_iTracks].fZ, t );

    cMat.m_.sMatrix.stBaseW.fX = cPos.fX;
    cMat.m_.sMatrix.stBaseW.fY = m_pTerrain->GetSample( 0, cPos.fX, cPos.fZ ) + 30;
    cMat.m_.sMatrix.stBaseW.fZ = cPos.fZ;

    cCam.SetFrustum(-.6f, .6f, -.45f, .45f, 1, 300.0f );
    cCam.SetView( cMat, 0 );

    m_pTerrain->Render( cCam );
}
