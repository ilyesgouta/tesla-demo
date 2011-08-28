/**
 * programming by KZ
 * Copyright (C) by Konrad Zagorowicz
 */

#ifdef WIN32
#include "stdafx.h"
#endif

#include "tessellator.hpp"

void CObjectNode::glFace(CNodeData& cV1, CNodeData& cV2, CNodeData& cV3, float fAlpha, float fUShift, float fVShift)
{
#ifdef GL_VERSION_ES_CM_1_1
    if (m_triCurrentIndex == m_triBufSize) {
        glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
        glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);
        glColorPointer(4, GL_FLOAT, 0, m_Color);

        glDrawArrays(GL_TRIANGLES, 0, m_triBufSize);

        m_triCurrentIndex = 0;
    } else {
        m_Vertex[m_triCurrentIndex].x = cV1.m_cPosition.fX;
        m_Vertex[m_triCurrentIndex].y = cV1.m_cPosition.fY;
        m_Vertex[m_triCurrentIndex].z = cV1.m_cPosition.fZ;

        m_Texture[m_triCurrentIndex].s0 = cV1.m_cTexel.fU + fUShift;
        m_Texture[m_triCurrentIndex].t0 = cV1.m_cTexel.fV + fVShift;

        m_Color[m_triCurrentIndex].r = cV1.m_cColor.fR;
        m_Color[m_triCurrentIndex].g = cV1.m_cColor.fG;
        m_Color[m_triCurrentIndex].b = cV1.m_cColor.fB;
        m_Color[m_triCurrentIndex].a = cV1.m_cColor.fA * fAlpha;

        m_triCurrentIndex++;

        m_Vertex[m_triCurrentIndex].x = cV2.m_cPosition.fX;
        m_Vertex[m_triCurrentIndex].y = cV2.m_cPosition.fY;
        m_Vertex[m_triCurrentIndex].z = cV2.m_cPosition.fZ;

        m_Texture[m_triCurrentIndex].s0 = cV2.m_cTexel.fU + fUShift;
        m_Texture[m_triCurrentIndex].t0 = cV2.m_cTexel.fV + fVShift;

        m_Color[m_triCurrentIndex].r = cV2.m_cColor.fR;
        m_Color[m_triCurrentIndex].g = cV2.m_cColor.fG;
        m_Color[m_triCurrentIndex].b = cV2.m_cColor.fB;
        m_Color[m_triCurrentIndex].a = cV2.m_cColor.fA * fAlpha;

        m_triCurrentIndex++;

        m_Vertex[m_triCurrentIndex].x = cV3.m_cPosition.fX;
        m_Vertex[m_triCurrentIndex].y = cV3.m_cPosition.fY;
        m_Vertex[m_triCurrentIndex].z = cV3.m_cPosition.fZ;

        m_Texture[m_triCurrentIndex].s0 = cV3.m_cTexel.fU + fUShift;
        m_Texture[m_triCurrentIndex].t0 = cV3.m_cTexel.fV + fVShift;

        m_Color[m_triCurrentIndex].r = cV3.m_cColor.fR;
        m_Color[m_triCurrentIndex].g = cV3.m_cColor.fG;
        m_Color[m_triCurrentIndex].b = cV3.m_cColor.fB;
        m_Color[m_triCurrentIndex].a = cV3.m_cColor.fA * fAlpha;

        m_triCurrentIndex++;
    }
#else
    glTexCoord2f(cV1.m_cTexel.fU + fUShift, cV1.m_cTexel.fV + fVShift);
    glColor4f(cV1.m_cColor.fR, cV1.m_cColor.fG, cV1.m_cColor.fB, cV1.m_cColor.fA*fAlpha);
    glVertex3f(cV1.m_cPosition.fX, cV1.m_cPosition.fY, cV1.m_cPosition.fZ);

    glTexCoord2f(cV2.m_cTexel.fU + fUShift, cV2.m_cTexel.fV + fVShift);
    glColor4f(cV2.m_cColor.fR, cV2.m_cColor.fG, cV2.m_cColor.fB, cV2.m_cColor.fA*fAlpha);
    glVertex3f(cV2.m_cPosition.fX, cV2.m_cPosition.fY, cV2.m_cPosition.fZ);

    glTexCoord2f(cV3.m_cTexel.fU + fUShift, cV3.m_cTexel.fV + fVShift);
    glColor4f(cV3.m_cColor.fR, cV3.m_cColor.fG, cV3.m_cColor.fB, cV3.m_cColor.fA*fAlpha);
    glVertex3f(cV3.m_cPosition.fX, cV3.m_cPosition.fY, cV3.m_cPosition.fZ);
#endif
}

void CObjectNode::glEnv(CNodeData& cV1, CNodeData& cV2, CNodeData& cV3, float fAlpha)
{
#ifdef GL_VERSION_ES_CM_1_1
    if (m_triEnvCurrentIndex == m_triEnvBufSize) {
        glVertexPointer(3, GL_FLOAT, 0, m_EnvVertex);
        glTexCoordPointer(2, GL_FLOAT, 0, m_EnvTexture);
        glColorPointer(4, GL_FLOAT, 0, m_EnvColor);

        glDrawArrays(GL_TRIANGLES, 0, m_triEnvBufSize);

        m_triEnvCurrentIndex = 0;
    } else {
        m_EnvVertex[m_triEnvCurrentIndex].x = cV1.m_cPosition.fX;
        m_EnvVertex[m_triEnvCurrentIndex].y = cV1.m_cPosition.fY;
        m_EnvVertex[m_triEnvCurrentIndex].z = cV1.m_cPosition.fZ;

        m_EnvTexture[m_triEnvCurrentIndex].s0 = cV1.m_cNormal.fX;
        m_EnvTexture[m_triEnvCurrentIndex].t0 = cV1.m_cNormal.fY;

        m_EnvColor[m_triEnvCurrentIndex].r = cV1.m_cColor.fR;
        m_EnvColor[m_triEnvCurrentIndex].g = cV1.m_cColor.fG;
        m_EnvColor[m_triEnvCurrentIndex].b = cV1.m_cColor.fB;
        m_EnvColor[m_triEnvCurrentIndex].a = cV1.m_cColor.fA * fAlpha;

        m_triEnvCurrentIndex++;

        m_EnvVertex[m_triEnvCurrentIndex].x = cV2.m_cPosition.fX;
        m_EnvVertex[m_triEnvCurrentIndex].y = cV2.m_cPosition.fY;
        m_EnvVertex[m_triEnvCurrentIndex].z = cV2.m_cPosition.fZ;

        m_EnvTexture[m_triEnvCurrentIndex].s0 = cV2.m_cNormal.fX;
        m_EnvTexture[m_triEnvCurrentIndex].t0 = cV2.m_cNormal.fY;

        m_EnvColor[m_triEnvCurrentIndex].r = cV2.m_cColor.fR;
        m_EnvColor[m_triEnvCurrentIndex].g = cV2.m_cColor.fG;
        m_EnvColor[m_triEnvCurrentIndex].b = cV2.m_cColor.fB;
        m_EnvColor[m_triEnvCurrentIndex].a = cV2.m_cColor.fA * fAlpha;

        m_triEnvCurrentIndex++;

        m_EnvVertex[m_triEnvCurrentIndex].x = cV3.m_cPosition.fX;
        m_EnvVertex[m_triEnvCurrentIndex].y = cV3.m_cPosition.fY;
        m_EnvVertex[m_triEnvCurrentIndex].z = cV3.m_cPosition.fZ;

        m_EnvTexture[m_triEnvCurrentIndex].s0 = cV3.m_cNormal.fX;
        m_EnvTexture[m_triEnvCurrentIndex].t0 = cV3.m_cNormal.fY;

        m_EnvColor[m_triEnvCurrentIndex].r = cV3.m_cColor.fR;
        m_EnvColor[m_triEnvCurrentIndex].g = cV3.m_cColor.fG;
        m_EnvColor[m_triEnvCurrentIndex].b = cV3.m_cColor.fB;
        m_EnvColor[m_triEnvCurrentIndex].a = cV3.m_cColor.fA * fAlpha;

        m_triEnvCurrentIndex++;
    }
#else
    glTexCoord2f(cV1.m_cNormal.fX, cV1.m_cNormal.fY);
    glColor4f(cV1.m_cColor.fR, cV1.m_cColor.fG, cV1.m_cColor.fB, cV1.m_cColor.fA*fAlpha);
    glVertex3f(cV1.m_cPosition.fX, cV1.m_cPosition.fY, cV1.m_cPosition.fZ);

    glTexCoord2f(cV2.m_cNormal.fX, cV2.m_cNormal.fY);
    glColor4f(cV2.m_cColor.fR, cV2.m_cColor.fG, cV2.m_cColor.fB, cV2.m_cColor.fA*fAlpha);
    glVertex3f(cV2.m_cPosition.fX, cV2.m_cPosition.fY, cV2.m_cPosition.fZ);

    glTexCoord2f(cV3.m_cNormal.fX, cV3.m_cNormal.fY);
    glColor4f(cV3.m_cColor.fR, cV3.m_cColor.fG, cV3.m_cColor.fB, cV3.m_cColor.fA*fAlpha);
    glVertex3f(cV3.m_cPosition.fX, cV3.m_cPosition.fY, cV3.m_cPosition.fZ);
#endif
}

void CObjectNode::glFaceFlush()
{
    glVertexPointer(3, GL_FLOAT, 0, m_Vertex);
    glTexCoordPointer(2, GL_FLOAT, 0, m_Texture);
    glColorPointer(4, GL_FLOAT, 0, m_Color);

    glDrawArrays(GL_TRIANGLES, 0, m_triCurrentIndex);

    m_triCurrentIndex = 0;
}

void CObjectNode::glEnvFlush()
{
    glVertexPointer(3, GL_FLOAT, 0, m_EnvVertex);
    glTexCoordPointer(2, GL_FLOAT, 0, m_EnvTexture);
    glColorPointer(4, GL_FLOAT, 0, m_EnvColor);

    glDrawArrays(GL_TRIANGLES, 0, m_triEnvCurrentIndex);

    m_triEnvCurrentIndex = 0;
}

static void glLineFace(CNodeData& cV1, CNodeData& cV2, CNodeData& cV3)
{
#ifdef GL_VERSION_ES_CM_1_1
#else
    glVertex3f(cV1.m_cPosition.fX, cV1.m_cPosition.fY, cV1.m_cPosition.fZ);
    glVertex3f(cV2.m_cPosition.fX, cV2.m_cPosition.fY, cV2.m_cPosition.fZ);

    glVertex3f(cV2.m_cPosition.fX, cV2.m_cPosition.fY, cV2.m_cPosition.fZ);
    glVertex3f(cV3.m_cPosition.fX, cV3.m_cPosition.fY, cV3.m_cPosition.fZ);

    glVertex3f(cV3.m_cPosition.fX, cV3.m_cPosition.fY, cV3.m_cPosition.fZ);
    glVertex3f(cV1.m_cPosition.fX, cV1.m_cPosition.fY, cV1.m_cPosition.fZ);
#endif
}

static float calc_cathmull_seg_len(CVector& stA, CVector& stB, CVector& stC, CVector& stD)
{
    float	fRes;
    float	a, b, c, e, f, g, i, j, k;

    /*
     * lets start ritual dance around fire place
     */

    a = 0.5f * (3 * stB.fX + stD.fX - stA.fX -3 * stC.fX);
    b = stA.fX + 2 * stC.fX - 0.5f * (5 * stB.fX + stD.fX);
    c = 0.5f * (stC.fX - stA.fX);

    e = 0.5f * (3 * stB.fY + stD.fY - stA.fY -3 * stC.fY);
    f = stA.fY + 2 * stC.fY - 0.5f * (5 * stB.fY + stD.fY);
    g = 0.5f * (stC.fY - stA.fY);

    i = 0.5f * (3 * stB.fZ + stD.fZ - stA.fZ -3 * stC.fZ);
    j = stA.fZ + 2 * stC.fZ - 0.5f * (5 * stB.fZ + stD.fZ);
    k = 0.5f * (stC.fZ - stA.fZ);

    /*
     * lets start a black magic
     */

    fRes = (float)sqrt(
            9 * a * a + 6 * a * (2 * b + c) + 4 * b * b + 4 * b * c + c * c + 9 * e * e + 6 * e * (2 * f + g)
            + 4 * f * f + 4 * f * g + g * g + (3 * i + 2 * j + k) * (3 * i + 2 * j + k)) +
            (float)sqrt(c * c + g * g + k * k);

    /*
     * uff.. now we have computed spline seg len
     */

    return fRes;
}

static inline void calc_cathmull(CVector& stResult, float fA, float fB, float fC, float fD, float fT)
{
    register float   fa, fb, fc;

    fa = 0.5f * (3 * fB + fD - fA -3 * fC);
    fb = fA + 2 * fC - 0.5f * (5 * fB + fD);
    fc = 0.5f * (fC - fA);

    stResult.fX = fT * fT * fT * fa + fT * fT * fb + fT * fc + fB;
    stResult.fY = 3 * fT * fT * fa + 2 * fT * fb + fc;
    stResult.fZ = 6 * fT * fa + 2 * fb;
}

void CSplinedObject::AddTable(CObjectNode* pTable, int nResU, int nResV)
{
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

void CSplinedObject::CloseTableU()
{
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

void CSplinedObject::Render(CMatrix& cCameraMatrix, CMatrix& cProjection)
{
    CObjectNode* pNode;
    CObjectNode* pEdge;

    if (!m_pRoot)
        return;

    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(cCameraMatrix.m_.aMatrix);
    glMultMatrixf(m_cMatrix.m_.aMatrix);

    if (m_bGenerateNormals)
    {
        CMatrix cModelView;
        glGetFloatv(GL_MODELVIEW_MATRIX, (float*)&cModelView.m_.aMatrix);
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

CObjectNode::CObjectNode()
{
    m_pUp = m_pDown = m_pLeft = m_pRight = 0;
    m_nWarapUV = 0;

    m_triBufSize = m_triEnvBufSize = 24 * 3;
    m_triCurrentIndex = m_triEnvCurrentIndex = 0;

    m_Vertex = new CVertex[m_triBufSize];
    m_Texture = new CVertexTex[m_triBufSize];
    m_Color = new CVertexColor[m_triBufSize];

    m_EnvVertex = new CVertex[m_triEnvBufSize];
    m_EnvTexture = new CVertexTex[m_triEnvBufSize];
    m_EnvColor = new CVertexColor[m_triEnvBufSize];
}

CObjectNode::~CObjectNode()
{
    delete [] m_Vertex;
    delete [] m_Texture;
    delete [] m_Color;
}

void CObjectNode::RenderPatch(int nSeedU, int nSeedV, CMultiTexData* pTexData, int nTexData)
{
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
        fV = (float)nV / (float)(nSeedV - 1);
        SInterpolate(aEdges[0][nV], pN1, pN2, pN3, pN4, fV);
    }

    aEdges[0][nSeedV - 1] = pN3->m_cNodeData;

    /* calculate edge 2 */

    pN1 = GetValidUp();
    pN2 = this;
    pN3 = GetValidDown();
    pN4 = pN3->GetValidDown();

    aEdges[1][0] = pN2->m_cNodeData;

    for (nV = 1; nV != nSeedV - 1; nV++) {
        fV = (float)nV / (float)(nSeedV - 1);
        SInterpolate(aEdges[1][nV], pN1, pN2, pN3, pN4, fV);
    }

    aEdges[1][nSeedV - 1] = pN3->m_cNodeData;

    /* calculate edge 3 */

    pN2 = pN1 = GetValidRight();
    pN1 = pN1->GetValidUp();
    pN3 = pN2->GetValidDown();
    pN4 = pN3->GetValidDown();

    aEdges[2][0] = pN2->m_cNodeData;

    for (nV = 1; nV != nSeedV - 1; nV++) {
        fV = (float)nV / (float)(nSeedV - 1);
        SInterpolate(aEdges[2][nV], pN1, pN2, pN3, pN4, fV);
    }

    aEdges[2][nSeedV - 1] = pN3->m_cNodeData;

    /* calculate edge 4 */

    pN2 = pN2->GetValidRight();
    pN1 = pN2->GetValidUp();
    pN3 = pN2->GetValidDown();
    pN4 = pN3->GetValidDown();

    aEdges[3][0] = pN2->m_cNodeData;

    for (nV = 1; nV != nSeedV - 1; nV++) {
        fV = (float)nV / (float)(nSeedV - 1);
        SInterpolate(aEdges[3][nV], pN1, pN2, pN3, pN4, fV);
    }

    aEdges[3][nSeedV - 1] = pN3->m_cNodeData;

    /* make faces */

    int nWrap;

    if (m_nWarapUV) nWrap = 1;
    else
    if (GetValidLeft()->m_nWarapUV) nWrap = -1;
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

    for (nV = 1; nV != nSeedV; nV++)
    {
        //pHLine2[0] = aEdges[1][nV];
        for (nU = 0; nU != nSeedU; nU++) {
            fU = (float)nU/(float)(nSeedU - 1);
            SInterpolate(pHLine2[nU], aEdges[0][nV], aEdges[1][nV], aEdges[2][nV], aEdges[3][nV], fU, nWrap);
        }
        //pHLine2[0] = aEdges[2][nV];

        /* oki.. we've got here a strip, so render it */

#ifdef GL_VERSION_ES_CM_1_1
        glClientActiveTexture(GL_TEXTURE0);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
        for (nTex = 0; nTex != nTexData; nTex++)
        {
            if (pTexData[nTex].m_nGLTexName)
            {
                glBindTexture(GL_TEXTURE_2D, *pTexData[nTex].m_nGLTexName);
#ifndef GL_VERSION_ES_CM_1_1
                glBegin(GL_TRIANGLES);
#endif

                if (pTexData[nTex].m_nMaterial & 1)
                {
                    for (nU = 0; nU != nSeedU - 1; nU++) {
                        glFace(pHLine1[nU], pHLine1[nU + 1], pHLine2[nU], pTexData[nTex].m_fAlpha, pTexData[nTex].m_fUShift, pTexData[nTex].m_fVShift);
                        glFace(pHLine1[nU + 1], pHLine2[nU + 1], pHLine2[nU], pTexData[nTex].m_fAlpha, pTexData[nTex].m_fUShift, pTexData[nTex].m_fVShift);
                    }
                } else
                if (pTexData[nTex].m_nMaterial & 2)
                {
                    for (nU = 0; nU != nSeedU - 1; nU++) {
                        glEnv(pHLine1[nU], pHLine1[nU + 1], pHLine2[nU], pTexData[nTex].m_fAlpha);
                        glEnv(pHLine1[nU + 1], pHLine2[nU + 1], pHLine2[nU], pTexData[nTex].m_fAlpha);
                    }
                }
#ifndef GL_VERSION_ES_CM_1_1
                glEnd();
#endif
            }
        }

#ifdef GL_VERSION_ES_CM_1_1
        glFaceFlush();
        glEnvFlush();

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#endif
        pTmp = pHLine1;
        pHLine1 = pHLine2;
        pHLine2 = pTmp;
    }
}

void CSplinedObject::GenerateNormals(CMatrix& cModelView)
{
    if (!m_bGenerateNormals)
        return;

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
