#ifndef __SCREWBOLT_HPP
#define __SCREWBOLT_HPP

#include "Effect.hpp"

#define HELIX_COLOR1 0.8, 0.7, 0.6, 0.3
#define HELIX_COLOR2 0.8, 0.7, 0.6, 1.0

class CScrewBolt : public CEffect {
public:
 float fAngleX, fAngleY;

 CScrewBolt(float fAX = 0.0, float fAY = 0.0) {
 }

 void Do(float fTime, float fTimeStart);

};

#endif /* __SCREWBOLT_HPP */

