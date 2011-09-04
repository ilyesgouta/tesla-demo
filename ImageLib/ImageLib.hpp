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
