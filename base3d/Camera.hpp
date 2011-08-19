
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

