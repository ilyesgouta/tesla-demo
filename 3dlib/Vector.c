// programming by Yoghurt/Pulse  v4.0
// date 16.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************
// float math / vectors

#include	<math.h>
#include	"Vector.h"

/******************************************************************** CODE */

/***************************************************************************/
void vRotX(vector_t *vert,float Rt_X,int num)
{
	float	COS,SIN,TMPY,TMPZ;

	COS=cos(Rt_X);
	SIN=sin(Rt_X);

	while(num--)
	{
	  TMPY=vert->y;
	  TMPZ=vert->z;
	  vert->y=TMPY*COS+TMPZ*SIN;
	  vert->z=TMPZ*COS-TMPY*SIN;
	  vert++;
	}
}
/***************************************************************************/
void vRotY(vector_t *vert,float Rt_Y,int num)
{
	double	COS,SIN,TMPX,TMPZ;

	COS=cos(Rt_Y);
	SIN=sin(Rt_Y);

	while(num--)
	{
	  TMPX=vert->x;
	  TMPZ=vert->z;
	  vert->x=TMPX*COS-TMPZ*SIN;
	  vert->z=TMPZ*COS+TMPX*SIN;
	  vert++;
	}
}
/***************************************************************************/
void vRotZ(vector_t *vert,float Rt_Z,int num)
{
	float	COS,SIN,TMPX,TMPY;

	COS=cos(Rt_Z);
	SIN=sin(Rt_Z);

	while(num--)
	{
	  TMPX=vert->x;
	  TMPY=vert->y;
	  vert->x=TMPX*COS+TMPY*SIN;
	  vert->y=TMPY*COS-TMPX*SIN;
	  vert++;
	}
}
/***************************************************************************/
