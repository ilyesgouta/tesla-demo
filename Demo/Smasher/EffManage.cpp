//
// tesla-demo, an OpenGL|ES 1.1 port of Sunflower's original Tesla demo.
//
// Original Tesla code, Copyright (C) 2000 Sunflower
// Linux EGL/X11 port by Ilyes Gouta, ilyes.gouta@gmail.com
//
// Port released under GNU General Public License with permission from
// Konrad Zagorowicz, original developer from Sunflower.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifdef WIN32
#include "stdafx.h"
#endif

#include <string.h>

#include "EffManage.hpp"

CEffManager::CEffManager()
{
    memset( m_aEffects, 0, sizeof(m_aEffects) );
    m_iEffects = 0;

    m_aTFinish = 0;
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

    if (m_aTFinish < fTimeEnd)
        m_aTFinish = fTimeEnd;

    m_iEffects++;
    return true;
}

void CEffManager::PlayEffects( float fTime, bool &finished )
{
    finished = (fTime >= m_aTFinish);

    for ( int i = 0; i != m_iEffects; i++ )
        if ( fTime > m_aTStart[i] && fTime < m_aTEnd[i] )
            m_aEffects[i]->Do( fTime, m_aTStart[i] );
}
