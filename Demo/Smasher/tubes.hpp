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

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"
#include "base3d/CVector.hpp"

#include "TexManager.hpp"

#include "Effect.hpp"

#include <GLES/gl.h>

#include "tessellator.hpp"

class CTubes : public CEffect {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    CTubes();
    ~CTubes();

    virtual void Do( float fTime, float fTimeStart = 0 );

protected:
    float m_fTime;

    void RenderTube( float fScale, float fAngle0 );

    void MakeTubes( float fAlpha );

    int m_iGLTex1;
    int m_iGLTex1a;
    int m_iGLTex2;

    CObjectNode* m_pTable;
    CSplinedObject* m_pSObject;

    int m_iTubeVertices;
    int m_iTubeFaces;

    CVector* m_pTubeVertices;
    float* m_pTubeUV;
    int* m_pTubeFaces;

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex m_Vertex[4];
    CTex m_Texture[4];
#endif
};
