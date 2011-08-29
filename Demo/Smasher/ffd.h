// programming by Yoghurt
// copyrights (C) 1999 by Konrad Zagorowicz
// free form deformations class def

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include <GLES/gl.h>

#if !defined (ffd_h)
#define ffd_h

class CFFD
{
public:
    CFFD();
    virtual ~CFFD();


    /**
     * this method sets mesh data into class instance
     * pTable points to 3 floats
     */
    void set_vector_table(void* pTable, int nElems, int nStride);

    /**
     * defines deformation, pDeform points to 3 floats
     */
    void set_deform(void* pDeform, int nResX, int nResY, int nResZ, int nStride);

    /**
     * pDest points to 3 floats
     */
    void calc_afine_deform(void* pDest, int nStride);

    /**
     * pDest points to 3 floats
     */
    void calc_spline_deform(void* pDest, int nStride);

protected:
    CVector* m_pVectorTable;
    int m_nVectorStride;
    int m_nElements;

    CVector* m_pDeformTable;
    int m_nDeformResX, m_nDeformResY, m_nDeformResZ;
    int m_nDeformStride;

    CVector m_cBMin, m_cBMax;

    void calc_bbox();

    CVector* get_deform_point(int nX, int nY, int nZ)
    {
        char*   pRes = (char*)m_pDeformTable;
        if (nX < 0) nX = 0; else if (nX >= m_nDeformResX) nX = m_nDeformResX - 1;
        if (nY < 0) nY = 0; else if (nY >= m_nDeformResY) nY = m_nDeformResY - 1;
        if (nZ < 0) nZ = 0; else if (nZ >= m_nDeformResZ) nZ = m_nDeformResZ - 1;
        return (CVector*)&pRes[(nX + (nY + nZ * m_nDeformResY) * m_nDeformResX) * m_nDeformStride];
    }

    void afine_interpolate(CVector* pI2, CVector* pI1, float fT, CVector& cDest)
    {
        cDest.Sub(*pI2, *pI1);
        cDest *= fT;
        cDest += *pI1;
    }

    float calc_catmull(float fA, float fB, float fC, float fD, float fT)
    {
        register float   fa, fb, fc;

        fa = 0.5f*(3*fB + fD - fA -3*fC);
        fb = fA + 2*fC - 0.5f*(5*fB + fD);
        fc = 0.5f*(fC - fA);

        return (fT*fT*fT*fa + fT*fT*fb + fT*fc + fB);
    }

    void spline_interpolate(CVector& cI1, CVector& cI2, CVector& cI3, CVector& cI4, float fT, CVector& cDest)
    {
        cDest.fX = calc_catmull(cI1.fX, cI2.fX, cI3.fX, cI4.fX, fT);
        cDest.fY = calc_catmull(cI1.fY, cI2.fY, cI3.fY, cI4.fY, fT);
        cDest.fZ = calc_catmull(cI1.fZ, cI2.fZ, cI3.fZ, cI4.fZ, fT);
    }
};

#endif
