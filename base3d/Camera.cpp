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
#else
#include "Camera.hpp"
#endif

#define CAMERA_DEF_FRUSTUM -.6f, .6f, -.45f, .45f, 1, 250.0f

static CMatrix l_cNeg;

//***********************************************************************************
void Frustum( CMatrix& cDest, float fLeft, float fRight, float fDown, float fUp, float fNear, float fFar ) {

        double fA, fB, fC, fD;

        fA = (fRight + fLeft)/(fRight - fLeft);
        fB = (fUp + fDown)/(fUp - fDown);
        fC = -(fFar + fNear)/(fFar - fNear);
        fD = -2*(fFar*fNear)/(fFar - fNear);

        cDest.Identity();

        cDest.m_.aMatrix[M_00] = (2*fNear)/(fRight - fLeft);
        cDest.m_.aMatrix[M_11] = (2*fNear)/(fUp - fDown);
        cDest.m_.aMatrix[M_22] = (float)fC;
        cDest.m_.aMatrix[M_33] = 0;
        cDest.m_.aMatrix[M_02] = (float)fA;
        cDest.m_.aMatrix[M_12] = (float)fB;
        cDest.m_.aMatrix[M_32] = -1;
        cDest.m_.aMatrix[M_23] = (float)fD;

        cDest.Transpose();
}
//***********************************************************************************







//***********************************************************************************
CCamera::CCamera()
{
    l_cNeg.Identity();
    l_cNeg.m_.sMatrix.stBaseX.fX = -1;
    l_cNeg.m_.sMatrix.stBaseX.fY = 0;
    l_cNeg.m_.sMatrix.stBaseX.fZ = 0;

    l_cNeg.m_.sMatrix.stBaseY.fX = 0;
    l_cNeg.m_.sMatrix.stBaseY.fY = 1;
    l_cNeg.m_.sMatrix.stBaseY.fZ = 0;

    l_cNeg.m_.sMatrix.stBaseZ.fX = 0;
    l_cNeg.m_.sMatrix.stBaseZ.fY = 0;
    l_cNeg.m_.sMatrix.stBaseZ.fZ = -1;

    m_cInvViewMatrix.Identity();
    m_cViewMatrix.Identity();

    SetFrustum( CAMERA_DEF_FRUSTUM );

    SetView( CVector(1, 0, 0),
             CVector(0, 1, 0),
             CVector(0, 0, 1),
             CVector(0, 0, 0) );
};
//***********************************************************************************
void CCamera::SetView(CMatrix& cViewMatrix, int nViewMatrix) {

        if ( nViewMatrix )
        {
          m_cViewMatrix = cViewMatrix;
          m_cInvViewMatrix.Inverse( m_cViewMatrix );
        }
        else 
        {
          m_cInvViewMatrix = cViewMatrix;
          m_cViewMatrix.Inverse( m_cInvViewMatrix );
        }

        m_stBaseX.fX = m_cInvViewMatrix.m_.aMatrix[M_00];
        m_stBaseX.fY = m_cInvViewMatrix.m_.aMatrix[M_01];
        m_stBaseX.fZ = m_cInvViewMatrix.m_.aMatrix[M_02];

        m_stBaseY.fX = m_cInvViewMatrix.m_.aMatrix[M_10];
        m_stBaseY.fY = m_cInvViewMatrix.m_.aMatrix[M_11];
        m_stBaseY.fZ = m_cInvViewMatrix.m_.aMatrix[M_12];

        m_stBaseZ.fX = m_cInvViewMatrix.m_.aMatrix[M_20];
        m_stBaseZ.fY = m_cInvViewMatrix.m_.aMatrix[M_21];
        m_stBaseZ.fZ = m_cInvViewMatrix.m_.aMatrix[M_22];
        
        m_stPosition.fX = m_cInvViewMatrix.m_.aMatrix[M_30];
        m_stPosition.fY = m_cInvViewMatrix.m_.aMatrix[M_31];
        m_stPosition.fZ = m_cInvViewMatrix.m_.aMatrix[M_32];

        ComputeExtents();
}
//***********************************************************************************
void CCamera::SetView(const CVector& stRight, const CVector& stUp, const CVector& stForward, const CVector& stPos) {

        m_stBaseX = stRight;
        m_stBaseY = stUp;
        m_stBaseZ = stForward;
        m_stPosition = stPos;

        m_stBaseX.Normalize();
        m_stBaseY.Normalize();
        m_stBaseZ.Normalize();

        m_cInvViewMatrix.m_.sMatrix.stBaseX.fX = m_stBaseX.fX;
        m_cInvViewMatrix.m_.sMatrix.stBaseX.fY = m_stBaseX.fY;
        m_cInvViewMatrix.m_.sMatrix.stBaseX.fZ = m_stBaseX.fZ;

        m_cInvViewMatrix.m_.sMatrix.stBaseY.fX = m_stBaseY.fX;
        m_cInvViewMatrix.m_.sMatrix.stBaseY.fY = m_stBaseY.fY;
        m_cInvViewMatrix.m_.sMatrix.stBaseY.fZ = m_stBaseY.fZ;

        m_cInvViewMatrix.m_.sMatrix.stBaseZ.fX = m_stBaseZ.fX;
        m_cInvViewMatrix.m_.sMatrix.stBaseZ.fY = m_stBaseZ.fY;
        m_cInvViewMatrix.m_.sMatrix.stBaseZ.fZ = m_stBaseZ.fZ;

        m_cInvViewMatrix.m_.sMatrix.stBaseW.fX = m_stPosition.fX;
        m_cInvViewMatrix.m_.sMatrix.stBaseW.fY = m_stPosition.fY;
        m_cInvViewMatrix.m_.sMatrix.stBaseW.fZ = m_stPosition.fZ;

        m_cViewMatrix.Inverse( m_cInvViewMatrix );

        ComputeExtents();
}
//***********************************************************************************
void CCamera::SetFrustum(float fLeft, float fRight, float fBottom, float fTop, float fNear, float fFar) {

        m_fLeft = fLeft;
        m_fRight = fRight;
        m_fBottom = fBottom;
        m_fTop = fTop;
        m_fNear = fNear;
        m_fFar = fFar;

        Frustum( m_cProjection, m_fLeft, m_fRight, m_fBottom, m_fTop, m_fNear, m_fFar);

        ComputeFrustumPoints();
        ComputeExtents();
}
//***********************************************************************************
void CCamera::ComputeFrustumPoints() {

        float fRatio;

        m_aFrustumPoints[0].fX = m_fLeft;
        m_aFrustumPoints[0].fY = m_fTop;
        m_aFrustumPoints[0].fZ = -m_fNear;

        m_aFrustumPoints[1].fX = m_fRight;
        m_aFrustumPoints[1].fY = m_fTop;
        m_aFrustumPoints[1].fZ = -m_fNear;

        m_aFrustumPoints[2].fX = m_fRight;
        m_aFrustumPoints[2].fY = m_fBottom;
        m_aFrustumPoints[2].fZ = -m_fNear;

        m_aFrustumPoints[3].fX = m_fLeft;
        m_aFrustumPoints[3].fY = m_fBottom;
        m_aFrustumPoints[3].fZ = -m_fNear;

        fRatio = m_fFar / m_fNear;

        m_aFrustumPoints[4].fX = m_fLeft * fRatio;
        m_aFrustumPoints[4].fY = m_fTop * fRatio;
        m_aFrustumPoints[4].fZ = -m_fFar;

        m_aFrustumPoints[5].fX = m_fRight * fRatio;
        m_aFrustumPoints[5].fY = m_fTop * fRatio;
        m_aFrustumPoints[5].fZ = -m_fFar;

        m_aFrustumPoints[6].fX = m_fRight * fRatio;
        m_aFrustumPoints[6].fY = m_fBottom * fRatio;
        m_aFrustumPoints[6].fZ = -m_fFar;

        m_aFrustumPoints[7].fX = m_fLeft * fRatio;
        m_aFrustumPoints[7].fY = m_fBottom * fRatio;
        m_aFrustumPoints[7].fZ = -m_fFar;
}
//***********************************************************************************
void CCamera::ComputeExtents() {

        CVector aCamVertices[8];
        int i;

        m_cInvViewMatrix.MulVertices( aCamVertices, m_aFrustumPoints, 8 );

        m_stExtents.m_cMin.fX = 
        m_stExtents.m_cMax.fX = aCamVertices[0].fX;

        m_stExtents.m_cMin.fY = 
        m_stExtents.m_cMax.fY = aCamVertices[0].fY;

        m_stExtents.m_cMin.fZ = 
        m_stExtents.m_cMax.fZ = aCamVertices[0].fZ;

        for (i = 1; i < 8; i++)
        {
          if (m_stExtents.m_cMax.fX < aCamVertices[i].fX) m_stExtents.m_cMax.fX = aCamVertices[i].fX;
          if (m_stExtents.m_cMin.fX > aCamVertices[i].fX) m_stExtents.m_cMin.fX = aCamVertices[i].fX;

          if (m_stExtents.m_cMax.fY < aCamVertices[i].fY) m_stExtents.m_cMax.fY = aCamVertices[i].fY;
          if (m_stExtents.m_cMin.fY > aCamVertices[i].fY) m_stExtents.m_cMin.fY = aCamVertices[i].fY;

          if (m_stExtents.m_cMax.fZ < aCamVertices[i].fZ) m_stExtents.m_cMax.fZ = aCamVertices[i].fZ;
          if (m_stExtents.m_cMin.fZ > aCamVertices[i].fZ) m_stExtents.m_cMin.fZ = aCamVertices[i].fZ;
        }

}
//***********************************************************************************

#undef CAMERA_DEF_FRUSTUM 

