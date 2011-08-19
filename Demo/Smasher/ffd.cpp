// programming by Yoghurt
// copyrights (C) 1999 by Konrad Zagorowicz
// free form deformations 

#include "stdafx.h"
#include "ffd.h"

//**************************************************************************************
CFFD::CFFD()
{
	m_pVectorTable = 0;
	m_nVectorStride = 0;
	m_pDeformTable = 0;
	m_nDeformStride = 0;
	m_nDeformResX = m_nDeformResY = m_nDeformResZ = 0;
}
//**************************************************************************************
CFFD::~CFFD()
{
}
//**************************************************************************************
void CFFD::set_vector_table(void* pTable, int nElems, int nStride)
{
	m_pVectorTable = (CVector*)pTable;
	m_nVectorStride = nStride;
	m_nElements = nElems;
}
//**************************************************************************************
void CFFD::set_deform(void* pDeform, int nResX, int nResY, int nResZ, int nStride)
{
	m_pDeformTable = (CVector*)pDeform;
	m_nDeformResX = nResX;
	m_nDeformResY = nResY;
	m_nDeformResZ = nResZ;
	m_nDeformStride = nStride;
}
//**************************************************************************************
void CFFD::calc_afine_deform(void* pDest, int nStride)
{
        float     fDelX, fDelY, fDelZ, fX, fY, fZ;
        int       nX, nY, nZ;
        CVector   cT, cI1, cI2, cI3, cI4, cI5, cI6;
        CVector*  pTab = m_pVectorTable;
        CVector*  pDeformed = (CVector*)pDest;
        CVector*  pD1;
        CVector*  pD2;

        calc_bbox();

        fDelX = 1.0f/((m_cBMax.fX - m_cBMin.fX)/(float)(m_nDeformResX - 1));
        fDelY = 1.0f/((m_cBMax.fY - m_cBMin.fY)/(float)(m_nDeformResY - 1));
        fDelZ = 1.0f/((m_cBMax.fZ - m_cBMin.fZ)/(float)(m_nDeformResZ - 1));

        for (int nI = 0; nI != m_nElements; nI++)
        {
          cT.fX = (pTab->fX - m_cBMin.fX)*fDelX;
          cT.fY = (pTab->fY - m_cBMin.fY)*fDelY;
          cT.fZ = (pTab->fZ - m_cBMin.fZ)*fDelZ;

          nX = (int)cT.fX;
          nY = (int)cT.fY;
          nZ = (int)cT.fZ;

          fX = cT.fX - (float)nX;
          fY = cT.fY - (float)nY;
          fZ = cT.fZ - (float)nZ;

          pD1 = get_deform_point(nX, nY, nZ);
          pD2 = get_deform_point(nX + 1, nY, nZ);
          afine_interpolate(pD2, pD1, fX, cI1);

          pD1 = get_deform_point(nX, nY + 1, nZ);
          pD2 = get_deform_point(nX + 1, nY + 1, nZ);
          afine_interpolate(pD2, pD1, fX, cI2);

          pD1 = get_deform_point(nX, nY, nZ + 1);
          pD2 = get_deform_point(nX + 1, nY, nZ + 1);
          afine_interpolate(pD2, pD1, fX, cI3);

          pD1 = get_deform_point(nX, nY + 1, nZ + 1);
          pD2 = get_deform_point(nX + 1, nY + 1, nZ + 1);
          afine_interpolate(pD2, pD1, fX, cI4);

          afine_interpolate(&cI2, &cI1, fY, cI5);
          afine_interpolate(&cI4, &cI3, fY, cI6);
          afine_interpolate(&cI6, &cI5, fZ, *pDeformed);

          pTab = (CVector*)((char*)pTab + m_nVectorStride);
          pDeformed = (CVector*)((char*)pDeformed + nStride);
        }
}
//**************************************************************************************
void CFFD::calc_spline_deform(void *pDest, int nStride)
{
        float     fDelX, fDelY, fDelZ, fX, fY, fZ;
        int       nX, nY, nZ, nI, nQ;
        CVector   cT;
        CVector*  pTab = m_pVectorTable;
        CVector*  pDeformed = (CVector*)pDest;

        CVector   aI1[4][4];
        CVector   aI2[4];

        calc_bbox();

        fDelX = 1.0f/((m_cBMax.fX - m_cBMin.fX)/(float)(m_nDeformResX - 1));
        fDelY = 1.0f/((m_cBMax.fY - m_cBMin.fY)/(float)(m_nDeformResY - 1));
        fDelZ = 1.0f/((m_cBMax.fZ - m_cBMin.fZ)/(float)(m_nDeformResZ - 1));

        for (int nS = 0; nS != m_nElements; nS++)
        {
          cT.fX = (pTab->fX - m_cBMin.fX)*fDelX;
          cT.fY = (pTab->fY - m_cBMin.fY)*fDelY;
          cT.fZ = (pTab->fZ - m_cBMin.fZ)*fDelZ;

          nX = (int)cT.fX;
          nY = (int)cT.fY;
          nZ = (int)cT.fZ;

          fX = cT.fX - (float)nX;
          fY = cT.fY - (float)nY;
          fZ = cT.fZ - (float)nZ;

          for (nQ = 0; nQ != 4; nQ++)
          {
            for (nI = 0; nI != 4; nI++)
            {
              spline_interpolate(*get_deform_point(nX - 1, nY - 1 + nI, nZ - 1 + nQ),
                                 *get_deform_point(nX    , nY - 1 + nI, nZ - 1 + nQ),
                                 *get_deform_point(nX + 1, nY - 1 + nI, nZ - 1 + nQ),
                                 *get_deform_point(nX + 2, nY - 1 + nI, nZ - 1 + nQ), fX, aI1[nI][nQ]);
            }
          }

          for (nI = 0; nI != 4; nI++)
            spline_interpolate(aI1[0][nI], aI1[1][nI], aI1[2][nI], aI1[3][nI], fY, aI2[nI]);

          spline_interpolate(aI2[0], aI2[1], aI2[2], aI2[3], fZ, *pDeformed);


          pTab = (CVector*)((char*)pTab + m_nVectorStride);
          pDeformed = (CVector*)((char*)pDeformed + nStride);
        }
}
//**************************************************************************************
void CFFD::calc_bbox()
{
        CVector*  pTab = m_pVectorTable;

        m_cBMin.fX = m_cBMin.fY = m_cBMin.fZ =  1e30f;
        m_cBMax.fX = m_cBMax.fY = m_cBMax.fZ = -1e30f;

        for (int nI = 0; nI != m_nElements; nI++)
        {
          if (pTab->fX < m_cBMin.fX) m_cBMin.fX = pTab->fX;
          if (pTab->fY < m_cBMin.fY) m_cBMin.fY = pTab->fY;
          if (pTab->fZ < m_cBMin.fZ) m_cBMin.fZ = pTab->fZ;
          if (pTab->fX > m_cBMax.fX) m_cBMax.fX = pTab->fX;
          if (pTab->fY > m_cBMax.fY) m_cBMax.fY = pTab->fY;
          if (pTab->fZ > m_cBMax.fZ) m_cBMax.fZ = pTab->fZ;
          pTab = (CVector*)((char*)pTab + m_nVectorStride);
        }

        m_cBMax.fX += 0.0001f;
        m_cBMax.fY += 0.0001f;
        m_cBMax.fZ += 0.0001f;

        m_cBMin.fX -= 0.0001f;
        m_cBMin.fY -= 0.0001f;
        m_cBMin.fZ -= 0.0001f;
}
//**************************************************************************************
