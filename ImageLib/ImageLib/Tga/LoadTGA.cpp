
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