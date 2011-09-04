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
#include "load3ds/Load3ds.h"

#include "TexManager.hpp"

#include "Effect.hpp"

#include <GLES/gl.h>

class CFlareStream {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    CFlareStream();
    ~CFlareStream();

    void Init( int iSeed, int iGLFlareTex, const CVector& cBasePos, float fSpeed );

    void Render( float fTime, CVector& cBaseX, CVector& cBaseY, float fAlpha );

protected:
    CVector* m_pFlares;
    int m_iFlares;
    int m_iGLFlareTex;

    float m_fSpeed;

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex m_Vertex[4];
    CTex m_Texture[4];
#endif
};

class CEnergyStream : public CEffect {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    CEnergyStream();
    virtual ~CEnergyStream();

    virtual void Do( float fTime, float fTimeStart = 0 );

protected:        
    int m_iGLTex1;
    int m_iGLTex2;

    CFlareStream* m_pFStreams;
    int m_iFStreams;

    void PutQuad( CTexel cUVPos );

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex m_Vertex[4];
    CTex m_Texture[4];
#endif
};
