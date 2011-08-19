

#if !defined (_CGridNode_hpp_)
#define _CGridNode_hpp_

class CGridNode {

public:
        friend class CGridTable;

        CGridNode() {

          m_dwTerrainBegin = 0;
          m_cBoundMax = CVector(-1e30f, -1e30f, -1e30f);
          m_cBoundMin = CVector( 1e30f,  1e30f,  1e30f);

          m_aSubGrid[0] = m_aSubGrid[1] = m_aSubGrid[2] = m_aSubGrid[3] = 0;
        };

protected:

        unsigned int m_dwTerrainBegin;
        CVector m_cBoundMin, m_cBoundMax;

        CGridNode* m_aSubGrid[4];
};


class CGridTable {

public:
        CGridTable() {
          m_pGrid = 0;
          m_dwGridResX = m_dwGridResZ = 0;
          m_dwNodeResX = m_dwNodeResZ = 0;
          m_fNodeSizeX = m_fNodeSizeZ = 0;
        }

        ~CGridTable() {
          if ( m_pGrid ) delete[] m_pGrid;
        };

        void Init( unsigned int dwNodeX, unsigned int dwNodeZ, float fNodeSize, CVector* pMapVertices, unsigned int dwMapResX, unsigned int dwMapResZ );


        /* returns height at (fX, fZ) and fills normal vector, pNormal may be NULL */
        float GetSample( CVector* pNormal, const float fX, const float fZ ) const;

        void SetTexture( unsigned int dwGLTexName, int iTexture ) {
          m_aGLTex[iTexture] = dwGLTexName;
        }


        void Render( CCamera& cCamera );

protected:

        /* grid */
        CGridNode* m_pGrid;

        /* ilosc gridow */
        unsigned int m_dwGridResX, m_dwGridResZ;


        /* wielkosci jednego node'a (w oczkach siatki) */
        unsigned int m_dwNodeResX, m_dwNodeResZ;

        /* wielkosc pojedynczego node'a */
        float m_fNodeSizeX, m_fNodeSizeZ;


        /* szerokosc mapy w oczkach siatki */
        unsigned int m_dwMapResX;
        unsigned int m_dwMapResZ;
        CVector* m_pMap;

        /* textury */
        unsigned int m_aGLTex[4];
};

#endif /* _CGridNode_hpp_ */

