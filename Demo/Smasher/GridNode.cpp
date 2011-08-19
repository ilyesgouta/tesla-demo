
#include "stdafx.h"
#include "GridNode.hpp"

// CGridTable
/************************************************************************************/
void CGridTable::Init( unsigned int dwNodeX, unsigned int dwNodeZ, float fNodeSize, CVector* pMapVertices, unsigned int dwMapResX, unsigned int dwMapResZ ) {

        m_dwMapResX = dwMapResX;
        m_dwMapResZ = dwMapResZ;
        m_pMap = pMapVertices;
        
        m_dwGridResX = (int)ceil( (float)(dwMapResX - 1)/(dwNodeX - 1) );
        m_dwGridResZ = (int)ceil( (float)(dwMapResZ - 1)/(dwNodeZ - 1) );

        m_dwNodeResX = dwNodeX;
        m_dwNodeResZ = dwNodeZ;

        m_fNodeSizeX = fNodeSize*(dwNodeX - 1);
        m_fNodeSizeZ = fNodeSize*(dwNodeZ - 1);

        m_pGrid = new CGridNode[m_dwGridResX*m_dwGridResZ];

        for ( unsigned int z = 0; z != m_dwGridResZ; z++ )
        {
          for ( unsigned int x = 0; x != m_dwGridResX; x++ )
          {
            CGridNode& cGrid = m_pGrid[z*m_dwGridResX + x];

            cGrid.m_dwTerrainBegin = z*dwMapResX*(dwNodeZ - 1) + x*(dwNodeX - 1);
          }
        }
}
/************************************************************************************/
float CGridTable::GetSample( CVector* pNormal, const float fX, const float fZ ) const {

        int iMapX, iMapZ, i;
        float fHeight, fH, dydx, dydz;

        iMapX = (int)floor( (fX*(m_dwNodeResX - 1))/m_fNodeSizeX );
        iMapZ = (int)floor( (fZ*(m_dwNodeResZ - 1))/m_fNodeSizeZ );
        
        if ( iMapX < 0 ) return 0;
        if ( (unsigned)iMapX >= m_dwMapResX ) return 0;
        if ( iMapZ < 0 ) return 0;
        if ( (unsigned)iMapZ >= m_dwMapResZ ) return 0;

        i = iMapZ*m_dwMapResX + iMapX;

        fH = m_pMap[i + 1].fZ + m_pMap[i + 1].fX;

        if ( fZ < -fX + fH )
        {
          dydx = (m_pMap[i + 1].fY - m_pMap[i].fY)/(m_pMap[i + 1].fX - m_pMap[i].fX);
          dydz = (m_pMap[i + m_dwMapResX].fY - m_pMap[i].fY)/(m_pMap[i + m_dwMapResX].fZ - m_pMap[i].fZ);
          fHeight = dydx*(fX - m_pMap[i].fX) + dydz*(fZ - m_pMap[i].fZ) + m_pMap[i].fY;
        }
        else
        {
          dydx = (m_pMap[i + 1 + m_dwMapResX].fY - m_pMap[i + m_dwMapResX].fY)/(m_pMap[i + 1 + m_dwMapResX].fX - m_pMap[i + m_dwMapResX].fX);
          dydz = (m_pMap[i + 1].fY - m_pMap[i + 1 + m_dwMapResX].fY)/(m_pMap[i + 1].fZ - m_pMap[i + 1 + m_dwMapResX].fZ);
          fHeight = dydx*(fX - m_pMap[i + m_dwMapResX].fX) + dydz*(fZ - m_pMap[i + 1 + m_dwMapResX].fZ) + m_pMap[i + m_dwMapResX].fY;
        }


        return fHeight;
}
/************************************************************************************/
void CGridTable::Render( CCamera& cCamera ) {
  
        CVector cCamPos;
        CAABoundBox* pBoundBox;

        int dwGridX0, dwGridX1;
        int dwGridZ0, dwGridZ1;

        float aMapping[8] = { 0, 0, 0, 1,
                              1, 0, 1, 1 };


        cCamera.GetPositon( cCamPos );
        pBoundBox = cCamera.GetExtents();

        dwGridX0 = (int)floor( pBoundBox->m_cMin.fX/m_fNodeSizeX );
        dwGridX1 = (int)floor( pBoundBox->m_cMax.fX/m_fNodeSizeX );
        dwGridZ0 = (int)floor( pBoundBox->m_cMin.fZ/m_fNodeSizeZ );
        dwGridZ1 = (int)floor( pBoundBox->m_cMax.fZ/m_fNodeSizeZ );

        if ( dwGridX0 < 0 ) dwGridX0 = 0;
        else if ( dwGridX0 >= (signed)m_dwGridResX ) return;

        if ( dwGridX1 < 0 ) return;
        else if ( dwGridX1 >= (signed)m_dwGridResX ) dwGridX1 = m_dwGridResX - 1;

        if ( dwGridZ0 < 0 ) dwGridZ0 = 0;
        else if ( dwGridZ0 >= (signed)m_dwGridResZ ) return;

        if ( dwGridZ1 < 0 ) return;
        else if ( dwGridZ1 >= (signed)m_dwGridResZ ) dwGridZ1 = m_dwGridResZ - 1;

        glDisable( GL_BLEND );

        glColor4f( 1, 1, 1, 1 );
        int i = 0;

        for ( unsigned int gz = dwGridZ0; gz <= (unsigned)dwGridZ1; gz++ )
        {
          for ( unsigned int gx = dwGridX0; gx <= (unsigned)dwGridX1; gx ++ )
          {
            int iBegin = m_pGrid[gz*m_dwGridResX + gx].m_dwTerrainBegin;

            /* render node */
            for ( unsigned int z = 0; z != m_dwNodeResZ - 1; z++ )
            {
              glBindTexture( GL_TEXTURE_2D, m_aGLTex[0] );
              glBegin( GL_TRIANGLE_STRIP );

              for ( unsigned int x = 0; x != m_dwNodeResX; x++ )
              {
                glTexCoord2fv( &aMapping[i]);
                glVertex3fv( (float*)&m_pMap[iBegin + z*m_dwMapResX + x] );
                glTexCoord2fv( &aMapping[i + 4] );
                glVertex3fv( (float*)&m_pMap[iBegin + (z+1)*m_dwMapResX + x] );
                i ^= 2;
              }

              glEnd();
            }
            /* end render node */
          }
        }
}
/************************************************************************************/


// CGridNode
/************************************************************************************/
/************************************************************************************/

