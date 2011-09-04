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

#include <stdio.h>
#include "../../ImageLib.hpp"
#include "LoadTGA.hpp"


CImage* ReadTGA( FILE* hFile, unsigned int dwFileLen ) {

#pragma pack(push)
#pragma pack(1)

class CTGAHeader {
public:
        unsigned char bIDLen;
        unsigned char bColorMapType;
        unsigned char bImageTypeCode;
        unsigned char aColorMapSpec[5];
        unsigned short wXOrigin;
        unsigned short wYOrigin;
        unsigned short wWidth;
        unsigned short wHeight;
        unsigned char bPelSize;
        unsigned char bImageDescriptor;
};

#pragma pack(pop)

        CImage* pResult = 0;

        CTGAHeader cHdr;
        unsigned char *p;

        if ( !fread(&cHdr, sizeof(CTGAHeader), 1, hFile) ) return 0;
        fseek( hFile, cHdr.bIDLen, SEEK_CUR );

        unsigned int nWidth = cHdr.wWidth;
        unsigned int nHeight = cHdr.wHeight;

        int nBytes = (cHdr.bPelSize + 7) >> 3;
        p = new unsigned char[nWidth*nHeight*nBytes];

        if ( !fread(p, nBytes*nWidth*nHeight, 1, hFile) ) 
        {
          delete[] p;
          return 0;
        }

        unsigned char* pRaw = new unsigned char[nWidth*nHeight*nBytes];
        unsigned int dwStride = nBytes*nWidth;

        for ( unsigned int y = 0; y < nHeight; y++ )
        {
          for ( unsigned int x = 0; x < nWidth; x++ )
          {
            for ( int i = 0; i != nBytes; i++ )
              pRaw[(nHeight - y - 1)*dwStride + x*nBytes + i] = p[y*dwStride + x*nBytes + ((nBytes - i - 2)&3)];
          }
        }

        pResult = new CImage( nWidth, nHeight, nBytes<<3, pRaw );

        delete[] p;
        return pResult;
}