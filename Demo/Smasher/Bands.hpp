#ifndef __BANDS_HPP
#define __BANDS_HPP

#include "Effect.hpp"


#define BAND_SEGMENTS 32
#define BAND_NEAR_PLANE -1.0f
#define BAND_FAR_PLANE -50.0f


class CBand {
public:
 CVector aPts[BAND_SEGMENTS+1][2];
 float aAngles[BAND_SEGMENTS+1];
 int aDraw[BAND_SEGMENTS+1];
 float fBandWidth;
 float fSpeedFactor;
 
 CBand(float fNewBandWidth,
       float fNewSF);
 void Render(float fAlpha = 1.0f);
 void Move(float fMove);
};

class CBands : public CEffect {
public:
 int nBands;
 CBand **aBands;
 unsigned int nTex;
 float fLastTime;
 
 CBands(int nNewBands = 40);
 ~CBands();
 void Render(void);
 void Move(float fMove);

 void Do(float fTime, float fTimeStart);
};

#endif /* __BANDS_HPP */

