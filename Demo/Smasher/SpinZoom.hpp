
#if !defined (_SPIN_ZOOM_HPP_)
#define _SPIN_ZOOM_HPP_

#include "Effect.hpp"
#include "sinus.hpp"

class CSpin {

public:
        CSpin() {
          m_cPosition = CVector(0, 0, 0);
          m_fAngle = 0;
          m_fAngleChange = 0;
          m_fScaleChange = 0;        
        };

        void Init( float fAngle0, float fAngleChange, float fScaleChange, CSinWave cSinWave );

        void Render( float fTime );

protected:

        CVector m_cPosition;

        float m_fAngle;
        float m_fAngleChange;

        float m_fScaleChange;

        CSinWave m_cSinWave;
};

class CSpinZoom : public CEffect {

public:
        CSpinZoom();
        virtual ~CSpinZoom();

        virtual void Do( float fTime, float fTimeStart = 0 );

protected:
        float m_fTime;

        int m_iTex1;
        int m_iTex2;

        CSpin* m_pSpins;
        int m_iSpins;
};

#endif 