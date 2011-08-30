#ifndef __BASE_H
#define __BASE_H

#include <math.h>
//#include "m.h"

#define	MAX_MESH_NAME	  16

#define NOTEXTURE -1
#define BLEND_REPLACE     0
#define BLEND_MIX         1 
#define BLEND_SATURATE    2
#define BLEND_ADD         3


#define M4_00             0
#define M4_01             1
#define M4_02             2
#define M4_03             3
#define M4_10             4
#define M4_11             5
#define M4_12             6
#define M4_13             7
#define M4_20             8
#define M4_21             9
#define M4_22            10
#define M4_23            11
#define M4_30            12
#define M4_31            13
#define M4_32            14
#define M4_33            15

#define MATRIXSTACKDEPTH 16

#define ERR_OK       0
#define ERR_BOUNDS   1
#define ERR_BADPARM  2
#define ERR_NODATA   3
#define ERR_BADSTATE 4

#define OBJMAGIC_UNKN  'UNKN' /* unknown */
#define OBJMAGIC_MESH  'MESH' /* mesh */
#define OBJMAGIC_MPMS  'MPMS' /* mip mesh */
#define	OBJMAGIC_FMSH  'FMSH' /* normal mesh + ship info */

#define RENDERMETHOD_FULLBRIGHT 0
#define RENDERMETHOD_FLAT       1
#define RENDERMETHOD_SMOOTH     2
#define RENDERMETHOD_GOURAUD    3
#define RENDERMETHOD_BLEND      4 /* FULLBRIGHT with ALPHA channel */
#define RENDERMETHOD_MASK       0xFFFF
/* add env after rendering */
#define RENDERMETHOD_ENV        0x10000

/* effect update flags */
#define EFFF_POS      1
#define EFFF_NORMAL   2
#define EFFF_MATRIX   4
#define EFFF_WORLD    8 /* treat coords as already in world */


#ifdef __cplusplus
class VECTOR3F {
public:
 float fX;
 float fY;
 float fZ;
 
 VECTOR3F() {} /* default constructor does nothing */

 VECTOR3F(float fX, float fY, float fZ) {
  this->fX = fX;
  this->fY = fY;
  this->fZ = fZ;
 }
 VECTOR3F(const VECTOR3F &stV) {
  this->fX = stV.fX;
  this->fY = stV.fY;
  this->fZ = stV.fZ;
 }
 VECTOR3F(const VECTOR3F *pV) {
  this->fX = pV->fX;
  this->fY = pV->fY;
  this->fZ = pV->fZ;
 }
 /* utility funcs */
 
 void Zero(void) {
  fX = 
  fY =
  fZ = 0.0f;
 }

 float Len(void) {
  return (float)sqrt(fX * fX + fY * fY + fZ * fZ);
 }

 float Len2(void) {
  return (fX * fX + fY * fY + fZ * fZ);
 }

 void Normalize(void) {
  //mNormalize_3F_3F(&fX, &fX);
     float d = sqrtf(fX * fX + fY * fY + fZ * fZ);
     fX = fX / d;
     fY = fY / d;
     fZ = fZ / d;
 }

 float 
 Distance2(const VECTOR3F &stV) {
  register float fDX, fDY, fDZ;
  fDX = fX - stV.fX; fDY = fY - stV.fY; fDZ = fZ - stV.fZ;
  return (fDX * fDX + fDY * fDY + fDZ * fDZ);
 }

 float 
 Distance2(const VECTOR3F *pV) {
  register float fDX, fDY, fDZ;
  fDX = fX - pV->fX; fDY = fY - pV->fY; fDZ = fZ - pV->fZ;
  return (fDX * fDX + fDY * fDY + fDZ * fDZ);
 }

 float 
 Distance(const VECTOR3F &stV) {
  float fDX, fDY, fDZ;
  fDX = fX - stV.fX; fDY = fY - stV.fY; fDZ = fZ - stV.fZ;
  return (float)sqrt(fDX * fDX + fDY * fDY + fDZ * fDZ);
 }

 float 
 Distance(const VECTOR3F *pV) {
  float fDX, fDY, fDZ;
  fDX = fX - pV->fX; fDY = fY - pV->fY; fDZ = fZ - pV->fZ;
  return (float)sqrt(fDX * fDX + fDY * fDY + fDZ * fDZ);
 }

 float 
 Dot(const VECTOR3F &stV) {
  return (fX * stV.fX
          + fY * stV.fY
          + fZ * stV.fZ);
 }
 
 float 
 Dot(const VECTOR3F *pV) {
  return (fX * pV->fX
          + fY * pV->fY
          + fZ * pV->fZ);
 }         

 void
 Vector(const VECTOR3F &stV1, 
        const VECTOR3F &stV2) {
  fX = stV1.fY * stV2.fZ
     - stV1.fZ * stV2.fY;
  fY = stV1.fZ * stV2.fX
     - stV1.fX * stV2.fZ;
  fZ = stV1.fX * stV2.fY
     - stV1.fY * stV2.fX;
 }

 void
 Vector(const VECTOR3F *pV1, 
        const VECTOR3F *pV2) {
  fX = pV1->fY * pV2->fZ
     - pV1->fZ * pV2->fY;
  fY = pV1->fZ * pV2->fX
     - pV1->fX * pV2->fZ;
  fZ = pV1->fX * pV2->fY
     - pV1->fY * pV2->fX;
 }

        VECTOR3F Vector( const VECTOR3F& cV1 ) {

          return VECTOR3F( fY*cV1.fZ - fZ*cV1.fY, 
                           fZ*cV1.fX - fX*cV1.fZ,
                           fX*cV1.fY - fY*cV1.fX );
        }

 void Floor() {
  fX = (float)floor(fX);
  fY = (float)floor(fY);
  fZ = (float)floor(fZ);
 }

        bool EqualEpsilon( const VECTOR3F& stV, float fEpsilon ) {
          if ( fabs(stV.fX - fX) < fEpsilon && 
               fabs(stV.fY - fY) < fEpsilon && 
               fabs(stV.fZ - fZ) < fEpsilon ) return true;
          else
            return false;
        }

 /* operators */
 VECTOR3F& operator += (const VECTOR3F &stV) {
  fX += stV.fX;
  fY += stV.fY;
  fZ += stV.fZ;
  return *this;
 };

 VECTOR3F& operator -= (const VECTOR3F &stV) {
  fX -= stV.fX;
  fY -= stV.fY;
  fZ -= stV.fZ;
  return *this;
 };

 VECTOR3F& operator *= (const VECTOR3F &stV) {
  fX *= stV.fX;
  fY *= stV.fY;
  fZ *= stV.fZ;
  return *this;
 };

  VECTOR3F& operator *= (const float f) {
  fX *= f;
  fY *= f;
  fZ *= f;
  return *this;
 };

  VECTOR3F& operator /= (const VECTOR3F &stV) {
  fX /= stV.fX;
  fY /= stV.fY;
  fZ /= stV.fZ;
  return *this;
 };

  VECTOR3F& operator /= (const float f) {
  float d;
  d = 1.0f / f;
  fX *= d;
  fY *= d;
  fZ *= d;
  return *this;
 };

        bool operator == ( const VECTOR3F& stV ) {
          if ( stV.fX == fX && stV.fY == fY && stV.fZ == fZ ) return true;
          else return false;
        }

        bool operator != ( const VECTOR3F& stV ) {
          if ( stV.fX != fX || stV.fY != fY || stV.fZ != fZ ) return true;
          else return false;
        }

};

/* operators defined outside the class */
inline 
VECTOR3F operator - (const VECTOR3F &stV1, const VECTOR3F stV2)
{
 return VECTOR3F(stV1.fX - stV2.fX, 
                 stV1.fY - stV2.fY, 
                 stV1.fZ - stV2.fZ);
}
inline 
VECTOR3F operator + (const VECTOR3F &stV1, const VECTOR3F stV2)
{
 return VECTOR3F(stV1.fX + stV2.fX, 
                 stV1.fY + stV2.fY, 
                 stV1.fZ + stV2.fZ);
}
inline 
VECTOR3F operator - (const VECTOR3F &stV1)
{
 return VECTOR3F(-stV1.fX, 
                 -stV1.fY, 
                 -stV1.fZ);
}

inline 
VECTOR3F operator * (const VECTOR3F &stV1, const VECTOR3F stV2)
{
 return VECTOR3F(stV1.fX * stV2.fX, 
                 stV1.fY * stV2.fY, 
                 stV1.fZ * stV2.fZ);
}

inline 
VECTOR3F operator * (const VECTOR3F &stV1, const float f)
{
 return VECTOR3F(stV1.fX * f, 
                 stV1.fY * f, 
                 stV1.fZ * f);
}

inline 
VECTOR3F operator * (const float f,const  VECTOR3F &stV1)
{
 return VECTOR3F(stV1.fX * f, 
                 stV1.fY * f, 
                 stV1.fZ * f);
}
 
#else
typedef struct VECTOR3Ftag
{
 float fX;
 float fY;
 float fZ;
} VECTOR3F;

#define DOT3F(v1, v2) (v1.fX*v2.fX + v1.fY*v2.fY + v1.fZ*v2.fZ)
#define SUB3F(dest, v1, v2) (dest.fX = v1.fX - v2.fX,\
                             dest.fY = v1.fY - v2.fY,\
                             dest.fZ = v1.fZ - v2.fZ)
#define ADD3F(dest, v1, v2) (dest.fX = v1.fX + v2.fX,\
                             dest.fY = v1.fY + v2.fY,\
                             dest.fZ = v1.fZ + v2.fZ)
#define CROSS3F(dest, X, Y) ((dest).fX = (X).fY*(Y).fZ - (X).fZ*(Y).fY,\
			     (dest).fY = (X).fZ*(Y).fX - (X).fX*(Y).fZ,\
			     (dest).fZ = (X).fX*(Y).fY - (X).fY*(Y).fX)


#define DOT3Fp(v1, v2) ((v1)->fX*(v2)->fX + (v1)->fY*(v2)->fY + (v1)->fZ*(v2)->fZ)
#define SUB3Fp(dest, v1, v2) ((dest)->fX = (v1)->fX - (v2)->fX,\
                             (dest)->fY = (v1)->fY - (v2)->fY,\
                             (dest)->fZ = (v1)->fZ - (v2)->fZ)
#define ADD3Fp(dest, v1, v2) ((dest)->fX = (v1)->fX + (v2)->fX,\
                             (dest)->fY = (v1)->fY + (v2)->fY,\
                             (dest)->fZ = (v1)->fZ + (v2)->fZ)
#define CROSS3Fp(V,X,Y) ((V)->fX = (X)->fY*(Y)->fZ - (X)->fZ*(Y)->fY,\
			 (V)->fY = (X)->fZ*(Y)->fX - (X)->fX*(Y)->fZ,\
			 (V)->fZ = (X)->fX*(Y)->fY - (X)->fY*(Y)->fX)


#endif


typedef struct VECTOR4Ftag
{
    float	fX;
    float	fY;
    float	fZ;
    float	fW;
} VECTOR4F;

#define VERTEX3F VECTOR3F 

typedef struct TEXCOORDtag
{
    float	fU;
    float	fV;
} TEXCOORD;

#define RSFTYPE_NONE      0
#define RSFTYPE_FRUSTUM   1
#define RSFTYPE_ORTHO     2

typedef struct RSFRUSTUMtag
{
    int	nType;
    float	fLeft;
    float	fRight;
    float	fBottom;
    float	fTop;
    float	fNear;
    float	fFar;
} RSFRUSTUM;


typedef struct COLOR3Ftag
{
    float	fR;
    float	fG;
    float	fB;
} COLOR3F;

typedef struct COLOR4Ftag 
{
    float	fR;
    float	fG;
    float	fB;
    float	fA;

    #ifdef __cplusplus
    COLOR4Ftag() {};
    COLOR4Ftag(float R, float G, float B, float A) {
      fR = R; fG = G; fB = B; fA = A;
    };

    COLOR4Ftag& operator *= ( COLOR4Ftag& col ) {
      fR *= col.fR;
      fG *= col.fG;
      fB *= col.fB;
      fA *= col.fA;
      return *this;
    }

    COLOR4Ftag& operator += ( COLOR4Ftag& col ) {
      fR += col.fR;
      fG += col.fG;
      fB += col.fB;
      fA += col.fA;
      return *this;
    }

    COLOR4Ftag operator + ( COLOR4Ftag& col ) {
      return COLOR4Ftag( fR + col.fR, fG + col.fG, fB + col.fB, fA + col.fA );
    }

    COLOR4Ftag operator * ( COLOR4Ftag& col ) {
      return COLOR4Ftag( fR*col.fR, fG*col.fG, fB*col.fB, fA*col.fA );
    }
    #endif 

} COLOR4F;

#define FACEFLAG_BLEND 0xF

typedef struct TCFACEtag {
 int nTextureName;
 unsigned int nFlags;
 COLOR4F stColor;
 VERTEX3F *aVertices[3];
 TEXCOORD aTexCoords[3];
} TCFACE;

#ifdef __cplusplus
class EXTENTS {
public:
 float fXMin;
 float fXMax;
 float fYMin;
 float fYMax;
 float fZMin;
 float fZMax;

 EXTENTS() {
 }
 
 EXTENTS(float fXMin, float fXMax,
         float fYMin, float fYMax,
         float fZMin, float fZMax) {
  this->fXMin = fXMin;
  this->fXMax = fXMax;
  this->fYMin = fYMin;
  this->fYMax = fYMax;
  this->fZMin = fZMin;
  this->fZMax = fZMax;
 }

 EXTENTS& operator += (const VECTOR3F &stV) {
  fXMin += stV.fX;
  fXMax += stV.fX;
  fYMin += stV.fY;
  fYMax += stV.fY;
  fZMin += stV.fZ;
  fZMax += stV.fZ;
  return *this;
}

 EXTENTS& operator -= (const VECTOR3F &stV) {
  fXMin -= stV.fX;
  fXMax -= stV.fX;
  fYMin -= stV.fY;
  fYMax -= stV.fY;
  fZMin -= stV.fZ;
  fZMax -= stV.fZ;
  return *this;
 }
};

inline 
EXTENTS operator - (const EXTENTS &stE, const VECTOR3F stV)
{
 return EXTENTS(stE.fXMin - stV.fX, stE.fXMax - stV.fX, 
                stE.fYMin - stV.fY, stE.fYMax - stV.fY, 
                stE.fZMin - stV.fZ, stE.fZMax - stV.fZ);
}

inline 
EXTENTS operator + (const EXTENTS &stE, const VECTOR3F stV)
{
 return EXTENTS(stE.fXMin + stV.fX, stE.fXMax + stV.fX, 
                stE.fYMin + stV.fY, stE.fYMax + stV.fY, 
                stE.fZMin + stV.fZ, stE.fZMax + stV.fZ);
}

#else
typedef struct EXTENTStag
{
 float fXMin;
 float fXMax;
 float fYMin;
 float fYMax;
 float fZMin;
 float fZMax;
} EXTENTS;
#endif

#define BBOX EXTENTS

#endif /* __BASE_H */
