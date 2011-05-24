#include "stdafx.h"
#include "base.h"
#include "ScrewBolt.hpp"


#define SEGMENTS 32
#define NEAR_PLANE -1.0f
#define FAR_PLANE -50.0f

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
     }
 glColor4f(HELIX_COLOR1);     
 glBegin(GL_QUAD_STRIP);
 for (i = 0; i < nSegments; i++)
     {
      glVertex3fv(&(aPts[i][0].fX));
      glVertex3fv(&(aPts[i][1].fX));
     }
 glEnd();
 glColor4f(HELIX_COLOR2);     
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
}


void
CScrewBolt::Do(float fTime, float fTimeStart)
{
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glFrustum(-0.5, 0.5, 
           -0.375, 0.375, 
           -NEAR_PLANE, -FAR_PLANE);
 
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();

 glDisable(GL_CULL_FACE);
 glDisable(GL_LIGHTING);
 glDisable(GL_TEXTURE_2D);
 glDisable(GL_DEPTH_TEST);
 glEnable(GL_BLEND);
 glBlendFunc(GL_SRC_ALPHA, GL_ONE);


 glPushMatrix();
 glRotatef(45.0, 0.0, 0.0, 1.0);
 glTranslatef(0.0, 0.0, -5.0);
 glRotatef(60.0, 1.0, 0.0, 0.0);
 glTranslatef(0.0, 0.0, 5.0);
 glRotatef(fTime * 200.0, 0.0, 0.0, 1.0);
 glLineWidth(5.0);
 DrawHelix(10.0, 
           0.3, 
           1.5, fTime * 5.0, 0.2, 5.0,
           5.0, 
           100); 
 glPopMatrix();

}

 
