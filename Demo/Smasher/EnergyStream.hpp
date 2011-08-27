
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

class CFlareStream {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    CFlareStream();
    ~CFlareStream();

    void Init( int iSeed, int iGLFlareTex, const CVector& cBasePos, float fSpeed );

    void Render( float fTime, CVector& cBaseX, CVector& cBaseY, float fAlpha );

protected:
    CVector* m_pFlares;
    int m_iFlares;
    int m_iGLFlareTex;

    float m_fSpeed;

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex m_Vertex[4];
    CTex m_Texture[4];
#endif
};

class CEnergyStream : public CEffect {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    CEnergyStream();
    virtual ~CEnergyStream();

    virtual void Do( float fTime, float fTimeStart = 0 );

protected:        
    int m_iGLTex1;
    int m_iGLTex2;

    CFlareStream* m_pFStreams;
    int m_iFStreams;

    void PutQuad( CTexel cUVPos );

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex m_Vertex[4];
    CTex m_Texture[4];
#endif
};
