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

#include "ImageLib.hpp"
#include "ImageLib/JPEG/Loadjpg.hpp"
#include "ImageLib/Tga/LoadTGA.hpp"
#include "ImageLib/PNG/LoadPNG.hpp"



#define MIN_FILE_LEN 64

/*******************************************************************************************/
CImage::~CImage() {

        if ( m_pRawData ) delete[] m_pRawData;
}
/*******************************************************************************************/




CImageLib g_cImageLib;

/*******************************************************************************************/
CImageLib::CImageLib() {

}
/*******************************************************************************************/
CImageLib::~CImageLib() {

}
/*******************************************************************************************/
CImage* CImageLib::LoadFile( char* pszFileName ) {

        CImage* pResult = 0;

        FILE* hFile = fopen( pszFileName, "rb" );
        if ( !hFile ) return 0;

        fseek( hFile, 0, SEEK_END );
        unsigned int dwFileLen = ftell( hFile );
        fseek( hFile, 0, SEEK_SET );

        switch ( RecognizeFileFormat(hFile, dwFileLen) )
        {
          case 0: // JPEG
            pResult = ReadJPG( hFile, dwFileLen );
            break;

          case 1: // PNG
            pResult = ReadPNG( hFile, dwFileLen );
            break;

          case 2: // TGA
            pResult = ReadTGA( hFile, dwFileLen );
            break;

          case 3: // MIP
            break;

          default: // error;
            break;
        }

        fclose( hFile );

        return pResult;
}
/*******************************************************************************************/
int CImageLib::RecognizeFileFormat( FILE* hFile, unsigned int dwFileLen ) {

        int dwRes = -1;

        unsigned char aBuffer[MIN_FILE_LEN];

        if ( dwFileLen < MIN_FILE_LEN ) return -1;

        fread( aBuffer, MIN_FILE_LEN, 1, hFile );

        if ( *(int*)aBuffer == 0xe0ffd8ff && *((int*)&aBuffer[2] + 1) == 0x4649464a ) dwRes = 0;
        else if ( *(int*)aBuffer == 0x00020000 && *((int*)aBuffer + 1) == 0 ) dwRes = 2;
        else if ( *(int*)aBuffer == 0x474e5089 ) dwRes = 1;
        
        
        fseek( hFile, 0, SEEK_SET );

        return dwRes;
}
/*******************************************************************************************/
