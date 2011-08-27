
#if !defined (_FACE_TRAILS_)
#define _FACE_TRAILS_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include "TexManager.hpp"
#include "Effect.hpp"

#include <GLES/gl.h>

class CShadeBall : public CEffect {

typedef struct __attribute__ ((packed)) CShadeBallVertex {
    float x, y, z;
} CShadeBallVertex;

typedef struct __attribute__ ((packed)) CShadeBallTex {
    float s0, t0;
} CShadeBallTex;

public:
    CShadeBall();
    virtual ~CShadeBall();

    virtual void Do( float fTime, float fTimeStart );

protected:
    int m_iGLTex;
    int m_iGLLayer1;


    CVector* m_pVertices;
    CTexel* m_pUV;
    int m_iVertices;

    int* m_pFaces;
    int m_iFaces;

    void MakeSphere();
    void PutQuad( CTexel cUVPos, float fScale );

#ifdef GL_VERSION_ES_CM_1_1
private:
    CShadeBallVertex m_Vertex[4];
    CShadeBallTex m_Texture[4];
#endif

};

#endif
