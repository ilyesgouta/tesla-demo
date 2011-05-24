// programming by Yoghurt/Pulse  v4.0
// date 09.02.1998
// copyright (C) by Konrad Zagorowicz
// **********************************
// keyframer data reader

#include        <stdio.h>
#include        <stdlib.h>
#include	<string.h>
#include	"../3dlib/3dlib.h"

#include	"3ds.h"

#ifndef pi
#define pi 3.1415926535897932384626433832795
#endif

extern header_t *SearchInside(header_t *chunk,word ID,uint num);
extern header_t *SkipAsciiz(header_t *chunk);
extern object_t *FindObject(object_t *list,char *name);
extern object_t *FindDummy(object_t *list,char *name);
extern camera_t *FindCamera(camera_t *list,char *name);
extern light_t *FindLight(light_t *list,char *name);
extern void PrepareSpline(key_t keys[],int keycnt);

	static	struct{
		float	T,C,B,ET,EF;
	} TCBETEF;

//***************************************************************************
static void ReadSplineFlags(char **k_track,word flags)
{
	int	I;
	float	dat;

	for(I=0; I!=5; I++) ((int*)(&TCBETEF))[I]=0;

	for(I=0; I<16; I++)
	  if(flags&(1<<I))
	  {
	    dat=*((float*)(*k_track));
	    *k_track+=sizeof(float);
	    switch(I)
	    {
	      case 0: TCBETEF.T=dat; break;
	      case 1: TCBETEF.C=dat; break;
	      case 2: TCBETEF.B=dat; break;
	      case 3: TCBETEF.ET=dat; break;
	      case 4: TCBETEF.EF=dat; break;
	    }
	  }
}
//***************************************************************************
static void Read_1_Track(header_t *chunk,track_t *valtrack,float DATA)
{
	int	Q;
	word	*data=(word*)(chunk+1),flags;
	key_t	*key;
	char	*kfpos;

	valtrack->keys=data[5];
	key=valtrack->track= malloc(data[5]*sizeof(key_t));
	kfpos=(char*)&data[7];

	for(Q=0; Q!=data[5]; Q++)
	{
	  key->frame=*(word*)kfpos; kfpos+=sizeof(word);
	  flags=((word*)kfpos)[1]; kfpos+=sizeof(word)*2;
	  ReadSplineFlags(&kfpos,flags);
	  key->t=TCBETEF.T;
	  key->c=TCBETEF.C;
	  key->b=TCBETEF.B;
	  key->eto=TCBETEF.ET;
	  key->efrom=TCBETEF.EF;
	  key->quat.w=((float *)kfpos)[0]*DATA;
	  kfpos+=sizeof(float);
	  key++;
	}

	PrepareSpline(valtrack->track,valtrack->keys);
}
//***************************************************************************
static void Read_3_Track(header_t *chunk,track_t *postrack)
{
	int	Q;
	word	*data=(word*)(chunk+1),flags;
	key_t	*key;
	char	*kfpos;

	postrack->keys=data[5];
	key=postrack->track=malloc(data[5]*sizeof(key_t));
	kfpos=(char*)&data[7];

	for(Q=0; Q!=data[5]; Q++)
	{
	  key->frame=*(word*)kfpos; kfpos+=sizeof(word);
	  flags=((word*)kfpos)[1]; kfpos+=sizeof(word)*2;
	  ReadSplineFlags(&kfpos,flags);
	  key->t=TCBETEF.T;
	  key->c=TCBETEF.C;
	  key->b=TCBETEF.B;
	  key->eto=TCBETEF.ET;
	  key->efrom=TCBETEF.EF;
	  key->quat.x=((vector_t *)kfpos)->x;
	  key->quat.y=((vector_t *)kfpos)->z;
	  key->quat.z=((vector_t *)kfpos)->y;
	  kfpos+=sizeof(vector_t);
	  key++;
	}

	PrepareSpline(postrack->track,postrack->keys);
}
//***************************************************************************
static void Read_4_Track(header_t *chunk,track_t *rottrack)
{
	int	Q,flag=0;
	word	*data=(word*)(chunk+1),flags;
	key_t	*key;
	char	*kfpos;
	quat_t	quat,old,tmp;
	float	d;

	rottrack->keys=data[5];
	key=rottrack->track=malloc(data[5]*sizeof(key_t));
	kfpos=(char*)&data[7];

	for(Q=0; Q!=data[5]; Q++)
	{
	  key->frame=*(word*)kfpos; kfpos+=sizeof(word);
	  flags=((word*)kfpos)[1]; kfpos+=sizeof(word)*2;
	  ReadSplineFlags(&kfpos,flags);
	  key->t=TCBETEF.T;
	  key->c=TCBETEF.C;
	  key->b=TCBETEF.B;
	  key->eto=TCBETEF.ET;
	  key->efrom=TCBETEF.EF;
	  tmp=*(quat_t*)kfpos; d=-tmp.y; tmp.y=-tmp.z; tmp.z=d; tmp.x=-tmp.x;
	  qtConvert(&tmp,&quat);
	  kfpos+=sizeof(quat_t);
	  if(flag)
	  {
	    qtMul(&old,&quat,&tmp);
	    quat=tmp;
	  }
	  old=quat;
	  key->quat=quat;
	  flag=1;
	  key++;
	}

	PrepareSpline(rottrack->track,rottrack->keys);
}
//***************************************************************************
static void ReadMorphTrack(header_t *chunk,morphtrack_t *mtrack,object_t *list)
{
	int		Q;
	word		*data=(word*)(chunk+1),flags;
	morphkey_t	*mkey;
	char		*kfpos;

	mtrack->keys=data[5];
	mkey=mtrack->track=malloc(data[5]*sizeof(morphkey_t));
	kfpos=(char*)&data[7];

	for(Q=0; Q!=data[5]; Q++)
	{
	  mkey->frame=*(word*)kfpos; kfpos+=sizeof(word);
	  flags=((word*)kfpos)[1]; kfpos+=sizeof(word)*2;
	  ReadSplineFlags(&kfpos,flags);
	  mkey->t=TCBETEF.T;
	  mkey->c=TCBETEF.C;
	  mkey->b=TCBETEF.B;
	  mkey->eto=TCBETEF.ET;
	  mkey->efrom=TCBETEF.EF;
	  mkey->morph=FindObject(list,kfpos);
	  kfpos+=strlen(kfpos)+1;
	  mkey++;
	}
}
//***************************************************************************
static void ReadHideTrack(header_t *chunk,track_t *track)
{
	int	Q;
	word	*data=(word*)(chunk+1),flags;
	key_t	*key;
	char	*kfpos;
	int	FLAG=1;

	track->keys=data[5];
	key=track->track=malloc(data[5]*sizeof(key_t));
	kfpos=(char*)&data[7];

	for(Q=0; Q!=data[5]; Q++)
	{
	  key->frame=*(word*)kfpos; kfpos+=sizeof(word);
	  flags=((word*)kfpos)[1]; kfpos+=sizeof(word)*2;
	  ReadSplineFlags(&kfpos,flags);
	  key->t=TCBETEF.T;
	  key->c=TCBETEF.C;
	  key->b=TCBETEF.B;
	  key->eto=TCBETEF.ET;
	  key->efrom=TCBETEF.EF;
	  key->visible=FLAG*65535;
	  kfpos+=sizeof(int);
	  key++; FLAG^=1;
	}
}
//***************************************************************************
static void ReadObjectMove(object_t *objects,object_t *dummys,header_t *chnode)
{
	uint		pos=6,size=chnode->len;
	object_t	*object=0;

	chnode++;

	while(pos<size)
	{
	  switch(chnode->id)
	  {
	    case NODE_HDR:
	    {
	      word	*d=(word*)SkipAsciiz(chnode);
	      char	*name=(char*)(chnode+1);

	      if(!strcmp(name,"$$$DUMMY"))
	      {
		header_t *chinname=chnode;

		while(chinname->id!=INNAME)
		  chinname=(header_t*)((uint)chinname+chinname->len);

		name=(char*)(chinname+1);
		object=FindDummy(dummys,name);
	      }
	      else object=FindObject(objects,name);

	      if(object) object->hierarchy=d[2];
	    } break;

	    case PIVOT:
	    {
	      float *d=(float*)(chnode+1);
	      object->pivot.x=-d[0];
	      object->pivot.y=-d[2];
	      object->pivot.z=-d[1];
	    } break;

	    case MORPH_SMOOTH: break;
	    case POS_TRACK_TAG: if(object) Read_3_Track(chnode,&object->kfinfo.postrack); break;
	    case ROT_TRACK_TAG: if(object) Read_4_Track(chnode,&object->kfinfo.rottrack); break;
	    case SCALE_TRACK_TAG: if(object) Read_3_Track(chnode,&object->kfinfo.scltrack); break;
	    case MORPH_TRACK_TAG: if(object) ReadMorphTrack(chnode,&object->kfinfo.morphtrack,objects); break;
	    case HIDE_TRACK_TAG: if(object) ReadHideTrack(chnode,&object->kfinfo.hidetrack);break;
	  }

	  pos+=chnode->len;
	  chnode=(header_t*)((uint)chnode+chnode->len);
	}
}
//***************************************************************************
static void ReadCameraMove(camera_t *cameras,header_t *chnode)
{
	uint		pos=6,size=chnode->len;
	camera_t	*camera=0;

	chnode++;

	while(pos<size)
	{
	  switch(chnode->id)
	  {
	    case NODE_HDR:
	    {
	      word	*d=(word*)SkipAsciiz(chnode);
	      char	*name=(char*)(chnode+1);
	      camera=FindCamera(cameras,name);
	      camera->hierarchy1=d[2];
	    } break;

	    case POS_TRACK_TAG: Read_3_Track(chnode,&camera->kfinfo.postrack); break;
	    case FOV_TRACK_TAG: Read_1_Track(chnode,&camera->kfinfo.fovtrack,pi/180.); break;
	    case ROLL_TRACK_TAG: Read_1_Track(chnode,&camera->kfinfo.rolltrack,pi/180.); break;
	  }

	  pos+=chnode->len;
	  chnode=(header_t*)((uint)chnode+chnode->len);
	}
}
//***************************************************************************
static void ReadCameraTarget(camera_t *cameras,header_t *chnode)
{
	uint		pos=6,size=chnode->len;
	camera_t	*camera=0;

	chnode++;

	while(pos<size)
	{
	  switch(chnode->id)
	  {
	    case NODE_HDR:
	    {
	      word	*d=(word*)SkipAsciiz(chnode);
	      char	*name=(char*)(chnode+1);
	      camera=FindCamera(cameras,name);
	      camera->hierarchy2=d[2];
	    } break;

	    case POS_TRACK_TAG: Read_3_Track(chnode,&camera->kfinfo.targettrack); break;
	  }

	  pos+=chnode->len;
	  chnode=(header_t*)((uint)chnode+chnode->len);
	}
}
//***************************************************************************
static void ReadLightMove(light_t *lights,header_t *chnode)
{
	uint		pos=6,size=chnode->len;
	light_t 	*light=0;

	chnode++;

	while(pos<size)
	{
	  switch(chnode->id)
	  {
	    case NODE_HDR:
	    {
	      word	*d=(word*)SkipAsciiz(chnode);
	      char	*name=(char*)(chnode+1);
	      light=FindLight(lights,name);
	      light->hierarchy1=d[2];
	    } break;

	    case POS_TRACK_TAG: Read_3_Track(chnode,&light->kfinfo.postrack); break;
	    case COL_TRACK_TAG: Read_3_Track(chnode,&light->kfinfo.coltrack); break;
	  }

	  pos+=chnode->len;
	  chnode=(header_t*)((uint)chnode+chnode->len);
	}
}
//***************************************************************************
static void ReadSpotLightMove(light_t *lights,header_t *chnode)
{
	uint		pos=6,size=chnode->len;
	light_t 	*light=0;

	chnode++;

	while(pos<size)
	{
	  switch(chnode->id)
	  {
	    case NODE_HDR:
	    {
	      word	*d=(word*)SkipAsciiz(chnode);
	      char	*name=(char*)(chnode+1);
	      light=FindLight(lights,name);
	      light->hierarchy1=d[2];
	    } break;

	    case POS_TRACK_TAG: Read_3_Track(chnode,&light->kfinfo.postrack); break;
	    case COL_TRACK_TAG: Read_3_Track(chnode,&light->kfinfo.coltrack); break;
	    case FALL_TRACK_TAG: Read_1_Track(chnode,&light->kfinfo.falltrack,1.); break;
	    case HOT_TRACK_TAG: Read_1_Track(chnode,&light->kfinfo.hottrack,1.); break;
	    case ROLL_TRACK_TAG: Read_1_Track(chnode,&light->kfinfo.rolltrack,pi/180.); break;
	  }

	  pos+=chnode->len;
	  chnode=(header_t*)((uint)chnode+chnode->len);
	}
}
//***************************************************************************
static void ReadSpotLightTarget(light_t *lights,header_t *chnode)
{
	uint		pos=6,size=chnode->len;
	light_t 	*light=0;

	chnode++;

	while(pos<size)
	{
	  switch(chnode->id)
	  {
	    case NODE_HDR:
	    {
	      word	*d=(word*)SkipAsciiz(chnode);
	      char	*name=(char*)(chnode+1);
	      light=FindLight(lights,name);
	      light->hierarchy2=d[2];
	    } break;

	    case POS_TRACK_TAG: Read_3_Track(chnode,&light->kfinfo.targettrack); break;
	  }

	  pos+=chnode->len;
	  chnode=(header_t*)((uint)chnode+chnode->len);
	}
}
//***************************************************************************
static void ReadNODE_HDR(header_t *chnode,char **name)
{
	uint		pos=6,size=chnode->len;
	chnode++;

	while(pos<size)
	{
	  switch(chnode->id)
	  {
	    case NODE_HDR:
	    {

	      *name=(char*)(chnode+1);
	    } return;
	  }

	  pos+=chnode->len;
	  chnode=(header_t*)((uint)chnode+chnode->len);
	}
}
//***************************************************************************
static void ColectElements(header_t *chkeyf,scene_t *scene)
{
	uint	pos=6,size=(chkeyf++)->len;
	char	*name;

	element_t	ELEMS[MAX_ELEMENTS];
	uint		nELEMS=0;

	while(pos<size)
	{
	  switch(chkeyf->id)
	  {
	    case OBJECT_NODE_TAG:
	    {
	      ReadNODE_HDR(chkeyf,&name);
	      if(strcmp(name,"$$$DUMMY"))
	      {
		ELEMS[nELEMS].element=FindObject(scene->objects,name);
		ELEMS[nELEMS++].type=_OBJECT;
	      }
	      else
	      {
		ELEMS[nELEMS].element=chkeyf;
		ELEMS[nELEMS++].type=_DUMMY;
		scene->ndummys+=1;
	      }
	    } break;

	    case CAMERA_NODE_TAG:
	    {
	      ReadNODE_HDR(chkeyf,&name);
	      ELEMS[nELEMS].element=FindCamera(scene->cameras,name);;
	      ELEMS[nELEMS++].type=_CAMERA;
	    } break;

	    case TARGET_NODE_TAG:
	    {
	      ReadNODE_HDR(chkeyf,&name);
	      ELEMS[nELEMS].element=FindCamera(scene->cameras,name);;
	      ELEMS[nELEMS++].type=_TCAMERA;
	    } break;
	    case LIGHT_NODE_TAG:
	    {
	      ReadNODE_HDR(chkeyf,&name);
	      ELEMS[nELEMS].element=FindLight(scene->lights,name);;
	      ELEMS[nELEMS++].type=_LIGHT;
	    } break;
	    case SPOTLIGHT_NODE_TAG:
	    {
	      ReadNODE_HDR(chkeyf,&name);
	      ELEMS[nELEMS].element=FindLight(scene->lights,name);;
	      ELEMS[nELEMS++].type=_LIGHT;
	    } break;
	    case L_TARGET_NODE_TAG:
	    {
	      ReadNODE_HDR(chkeyf,&name);
	      ELEMS[nELEMS].element=FindLight(scene->lights,name);;
	      ELEMS[nELEMS++].type=_TLIGHT;
	    } break;
	  }


#ifdef _DEBUG
//	  if(pos>185000) 
//	    DebugMessage("bug expected");
#endif
	  pos+=chkeyf->len;
	  chkeyf=(header_t*)((uint)chkeyf+chkeyf->len);
	}

	if(nELEMS)
	{

	  scene->elements=malloc(nELEMS*sizeof(element_t));
	  scene->nelements=nELEMS;

	  while(nELEMS--)
	    scene->elements[nELEMS]=ELEMS[nELEMS];
	}
}
//***************************************************************************
static void CreateDummys(scene_t *scene)
{
	int		Q,nDummy=0;
	header_t	*chNode;
	object_t	*object;
	char		*name;
	scene->dummys=malloc(scene->ndummys*sizeof(object_t));
	memset( &scene->dummys, 0, scene->ndummys*sizeof(object_t) );

	for(Q=0; Q!=scene->nelements; Q++)
	{
	  if(scene->elements[Q].type==_DUMMY)
	  {
	    chNode=scene->elements[Q].element;
	    scene->elements[Q].type=_OBJECT;
	    object=scene->elements[Q].element=&scene->dummys[nDummy++];
	    chNode=SearchInside(chNode,INNAME,0);
	    name=(char*)(chNode+1);
	    strcpy(object->name,name);
	    object->flags=1;
	  }
	}
}
//***************************************************************************
void ReadKeyFData(scene_t *scene,void *chunkmain)
{
	header_t	*chkeyf=SearchInside(chunkmain,C_KEYF,0);
	uint		pos=6,size=chkeyf->len;

	ColectElements(chkeyf++,scene);
	if(scene->ndummys) CreateDummys(scene);

	while(pos<size)
	{
	  switch(chkeyf->id)
	  {
	    case KFFRAMES:  scene->frames=((uint*)(chkeyf+1))[1]-((uint*)(chkeyf+1))[0]+1; break;
	    case AMBIENT_NODE_TAG:  break;
	    case OBJECT_NODE_TAG:  ReadObjectMove(scene->objects,scene->dummys,chkeyf); break;
	    case CAMERA_NODE_TAG:  ReadCameraMove(scene->cameras,chkeyf); break;
	    case TARGET_NODE_TAG:  ReadCameraTarget(scene->cameras,chkeyf); break;
	    case LIGHT_NODE_TAG:  ReadLightMove(scene->lights,chkeyf); break;
	    case SPOTLIGHT_NODE_TAG:  ReadSpotLightMove(scene->lights,chkeyf); break;
	    case L_TARGET_NODE_TAG:  ReadSpotLightTarget(scene->lights,chkeyf); break;
	  }

	  pos+=chkeyf->len;
	  chkeyf=(header_t*)((uint)chkeyf+chkeyf->len);
	}
}
//***************************************************************************
