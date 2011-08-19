
#if !defined (_FFD_ENV_VECTOR_HPP_)
#define _FFD_ENV_VECTOR_HPP_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"
#include "load3ds/Load3ds.h"

#include "TexManager.hpp"

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

        unsigned short* m_pFaces; // TODO: should this be signed?
        int m_iFaces;
};

#endif /* _FACE_MORPH_HPP_ */
