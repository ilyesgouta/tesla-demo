
#include "tessellator.hpp"
#include "Effect.hpp"

class CTubes : public CEffect {

public:
        CTubes();
        ~CTubes();

        virtual void Do( float fTime, float fTimeStart = 0 );

protected:
        float m_fTime;

        void RenderTube( float fScale, float fAngle0 );

        void MakeTubes( float fAlpha );

        int m_iGLTex1;
        int m_iGLTex1a;
        int m_iGLTex2;

        CObjectNode* m_pTable;
        CSplinedObject* m_pSObject;

        int m_iTubeVertices;
        int m_iTubeFaces;

        CVector* m_pTubeVertices;
        float* m_pTubeUV;
        int* m_pTubeFaces;

};

