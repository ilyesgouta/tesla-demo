
#include "stdafx.h"
#include "TexManager.hpp"
#include "../../ImageLib/ImageLib.hpp"

CTextureManager g_cTexManager;

/*******************************************************************************************/
int CTextureManager::LoadTexture( char* pszFileName, int iCreateMipMaps ) {

        CTexture* pLoaded = FindTexture( pszFileName );

        if ( pLoaded )
        {
          pLoaded->m_iRefCount++;
          return pLoaded->m_iGLTexName;
        }

        CImage* pImage = g_cImageLib.LoadFile( pszFileName );

        if ( !pImage )
        {
          g_pMainFrame->ErrorQuit( "[CTextureManager::LoadTexture] Cant load file : %s", pszFileName );
          return -1;
        }

        int iResult = g_cOpenGL.UploadTexture( pImage->GetRawData(), pImage->GetWidth(), pImage->GetHeight(), pImage->GetBitsPerPixel(), iCreateMipMaps );
        delete pImage;

        if ( iResult != -1 )
        {
          CTexture* pTexture = new CTexture;

          pTexture->m_pszFileName = strdup( pszFileName );
          pTexture->m_iGLTexName = iResult;
          pTexture->m_iRefCount++;
          pTexture->m_bCreateMipMaps = iCreateMipMaps;

          pTexture->m_pNext = m_pTextures;
          m_pTextures = pTexture;
          m_iTextures++;
        }

        return iResult;
}
/*******************************************************************************************/
void CTextureManager::ReleaseTexture( int iTexName ) {

        CTexture* pUnload = FindTexture( iTexName );

        if ( pUnload )
        {
          pUnload->m_iRefCount--;

          if ( pUnload->m_iRefCount == 0 )
          {
            glDeleteTextures( 1, (unsigned int*)&iTexName );

            CTexture* pPrev = 0;
            CTexture* pTexture = m_pTextures;

            while ( pTexture )
            {
              if ( pTexture == pUnload )
              {
                if ( pPrev )
                {
                  pPrev->m_pNext = pTexture->m_pNext;
                }
                else
                  m_pTextures = pTexture->m_pNext;

                delete pTexture;
                break;
              }

              pPrev = pTexture;
              pTexture = pTexture->m_pNext;
            }
          }
        }
}
/*******************************************************************************************/
bool CTextureManager::ReloadAllTextures() {

        return true;
}
/*******************************************************************************************/


