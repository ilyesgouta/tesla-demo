// programming by Yoghurt/Pulse  v4.0
// date 16.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************

#ifndef _QUAT_H_INCLUDED_
#define _QUAT_H_INCLUDED_

#include	<math.h>

#pragma warning(disable : 4201)

#include	"vector.h"
#include	"matrix.h"

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

typedef union quat_u
{
	struct{
	 float	w,x,y,z;
	};

	struct	{
	  float 	angle;
	  vector_t	vector;
	};
} quat_t;

extern void qtConvert(const quat_t *q,quat_t *q1);
extern void qtMul(const quat_t *qL,const quat_t *qR,quat_t *qq);
extern void qtInvMatrix(const quat_t *q,matrix_t *mat);
extern void qtToMatrix(const quat_t *a,matrix_t *mat);

#ifdef __cplusplus
};
#endif
#endif

