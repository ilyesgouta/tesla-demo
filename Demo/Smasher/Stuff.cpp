
#ifdef WIN32
#include "stdafx.h"
#endif

#include <stdlib.h>

#include "base3d/CColor.hpp"
#include "Stuff.hpp"

#include <GLES/gl.h>

void CDarkQuads::Render( int iSeed, CColor& cCol ) {

        int iHeight;
        int iY;

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrthof( 0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f );

        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        glDisable( GL_TEXTURE_2D );
        glDisable( GL_DEPTH_TEST );
        glDisable( GL_CULL_FACE );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glColor4f( cCol.fR, cCol.fG, cCol.fB, cCol.fA );

        // TODO: port to GL ES 1.1
        //glBegin( GL_QUADS );

        for ( int i = 0; i != iSeed; i++ )
        {
          iY = rand()%480;
          iHeight = rand()%8 + 1;

          //glVertex3f(   0, iY + iHeight, 0 );
          //glVertex3f( 640, iY + iHeight, 0 );
          //glVertex3f( 640, iY - iHeight, 0 );
          //glVertex3f(   0, iY - iHeight, 0 );
        }

        //glEnd();
}
