
#if !defined (_SPIN_ZOOM_HPP_)
#define _SPIN_ZOOM_HPP_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include "Effect.hpp"
#include "sinus.hpp"

#include "Effect.hpp"

#include "TexManager.hpp"

#include <GLES/gl.h>

class CSpin {

public:
    CSpin() {
      m_cPosition = CVector(0, 0, 0);
      m_fAngle = 0;
      m_fAngleChange = 0;
      m_fScaleChange = 0;
    };

    void Init( float fAngle0, float fAngleChange, float fScaleChange, CSinWave cSinWave );

    void Render( float fTime );

protected:
    CVector m_cPosition;

    float m_fAngle;
    float m_fAngleChange;

    float m_fScaleChange;

    CSinWave m_cSinWave;
};

typedef struct __attribute__ ((packed)) CSpinZoomVertex {
    float x, y, z;
} CSpinZoomVertex;

typedef struct __attribute__ ((packed)) CSpinZoomTex {
    float s0, t0;
} CSpinZoomTex;

class CSpinZoom : public CEffect {

public:
    CSpinZoom();
    virtual ~CSpinZoom();

    virtual void Do( float fTime, float fTimeStart = 0 );

    static void PutQuad();
protected:
    float m_fTime;

    int m_iTex1;
    int m_iTex2;

    CSpin* m_pSpins;
    int m_iSpins;
#ifdef GL_VERSION_ES_CM_1_1
private:
    static CSpinZoomVertex s_Vertex[4];
    static CSpinZoomTex s_Texture[4];
#endif
};

#endif 
