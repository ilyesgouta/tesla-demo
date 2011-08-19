// programing by Yoghurt
// copyright (C) 1999 by Konrad Zagorowicz


#if !defined(CTexel_hpp)
#define CTexel_hpp

#include "inline3d.hpp"

//************************************************************************************
class CTexel
{
public:
	CTexel() {}
	CTexel(float U, float V) {
	  fU = U; fV = V;
	}

	void ClampUV() {
          clamp(&fU);
          clamp(&fV);
	}

	void ClampU() {
          clamp(&fU);
	}
	  
	void ClampV() {
          clamp(&fV);
	}

        float fU, fV;
	  
};
//************************************************************************************

#endif