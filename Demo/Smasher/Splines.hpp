

#if !defined (_SPLINES_HPP_)
#define _SPLINES_HPP_

#include "Effect.hpp"


class CSplineTrail {

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