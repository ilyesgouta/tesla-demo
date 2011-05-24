
#if !defined (_FFD_ENV_VECTOR_HPP_)
#define _FFD_ENV_VECTOR_HPP_

#include "Effect.hpp"

class CFFDEnv : public CEffect {

public:
        CFFDEnv();
        virtual ~CFFDEnv();

        virtual void Do( float fTime, float fTimeStrat );

protected:

        scene_t* m_pScene;

        int m_iGLTex1;
        int m_iGLTex2;
        int m_iGLTexBlend;

        CVector* m_pVertices;
        CVector* m_pNormals;
        CTexel* m_pUV;
        CTexel* m_pEnvUV;
        int m_iVertices;

        int* m_pFaces;
        int m_iFaces;
};

#endif /* _FACE_MORPH_HPP_ */s