//
// tesla-demo, an OpenGL|ES 1.1 port of Sunflower's original Tesla demo.
//
// Original Tesla code, Copyright (C) 2000 Sunflower
// Linux EGL/X11 port by Ilyes Gouta, ilyes.gouta@gmail.com
//
// Port released under GNU General Public License with permission from
// Konrad Zagorowicz, original developer from Sunflower.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifdef WIN32
#include "stdafx.h"
#endif

#include "OpenGL/OpenGL.hpp"
#include "MainFrame/MainFrame.hpp"

#include "TexManager.hpp"
#include "../../ImageLib/ImageLib.hpp"

CTextureManager g_cTexManager;

int CTextureManager::LoadTexture( char* pszFileName, int iCreateMipMaps )
{
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

void CTextureManager::ReleaseTexture( int iTexName )
{
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
                        pPrev->m_pNext = pTexture->m_pNext;
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

bool CTextureManager::ReloadAllTextures()
{
    return true;
}
