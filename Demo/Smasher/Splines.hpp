

#if !defined (_SPLINES_HPP_)
#define _SPLINES_HPP_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include "TexManager.hpp"
#include "Effect.hpp"

#include <GLES/gl.h>

class CSplineTrail {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    CSplineTrail() {
        m_iGLTex = 0;
        m_iTailLen = 0;
    }

    void Init( int iGLTex, int iTailLen, CVector cXSinParams, CVector cYSinParams, CVector cZSinParams );

    void Render( float fTime );

protected:
    int m_iGLTex;
    int m_iTailLen;

    CVector m_cXSinParams;
    CVector m_cYSinParams;
    CVector m_cZSinParams;
#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex m_Vertex[4];
    CTex m_Texture[4];
#endif
};

class CSplines : public CEffect {

public:
    CSplines();
    virtual ~CSplines();

    virtual void Do( float fTime, float fTimeStart );

protected:  
    int m_iFlareGLTex;
    int m_iGLTex;

    CSplineTrail* m_pSplines;
    int m_iSplines;


    CVector* m_pVertices;
    CTexel* m_pUV;
    int m_iVertices;

    int* m_pFaces;
    int m_iFaces;

    void MakeSphere();
};

#endif 
