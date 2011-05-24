// programming by Yoghurt/Pulse  v4.0
// date 16.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************
// float math / quaternions

#include	<math.h>
#include	"matrix.h"
#include	"quater.h"

/******************************************************************** CODE */

/***************************************************************************/
void qtConvert(const quat_t *q1,quat_t *q)
{
	float s=sin(q1->angle*.5);
	q->w=cos(q1->angle*.5);
	q->x=s*q1->x;
	q->y=s*q1->y;
	q->z=s*q1->z;
}
/***************************************************************************/
void qtMul(const quat_t *qL,const quat_t *qR,quat_t *qq)
{
	qq->w=qL->w*qR->w-qL->x*qR->x-qL->y*qR->y-qL->z*qR->z;
	qq->x=qL->w*qR->x+qL->x*qR->w+qL->y*qR->z-qL->z*qR->y;
	qq->y=qL->w*qR->y+qL->y*qR->w+qL->z*qR->x-qL->x*qR->z;
	qq->z=qL->w*qR->z+qL->z*qR->w+qL->x*qR->y-qL->y*qR->x;
}
/***************************************************************************/
void qtInvMatrix(const quat_t *q,matrix_t *mat)
{
	float s,xs,ys,zs,wx,wy,zz;
	float wz,xx,xy,xz,yy,yz,den;

	den=(q->x*q->x+q->y*q->y+q->z*q->z+q->w*q->w);
	if(den==0.0) s=1.0; else s=2.0/den;

	xs=q->x*s; ys=q->y*s; zs=q->z*s;
	wx=q->w*xs; wy=q->w*ys; wz=q->w*zs;
	xx=q->x*xs; xy=q->x*ys; xz=q->x*zs;
	yy=q->y*ys; yz=q->y*zs; zz=q->z*zs;

	mat->m[0][0]=1.0-(yy+zz); mat->m[0][1]=xy-wz; mat->m[0][2]=xz+wy;
	mat->m[1][0]=xy+wz; mat->m[1][1]=1.0-(xx+zz); mat->m[1][2]=yz-wx;
	mat->m[2][0]=xz-wy; mat->m[2][1]=yz+wx; mat->m[2][2]=1.0-(xx+yy);
}
/***************************************************************************/
void qtToMatrix(const quat_t *a,matrix_t *mat)
{
	float x2,y2,z2,wx,wy,wz,xx,xy,xz,yy,yz,zz;

	x2=a->x+a->x;
	y2=a->y+a->y;
	z2=a->z+a->z;
	wx=a->w*x2;
	wy=a->w*y2;
	wz=a->w*z2;
	xx=a->x*x2;
	xy=a->x*y2;
	xz=a->x*z2;
	yy=a->y*y2;
	yz=a->y*z2;
	zz=a->z*z2;

	mat->m[0][0]=1-(yy+zz);
	mat->m[0][1]=xy+wz;
	mat->m[0][2]=xz-wy;

	mat->m[1][0]=xy-wz;
	mat->m[1][1]=1-(xx+zz);
	mat->m[1][2]=yz+wx;

	mat->m[2][0]=xz+wy;
	mat->m[2][1]=yz-wx;
	mat->m[2][2]=1-(xx+yy);
}
/***************************************************************************/
