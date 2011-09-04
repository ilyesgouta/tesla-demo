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

#if !defined (SG_Camera_h)
#define SG_Camera_h

#include "CMatrix.hpp"
#include "BoundBox.hpp"

class CCamera {

protected:
    CMatrix m_cViewMatrix;
    CMatrix m_cInvViewMatrix;
    CMatrix m_cProjection;

    /** vector left-right */
    CVector m_stBaseX;

    /** vector up-down */
    CVector m_stBaseY;

    /** vector forward-backward */
    CVector m_stBaseZ;

    /** camera position */
    CVector m_stPosition;

    /** camera parameters */
    float m_fLeft, m_fRight, m_fBottom, m_fTop, m_fNear, m_fFar;

    /** camera frustum points */
    CVector m_aFrustumPoints[8];

    /** camera axis aligned extents */
    CAABoundBox m_stExtents;

    /** some private methods */
    void ComputeFrustumPoints();
    void ComputeExtents();

public:
    CCamera();

    /**
     * nViewMatrix = 1 podana macierz to ViewMatrix
     * w przeciwnym razie inverse view
     */
    void SetView(CMatrix& cMatrix, int nViewMatrix = 1);
    void SetView(const CVector& stRight, const CVector& stUp, const CVector& stForward, const CVector& stPos);

    void SetFrustum(float fLeft, float fRight, float fBottom, float fTop, float fNear, float fFar);

    /** mathod returns axis aligned camra extents */
    CAABoundBox* GetExtents() {
      return &m_stExtents;
    }

    CMatrix* GetCameraMatrix() {
      return &m_cViewMatrix;
    }

    CMatrix* GetInverseCameraMatrix() {
      return &m_cInvViewMatrix;
    }

    CMatrix* GetProjectionMatrix() {
      return &m_cProjection;
    }

    void GetBaseX(CVector& stBaseX) {
      stBaseX = m_stBaseX;
    }

    void GetBaseY(CVector& stBaseY) {
      stBaseY = m_stBaseY;
    }

    void GetBaseZ(CVector& stBaseZ) {
      stBaseZ = m_stBaseZ;
    }

    void GetPositon(CVector& stPosition) {
      stPosition = m_stPosition;
    }
};

extern void Frustum( CMatrix& cDest, float fLeft, float fRight, float fDown, float fUp, float fNear, float fFar );


#endif /* SG_Camera_h */

