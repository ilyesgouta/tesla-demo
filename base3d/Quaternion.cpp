// programing by Yoghurt
// copyright (C) 1999 by Konrad Zagorowicz

#ifdef WIN32
#include "stdafx.h"
#endif

#include <math.h>

#include "Quaternion.hpp"

/************************************************************************************/
void CQuaternion::FromAxisAndAngle( CVector& cAxis, float fAngle ) {
  
        fAngle *= .5f;

        fScalar = (float)cos( fAngle );
        cV = cAxis*(float)sin( fAngle );
}
/************************************************************************************/
void CQuaternion::FromEulerRoll( float fRoll ) {

        fRoll *= .5f;

        cV.fX = 0;
        cV.fY = 0;
        cV.fZ = (float)sin( fRoll );

        fScalar = (float)cos( fRoll );
}
/************************************************************************************/
void CQuaternion::FromEulerPitch( float fPitch ) {
  
        fPitch *= .5f;

        cV.fX = 0;
        cV.fY = (float)sin( fPitch );
        cV.fZ = 0;

        fScalar = (float)cos( fPitch );
}
/************************************************************************************/
void CQuaternion::FromEulerYaw( float fYaw ) {
  
        fYaw *= .5f;

        cV.fX = (float)sin( fYaw );
        cV.fY = 0;
        cV.fZ = 0;

        fScalar = (float)cos( fYaw );
}
/************************************************************************************/
void CQuaternion::FromMatrix( CMatrix& cMatrix ) {
  
        float  fDiagonal, fS, q[4];
        int    i, j, k, nxt[3] = {1, 2, 0};

        fDiagonal = cMatrix.m_.aMatrix[M_00] + cMatrix.m_.aMatrix[M_11] + cMatrix.m_.aMatrix[M_22];

        if ( fDiagonal > 0.f ) 
        {
          fS = (float)sqrt( fDiagonal + 1.f );
          fScalar = fS*.5f;
          fS = .5f/fS;
          cV.fX = (cMatrix.m_.aMatrix[M_12] - cMatrix.m_.aMatrix[M_21]) * fS;
          cV.fY = (cMatrix.m_.aMatrix[M_20] - cMatrix.m_.aMatrix[M_02]) * fS;
          cV.fZ = (cMatrix.m_.aMatrix[M_01] - cMatrix.m_.aMatrix[M_10]) * fS;
        } 
        else 
        {
          i = 0;
          if ( cMatrix.m_.aMatrix[M_11] > cMatrix.m_.aMatrix[M_00] ) i = 1;
          if ( cMatrix.m_.aMatrix[M_22] > cMatrix.m_.aMatrix[i*4 + i] ) i = 2;
          j = nxt[i];
          k = nxt[j];

          fS = (float)sqrt( (cMatrix.m_.aMatrix[i*4 + i] - (cMatrix.m_.aMatrix[j*4 + j] + cMatrix.m_.aMatrix[k*4 + k])) + 1.f );

          q[i] = fS*.5f;

          if ( fS != 0.f ) fS = .5f/fS;

          q[3] = (cMatrix.m_.aMatrix[j*4 + k] - cMatrix.m_.aMatrix[k*4 + j])*fS;
          q[j] = (cMatrix.m_.aMatrix[i*4 + j] + cMatrix.m_.aMatrix[j*4 + i])*fS;
          q[k] = (cMatrix.m_.aMatrix[i*4 + k] + cMatrix.m_.aMatrix[k*4 + i])*fS;

          cV.fX = q[0];
          cV.fY = q[1];
          cV.fZ = q[2];
          fScalar = q[3];
        }
}
/************************************************************************************/
void CQuaternion::ToMatrix( CMatrix& cMatrix ) {

        float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

        x2 = cV.fX + cV.fX; y2 = cV.fY + cV.fY; 
        z2 = cV.fZ + cV.fZ;
        xx = cV.fX*x2; xy = cV.fX*y2; xz = cV.fX*z2;
        yy = cV.fY*y2; yz = cV.fY*z2; zz = cV.fZ*z2;
        wx = fScalar*x2; wy = fScalar*y2; wz = fScalar*z2;

        cMatrix.m_.aMatrix[M_00] = 1.f - (yy + zz); cMatrix.m_.aMatrix[M_01] = xy - wz;
        cMatrix.m_.aMatrix[M_02] = xz + wy; cMatrix.m_.aMatrix[M_03] = 0.f;

        cMatrix.m_.aMatrix[M_10] = xy + wz; cMatrix.m_.aMatrix[M_11] = 1.f - (xx + zz);
        cMatrix.m_.aMatrix[M_12] = yz - wx; cMatrix.m_.aMatrix[M_13] = 0.f;

        cMatrix.m_.aMatrix[M_20] = xz - wy; cMatrix.m_.aMatrix[M_21] = yz + wx;
        cMatrix.m_.aMatrix[M_22] = 1.f - (xx + yy); cMatrix.m_.aMatrix[M_23] = 0.f;

        cMatrix.m_.aMatrix[M_30] = 0.f; cMatrix.m_.aMatrix[M_31] = 0.f;
        cMatrix.m_.aMatrix[M_32] = 0.f; cMatrix.m_.aMatrix[M_33] = 1.f;
}
/************************************************************************************/
CQuaternion CQuaternion::Slerp( CQuaternion& cQ1, float fT )
{
        float to1[4];
        double omega, cosom, sinom, scale0, scale1;

        // calc cosine
        cosom = cV.Dot( cQ1.cV ) + fScalar*cQ1.fScalar;

        
        if ( cosom < 0.0 )
        { 
          cosom = -cosom; 
          to1[0] = -cQ1.cV.fX;
          to1[1] = -cQ1.cV.fY;
          to1[2] = -cQ1.cV.fZ;
          to1[3] = -cQ1.fScalar;
        }
        else  
        {
          to1[0] = cQ1.cV.fX;
          to1[1] = cQ1.cV.fY;
          to1[2] = cQ1.cV.fZ;
          to1[3] = cQ1.fScalar;
        }


        if ( (1.0 - cosom) > 0.001 ) 
        {
          omega = acos( cosom );
          sinom = sin( omega );
          scale0 = sin( (1.0 - fT) * omega )/sinom;
          scale1 = sin( fT * omega )/sinom;
        }
        else 
        {        
          scale0 = 1.0 - fT;
          scale1 = fT;
        }

        return CQuaternion( (float)(scale0*cV.fX + scale1*to1[0]), 
                            (float)(scale0*cV.fY + scale1*to1[1]), 
                            (float)(scale0*cV.fZ + scale1*to1[2]),
                            (float)(scale0*fScalar + scale1*to1[3]) );
}
/************************************************************************************/

