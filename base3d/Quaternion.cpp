// programing by Yoghurt
// copyright (C) 1999 by Konrad Zagorowicz

#include "stdafx.h"

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

        fDiagonal = cMatrix.aMatrix[M_00] + cMatrix.aMatrix[M_11] + cMatrix.aMatrix[M_22];

        if ( fDiagonal > 0.f ) 
        {
          fS = (float)sqrt( fDiagonal + 1.f );
          fScalar = fS*.5f;
          fS = .5f/fS;
          cV.fX = (cMatrix.aMatrix[M_12] - cMatrix.aMatrix[M_21])*fS;
          cV.fY = (cMatrix.aMatrix[M_20] - cMatrix.aMatrix[M_02])*fS;
          cV.fZ = (cMatrix.aMatrix[M_01] - cMatrix.aMatrix[M_10])*fS;
        } 
        else 
        {
          i = 0;
          if ( cMatrix.aMatrix[M_11] > cMatrix.aMatrix[M_00] ) i = 1;
          if ( cMatrix.aMatrix[M_22] > cMatrix.aMatrix[i*4 + i] ) i = 2;
          j = nxt[i];
          k = nxt[j];

          fS = (float)sqrt( (cMatrix.aMatrix[i*4 + i] - (cMatrix.aMatrix[j*4 + j] + cMatrix.aMatrix[k*4 + k])) + 1.f );

          q[i] = fS*.5f;

          if ( fS != 0.f ) fS = .5f/fS;

          q[3] = (cMatrix.aMatrix[j*4 + k] - cMatrix.aMatrix[k*4 + j])*fS;
          q[j] = (cMatrix.aMatrix[i*4 + j] + cMatrix.aMatrix[j*4 + i])*fS;
          q[k] = (cMatrix.aMatrix[i*4 + k] + cMatrix.aMatrix[k*4 + i])*fS;

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

        cMatrix.aMatrix[M_00] = 1.f - (yy + zz); cMatrix.aMatrix[M_01] = xy - wz;
        cMatrix.aMatrix[M_02] = xz + wy; cMatrix.aMatrix[M_03] = 0.f;

        cMatrix.aMatrix[M_10] = xy + wz; cMatrix.aMatrix[M_11] = 1.f - (xx + zz);
        cMatrix.aMatrix[M_12] = yz - wx; cMatrix.aMatrix[M_13] = 0.f;

        cMatrix.aMatrix[M_20] = xz - wy; cMatrix.aMatrix[M_21] = yz + wx;
        cMatrix.aMatrix[M_22] = 1.f - (xx + yy); cMatrix.aMatrix[M_23] = 0.f;

        cMatrix.aMatrix[M_30] = 0.f; cMatrix.aMatrix[M_31] = 0.f;
        cMatrix.aMatrix[M_32] = 0.f; cMatrix.aMatrix[M_33] = 1.f;
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

