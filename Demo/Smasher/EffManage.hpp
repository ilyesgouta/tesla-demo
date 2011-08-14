
#if !defined (_EFF_MANAGE_HPP_)
#define _EFF_MANAGE_HPP_

#include "Effect.hpp"

#define EFFECTS_MAX 64

class CEffManager {

public:
    CEffManager();
    virtual ~CEffManager();

    bool AddEffect( CEffect* pEffect, float fTimeStart, float fTimeEnd );

    void PlayEffects( float fTime );

protected:
    CEffect* m_aEffects[EFFECTS_MAX];
    float m_aTStart[EFFECTS_MAX];
    float m_aTEnd[EFFECTS_MAX];
    int m_iEffects;
};

#endif /*_EFF_MANAGE_HPP_*/
