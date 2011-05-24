
#include "stdafx.h"
#include "TerrainGen.hpp"

/***********************************************************************************/



CTerrain::CTerrain() {

        m_pGridTable = 0;
  
        m_dwResX = m_dwResZ = 0;

        m_pMapVertices = 0;
        m_nMapVertices = 0;

};
/***********************************************************************************/
CTerrain::~CTerrain() {

        if ( m_pMapVertices ) delete[] m_pMapVertices;
        if ( m_pGridTable ) delete m_pGridTable;
}
/***********************************************************************************/
bool CTerrain::LoadRawMap( char* pszMapFileName ) {

        unsigned int dwFileSize;
  
        if ( !pszMapFileName ) return false;
        if ( *pszMapFileName == 0 ) return false;

        FILE* pFile = fopen( pszMapFileName, "rb" );

        if ( !pFile ) return false;
        
        fseek( pFile, 0, SEEK_END );
        dwFileSize = ftell( pFile );
        fseek( pFile, 0, SEEK_SET );

        /* temp: assume map res is 512x512 */
        if ( dwFileSize != 512*512 ) return false;

        m_dwResX = 512;
        m_dwResZ = 512;

        unsigned char* pMapRawData = new unsigned char[dwFileSize];
        memset( pMapRawData, 0, dwFileSize );

        if ( !pMapRawData ) 
        {
          fclose( pFile );
          return false;
        }

        if ( fread(pMapRawData, dwFileSize, 1, pFile) != 1 )
        {
          delete[] pMapRawData;
          fclose( pFile );
          return false;
        }

        fclose( pFile );

        GenMeshFromRaw( pMapRawData );

        delete[] pMapRawData;

        m_pGridTable->SetTexture( g_cTexManager.LoadTexture("data/textures/scape.jpg", 1), 0 );

        return true;
}
/***********************************************************************************/
static const float l_fMeshMinY =  0.f;
static const float l_fMeshMaxY = 300.f;
static const float l_fMapGridSize = 8.f;
/***********************************************************************************/
void CTerrain::GenMeshFromRaw( unsigned char* pMapRawData ) {

        unsigned int x, z;
        float fMeshDelY = l_fMeshMaxY - l_fMeshMinY;
        
        float fMapX, fMapY, fMapZ;

        if ( m_pMapVertices ) delete[] m_pMapVertices;

        m_pMapVertices = new CVector[m_dwResX*m_dwResZ];

        for ( z = 0; z != m_dwResZ; z++ )
        {
          for ( x = 0; x != m_dwResX; x++ )
          {
            fMapX = (float)x*l_fMapGridSize;
            fMapY = (float)pMapRawData[x + z*m_dwResX]/256.f*fMeshDelY + l_fMeshMinY;
            fMapZ = (float)z*l_fMapGridSize;
            
            m_pMapVertices[x + z*m_dwResX] = CVector(fMapX, fMapY, fMapZ);

            m_nMapVertices++;
          }
        }

        InitGrid();
}
/***********************************************************************************/
void CTerrain::InitGrid() {
  
        m_pGridTable = new CGridTable;

        m_pGridTable->Init( 8, 8, l_fMapGridSize, m_pMapVertices, m_dwResX, m_dwResZ );
}
/***********************************************************************************/
void CTerrain::Render( CCamera& cCamera ) {

        CQuaternion cBase;

        glMatrixMode( GL_PROJECTION );
        glLoadMatrixf( cCamera.GetProjectionMatrix()->aMatrix );

        glMatrixMode( GL_MODELVIEW );
        glLoadMatrixf( cCamera.GetCameraMatrix()->aMatrix );

        glEnable( GL_TEXTURE_2D );
        glEnable( GL_CULL_FACE );
        glEnable( GL_DEPTH_TEST );

        m_pGridTable->Render( cCamera );
}
/***********************************************************************************/
