
#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"
#include "base3d/CVector.hpp"
#include "load3ds/Load3ds.h"

#include "TexManager.hpp"

#include "Effect.hpp"

#include <GLES/gl.h>

#include "tessellator.hpp"

class CTubes : public CEffect {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    CTubes();
    ~CTubes();

    virtual void Do( float fTime, float fTimeStart = 0 );

protected:
    float m_fTime;

    void RenderTube( float fScale, float fAngle0 );

    void MakeTubes( float fAlpha );

    int m_iGLTex1;
    int m_iGLTex1a;
    int m_iGLTex2;

    CObjectNode* m_pTable;
    CSplinedObject* m_pSObject;

    int m_iTubeVertices;
    int m_iTubeFaces;

    CVector* m_pTubeVertices;
    float* m_pTubeUV;
    int* m_pTubeFaces;

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex m_Vertex[4];
    CTex m_Texture[4];
#endif
};
