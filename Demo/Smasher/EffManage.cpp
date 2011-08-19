
#ifdef WIN32
#include "stdafx.h"
#endif

#include <string.h>

#include "EffManage.hpp"

CEffManager::CEffManager()
{
    memset( m_aEffects, 0, sizeof(m_aEffects) );
    m_iEffects = 0;
}

CEffManager::~CEffManager()
{
    for ( int i = 0; i != m_iEffects; i++ )
        delete m_aEffects[i];
}

bool CEffManager::AddEffect( CEffect* pEffect, float fTimeStart, float fTimeEnd )
{
    if ( m_iEffects >= EFFECTS_MAX )
        return false;

    m_aEffects[m_iEffects] = pEffect;
    m_aTStart[m_iEffects] = fTimeStart;
    m_aTEnd[m_iEffects] = fTimeEnd;

    m_iEffects++;
    return true;
}        

void CEffManager::PlayEffects( float fTime )
{
    for ( int i = 0; i != m_iEffects; i++ )
        if ( fTime > m_aTStart[i] && fTime < m_aTEnd[i] )
            m_aEffects[i]->Do( fTime, m_aTStart[i] );
}
