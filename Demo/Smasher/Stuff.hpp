
#if !defined (_STUFF_HPP_)
#define _STUFF_HPP_

class CDarkQuads {

public: 
        CDarkQuads() {};

        void Render( int iSeed, CColor& cColor /*= CColor(0, 0, 0, .2)*/ );

protected:

        int m_iSeed;
};

#endif
