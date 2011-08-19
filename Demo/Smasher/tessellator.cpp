/**
 * programming by KZ
 * Copyright (C) by Konrad Zagorowicz
 */

#include "stdafx.h"
#include "tessellator.hpp"

//***********************************************************************************
static inline void glFace(CNodeData& cV1, CNodeData& cV2, CNodeData& cV3, float fAlpha, float fUShift, float fVShift) {
        
        glTexCoord2f(cV1.m_cTexel.fU + fUShift, cV1.m_cTexel.fV + fVShift);
        glColor4f(cV1.m_cColor.fR, cV1.m_cColor.fG, cV1.m_cColor.fB, cV1.m_cColor.fA*fAlpha);
        glVertex3f(cV1.m_cPosition.fX, cV1.m_cPosition.fY, cV1.m_cPosition.fZ);
        glTexCoord2f(cV2.m_cTexel.fU + fUShift, cV2.m_cTexel.fV + fVShift);
        glColor4f(cV2.m_cColor.fR, cV2.m_cColor.fG, cV2.m_cColor.fB, cV2.m_cColor.fA*fAlpha);
        glVertex3f(cV2.m_cPosition.fX, cV2.m_cPosition.fY, cV2.m_cPosition.fZ);
        glTexCoord2f(cV3.m_cTexel.fU + fUShift, cV3.m_cTexel.fV + fVShift);
        glColor4f(cV3.m_cColor.fR, cV3.m_cColor.fG, cV3.m_cColor.fB, cV3.m_cColor.fA*fAlpha);
        glVertex3f(cV3.m_cPosition.fX, cV3.m_cPosition.fY, cV3.m_cPosition.fZ);
}
//***********************************************************************************
static inline void glEnv(CNodeData& cV1, CNodeData& cV2, CNodeData& cV3, float fAlpha) {
        

        glTexCoord2f(cV1.m_cNormal.fX, cV1.m_cNormal.fY);
        glColor4f(cV1.m_cColor.fR, cV1.m_cColor.fG, cV1.m_cColor.fB, cV1.m_cColor.fA*fAlpha);
        glVertex3f(cV1.m_cPosition.fX, cV1.m_cPosition.fY, cV1.m_cPosition.fZ);
        glTexCoord2f(cV2.m_cNormal.fX, cV2.m_cNormal.fY);
        glColor4f(cV2.m_cColor.fR, cV2.m_cColor.fG, cV2.m_cColor.fB, cV2.m_cColor.fA*fAlpha);
        glVertex3f(cV2.m_cPosition.fX, cV2.m_cPosition.fY, cV2.m_cPosition.fZ);
        glTexCoord2f(cV3.m_cNormal.fX, cV3.m_cNormal.fY);
        glColor4f(cV3.m_cColor.fR, cV3.m_cColor.fG, cV3.m_cColor.fB, cV3.m_cColor.fA*fAlpha);
        glVertex3f(cV3.m_cPosition.fX, cV3.m_cPosition.fY, cV3.m_cPosition.fZ);
}
//***********************************************************************************
static void glLineFace(CNodeData& cV1, CNodeData& cV2, CNodeData& cV3) {

        glVertex3f(cV1.m_cPosition.fX, cV1.m_cPosition.fY, cV1.m_cPosition.fZ);
        glVertex3f(cV2.m_cPosition.fX, cV2.m_cPosition.fY, cV2.m_cPosition.fZ);

        glVertex3f(cV2.m_cPosition.fX, cV2.m_cPosition.fY, cV2.m_cPosition.fZ);
        glVertex3f(cV3.m_cPosition.fX, cV3.m_cPosition.fY, cV3.m_cPosition.fZ);

        glVertex3f(cV3.m_cPosition.fX, cV3.m_cPosition.fY, cV3.m_cPosition.fZ);
        glVertex3f(cV1.m_cPosition.fX, cV1.m_cPosition.fY, cV1.m_cPosition.fZ);
}
//***********************************************************************************
static float calc_cathmull_seg_len(CVector& stA, CVector& stB, CVector& stC, CVector& stD) {

        float	fRes;
        float	a, b, c, e, f, g, i, j, k;

        /*
         * lets start ritual dance around fire place
         */

        a = 0.5f*(3*stB.fX + stD.fX - stA.fX -3*stC.fX);
        b = stA.fX + 2*stC.fX - 0.5f*(5*stB.fX + stD.fX);
        c = 0.5f*(stC.fX - stA.fX);

        e = 0.5f*(3*stB.fY + stD.fY - stA.fY -3*stC.fY);
        f = stA.fY + 2*stC.fY - 0.5f*(5*stB.fY + stD.fY);
        g = 0.5f*(stC.fY - stA.fY);

        i = 0.5f*(3*stB.fZ + stD.fZ - stA.fZ -3*stC.fZ);
        j = stA.fZ + 2*stC.fZ - 0.5f*(5*stB.fZ + stD.fZ);
        k = 0.5f*(stC.fZ - stA.fZ);

        /*
         * lets start a black magic
         */

        fRes = (float)sqrt(
                9*a*a + 6*a*(2*b + c) + 4*b*b + 4*b*c+c*c + 9*e*e + 6*e*(2*f + g)
                + 4*f*f + 4*f*g + g*g + (3*i + 2*j + k)*(3*i + 2*j + k)) + 
                (float)sqrt(c*c + g*g + k*k);

        /*
         * uff.. now we have computed spline seg len
         */

        return fRes;
}
//***********************************************************************************
static inline void calc_cathmull(CVector& stResult, float fA, float fB, float fC, float fD, float fT) {

        register float   fa, fb, fc;

        fa = 0.5f*(3*fB + fD - fA -3*fC);
        fb = fA + 2*fC - 0.5f*(5*fB + fD);
        fc = 0.5f*(fC - fA);        
    
        stResult.fX = fT*fT*fT*fa + fT*fT*fb + fT*fc + fB;
        stResult.fY = 3*fT*fT*fa + 2*fT*fb + fc;
        stResult.fZ = 6*fT*fa + 2*fb;
}
//***********************************************************************************
void CSplinedObject::AddTable(CObjectNode* pTable, int nResU, int nResV) {

        CObjectNode* pRoot;
        CObjectNode* pLink;
        int nI;

        m_pRoot = pTable;
        m_nResU = nResU;
        m_nResV = nResV;

	pRoot = pLink = m_pRoot;
	pTable++;

	for (nI = 0; nI != nResU - 1; nI++)
	{
	  pLink->LinkRight(pTable);
	  pLink = pLink->GetRight();
	  pTable++;
	}

	for (int nQ = 0; nQ != nResV - 1; nQ++)
	{
	  pRoot->LinkDown(pTable);
	  pLink = pRoot->GetDown();
	  pTable++;

	  for (nI = 0; nI != nResU - 1; nI++)
	  {
	    pLink->LinkRight(pTable);
	    pLink = pLink->GetRight();
	    pTable++;
	  }

	  pRoot = pRoot->GetDown();
	}
}
//***********************************************************************************
void CSplinedObject::CloseTableU() {

        CObjectNode* pNode;
        CObjectNode* pEdge;

        pEdge = m_pRoot;

        while (pEdge) {
          for (pNode = pEdge; pNode->m_pRight; pNode = pNode->m_pRight) {}
          pNode->m_pRight = pEdge;
          pEdge->m_pLeft = pNode; 
          pNode->m_nWarapUV = 1;         
          pEdge = pEdge->GetDown();
        }
}
//***********************************************************************************
void CSplinedObject::Render(CMatrix& cCameraMatrix, CMatrix& cProjection) {

	CObjectNode* pNode;
	CObjectNode* pEdge;

	if (!m_pRoot) return;


        glMatrixMode(GL_MODELVIEW);
        glMultMatrixf(cCameraMatrix.aMatrix);
        glMultMatrixf(m_cMatrix.aMatrix);

        if (m_bGenerateNormals)
        {
          CMatrix cModelView;
          glGetFloatv(GL_MODELVIEW_MATRIX, (float*)&cModelView.aMatrix);
          GenerateNormals(cModelView);
        }

        glEnable(GL_TEXTURE_2D);

        pEdge = m_pRoot;

        do {

          pNode = pEdge;
          do
          {
            pNode->RenderPatch(m_nSeedU, m_nSeedV, m_aMultiTex, m_nMultiTex);
            pNode = pNode->m_pRight;
          } while (pNode->m_pRight && pNode != pEdge);

          pEdge = pEdge->m_pDown;

        } while (pEdge->m_pDown);
}
//***********************************************************************************


//***********************************************************************************
void CObjectNode::RenderPatch(int nSeedU, int nSeedV, CMultiTexData* pTexData, int nTexData) {

	CObjectNode* pN1;
	CObjectNode* pN2;
	CObjectNode* pN3;
	CObjectNode* pN4;

        CNodeData aEdges[4][64];

        CNodeData aHLine1[64];
        CNodeData aHLine2[64];

        CNodeData* pHLine1 = aHLine1;
        CNodeData* pHLine2 = aHLine2;
        CNodeData* pTmp;

	float fU, fV;
        int nV, nU, nTex;

	CNodeData cE1, cE2, cE3, cE4, cE;

	/* calculate edge 1 */

	pN2 = pN1 = GetValidLeft();
	pN1 = pN1->GetValidUp();
	pN3 = pN2->GetValidDown();
	pN4 = pN3->GetValidDown();

        aEdges[0][0] = pN2->m_cNodeData;
        for (nV = 1; nV != nSeedV - 1; nV++) {
          fV = (float)nV/(float)(nSeedV - 1); SInterpolate(aEdges[0][nV], pN1, pN2, pN3, pN4, fV);
        }
        aEdges[0][nSeedV - 1] = pN3->m_cNodeData;

	/* calculate edge 2 */

	pN1 = GetValidUp();
	pN2 = this;
	pN3 = GetValidDown();
	pN4 = pN3->GetValidDown();

        aEdges[1][0] = pN2->m_cNodeData;
        for (nV = 1; nV != nSeedV - 1; nV++) {
          fV = (float)nV/(float)(nSeedV - 1); SInterpolate(aEdges[1][nV], pN1, pN2, pN3, pN4, fV);
        }
        aEdges[1][nSeedV - 1] = pN3->m_cNodeData;

	/* calculate edge 3 */

	pN2 = pN1 = GetValidRight();
	pN1 = pN1->GetValidUp();
	pN3 = pN2->GetValidDown();
	pN4 = pN3->GetValidDown();

        aEdges[2][0] = pN2->m_cNodeData;
        for (nV = 1; nV != nSeedV - 1; nV++) {
          fV = (float)nV/(float)(nSeedV - 1); SInterpolate(aEdges[2][nV], pN1, pN2, pN3, pN4, fV);
        }
        aEdges[2][nSeedV - 1] = pN3->m_cNodeData;


	/* calculate edge 4 */

	pN2 = pN2->GetValidRight();
	pN1 = pN2->GetValidUp();
	pN3 = pN2->GetValidDown();
	pN4 = pN3->GetValidDown();

        aEdges[3][0] = pN2->m_cNodeData;
        for (nV = 1; nV != nSeedV - 1; nV++) {
          fV = (float)nV/(float)(nSeedV - 1); SInterpolate(aEdges[3][nV], pN1, pN2, pN3, pN4, fV);
        }
        aEdges[3][nSeedV - 1] = pN3->m_cNodeData;

        /* make faces */

        int nWrap;

        if (m_nWarapUV) nWrap = 1;
        else if (GetValidLeft()->m_nWarapUV) nWrap = -1;
        else nWrap = 0;


/*
        if (nWrap == 0) pHLine1[0] = aEdges[1][0];
        else if (nWrap > 0)  {
          pHLine1[0] = aEdges[1][0];
          pHLine1[0].m_cTexel.fU += 1.0f;
        }
        else {
          pHLine1[0] = aEdges[1][0];
        }
*/
        for (nU = 0; nU != nSeedU ; nU++) {
          fU = (float)nU/(float)(nSeedU - 1);
          SInterpolate(pHLine1[nU], aEdges[0][0], aEdges[1][0], aEdges[2][0], aEdges[3][0], fU, nWrap);
        }
        //pHLine1[nSeedU - 1] = aEdges[2][0];

        for (nV = 1; nV != nSeedV; nV++) {

          //pHLine2[0] = aEdges[1][nV];
          for (nU = 0; nU != nSeedU; nU++) {
            fU = (float)nU/(float)(nSeedU - 1);
            SInterpolate(pHLine2[nU], aEdges[0][nV], aEdges[1][nV], aEdges[2][nV], aEdges[3][nV], fU, nWrap);
          }
          //pHLine2[0] = aEdges[2][nV];


          /* oki.. we've got here a strip, so render it */


          for (nTex = 0; nTex != nTexData; nTex++)
          {
            if (pTexData[nTex].m_nGLTexName) {

              glBindTexture(GL_TEXTURE_2D, *pTexData[nTex].m_nGLTexName);
              glBegin(GL_TRIANGLES);
              
              if (pTexData[nTex].m_nMaterial&1)
              {
                for (nU = 0; nU != nSeedU - 1; nU++) {
                  glFace(pHLine1[nU], pHLine1[nU + 1], pHLine2[nU], pTexData[nTex].m_fAlpha, pTexData[nTex].m_fUShift, pTexData[nTex].m_fVShift);
                  glFace(pHLine1[nU + 1], pHLine2[nU + 1], pHLine2[nU], pTexData[nTex].m_fAlpha, pTexData[nTex].m_fUShift, pTexData[nTex].m_fVShift);
                }
              } else
              if (pTexData[nTex].m_nMaterial&2)
              {
                for (nU = 0; nU != nSeedU - 1; nU++) {
                  glEnv(pHLine1[nU], pHLine1[nU + 1], pHLine2[nU], pTexData[nTex].m_fAlpha);
                  glEnv(pHLine1[nU + 1], pHLine2[nU + 1], pHLine2[nU], pTexData[nTex].m_fAlpha);
                }
              }

              glEnd();
            }
          }

          
          pTmp = pHLine1;
          pHLine1 = pHLine2;
          pHLine2 = pTmp;
        }
}
//***********************************************************************************
void CSplinedObject::GenerateNormals(CMatrix& cModelView) {

        if (!m_bGenerateNormals) return;

        CVector cRight, cDown, cRightDown;
        int u, v, i;
  
        for (v = 0; v != m_nResV; v++)
        {
          for (u = 0; u != m_nResU; u++)
          {
            i = u + v*m_nResU;
            
            cRight = m_pRoot[i].GetValidRight()->m_cNodeData.m_cPosition - m_pRoot[i].m_cNodeData.m_cPosition;
            cDown = m_pRoot[i].GetValidDown()->m_cNodeData.m_cPosition - m_pRoot[i].m_cNodeData.m_cPosition;
            cRightDown = m_pRoot[i].GetValidRight()->GetValidDown()->m_cNodeData.m_cPosition - m_pRoot[i].m_cNodeData.m_cPosition;

            m_pRoot[i].cNormals[1].Cross(cRightDown, cRight);
            m_pRoot[i].cNormals[0].Cross(cRightDown, cDown);

            m_pRoot[i].cNormals[0].fY = -m_pRoot[i].cNormals[0].fY;
            m_pRoot[i].cNormals[0].fX = -m_pRoot[i].cNormals[0].fX;

            m_pRoot[i].cNormals[1].fY = -m_pRoot[i].cNormals[1].fY;
            m_pRoot[i].cNormals[1].fX = -m_pRoot[i].cNormals[1].fX;

          }
        }

        for (v = 0; v != m_nResV; v++)
        {
          for (u = 0; u != m_nResU; u++)
          {
            CVector& cNormal = m_pRoot[i].m_cNodeData.m_cNormal;
            i = u + v*m_nResU;

            cNormal = CVector(0, 0, 0);

            cNormal += m_pRoot[i].cNormals[0];
            cNormal += m_pRoot[i].cNormals[1];
            cNormal += m_pRoot[i].GetValidUp()->cNormals[0];
            cNormal += m_pRoot[i].GetValidDown()->cNormals[1];
            cNormal += m_pRoot[i].GetValidLeft()->GetValidUp()->cNormals[0];
            cNormal += m_pRoot[i].GetValidLeft()->GetValidUp()->cNormals[1];

            cModelView.MulVectors( &cNormal, &cNormal, 1 );
            cNormal.Normalize();

	    cNormal.fX = cNormal.fX*.5f + .5f;
	    cNormal.fY = cNormal.fY*.5f + .5f;
          }
        }
}
//***********************************************************************************

