

#if !defined (_CTerrain_hpp_) 
#define _CTerrain_hpp_

#include "GridNode.hpp"

#include "base3d/Camera.hpp"
#include "base3d/CMatrix.hpp"
#include "base3d/Quaternion.hpp"

#include "TexManager.hpp"

class CTerrain {
  
public:
    CTerrain();
    ~CTerrain();

    /* output: ture if success, false if fail */
    bool LoadRawMap( char* pszMapFileName );

    void Render( CCamera& cCamera );
    void Collision();

    float GetSample( CVector* pNormal, const float fX, const float fZ ) {
        return m_pGridTable->GetSample( pNormal, fX, fZ );
    }

protected:
    /* map resolution */
    unsigned int m_dwResX, m_dwResZ;

    /* mesh data */
    CVector* m_pMapVertices;
    int m_nMapVertices;

    /* generates mesh from raw file */
    void GenMeshFromRaw( unsigned char* pMapRawData );

    /* */
    void InitGrid();

    /* grid tables */
    CGridTable* m_pGridTable;
};

#endif /* _CTerrain_hpp_ */





