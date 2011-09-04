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


#if !defined (_CTerrain_hpp_) 
#define _CTerrain_hpp_

#include "GridNode.hpp"

#include "base3d/Camera.hpp"
#include "base3d/CMatrix.hpp"
#include "base3d/Quaternion.hpp"

#include "TexManager.hpp"

class CTerrain {
  
public:
    CTerrain();
    ~CTerrain();

    /* output: ture if success, false if fail */
    bool LoadRawMap( char* pszMapFileName );

    void Render( CCamera& cCamera );
    void Collision();

    float GetSample( CVector* pNormal, const float fX, const float fZ ) {
        return m_pGridTable->GetSample( pNormal, fX, fZ );
    }

protected:
    /* map resolution */
    unsigned int m_dwResX, m_dwResZ;

    /* mesh data */
    CVector* m_pMapVertices;
    int m_nMapVertices;

    /* generates mesh from raw file */
    void GenMeshFromRaw( unsigned char* pMapRawData );

    /* */
    void InitGrid();

    /* grid tables */
    CGridTable* m_pGridTable;
};

#endif /* _CTerrain_hpp_ */





