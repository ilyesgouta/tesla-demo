
#if !defined (_SCAPE_HPP_)
#define _SCAPE_HPP_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"

#include "TexManager.hpp"
#include "Effect.hpp"

#include <GLES/gl.h>

class CTerrain;

class CScape : public CEffect {

public:
    CScape();
    virtual ~CScape();

    virtual void Do( float fTime, float fTimeStart = 0 );

private:
    CTerrain* m_pTerrain;
};

#endif
