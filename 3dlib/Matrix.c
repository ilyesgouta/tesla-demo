// programming by Yoghurt/Pulse  v4.0
// date 16.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************
// float math / matrices

#include <stdio.h>
#include <string.h>
#include	"Vector.h"
#include	"Matrix.h"

/******************************************************************** CODE */

/***************************************************************************/
void mtrxMulConst(matrix_t *m,float Q)
{
	m->m[0][0]*=Q; m->m[0][1]*=Q; m->m[0][2]*=Q;
	m->m[1][0]*=Q; m->m[1][1]*=Q; m->m[1][2]*=Q;
	m->m[2][0]*=Q; m->m[2][1]*=Q; m->m[2][2]*=Q;
	m->m[3][0]*=Q; m->m[3][1]*=Q; m->m[3][2]*=Q;
}
/***************************************************************************/
void mtrxMulMatrix(matrix_t *m1,const matrix_t *m2)
{
	matrix_t	m=*m1;

	m1->m[0][0]=m.a*m2->o+m.b*m2->r+m.c*m2->u;
	m1->m[0][1]=m.a*m2->p+m.b*m2->s+m.c*m2->w;
	m1->m[0][2]=m.a*m2->q+m.b*m2->t+m.c*m2->v;

	m1->m[1][0]=m.d*m2->o+m.e*m2->r+m.f*m2->u;
	m1->m[1][1]=m.d*m2->p+m.e*m2->s+m.f*m2->w;
	m1->m[1][2]=m.d*m2->q+m.e*m2->t+m.f*m2->v;

	m1->m[2][0]=m.g*m2->o+m.h*m2->r+m.i*m2->u;
	m1->m[2][1]=m.g*m2->p+m.h*m2->s+m.i*m2->w;
	m1->m[2][2]=m.g*m2->q+m.h*m2->t+m.i*m2->v;

	m1->m[3][0]=m2->x+m.j*m2->o+m.k*m2->r+m.l*m2->u;
	m1->m[3][1]=m2->y+m.j*m2->p+m.k*m2->s+m.l*m2->w;
	m1->m[3][2]=m2->z+m.j*m2->q+m.k*m2->t+m.l*m2->v;
}
/***************************************************************************/
void mtrxMulMatrix2(matrix_t *m1,const matrix_t *m,const matrix_t *m2)
{
	m1->m[0][0]=m->a*m2->o+m->b*m2->r+m->c*m2->u;
	m1->m[0][1]=m->a*m2->p+m->b*m2->s+m->c*m2->w;
	m1->m[0][2]=m->a*m2->q+m->b*m2->t+m->c*m2->v;

	m1->m[1][0]=m->d*m2->o+m->e*m2->r+m->f*m2->u;
	m1->m[1][1]=m->d*m2->p+m->e*m2->s+m->f*m2->w;
	m1->m[1][2]=m->d*m2->q+m->e*m2->t+m->f*m2->v;

	m1->m[2][0]=m->g*m2->o+m->h*m2->r+m->i*m2->u;
	m1->m[2][1]=m->g*m2->p+m->h*m2->s+m->i*m2->w;
	m1->m[2][2]=m->g*m2->q+m->h*m2->t+m->i*m2->v;

	m1->m[3][0]=m2->x+m->j*m2->o+m->k*m2->r+m->l*m2->u;
	m1->m[3][1]=m2->y+m->j*m2->p+m->k*m2->s+m->l*m2->w;
	m1->m[3][2]=m2->z+m->j*m2->q+m->k*m2->t+m->l*m2->v;
}
/***************************************************************************/
void mtrxVecMulMatrix(vector_t *v,const matrix_t *m)
{
	vector_t	vec=*v;

	v->x=vec.x*m->a+vec.y*m->d+vec.z*m->g+m->j;
	v->y=vec.x*m->b+vec.y*m->e+vec.z*m->h+m->k;
	v->z=vec.x*m->c+vec.y*m->f+vec.z*m->i+m->l;
}
/***************************************************************************/
void mtrxVecMulMatrix2(vector_t *v,const vector_t *vec,const matrix_t *m)
{
	v->x=vec->x*m->a+vec->y*m->d+vec->z*m->g+m->j;
	v->y=vec->x*m->b+vec->y*m->e+vec->z*m->h+m->k;
	v->z=vec->x*m->c+vec->y*m->f+vec->z*m->i+m->l;
}
/***************************************************************************/
void mtrxVecMulMatrix_(vector_t *v,const matrix_t *m)
{
	vector_t	vec=*v;

	v->x=vec.x*m->a+vec.y*m->d+vec.z*m->g;
	v->y=vec.x*m->b+vec.y*m->e+vec.z*m->h;
	v->z=vec.x*m->c+vec.y*m->f+vec.z*m->i;
}
/***************************************************************************/
void mtrxVecMulMatrix_2(vector_t *v,const vector_t *vec,const matrix_t *m)
{
	v->x=vec->x*m->a+vec->y*m->d+vec->z*m->g;
	v->y=vec->x*m->b+vec->y*m->e+vec->z*m->h;
	v->z=vec->x*m->c+vec->y*m->f+vec->z*m->i;
}
/***************************************************************************/
void mtrxInvert(matrix_t *m)
{
	float	a,b,c,d,e,f,g,h,i,j,k,l;
	float	W;

	a=m->m[0][0];b=m->m[0][1];c=m->m[0][2];
	d=m->m[1][0];e=m->m[1][1];f=m->m[1][2];
	g=m->m[2][0];h=m->m[2][1];i=m->m[2][2];
	j=m->m[3][0];k=m->m[3][1];l=m->m[3][2];

	W=1.0f/(a*(e*i-f*h)-(b*(d*i-f*g)+c*(e*g-d*h)));

	m->m[0][0]=(e*i-f*h)*W;
	m->m[0][1]=(c*h-b*i)*W;
	m->m[0][2]=(b*f-c*e)*W;

	m->m[1][0]=(f*g-d*i)*W;
	m->m[1][1]=(a*i-c*g)*W;
	m->m[1][2]=(c*d-a*f)*W;

	m->m[2][0]=(d*h-e*g)*W;
	m->m[2][1]=(b*g-a*h)*W;
	m->m[2][2]=(a*e-b*d)*W;

	m->m[3][0]=(e*(g*l-i*j)+f*(h*j-g*k)-d*(h*l-i*k))*W;
	m->m[3][1]=(a*(h*l-i*k)+b*(i*j-g*l)+c*(g*k-h*j))*W;
	m->m[3][2]=(b*(d*l-f*j)+c*(e*j-d*k)-a*(e*l-f*k))*W;
}
/***************************************************************************/
void mtrxTranslate(matrix_t *m,const vector_t *v)
{
	int	Q;

	for(Q=0; Q!=9; Q++) ((int *)m)[Q]=0;
	m->vec=*v;
}
/***************************************************************************/
void mtrxScale(matrix_t *m,const vector_t *v)
{
	m->vec.x=m->vec.y=m->vec.z=0;
	m->mat.m[0][0]=v->x;
	m->mat.m[1][1]=v->y;
	m->mat.m[2][2]=v->z;
}
/***************************************************************************/
void mtrxIdentity(matrix_t *matrix)
{
	int q;

	for(q=0; q!=9; q++)
	  ((float *)matrix)[q]=0;

	matrix->m[0][0]=1.; matrix->m[1][1]=1.; matrix->m[2][2]=1.;
}
/***************************************************************************/
void mtrxTranspose(float (*matrix)[4][4])
{
	int	q;
	float	tmp[4][4];

	memcpy(tmp,*matrix,sizeof(float)*16);

	for(q=0; q!=4; q++)
	{
	  (*matrix)[0][q]=tmp[q][0];
	  (*matrix)[1][q]=tmp[q][1];
	  (*matrix)[2][q]=tmp[q][2];
	  (*matrix)[3][q]=tmp[q][3];
	}

}
/***************************************************************************/

