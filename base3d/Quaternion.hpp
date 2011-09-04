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
// programing by Yoghurt
// copyright (C) 1999 by Konrad Zagorowicz

#if !defined (CQuaternion_hpp_)
#define CQuaternion_hpp_

#include "CVector.hpp"
#include "CMatrix.hpp"


class CQuaternion {

public:
        CVector cV;
        float fScalar;

        CQuaternion() {
          fScalar = 1;
          cV.fX = cV.fY = cV.fZ = 0;
        };

        CQuaternion( float x, float y, float z, float w ) {
          cV.fX = x; cV.fY = y; cV.fZ = z; fScalar = w;
        }

        CQuaternion( const CVector& cVector, float fS ) {
          cV = cVector;
          fScalar = fS;
        }

        CQuaternion( const CQuaternion& cQ ) {
          *this = cQ;
        }

        void Identity() {
          fScalar = 1;
          cV.fX = cV.fY = cV.fZ = 0;
        }


        /* addition */
        CQuaternion& operator += ( CQuaternion& cQ1 ) {
          cV += cQ1.cV;
          fScalar += cQ1.fScalar;
          return *this;
        }

        CQuaternion operator + ( const CQuaternion& cQ1 ) const {
          return CQuaternion( cV.fX + cQ1.cV.fX, cV.fY + cQ1.cV.fY, cV.fZ + cQ1.cV.fZ, fScalar + cQ1.fScalar );
        }

        /* substraction */
        CQuaternion& operator -= ( CQuaternion& cQ1 ) {
          cV -= cQ1.cV;
          fScalar -= cQ1.fScalar;
          return *this;
        }

        CQuaternion operator - ( CQuaternion& cQ1 ) const {
          return CQuaternion( cV.fX - cQ1.cV.fX, cV.fY - cQ1.cV.fY, cV.fZ - cQ1.cV.fZ, fScalar - cQ1.fScalar );
        }

        /* multiplication */
        CQuaternion& operator *= ( CQuaternion& cQ1 ) {

          CQuaternion cRes;

          cRes.fScalar = fScalar*cQ1.fScalar - cQ1.cV.Dot( cV );
          cRes.cV = cV.Cross( cQ1.cV ) + cQ1.cV*fScalar + cV*cQ1.fScalar;

          cV = cRes.cV;
          fScalar = cRes.fScalar;
          return *this;
        }

        CQuaternion operator * ( CQuaternion& cQ1 ) {

          return CQuaternion( cV.Cross(cQ1.cV) + cQ1.cV*fScalar + cV*cQ1.fScalar, 
                              fScalar*cQ1.fScalar - cQ1.cV.Dot(cV) );
        }

        /* conjugate */
        void Conjugate() {
          cV.fX = -cV.fX;
          cV.fY = -cV.fY;
          cV.fZ = -cV.fZ;
        }

        CQuaternion operator ^ ( CQuaternion& cQ1 ) {
          return CQuaternion( -cV, fScalar );
        }

        /* norm */
        float Len2() {
          return fScalar*fScalar + cV.Dot( cV );
        }

        /* inverse */
        void Inverse() {

          float fL = 1.f/Len2();

          Conjugate();
          cV *= fL;
          fScalar *= fL;
        }

        void InverseUnit() {
          Conjugate();
        }

        /* conversions */
        void FromAxisAndAngle( CVector& cAxis, float fAngle );

        /* to get result muliply quaternios ex. qroll*qyaw*qpitch */
        void FromEulerRoll( float fRoll );
        void FromEulerPitch( float fPitch );
        void FromEulerYaw( float fYaw );

        void FromMatrix( CMatrix& cMatrix );

        void ToMatrix( CMatrix& cMatrix );


        /* interpolation */
        CQuaternion Slerp( CQuaternion& cQ1, float fT );




};

#endif /* CQuaternion_hpp_ */
