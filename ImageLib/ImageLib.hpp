// y.

#if !defined (_IMAGE_LIB_HPP_)
#define _IMAGE_LIB_HPP_

#include <stdio.h>
#include <string.h>

class CImage {

public: 
        CImage() {

          m_dwWidth = 0;
          m_dwHeight = 0;
          m_dwBPP = 0;
          m_pRawData = 0;
        }

        CImage( unsigned int dwWidth, unsigned int dwHeight, unsigned int dwBPP, void* pRawData ) {

          m_dwWidth = dwWidth;
          m_dwHeight = dwHeight;
          m_dwBPP = dwBPP;
          m_pRawData = pRawData;
        }

        virtual ~CImage();

        unsigned int GetWidth() const {
          return m_dwWidth;
        }

        unsigned int GetHeight() const {
          return m_dwHeight;
        }

        unsigned int GetBitsPerPixel() const {
          return m_dwBPP;
        }

        void* GetRawData() {
          return m_pRawData;
        }

        CImage& operator = ( CImage& cImage ) {
          
          m_dwWidth = cImage.GetWidth();
          m_dwHeight = cImage.GetHeight();
          m_dwBPP = cImage.GetBitsPerPixel();

          if ( cImage.GetRawData() )
          {
            unsigned int dwRawSize = m_dwWidth*m_dwHeight*(m_dwBPP>>3);
            m_pRawData = new char[dwRawSize];
            memcpy( m_pRawData, cImage.GetRawData(), dwRawSize );
          }
          else
            m_pRawData = 0;

          return *this;
        }

protected:

        unsigned int m_dwWidth;
        unsigned int m_dwHeight;
        unsigned int m_dwBPP;
        void* m_pRawData;

private:

};

class CImageLib {

public:
        CImageLib();
        virtual ~CImageLib();

        CImage* LoadFile( char* pszFileName );

protected:

        /* 
         * return:
         * -1 - unknown format
         *  0 - JPEG
         *  1 - PNG
         *  2 - TGA
         *  3 - MIP
         */
        int RecognizeFileFormat( FILE* hFile, unsigned int dwFileLen );
};

extern CImageLib g_cImageLib;

#endif
