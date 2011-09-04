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

#if !defined (_SPIN_ZOOM_HPP_)
#define _SPIN_ZOOM_HPP_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include "Effect.hpp"
#include "sinus.hpp"

#include "TexManager.hpp"

#include <GLES/gl.h>

class CSpin {

public:
    CSpin() {
      m_cPosition = CVector(0, 0, 0);
      m_fAngle = 0;
      m_fAngleChange = 0;
      m_fScaleChange = 0;
    };

    void Init( float fAngle0, float fAngleChange, float fScaleChange, CSinWave cSinWave );

    void Render( float fTime );

protected:
    CVector m_cPosition;

    float m_fAngle;
    float m_fAngleChange;

    float m_fScaleChange;

    CSinWave m_cSinWave;
};

class CSpinZoom : public CEffect {

public:
    CSpinZoom();
    virtual ~CSpinZoom();

    virtual void Do( float fTime, float fTimeStart = 0 );

    static void PutQuad();
protected:
    float m_fTime;

    int m_iTex1;
    int m_iTex2;

    CSpin* m_pSpins;
    int m_iSpins;
};

#endif 
