
#ifndef _ROTATOR_HPP_
#define _ROTATOR_HPP_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include "TexManager.hpp"
#include "Effect.hpp"

#include <GLES/gl.h>

class CTwirl;

class CThing : public CEffect {

public:
    CThing();
    virtual ~CThing();

    virtual void Do( float fTime, float fTimeStart = 0 );

private:
    int m_iGLTexName;
    int m_iGLTex1Name;

    int m_iGLLayer1, m_iGLLayer2, m_iGLLayer3;

    CTexel m_cUVPos;
};

#endif
