// programing by Yoghurt
// copyright (C) 1999 by Konrad Zagorowicz


#if !defined(CVector_hpp)
#define CVector_hpp

#include  <math.h>

//************************************************************************************
class CVector
{
public:
    float fX, fY, fZ;

    CVector() {};

    CVector(float ffX, float ffY, float ffZ)
    {
        fX = ffX;
        fY = ffY;
        fZ = ffZ;
    }

    CVector( float fAll ) {
        fX = fY = fZ = fAll;
    }

    void Normalize()
    {
        register double dLen = sqrt(1.0/(fX*fX + fY*fY + fZ*fZ));

        fX = (float)(fX*dLen);
        fY = (float)(fY*dLen);
        fZ = (float)(fZ*dLen);
    }

    void Add(CVector& cV1, CVector& cV2)
    {
        fX = cV1.fX + cV2.fX;
        fY = cV1.fY + cV2.fY;
        fZ = cV1.fZ + cV2.fZ;
    }

    void Sub(CVector& cV1, CVector& cV2)
    {
        fX = cV1.fX - cV2.fX;
        fY = cV1.fY - cV2.fY;
        fZ = cV1.fZ - cV2.fZ;
    }

    float Dot(CVector& cV) const
    {
        return fX*cV.fX + fY*cV.fY + fZ*cV.fZ;
    }

    void  Cross(CVector& cV1, CVector& cV2)
    {
        fX = cV1.fY*cV2.fZ + cV1.fZ*cV2.fY;
        fY = cV1.fZ*cV2.fX + cV1.fX*cV2.fZ;
        fZ = cV1.fX*cV2.fY + cV1.fY*cV2.fX;
    }

    CVector Cross( CVector& cV1 ) {
        return CVector( fY*cV1.fZ + fZ*cV1.fY, fZ*cV1.fX + fX*cV1.fZ, fX*cV1.fY + fY*cV1.fX );
    }

    /* min - max */
    void Min( CVector& cV1 )
    {
        if ( fX > cV1.fX )
            fX = cV1.fX;
        if ( fY > cV1.fY )
            fY = cV1.fY;
        if ( fZ > cV1.fZ )
            fZ = cV1.fZ;
    }

    void Max( CVector& cV1 )
    {
        if ( fX < cV1.fX )
            fX = cV1.fX;
        if ( fY < cV1.fY )
            fY = cV1.fY;
        if ( fZ < cV1.fZ )
            fZ = cV1.fZ;
    }

    CVector& operator += (CVector& cV)
    {
        fX += cV.fX;
        fY += cV.fY;
        fZ += cV.fZ;
        return *this;
    }

    CVector& operator -= (CVector& cV)
    {
        fX -= cV.fX;
        fY -= cV.fY;
        fZ -= cV.fZ;
        return *this;
    }

    CVector& operator *= (CVector& cV)
    {
        fX *= cV.fX;
        fY *= cV.fY;
        fZ *= cV.fZ;
        return *this;
    }

    CVector& operator *= (float fValue)
    {
        fX *= fValue;
        fY *= fValue;
        fZ *= fValue;
        return *this;
    }

    CVector operator + (const CVector& cV1) const
    {
        return CVector(cV1.fX + fX, cV1.fY + fY, cV1.fZ + fZ);
    }

    CVector operator - (const CVector& cV2) const
    {
        return CVector(fX - cV2.fX, fY - cV2.fY, fZ - cV2.fZ);
    }

    CVector operator * (const CVector& cV2) const
    {
        return CVector(fX*cV2.fX, fY*cV2.fY, fZ*cV2.fZ);
    }

    friend CVector operator * (const CVector& cV1, float fVal)
    {
        return CVector(cV1.fX*fVal, cV1.fY*fVal, cV1.fZ*fVal);
    }

    float operator | (const CVector& cV2) const
    {
        return (fX*cV2.fX + fY*cV2.fY + fZ*cV2.fZ);
    }

    CVector operator ^ (const CVector& cV2) const
    {
        return CVector(fY*cV2.fZ + fZ*cV2.fY, fZ*cV2.fX + fX*cV2.fZ, fX*cV2.fY + fY*cV2.fX);
    }

    CVector operator - ()
    {
        return CVector(-fX, -fY, -fZ);
    }
};      

#endif
