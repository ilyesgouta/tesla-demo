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

#if !defined (_BoundBox_hpp_)
#define _BoundBox_hpp_

#include "CVector.hpp"

class CAABoundBox {

public:
      CAABoundBox() {
        m_cMin = CVector(1e30f, 1e30f, 1e30f);
        m_cMax = CVector(-1e30f, -1e30f, -1e30f);
      }

      bool Collide( CAABoundBox& cTest ) {

        if ( m_cMax.fX < cTest.m_cMin.fX ) return false;
        if ( m_cMin.fX > cTest.m_cMax.fX ) return false;
        if ( m_cMax.fY < cTest.m_cMin.fY ) return false;
        if ( m_cMin.fY > cTest.m_cMax.fY ) return false;
        if ( m_cMax.fZ < cTest.m_cMin.fZ ) return false;
        if ( m_cMin.fZ > cTest.m_cMax.fZ ) return false;

        return true;
      }

      CVector m_cMin;
      CVector m_cMax;
};

#endif

