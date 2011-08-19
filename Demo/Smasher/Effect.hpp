

#if !defined (_EFFECT_HPP_)
#define _EFFECT_HPP_

class CEffect {

public: 
        CEffect() {}
        virtual ~CEffect() {}

        virtual void Do( float fTime, float fTimeStart = 0 ) = 0;
};

#endif /* _EFFECT_HPP_ */