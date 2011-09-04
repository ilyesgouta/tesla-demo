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
