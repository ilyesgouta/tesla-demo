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
#include "load3ds/Load3ds.h"

#include "TexManager.hpp"
#include "MainFrame/MainFrame.hpp"

#include "Effect.hpp"

#include "ffd.h"

#include <GLES/gl.h>

class CTree : public CEffect {

public:
    CTree();
    virtual ~CTree();

    virtual void Do( float fTime, float fTimeStart = 0 );

protected:
    scene_t* m_pScene;

    CVector* m_pVertices;
    CTexel* m_pUVMap;
    int m_iVertices;

    unsigned short* m_pFaces;
    int m_iFaces;

    int m_iGLTex;
    int m_iGLTex1;

    CFFD m_cFFD;

    CVector m_aDeform[5*5*5];
};
