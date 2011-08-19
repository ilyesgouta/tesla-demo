

#include "Effect.hpp"

class CDragon : public CEffect {


public:
        CDragon();
        virtual ~CDragon();

        virtual void Do( float fTime, float fTimeStart );

protected:

        int m_iFlareTex;

        scene_t* m_pScene;

        CVector* m_pMorphedVertices;
        int* m_pMorphedFaces;
        
};