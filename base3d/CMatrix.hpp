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

#if !defined(_CMatrix_hpp_)
#define _CMatrix_hpp_

#include <string.h>

#include  "CVector.hpp"

#define M_00             0
#define M_01             1
#define M_02             2
#define M_03             3
#define M_10             4
#define M_11             5
#define M_12             6
#define M_13             7
#define M_20             8
#define M_21             9
#define M_22            10
#define M_23            11
#define M_30            12
#define M_31            13
#define M_32            14
#define M_33            15

class CBase : public CVector {
public:
    CBase() : CVector() {}

    CBase(float X, float Y, float Z, float W) : CVector(X, Y, Z) {
        fW = W;
    }

    CBase(CVector& cV) {
        *this = cV;
    }

    float fW;

    CBase operator = (const CVector& cV) {
        fX = cV.fX;
        fY = cV.fY;
        fZ = cV.fZ;
        return *this;
    }

    float Dot( CVector& cV ) {
        return fX * cV.fX + fY * cV.fY + fZ * cV.fZ + fW;
    }

    float Dot( CBase& cV ) {
        return fX * cV.fX + fY * cV.fY + fZ * cV.fZ + fW * cV.fW;
    }
};

class CMatrix
{
public:
    union m__ {
        m__() { memset(aMatrix, 0, sizeof(aMatrix)); }
        struct sMatrix {
            CBase stBaseX;
            CBase stBaseY;
            CBase stBaseZ;
            CBase stBaseW;
        } sMatrix;
        float aMatrix[16];
    } m_;

    CMatrix() { }

	void Identity() {
        m_.sMatrix.stBaseX = CBase(1, 0, 0, 0);
        m_.sMatrix.stBaseY = CBase(0, 1, 0, 0);
        m_.sMatrix.stBaseZ = CBase(0, 0, 1, 0);
        m_.sMatrix.stBaseW = CBase(0, 0, 0, 1);
	}

    CMatrix& operator *= (CMatrix& cM) {
        CMatrix cT;
        for (int i = 0; i != 4; i++)
            for (int j = 0; j != 4; j++) {
                cT.m_.aMatrix[j * 4 + i] = m_.aMatrix[i + 0 * 4] * cM.m_.aMatrix[j * 4 + 0] +
                                           m_.aMatrix[i + 1 * 4] * cM.m_.aMatrix[j * 4 + 1] +
                                           m_.aMatrix[i + 2 * 4] * cM.m_.aMatrix[j * 4 + 2] +
                                           m_.aMatrix[i + 3 * 4] * cM.m_.aMatrix[j * 4 + 3];
            }

        *this = cT;
        return *this;
    }

	CMatrix operator * (CMatrix& cM2) const {
        CMatrix cT;

        for (int i = 0; i != 4; i++)
            for (int j = 0; j != 4; j++) {
                cT.m_.aMatrix[j * 4 + i] = m_.aMatrix[i + 0 * 4] * cM2.m_.aMatrix[j * 4 + 0] +
                                           m_.aMatrix[i + 1 * 4] * cM2.m_.aMatrix[j * 4 + 1] +
                                           m_.aMatrix[i + 2 * 4] * cM2.m_.aMatrix[j * 4 + 2] +
                                           m_.aMatrix[i + 3 * 4] * cM2.m_.aMatrix[j * 4 + 3];
            }

        return cT;
    }

    void Inverse();

    void Inverse( CMatrix& cSrc ) {
        *this = cSrc;
        Inverse();
    }

    void Transpose();

    /* adds translate to result */
    void MulVertices( CVector* pDestVertices, CVector* pSrcVertices, int iCount );

    CVector operator * ( CVector& cV ) {
        CVector cRes;
        cRes.fX = cV.fX * m_.sMatrix.stBaseX.fX + cV.fY * m_.sMatrix.stBaseY.fX + cV.fZ * m_.sMatrix.stBaseZ.fX + m_.sMatrix.stBaseW.fX;
        cRes.fY = cV.fX * m_.sMatrix.stBaseX.fY + cV.fY * m_.sMatrix.stBaseY.fY + cV.fZ * m_.sMatrix.stBaseZ.fY + m_.sMatrix.stBaseW.fY;
        cRes.fZ = cV.fX * m_.sMatrix.stBaseX.fZ + cV.fY * m_.sMatrix.stBaseY.fZ + cV.fZ * m_.sMatrix.stBaseZ.fZ + m_.sMatrix.stBaseW.fZ;
        return cRes;
    }

    /* doesnt add translate to result */
    void MulVectors( CVector* pDestVectors, CVector* pSrcVectors, int iCount );

    CVector operator << ( CVector& cV ) {
        CVector cRes;
        cRes.fX = cV.fX * m_.sMatrix.stBaseX.fX + cV.fY * m_.sMatrix.stBaseY.fX + cV.fZ * m_.sMatrix.stBaseZ.fX;
        cRes.fY = cV.fX * m_.sMatrix.stBaseX.fY + cV.fY * m_.sMatrix.stBaseY.fY + cV.fZ * m_.sMatrix.stBaseZ.fY;
        cRes.fZ = cV.fX * m_.sMatrix.stBaseX.fZ + cV.fY * m_.sMatrix.stBaseY.fZ + cV.fZ * m_.sMatrix.stBaseZ.fZ;
        return cRes;
    }
};

#endif	
