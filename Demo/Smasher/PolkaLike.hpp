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

#ifndef _POLKA_LIKE_HPP_
#define _POLKA_LIKE_HPP_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"
#include "base3d/CVector.hpp"

#include "TexManager.hpp"

#include "Effect.hpp"

#include <GLES/gl.h>

#ifndef pi
#define pi 3.1415926535897932384626433832795
#endif

class TrackElem_c {

friend class Track_c;
public:
    TrackElem_c() {
        m_cDelPos = CVector(0, 0, 0);
        m_cPosition = CVector(0, 0, 0);
        m_fAnlgeZ = 0;
    }

    void Init( CVector& cPos0, CVector& cDelPos, float fAngleZ0 )
    {
        m_cDelPos = cDelPos;
        m_cPosition = cPos0;
        m_fAnlgeZ = fAngleZ0;
    }

    void Update( float fDelTime );

protected:
    CVector m_cDelPos;
    CVector m_cPosition;
    float m_fAnlgeZ;
};

class Track_c {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

typedef struct __attribute__ ((packed)) CColor {
    float r, g, b, a;
} CColor;

public:
    Track_c();

    ~Track_c() {
        if ( m_pTrackElems )
            delete[] m_pTrackElems;
    }

    void Init( int iElems, float fInitAngleChange, float fInitPosChange );
    void Render( float fDelTime, float fTime );

protected:
    TrackElem_c* m_pTrackElems;
    int m_iTrackElems;

    float m_fInitAngleZ;
    float m_fInitAngleChange;

    CVector m_cInitPos;
    float m_fInitPos;
    float m_fInitPosChange;

    int m_triBufSize, m_triCurrentIndex;

    void glPutFace(const CVector& cV1, const CVector& cV2, const CVector& cV3, const CVector& cV4, float alpha);
    void glFlushFaces();

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex *m_Vertex;
    CTex *m_Texture;
    CColor *m_Color;
#endif
};

class PolkaLike_c : public CEffect {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    PolkaLike_c();
    virtual ~PolkaLike_c();

    virtual void Do( float fTime, float fTimeStart = 0 );

protected:
    int m_iTexture;
    int m_iBack;

    Track_c* m_pTracks;
    int m_iTracks;

    void Init();

    void PutQuad( float fZ );

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex m_Vertex[4];
    CTex m_Texture[4];
#endif
};

#endif
