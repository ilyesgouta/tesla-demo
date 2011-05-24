// programing by Yoghurt
// copyright (C) 1999 by Konrad Zagorowicz


#if !defined(CColor_hpp)
#define CColor_hpp

//************************************************************************************
class CColor
{
public:
	CColor() {}
	CColor(float R, float G, float B, float A) {
	  fR = R; fG = G; fB = B; fA = A;
	}
	CColor(float R, float G, float B) {
	  fR = R; fG = G; fB = B; fA = 1.0f;
	}

        float fR, fG, fB, fA;

};
//************************************************************************************

#endif