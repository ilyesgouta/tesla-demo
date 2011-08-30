
#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include "TexManager.hpp"
#include "Effect.hpp"

#include <GLES/gl.h>

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

    unsigned short* m_pLines;
    int m_iLines;

    int m_iGLTexName;
    int m_iGLFlareName;

    CFFD* m_pFFD;

    void CreateMesh( int iHRes, int iVRes, float fSizeX, float fSizeY );
};
