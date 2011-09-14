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

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

void CDarkQuads::Render( int iSeed, CColor& cCol )
{
#if 0
    int iHeight;
    int iY;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrthof( 0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glDisable( GL_TEXTURE_2D );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glColor4f( cCol.fR, cCol.fG, cCol.fB, cCol.fA );

    CVertex vertex[4];

#ifdef GL_VERSION_ES_CM_1_1
    glClientActiveTexture(GL_TEXTURE0);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertex);
#else
    glBegin( GL_QUADS );
#endif

    for ( int i = 0; i != iSeed; i++ )
    {
        iY = rand() % 720;
        iHeight = rand() % 8 + 1;

#ifdef GL_VERSION_ES_CM_1_1
        vertex[0].x = 0;
        vertex[0].y = iY - iHeight;
        vertex[0].z = 0;

        vertex[1].x = 0;
        vertex[1].y = iY + iHeight;
        vertex[1].z = 0;

        vertex[2].x = 1280;
        vertex[2].y = iY - iHeight;
        vertex[2].z = 0;

        vertex[3].x = 1280;
        vertex[3].y = iY + iHeight;
        vertex[3].z = 0;

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
#else
        glVertex3f(   0, iY + iHeight, 0 );
        glVertex3f( 640, iY + iHeight, 0 );
        glVertex3f( 640, iY - iHeight, 0 );
        glVertex3f(   0, iY - iHeight, 0 );
#endif
    }

#ifdef GL_VERSION_ES_CM_1_1
    glDisableClientState(GL_VERTEX_ARRAY);
#else
    glEnd();
#endif
#endif
}
