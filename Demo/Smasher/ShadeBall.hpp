
#if !defined (_FACE_TRAILS_)
#define _FACE_TRAILS_

#include "Effect.hpp"

class CShadeBall : public CEffect {

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

};

#endif
