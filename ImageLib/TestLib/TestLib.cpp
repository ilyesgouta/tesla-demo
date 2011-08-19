
#include <windows.h>
#include "../ImageLib.hpp"

int WINAPI WinMain( HINSTANCE hi, HINSTANCE hpi, LPSTR lpCmdLine, int iShowCmd ) {


        CImage* pImage;

        pImage = g_cImageLib.LoadFile( "test.png" );


        return 0;
}