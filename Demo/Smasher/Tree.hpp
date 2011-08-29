
#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"
#include "load3ds/Load3ds.h"

#include "TexManager.hpp"
#include "MainFrame/MainFrame.hpp"

#include "Effect.hpp"

#include "ffd.h"

#include <GLES/gl.h>

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


        unsigned short* m_pFaces; // TODO: this should be signed?
        int m_iFaces;

        int m_iGLTex;
        int m_iGLTex1;


        CFFD m_cFFD;

        CVector m_aDeform[5*5*5];
};
