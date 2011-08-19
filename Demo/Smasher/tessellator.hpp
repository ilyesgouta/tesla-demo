/**
 * programming by KZ
 * Copyright (C) by Konrad Zagorowicz
 */

#ifndef pi
#define pi 3.1415926535897932384626433832795
#endif

class CMultiTexData {

public:
      CMultiTexData() {
        m_nGLTexName = NULL;
        m_fAlpha = 1.0f;
	m_fUShift = 0;
	m_fVShift = 0;
        m_nMaterial = 0x1;
      }
      int *m_nGLTexName;
      float m_fAlpha;
      float m_fUShift;
      float m_fVShift;
      int m_nMaterial;
      
};

/* node data */
class CNodeData {

public:
	CVector m_cPosition;
	CVector m_cNormal;
	CTexel m_cTexel;
	CColor m_cColor;
};

static inline float calc_cathmull(float fA, float fB, float fC, float fD, float fT) {

        register float   fa, fb, fc;

        fa = 0.5f*(3*fB + fD - fA -3*fC);
        fb = fA + 2*fC - 0.5f*(5*fB + fD);
        fc = 0.5f*(fC - fA);        
    
        return(fT*fT*fT*fa + fT*fT*fb + fT*fc + fB);
}


class CObjectNode {
	friend class CSplinedObject;

public:
	CObjectNode() { m_pUp = m_pDown = m_pLeft = m_pRight = 0; m_nWarapUV = 0; }
	~CObjectNode() {}

	void SetData(CNodeData& cData) {
	  m_cNodeData = cData;
	}

	void SetPosition(CVector& cPosition) {
	  m_cNodeData.m_cPosition = cPosition;
	}

	void SetTexel(CTexel& cTexel) {
	  m_cNodeData.m_cTexel = cTexel;
	}

	void SetColor(CColor& cColor) {
	  m_cNodeData.m_cColor = cColor;
	}

        CVector* GetPosition() { return &m_cNodeData.m_cPosition; }

        void LinkUp(CObjectNode* pNode) {
          if (m_pLeft && m_pLeft->m_pUp) { m_pLeft->m_pUp->m_pRight = pNode; pNode->m_pLeft = m_pRight->m_pDown; }
          if (m_pRight && m_pRight->m_pUp) { m_pRight->m_pUp->m_pLeft = pNode; pNode->m_pRight = m_pRight->m_pUp; }
          m_pUp = pNode;
	  pNode->m_pDown= this;
        };

        void LinkDown(CObjectNode* pNode) {
          if (m_pLeft && m_pLeft->m_pDown) { m_pLeft->m_pDown->m_pRight = pNode; pNode->m_pLeft = m_pLeft->m_pDown; }
          if (m_pRight && m_pRight->m_pDown) { m_pRight->m_pDown->m_pLeft = pNode; pNode->m_pRight = m_pRight->m_pDown; }
          m_pDown = pNode;
	  pNode->m_pUp = this;
        }

        void LinkLeft(CObjectNode* pNode) {
          if (m_pUp && m_pUp->m_pLeft) { m_pUp->m_pLeft->m_pDown = pNode; pNode->m_pUp = m_pUp->m_pLeft; }
          if (m_pDown && m_pDown->m_pLeft) { m_pDown->m_pLeft->m_pUp = pNode; pNode->m_pDown = m_pDown->m_pLeft; }
          m_pLeft = pNode;
	  pNode->m_pRight = this;
        }

        void LinkRight(CObjectNode* pNode) {
          if (m_pUp && m_pUp->m_pRight) { m_pUp->m_pRight->m_pDown = pNode; pNode->m_pUp = m_pUp->m_pRight; }
          if (m_pDown && m_pDown->m_pRight) { m_pDown->m_pRight->m_pUp = pNode; pNode->m_pDown = m_pDown->m_pRight; }
          m_pRight = pNode;
	  pNode->m_pLeft = this;
        }


	CObjectNode* GetLeft() { return m_pLeft; }
	CObjectNode* GetRight() { return m_pRight; }
	CObjectNode* GetUp() { return m_pUp; }
	CObjectNode* GetDown() { return m_pDown; }

	CObjectNode* GetValidLeft() { if (m_pLeft) return m_pLeft; else return this; }
	CObjectNode* GetValidRight() { if (m_pRight) return m_pRight; else return this; }
	CObjectNode* GetValidUp() { if (m_pUp) return m_pUp; else return this; }
	CObjectNode* GetValidDown() { if (m_pDown) return m_pDown; else return this; }

        void RenderPatch(int nSeedU, int nSeedV, CMultiTexData* pTexData, int nTexData);
	
protected:

	CNodeData m_cNodeData;

        CVector cNormals[2];

        int m_nWarapUV;

	CObjectNode* m_pUp;
	CObjectNode* m_pDown;
	CObjectNode* m_pLeft;
	CObjectNode* m_pRight;

	void SInterpolate(CNodeData& cDest, const CObjectNode* pN1, const CObjectNode* pN2, const CObjectNode* pN3, const CObjectNode* pN4, float fT)
	{
	  cDest.m_cPosition.fX = calc_cathmull(pN1->m_cNodeData.m_cPosition.fX, pN2->m_cNodeData.m_cPosition.fX, pN3->m_cNodeData.m_cPosition.fX, pN4->m_cNodeData.m_cPosition.fX, fT);
	  cDest.m_cPosition.fY = calc_cathmull(pN1->m_cNodeData.m_cPosition.fY, pN2->m_cNodeData.m_cPosition.fY, pN3->m_cNodeData.m_cPosition.fY, pN4->m_cNodeData.m_cPosition.fY, fT);
	  cDest.m_cPosition.fZ = calc_cathmull(pN1->m_cNodeData.m_cPosition.fZ, pN2->m_cNodeData.m_cPosition.fZ, pN3->m_cNodeData.m_cPosition.fZ, pN4->m_cNodeData.m_cPosition.fZ, fT);
	  cDest.m_cTexel.fU = calc_cathmull(pN1->m_cNodeData.m_cTexel.fU, pN2->m_cNodeData.m_cTexel.fU, pN3->m_cNodeData.m_cTexel.fU, pN4->m_cNodeData.m_cTexel.fU, fT);
	  cDest.m_cTexel.fV = calc_cathmull(pN1->m_cNodeData.m_cTexel.fV, pN2->m_cNodeData.m_cTexel.fV, pN3->m_cNodeData.m_cTexel.fV, pN4->m_cNodeData.m_cTexel.fV, fT);
	  cDest.m_cNormal.fX = calc_cathmull(pN1->m_cNodeData.m_cNormal.fX, pN2->m_cNodeData.m_cNormal.fX, pN3->m_cNodeData.m_cNormal.fX, pN4->m_cNodeData.m_cNormal.fX, fT);
	  cDest.m_cNormal.fY = calc_cathmull(pN1->m_cNodeData.m_cNormal.fY, pN2->m_cNodeData.m_cNormal.fY, pN3->m_cNodeData.m_cNormal.fY, pN4->m_cNodeData.m_cNormal.fY, fT);
          cDest.m_cColor.fR = calc_cathmull(pN1->m_cNodeData.m_cColor.fR, pN2->m_cNodeData.m_cColor.fR, pN3->m_cNodeData.m_cColor.fR, pN4->m_cNodeData.m_cColor.fR, fT);
          cDest.m_cColor.fG = calc_cathmull(pN1->m_cNodeData.m_cColor.fG, pN2->m_cNodeData.m_cColor.fG, pN3->m_cNodeData.m_cColor.fG, pN4->m_cNodeData.m_cColor.fG, fT);
          cDest.m_cColor.fB = calc_cathmull(pN1->m_cNodeData.m_cColor.fB, pN2->m_cNodeData.m_cColor.fB, pN3->m_cNodeData.m_cColor.fB, pN4->m_cNodeData.m_cColor.fB, fT);
          cDest.m_cColor.fA = calc_cathmull(pN1->m_cNodeData.m_cColor.fA, pN2->m_cNodeData.m_cColor.fA, pN3->m_cNodeData.m_cColor.fA, pN4->m_cNodeData.m_cColor.fA, fT);
	}

	void SInterpolate(CNodeData& cDest, const CNodeData& cE1, const CNodeData& cE2, const CNodeData& cE3, const CNodeData& cE4, float fT, int nWrap)
	{
	  cDest.m_cPosition.fX = calc_cathmull(cE1.m_cPosition.fX, cE2.m_cPosition.fX, cE3.m_cPosition.fX, cE4.m_cPosition.fX, fT);
	  cDest.m_cPosition.fY = calc_cathmull(cE1.m_cPosition.fY, cE2.m_cPosition.fY, cE3.m_cPosition.fY, cE4.m_cPosition.fY, fT);
	  cDest.m_cPosition.fZ = calc_cathmull(cE1.m_cPosition.fZ, cE2.m_cPosition.fZ, cE3.m_cPosition.fZ, cE4.m_cPosition.fZ, fT);

	  cDest.m_cNormal.fX = calc_cathmull(cE1.m_cNormal.fX, cE2.m_cNormal.fX, cE3.m_cNormal.fX, cE4.m_cNormal.fX, fT);
	  cDest.m_cNormal.fY = calc_cathmull(cE1.m_cNormal.fY, cE2.m_cNormal.fY, cE3.m_cNormal.fY, cE4.m_cNormal.fY, fT);

          if (nWrap == 0) cDest.m_cTexel.fU = calc_cathmull(cE1.m_cTexel.fU, cE2.m_cTexel.fU, cE3.m_cTexel.fU, cE4.m_cTexel.fU, fT);
          else if (nWrap > 0) cDest.m_cTexel.fU = calc_cathmull(cE1.m_cTexel.fU, cE2.m_cTexel.fU, cE3.m_cTexel.fU + 1, cE4.m_cTexel.fU + 1, fT);
          else cDest.m_cTexel.fU = calc_cathmull(cE1.m_cTexel.fU - 1, cE2.m_cTexel.fU, cE3.m_cTexel.fU, cE4.m_cTexel.fU, fT);

	  cDest.m_cTexel.fV = calc_cathmull(cE1.m_cTexel.fV, cE2.m_cTexel.fV, cE3.m_cTexel.fV, cE4.m_cTexel.fV, fT);
          cDest.m_cColor.fR = calc_cathmull(cE1.m_cColor.fR, cE2.m_cColor.fR, cE3.m_cColor.fR, cE4.m_cColor.fR, fT);
          cDest.m_cColor.fG = calc_cathmull(cE1.m_cColor.fG, cE2.m_cColor.fG, cE3.m_cColor.fG, cE4.m_cColor.fG, fT);
          cDest.m_cColor.fB = calc_cathmull(cE1.m_cColor.fB, cE2.m_cColor.fB, cE3.m_cColor.fB, cE4.m_cColor.fB, fT);
          cDest.m_cColor.fA = calc_cathmull(cE1.m_cColor.fA, cE2.m_cColor.fA, cE3.m_cColor.fA, cE4.m_cColor.fA, fT);
	}
};


class CSplinedObject {
public:
        /* default contructor */ 
	CSplinedObject() { 
		  m_pRoot = 0;
		  m_nMultiTex = 0;
		  m_nSeedU = 4;
		  m_nSeedV = 4;
		  m_bGenerateNormals = false;
		}

        /* you dont need it when you're using AddTable mehtod */
	  void AddRoot(CNodeData& cRootData) {
	    if (m_pRoot) return;
	    m_pRoot = new CObjectNode;
	    m_pRoot->SetData(cRootData);
	  }


        /* apply table to sobject, sobject has ptrs on this data so dont delete it */
        void AddTable(CObjectNode* pTable, int nResU, int nResV);

        /* object matrix */
        void SetMatrix(CMatrix& cMatrix) {
          m_cMatrix = cMatrix;
        }

        /* textures */

        void SetMultiTexData(CMultiTexData* pData, int nData) {
          for (int nI = 0; nI != nData; nI++) {
            m_aMultiTex[nI] = pData[nI];
          }

          m_nMultiTex = nData;
        }

        int GetNumMultiTex() {
          return m_nMultiTex;
        }

        CMultiTexData* GetPtrMultiTex() {
          return m_aMultiTex;
        }

        /* you can get the root of the table, well you dont need it coz you have your local ptr (see: AddTable) */
		CObjectNode* GetRoot() { return m_pRoot; }

        /* sets seedu and seedv */
        void SetSeed(int nSeedU, int nSeedV) {
          if (nSeedU >= 64) nSeedU = 63;
          if (nSeedV >= 64) nSeedV = 63;
          m_nSeedU = nSeedU;
          m_nSeedV = nSeedV;
        }

        /* */
        void CloseTableU();

        /* no comment */
        void Render(CMatrix& cCameraMatrix, CMatrix& cProjection);

        void EnableNormals() {
	  m_bGenerateNormals = true;
        }

        void DisableNormals() {
	  m_bGenerateNormals = false;
        }


protected:

        CMatrix m_cMatrix;
	CObjectNode* m_pRoot;

        CMultiTexData m_aMultiTex[16];
        int m_nMultiTex;

        int m_nResU, m_nResV;

        int m_nSeedU, m_nSeedV;
        bool m_bGenerateNormals;
        void GenerateNormals(CMatrix& cModelView);
};



