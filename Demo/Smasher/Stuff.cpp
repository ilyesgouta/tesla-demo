
#include "stdafx.h"
#include "Stuff.hpp"

/*******************************************************************************************/
void CDarkQuads::Render( int iSeed, CColor& cCol ) {

        int iHeight;
        int iY;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0, 640, 0, 480, -1, 1 );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glDisable( GL_TEXTURE_2D );
        glDisable( GL_DEPTH_TEST );
        glDisable( GL_CULL_FACE );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glColor4fv( (float*)&cCol );

        glBegin( GL_QUADS );

        for ( int i = 0; i != iSeed; i++ )
        {
          iY = rand()%480;
          iHeight = rand()%8 + 1;

          glVertex3f(   0, iY + iHeight, 0 );
          glVertex3f( 640, iY + iHeight, 0 );
          glVertex3f( 640, iY - iHeight, 0 );
          glVertex3f(   0, iY - iHeight, 0 );
        }

        glEnd();
}
/*******************************************************************************************/

