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
// programming by Yoghurt/Pulse  v4.0
// date 16.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************

#ifndef _VECTOR_H_INCLUDED_
#define _VECTOR_H_INCLUDED_

#include	<math.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
#ifdef _DEBUG
#pragma comment (lib,"3dlibD.lib")
#else
#pragma comment (lib,"3dlib.lib")
#endif
*/



typedef struct vector_s
{
	float	x,y,z;
} vector_t;

extern void fMathInit();
extern float fSqrt(float x);
extern float fReciSqrt(float x);

#define vAdd(V,X)		((V)->x+=(X)->x,(V)->y+=(X)->y,(V)->z+=(X)->z)
#define vAdd2(V,X,Y)		((V)->x=(X)->x+(Y)->x,(V)->y=(X)->y+(Y)->y,(V)->z=(X)->z+(Y)->z)

#define vSub(V,X)		((V)->x-=(X)->x,(V)->y-=(X)->y,(V)->z-=(X)->z)
#define vSub2(V,X,Y)		((V)->x=(X)->x-(Y)->x,(V)->y=(X)->y-(Y)->y,(V)->z=(X)->z-(Y)->z)

#define vMul(V,Q)		((V)->x*=(Q),(V)->y*=(Q),(V)->z*=(Q))
#define vMul2(V,X,Q)		((V)->x=(X)->x*(Q),(V)->y=(X)->y*(Q),(V)->z=(X)->z*(Q))

#define vDiv(V,Q)\
{\
	float	P=1./(Q);\
	vMul((V),P);\
}

#define vDiv2(V,X,Q)\
{\
	float	P=1./(Q);\
	vMul2((V),(X),P);\
}

#define vDotProduct(V,X)	((V)->x*(X)->x+(V)->y*(X)->y+(V)->z*(X)->z)
#define vCrossProduct(V,X,Y)	((V)->x=(X)->y*(Y)->z-(X)->z*(Y)->y,\
				 (V)->y=(X)->z*(Y)->x-(X)->x*(Y)->z,\
				 (V)->z=(X)->x*(Y)->y-(X)->y*(Y)->x)

#define vLength(V)		(sqrt((V)->x*(V)->x+(V)->y*(V)->y+(V)->z*(V)->z))
#define vLength2(V)		(((V)->x*(V)->x+(V)->y*(V)->y+(V)->z*(V)->z))

#define vNormalize(V)\
{\
	register double dTmp=1./sqrt(vDotProduct((V),(V)));\
	vMul((V),(float)dTmp);\
}

extern	void	vRotX(vector_t* v,float angle,int num);
extern	void	vRotY(vector_t* v,float angle,int num);
extern	void	vRotZ(vector_t* v,float angle,int num);
extern	float	vDist(vector_t* v1,vector_t* v2);

#ifdef __cplusplus
};
#endif
#endif

