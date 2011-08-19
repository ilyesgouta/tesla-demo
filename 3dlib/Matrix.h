// programming by Yoghurt/Pulse  v4.0
// date 16.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************

#ifndef _MATRIX_H_INCLUDED_
#define _MATRIX_H_INCLUDED_

//#pragma warning(disable: 4201)

#include	<math.h>
#include	"Vector.h"

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


typedef struct matrix3x3_s
{
	float	m[3][3];
} matrix3x3_t;


typedef union matrix_u
{
	float		m[4][3];
	struct{
	  matrix3x3_t	mat;
	  vector_t	vec;
	};
	struct{
	  float 	a,b,c;
	  float 	d,e,f;
	  float 	g,h,i;
	  float 	j,k,l;
	};
	struct{
	  float 	o,p,q;
	  float 	r,s,t;
	  float 	u,w,v;
	  float 	x,y,z;
	};
} matrix_t;

extern void mtrxMulConst(matrix_t *m,float Q);
extern void mtrxMulMatrix(matrix_t *m1,const matrix_t *m2);
extern void mtrxMulMatrix2(matrix_t *m1,const matrix_t *m,const matrix_t *m2);
extern void mtrxVecMulMatrix(vector_t *v,const matrix_t *m);
extern void mtrxVecMulMatrix2(vector_t *v,const vector_t *vec,const matrix_t *m);
extern void mtrxVecMulMatrix_2(vector_t *v,const vector_t *vec,const matrix_t *m);
extern void mtrxInvert(matrix_t *m);
extern void mtrxTranslate(matrix_t *m,const vector_t *v);
extern void mtrxScale(matrix_t *m,const vector_t *v);
extern void mtrxIdentity(matrix_t *m);
extern void mtrxTranspose(float (*matrix)[4][4]);

#ifdef __cplusplus
};
#endif
#endif

