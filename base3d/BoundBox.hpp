
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

