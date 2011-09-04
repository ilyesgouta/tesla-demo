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


#if !defined (_TEXTURE_MANAGER_HPP_)
#define _TEXTURE_MANAGER_HPP_

#include <stdlib.h>
#include <strings.h>

class CTextureManager {

class CTexture {
        
        friend class CTextureManager;

public:
        CTexture() {
         m_pszFileName = 0;
         m_iGLTexName = 0;
         m_bCreateMipMaps = 0;
         m_iRefCount = 0;
         m_pNext = 0;
        }

        ~CTexture() {
          if ( m_pszFileName )
              free( m_pszFileName );
        }

protected:
       char* m_pszFileName;
       int m_iGLTexName;
       int m_bCreateMipMaps;

       int m_iRefCount;

       CTexture* m_pNext;
};

public:
        CTextureManager() {
          m_iTextures = 0;
          m_pTextures = 0;
        }

        virtual ~CTextureManager() {
          CTexture* pDelTex;
          while ( m_pTextures )
          {
            pDelTex = m_pTextures;
            m_pTextures = m_pTextures->m_pNext;
            delete pDelTex;
          }
        }

        /* return TexName */
        int LoadTexture( char* pszFileName, int iCreateMipMaps = 0 );
        void ReleaseTexture( int iTexName );

        bool ReloadAllTextures();

protected:

        CTexture* m_pTextures;
        int m_iTextures;


        CTexture* FindTexture( char* pszName ) {

          CTexture* pTexture = m_pTextures;

          while ( pTexture )
          {
#ifdef WIN32
            if ( !stricmp(pTexture->m_pszFileName, pszName) ) return pTexture;
#else
            if ( !strcasecmp(pTexture->m_pszFileName, pszName) ) return pTexture;
#endif
            pTexture = pTexture->m_pNext;
          }

          return 0;
        }

        CTexture* FindTexture( int iGLTexName ) {

          CTexture* pTexture = m_pTextures;

          while ( pTexture )
          {
            if ( pTexture->m_iGLTexName == iGLTexName ) return pTexture;
            pTexture = pTexture->m_pNext;
          }

          return 0;
        }
};

extern CTextureManager g_cTexManager;

#endif /* _TEXTURE_MANAGER_HPP_ */
