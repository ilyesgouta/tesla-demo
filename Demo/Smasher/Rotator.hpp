
#ifndef _ROTATOR_HPP_
#define _ROTATOR_HPP_

#include "Effect.hpp"

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

