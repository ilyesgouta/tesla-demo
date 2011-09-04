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

#include "base.h"
#include "ScrewBolt.hpp"

#define SEGMENTS 32
#define NEAR_PLANE -1.0f
#define FAR_PLANE -50.0f

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

/*
 zjebana spiralka przeciwciazowa polozona wzdluz z
*/
void
DrawHelix(float fLen, // dlugosc chujstwa
          float fInRadius, // wewnentrzny promien
          float fOutRadius, // zewnentrzny promien
          float fORPhase,   // modyfikacja zewnentrznego promienia
          float fORMod,     // ..
          float fORScale,   // ..
          float fScale,     // chujwie skala sinusa (gestosc spiralek)
          int nSegments)    // ilosc segmentow
{
    int i;
    float fT, fA;
    float fOR;
    static VERTEX3F aPts[1024][2];

    CVertex *strip = new CVertex[nSegments * 2];
    CVertex *lines = new CVertex[nSegments * 6];

    for (i = 0; i < nSegments; i++)
    {
        fT = (float)i * fLen / (float)nSegments;
        fA = fT * fScale;
        aPts[i][0].fX = fInRadius * sin(fA);
        aPts[i][0].fY = fInRadius * cos(fA);
        aPts[i][0].fZ = -fT;

        fOR = fOutRadius + fORMod * sin(fORPhase + fT * fORScale);

        aPts[i][1].fX = fOR * sin(fA);
        aPts[i][1].fY = fOR * cos(fA);
        aPts[i][1].fZ = -fT;

        if (!i)
            continue;

        strip[i * 2 + 0].x = aPts[i][0].fX;
        strip[i * 2 + 0].y = aPts[i][0].fY;
        strip[i * 2 + 0].z = aPts[i][0].fZ;

        strip[i * 2 + 1].x = aPts[i][1].fX;
        strip[i * 2 + 1].y = aPts[i][1].fY;
        strip[i * 2 + 1].z = aPts[i][1].fZ;

        strip[i * 2 - 2].x = aPts[i - 1][0].fX;
        strip[i * 2 - 2].y = aPts[i - 1][0].fY;
        strip[i * 2 - 2].z = aPts[i - 1][0].fZ;

        strip[i * 2 - 1].x = aPts[i - 1][1].fX;
        strip[i * 2 - 1].y = aPts[i - 1][1].fY;
        strip[i * 2 - 1].z = aPts[i - 1][1].fZ;

        lines[i * 6 - 6].x = aPts[i - 1][0].fX;
        lines[i * 6 - 6].y = aPts[i - 1][0].fY;
        lines[i * 6 - 6].z = aPts[i - 1][0].fZ;

        lines[i * 6 - 5].x = aPts[i - 1][1].fX;
        lines[i * 6 - 5].y = aPts[i - 1][1].fY;
        lines[i * 6 - 5].z = aPts[i - 1][1].fZ;

        lines[i * 6 - 4].x = aPts[i - 1][0].fX;
        lines[i * 6 - 4].y = aPts[i - 1][0].fY;
        lines[i * 6 - 4].z = aPts[i - 1][0].fZ;

        lines[i * 6 - 3].x = aPts[i][0].fX;
        lines[i * 6 - 3].y = aPts[i][0].fY;
        lines[i * 6 - 3].z = aPts[i][0].fZ;

        lines[i * 6 - 2].x = aPts[i - 1][1].fX;
        lines[i * 6 - 2].y = aPts[i - 1][1].fY;
        lines[i * 6 - 2].z = aPts[i - 1][1].fZ;

        lines[i * 6 - 1].x = aPts[i][1].fX;
        lines[i * 6 - 1].y = aPts[i][1].fY;
        lines[i * 6 - 1].z = aPts[i][1].fZ;
    }

    glColor4f(HELIX_COLOR1);

#ifdef GL_VERSION_ES_CM_1_1
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, strip);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, nSegments * 2);

    glDisableClientState(GL_VERTEX_ARRAY);
#else
    glBegin(GL_QUAD_STRIP);

    for (i = 0; i < nSegments; i++)
    {
        glVertex3fv(&(aPts[i][0].fX));
        glVertex3fv(&(aPts[i][1].fX));
    }

    glEnd();
#endif

    glColor4f(HELIX_COLOR2);

#ifdef GL_VERSION_ES_CM_1_1
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, lines);

    glDrawArrays(GL_LINES, 0, nSegments * 6);

    glDisableClientState(GL_VERTEX_ARRAY);
#else
    glBegin(GL_LINES);

    for (i = 0; i < nSegments-1; i++)
    {
        glVertex3fv(&(aPts[i][0].fX));
        glVertex3fv(&(aPts[i][1].fX));

        glVertex3fv(&(aPts[i  ][0].fX));
        glVertex3fv(&(aPts[i+1][0].fX));

        glVertex3fv(&(aPts[i  ][1].fX));
        glVertex3fv(&(aPts[i+1][1].fX));
    }

    glVertex3fv(&(aPts[i][0].fX));
    glVertex3fv(&(aPts[i][1].fX));

    glEnd();
#endif
}

void
CScrewBolt::Do(float fTime, float fTimeStart)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustumf(-0.5, 0.5,
           -0.375, 0.375,
           -NEAR_PLANE, -FAR_PLANE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();

    glRotatef(fTime * 30.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -5.0);

    glRotatef(fTime * 60.0, 1.0, 0.0, 0.0);
    glRotatef(fTime * 60.0, 0.0, 0.0, 1.0);

    glScalef(0.2f, 0.2f, 0.5 * cos(fTime * 0.2f));
    glTranslatef(0.0, 0.0, 5.0);

    glLineWidth(3.0);

    DrawHelix(10.0,
           0.3,
           1.5, fTime * 5.0, 0.2, 5.0,
           5.0,
           100);

    glPopMatrix();
}
