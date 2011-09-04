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


#if !defined (_CGridNode_hpp_)
#define _CGridNode_hpp_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"
#include "base3d/Camera.hpp"

#include <GLES/gl.h>

class CGridNode {

public:
friend class CGridTable;

    CGridNode() {
        m_dwTerrainBegin = 0;
        m_cBoundMax = CVector(-1e30f, -1e30f, -1e30f);
        m_cBoundMin = CVector( 1e30f,  1e30f,  1e30f);

        m_aSubGrid[0] = m_aSubGrid[1] = m_aSubGrid[2] = m_aSubGrid[3] = 0;
    };

protected:
    unsigned int m_dwTerrainBegin;
    CVector m_cBoundMin, m_cBoundMax;

    CGridNode* m_aSubGrid[4];
};


class CGridTable {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    CGridTable() {
        m_pGrid = 0;
        m_dwGridResX = m_dwGridResZ = 0;
        m_dwNodeResX = m_dwNodeResZ = 0;
        m_fNodeSizeX = m_fNodeSizeZ = 0;
    }

    ~CGridTable() {
        if ( m_pGrid )
            delete[] m_pGrid;
    };

    void Init( unsigned int dwNodeX, unsigned int dwNodeZ, float fNodeSize, CVector* pMapVertices, unsigned int dwMapResX, unsigned int dwMapResZ );

    /* returns height at (fX, fZ) and fills normal vector, pNormal may be NULL */
    float GetSample( CVector* pNormal, const float fX, const float fZ ) const;

    void SetTexture( unsigned int dwGLTexName, int iTexture ) {
        m_aGLTex[iTexture] = dwGLTexName;
    }

    void Render( CCamera& cCamera );

protected:
    /* grid */
    CGridNode* m_pGrid;

    /* ilosc gridow */
    unsigned int m_dwGridResX, m_dwGridResZ;

    /* wielkosci jednego node'a (w oczkach siatki) */
    unsigned int m_dwNodeResX, m_dwNodeResZ;

    /* wielkosc pojedynczego node'a */
    float m_fNodeSizeX, m_fNodeSizeZ;

    /* szerokosc mapy w oczkach siatki */
    unsigned int m_dwMapResX;
    unsigned int m_dwMapResZ;
    CVector* m_pMap;

    /* textury */
    unsigned int m_aGLTex[4];

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex *m_Vertex;
    CTex *m_Texture;
#endif
};

#endif /* _CGridNode_hpp_ */
