#ifndef __SCREWBOLT_HPP
#define __SCREWBOLT_HPP

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include "TexManager.hpp"
#include "Effect.hpp"

#include <GLES/gl.h>

#define HELIX_COLOR1 0.8, 0.7, 0.6, 0.3
#define HELIX_COLOR2 0.8, 0.7, 0.6, 1.0

class CScrewBolt : public CEffect {
public:
    float fAngleX, fAngleY;

    CScrewBolt(float fAX = 0.0, float fAY = 0.0)
    {
    }

    void Do(float fTime, float fTimeStart);
};

#endif /* __SCREWBOLT_HPP */

