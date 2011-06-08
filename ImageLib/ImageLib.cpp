
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
