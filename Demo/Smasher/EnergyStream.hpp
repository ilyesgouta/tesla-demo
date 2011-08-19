
#include "Effect.hpp"


class CFlareStream {

public:
        CFlareStream();
        ~CFlareStream();

        void Init( int iSeed, int iGLFlareTex, CVector& cBasePos, float fSpeed );

        void Render( float fTime, CVector& cBaseX, CVector& cBaseY, float fAlpha );

protected:

        CVector* m_pFlares;
        int m_iFlares;
        int m_iGLFlareTex;

        float m_fSpeed;
};

class CEnergyStream : public CEffect {

public:
        CEnergyStream();
        virtual ~CEnergyStream();

        virtual void Do( float fTime, float fTimeStart = 0 );

protected:
        
        int m_iGLTex1;
        int m_iGLTex2;

        CFlareStream* m_pFStreams;
        int m_iFStreams;
};