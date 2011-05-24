// coded by Adept/Esteem
// modified by Yoghurt/Pulse

#include	<math.h>
#include	"../3dlib/3dlib.h"

//***************************************************************************
static void CompElementDeriv(float pp,float p,float pn,float *ds,float *dd,float ksm,float ksp,float kdm,float kdp)
{
	float delm, delp;

	delm = p - pp;
	delp = pn - p;
	*ds  = ksm*delm + ksp*delp;
	*dd  = kdm*delm + kdp*delp;
}
//***************************************************************************
static void CompDeriv( key_t *keyp,key_t *key,key_t *keyn )
{
	float tm,cm,cp,bm,bp,tmcm,tmcp,ksm,ksp,kdm,kdp,delm,delp,c;
	float dt,fp,fn;
	dt = .5 * ( keyn->frame - keyp->frame );
	fp = ( key->frame - keyp->frame ) / dt;
	fn = ( keyn->frame - key->frame ) / dt;
	c  = fabs( key->c );
	fp = fp + c - c * fp;
	fn = fn + c - c * fn;
	cm = 1.0 - key->c;
	tm = 0.5 * ( 1.0 - key->t );
	cp = 2.0 - cm;
	bm = 1.0 - key->b;
	bp = 2.0 - bm;
	tmcm = tm*cm;	tmcp = tm*cp;
	ksm = tmcm*bp*fp;	ksp = tmcp*bm*fp;
	kdm = tmcp*bp*fn;	kdp = tmcm*bm*fn;

	CompElementDeriv( keyp->quat.w, key->quat.w, keyn->quat.w,
			&key->ds.w, &key->dd.w, ksm, ksp, kdm, kdp );

	CompElementDeriv( keyp->quat.x, key->quat.x, keyn->quat.x,
			&key->ds.x, &key->dd.x, ksm, ksp, kdm, kdp );

	CompElementDeriv( keyp->quat.y, key->quat.y, keyn->quat.y,
			&key->ds.y, &key->dd.y, ksm, ksp, kdm, kdp );

	CompElementDeriv( keyp->quat.z, key->quat.z, keyn->quat.z,
			&key->ds.z, &key->dd.z, ksm, ksp, kdm, kdp );
}
//***************************************************************************
static void CompDerivFirst( key_t *key,key_t *keyn,key_t *keynn )
{
	float	f20,f10,v20,v10;
	f20 = keynn->frame - key->frame;
	f10 = keyn->frame - key->frame;

	v20 = keynn->quat.w - key->quat.w;
	v10 = keyn->quat.w - key->quat.w;
	key->dd.w = (1-key->t)*(v20*(0.25 - f10/(2*f20)) + (v10 - v20/2)*3/2 + v20/2);

	v20 = keynn->quat.x - key->quat.x;
	v10 = keyn->quat.x - key->quat.x;
	key->dd.x = (1-key->t)*(v20*(0.25 - f10/(2*f20)) + (v10 - v20/2)*3/2 + v20/2);

	v20 = keynn->quat.y - key->quat.y;
	v10 = keyn->quat.y - key->quat.y;
	key->dd.y = (1-key->t)*(v20*(0.25 - f10/(2*f20)) + (v10 - v20/2)*3/2 + v20/2);

	v20 = keynn->quat.z - key->quat.z;
	v10 = keyn->quat.z - key->quat.z;
	key->dd.z = (1-key->t)*(v20*(0.25 - f10/(2*f20)) + (v10 - v20/2)*3/2 + v20/2);
}
//***************************************************************************
static void CompDerivLast( key_t *keypp,key_t *keyp,key_t *key )
{
	float	f20,f10,v20,v10;
	f20 = key->frame - keypp->frame;
	f10 = key->frame - keyp->frame;

	v20 = key->quat.w - keypp->quat.w;
	v10 = key->quat.w - keyp->quat.w;
	key->ds.w = (1-key->t)*(v20*(0.25 - f10/(2*f20)) + (v10 - v20/2)*3/2 + v20/2);

	v20 = key->quat.x - keypp->quat.x;
	v10 = key->quat.x - keyp->quat.x;
	key->ds.x = (1-key->t)*(v20*(0.25 - f10/(2*f20)) + (v10 - v20/2)*3/2 + v20/2);

	v20 = key->quat.y - keypp->quat.y;
	v10 = key->quat.y - keyp->quat.y;
	key->ds.y = (1-key->t)*(v20*(0.25 - f10/(2*f20)) + (v10 - v20/2)*3/2 + v20/2);

	v20 = key->quat.z - keypp->quat.z;
	v10 = key->quat.z - keyp->quat.z;
	key->ds.z = (1-key->t)*(v20*(0.25 - f10/(2*f20)) + (v10 - v20/2)*3/2 + v20/2);
}
//***************************************************************************
static void CompDerivFirst2( key_t *key,key_t *keyn )
{
	float	v;

	v = keyn->quat.w - key->quat.w;
	key->dd.w = v*(1-key->t);

	v = keyn->quat.x - key->quat.x;
	key->dd.x = v*(1-key->t);

	v = keyn->quat.y - key->quat.y;
	key->dd.y = v*(1-key->t);

	v = keyn->quat.z - key->quat.z;
	key->dd.z = v*(1-key->t);
}
//***************************************************************************
static void CompDerivLast2( key_t *keyp,key_t *key )
{
	float	v;
	v = key->quat.w - keyp->quat.w;
	key->ds.w = v*(1-key->t);

	v = key->quat.x - keyp->quat.x;
	key->ds.x = v*(1-key->t);

	v = key->quat.y - keyp->quat.y;
	key->ds.y = v*(1-key->t);

	v = key->quat.z - keyp->quat.z;
	key->ds.z = v*(1-key->t);
}
//***************************************************************************
void PrepareSpline(key_t keys[],int keycnt)
{
	int	n;

	if(keycnt>2)
	{
	  for (n=1; n<keycnt-1; n++)
	    CompDeriv(&keys[n-1],&keys[n],&keys[n+1]);

	  CompDerivFirst(&keys[0],&keys[1],&keys[2]);
	  CompDerivLast(&keys[keycnt-3],&keys[keycnt-2],&keys[keycnt-1]);
	}
	else
	if(keycnt==2)
	{
	  CompDerivFirst2( &keys[0],&keys[1] );
	  CompDerivLast2( &keys[0],&keys[1] );
	}
}
//***************************************************************************
