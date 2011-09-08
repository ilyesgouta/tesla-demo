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
#ifndef __BANDS_HPP
#define __BANDS_HPP

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include "TexManager.hpp"
#include "MainFrame/MainFrame.hpp"

#include "Effect.hpp"

#include <GLES/gl.h>

#define BAND_SEGMENTS 32
#define BAND_NEAR_PLANE -1.0f
#define BAND_FAR_PLANE -50.0f


class CBand {

typedef struct __attribute__ ((packed)) CBandVertex {
    float x, y, z;
} CBandVertex;

typedef struct __attribute__ ((packed)) CBandColor {
    float r, g, b, a;
} CBandColor;

typedef struct __attribute__ ((packed)) CBandTex {
    float s0, t0;
} CBandTex;

public:
    CVector aPts[BAND_SEGMENTS+1][2];

    float aAngles[BAND_SEGMENTS+1];
    int aDraw[BAND_SEGMENTS+1];

    float fBandWidth;
    float fSpeedFactor;
 
    CBand(float fNewBandWidth, float fNewSF);

    ~CBand();

    void Render(float fAlpha = 1.0f);
    void Move(float fMove);

#ifdef GL_VERSION_ES_CM_1_1
private:
    CBandVertex m_Vertex[4];
    CBandColor m_Color[4];
    CBandTex m_Texture[4];
#endif
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
