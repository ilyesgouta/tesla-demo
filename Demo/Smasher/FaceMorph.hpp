
#if !defined (_FACE_MORPH_HPP_)
#define _FACE_MORPH_HPP_

#include "Effect.hpp"
#include "ffd.h"

class CFaceMorph : public CEffect {

public:
        CFaceMorph();
        virtual ~CFaceMorph();

        virtual void Do( float fTime, float fTimeStrat );

protected:

        scene_t* m_pScene;

        int m_iGLTex1;
        int m_iGLTex1a;
        int m_iGLTex2;
        int m_iGLBackTex;
        int m_iGLTexBlend;

        CVector* m_pVertices;
        CVector* m_pNormals;
        CTexel* m_pUV;
        CTexel* m_pEnvUV;
        int m_iVertices;

        int* m_pFaces;
        int m_iFaces;

        CVector m_aDeform[5*5*5];

        int m_iTubeVertices;
        int m_iTubeFaces;

        CVector* m_pTubeVertices;
        float* m_pTubeUV;
        int* m_pTubeFaces;

        void RenderTube( float fScale, float fAngle0 );
};

#endif /* _FACE_MORPH_HPP_ */s