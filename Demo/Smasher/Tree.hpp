
#include "Effect.hpp"

#include "ffd.h"

class CTree : public CEffect {

public:
        CTree();
        virtual ~CTree();

        virtual void Do( float fTime, float fTimeStart = 0 );

protected:

        scene_t* m_pScene;

        CVector* m_pVertices;
        CTexel* m_pUVMap;
        int m_iVertices;


        int* m_pFaces;
        int m_iFaces;

        int m_iGLTex;
        int m_iGLTex1;


        CFFD m_cFFD;

        CVector m_aDeform[5*5*5];
};