

#if !defined (_TEXTURE_MANAGER_HPP_)
#define _TEXTURE_MANAGER_HPP_


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
          if ( m_pszFileName ) free( m_pszFileName );
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
            if ( !stricmp(pTexture->m_pszFileName, pszName) ) return pTexture;
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
