// programing by Yoghurt
// copyright (C) 1999 by Konrad Zagorowicz

#if !defined(_CMatrix_hpp_)
#define _CMatrix_hpp_

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

//************************************************************************************
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

        CBase operator = (CVector& cV) {
          fX = cV.fX;
          fY = cV.fY;
          fZ = cV.fZ;
          return *this;
        }

        float Dot( CVector& cV ) {
          return fX*cV.fX + fY*cV.fY + fZ*cV.fZ + fW;
        }

        float Dot( CBase& cV ) {
          return fX*cV.fX + fY*cV.fY + fZ*cV.fZ + fW*cV.fW;
        }
};
//************************************************************************************
class CMatrix
{
public:
        union {

          struct {
            CBase stBaseX;
            CBase stBaseY;
            CBase stBaseZ;
            CBase stBaseW;
          };

          float aMatrix[16];
        };

	void Identity() {

	  stBaseX = CBase(1, 0, 0, 0);
	  stBaseY = CBase(0, 1, 0, 0);
	  stBaseZ = CBase(0, 0, 1, 0);
	  stBaseW = CBase(0, 0, 0, 1);
	}

	CMatrix& operator *= (CMatrix& cM) {
	  CMatrix cT;
	  for (int i = 0; i != 4; i++)
	    for (int j = 0; j != 4; j++) {
	      cT.aMatrix[j*4 + i] = aMatrix[i + 0*4]*cM.aMatrix[j*4 + 0] +
				    aMatrix[i + 1*4]*cM.aMatrix[j*4 + 1] +
				    aMatrix[i + 2*4]*cM.aMatrix[j*4 + 2] +
				    aMatrix[i + 3*4]*cM.aMatrix[j*4 + 3];

	    }

	    *this = cT;
	    return *this;
	}

	CMatrix operator * (CMatrix& cM2) const {
	  CMatrix cT;
	
	  for (int i = 0; i != 4; i++)
	    for (int j = 0; j != 4; j++) {
	      cT.aMatrix[j*4 + i] = aMatrix[i + 0*4]*cM2.aMatrix[j*4 + 0] +
				    aMatrix[i + 1*4]*cM2.aMatrix[j*4 + 1] +
				    aMatrix[i + 2*4]*cM2.aMatrix[j*4 + 2] +
				    aMatrix[i + 3*4]*cM2.aMatrix[j*4 + 3];

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
          cRes.fX = cV.fX*stBaseX.fX + cV.fY*stBaseY.fX + cV.fZ*stBaseZ.fX + stBaseW.fX;
          cRes.fY = cV.fX*stBaseX.fY + cV.fY*stBaseY.fY + cV.fZ*stBaseZ.fY + stBaseW.fY;
          cRes.fZ = cV.fX*stBaseX.fZ + cV.fY*stBaseY.fZ + cV.fZ*stBaseZ.fZ + stBaseW.fZ;
          return cRes;
        };

        /* doesnt add translate to result */
        void MulVectors( CVector* pDestVectors, CVector* pSrcVectors, int iCount );

        CVector operator << ( CVector& cV ) {

          CVector cRes;
          cRes.fX = cV.fX*stBaseX.fX + cV.fY*stBaseY.fX + cV.fZ*stBaseZ.fX;
          cRes.fY = cV.fX*stBaseX.fY + cV.fY*stBaseY.fY + cV.fZ*stBaseZ.fY;
          cRes.fZ = cV.fX*stBaseX.fZ + cV.fY*stBaseY.fZ + cV.fZ*stBaseZ.fZ;
          return cRes;

        }
};
//************************************************************************************

#endif	