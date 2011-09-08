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

#if !defined (_FACE_MORPH_HPP_)
#define _FACE_MORPH_HPP_

#include <lib3ds/types.h>
#include <lib3ds/mesh.h>
#include <lib3ds/vector.h>
#include <lib3ds/file.h>

#include "Effect.hpp"
#include "TexManager.hpp"
#include "ffd.h"

class CFaceMorph : public CEffect {

public:
    CFaceMorph();
    virtual ~CFaceMorph();

    virtual void Do( float fTime, float fTimeStrat );

protected:
    Lib3dsFile* m_pScene;

    int m_iGLTex1;
    int m_iGLTex1a;
    int m_iGLTex2;
    int m_iGLBackTex;
    int m_iGLTexBlend;

    CVector* m_pVertices;
    CVector* m_pNormals;
    Lib3dsVector* m_pMeshNormals[5];
    CTexel* m_pUV;
    CTexel* m_pEnvUV;
    int m_iVertices;

    Lib3dsMesh* GetMesh(int id);
    int GetMeshCount();

    unsigned short* m_pFaces;
    int m_iFaces;

    CVector m_aDeform[5 * 5 * 5];

    int m_iTubeVertices;
    int m_iTubeFaces;

    CVector* m_pTubeVertices;
    float* m_pTubeUV;
    unsigned short* m_pTubeFaces;

    void RenderTube( float fScale, float fAngle0 );
};

#endif /* _FACE_MORPH_HPP_ */
