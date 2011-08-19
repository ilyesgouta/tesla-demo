
#include "Effect.hpp"

class CFFD;

class CLinePlane : public CEffect {

public:
        CLinePlane();
        virtual ~CLinePlane();

        virtual void Do( float fTime, float fTimeStart = 0 );

protected:
  
        CVector* m_pVertices;
        CTexel* m_pTexels;
        int m_iVertices;

        int* m_pLines;
        int m_iLines;

        int m_iGLTexName;
        int m_iGLFlareName;

        CFFD* m_pFFD;

        void CreateMesh( int iHRes, int iVRes, float fSizeX, float fSizeY );
};