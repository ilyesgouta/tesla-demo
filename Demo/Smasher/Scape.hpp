

#if !defined (_SCAPE_HPP_)
#define _SCAPE_HPP_

#include "Effect.hpp"

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