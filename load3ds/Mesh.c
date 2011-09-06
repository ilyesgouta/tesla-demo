// programming by Yoghurt/Pulse  v4.0
// date 17.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************
// mesh data reader (objects/lights/cameras)

#include        <stdio.h>
#include        <stdlib.h>
#include	<string.h>

#include	"../3dlib/3dlib.h"
#include	"3ds.h"

#ifndef pi
  #define pi 3.1415926535897932384626433832795
#endif

extern header_t *SearchInside(header_t *chunk,word ID,uint num);
extern void CalculateNormal(face_t *face);
extern void TransformToLocal(scene_t *scene);
extern void CalculateWersors(object_t *object);
extern header_t *SkipAsciiz(header_t *chunk);
extern void CalculateWrapUV(object_t* pObject);
extern void CalculateBoundBoxes(scene_t *scene);

	static	scene_t 	*SCENE;
	static	vertex_t	*VERTICES;
	static	face_t		*FACES;

//***************************************************************************
static void ColectElements(header_t *chunk,uint *o,uint *l,uint *c,uint *v,uint *f)
{
	header_t	*ch=chunk+1,*chn;
	uint		pos=0;

	while(pos<chunk->len)
	{

	  if(ch->id==ELEMENT_NAME)
	  {
	    chn=SkipAsciiz(ch);
	    switch(chn->id)
	    {
	      case OBJECT:
	      {
		header_t	*chobj=chn+1;
		uint		p=0,sk=0;

		while(p<chn->len)
		{
		  switch(chobj->id)
		  {
		    case VERTICES_TAB:
		    {
		      (*v)+=((word*)(chobj+1))[0];
		      sk++;
		    } break;

		    case FACES_TAB:
		    {
		      (*f)+=((word*)(chobj+1))[0];
		      sk++;
		    } break;
		  };
		  p+=chobj->len;
		  chobj=(header_t*)((uint)chobj+chobj->len);
		  if(sk==2) break;
		}

	      } (*o)++; break;
	      case LIGHT: (*l)++; break;
	      case CAMERA: (*c)++; break;
	    };
	  }

	  pos+=ch->len;
	  ch=(header_t*)((uint)ch+ch->len);
	}
}
//***************************************************************************
static void ReadVertices(object_t *object,header_t *ch)
{
	word	*num=(word *)(ch+1);
	float	*fnum=(float *)(num+1);
	uint	Q=0;

	object->vertices=VERTICES;
	object->nvertices=*num;

	while(Q!=*num)
	{
	  VERTICES->vglobal.x=fnum[0];
	  VERTICES->vglobal.y=fnum[2];
	  VERTICES->vglobal.z=fnum[1];
	  VERTICES->flags=0x01;
	  fnum+=3;  VERTICES++;  Q++;
	}
}
//***************************************************************************
static void ReadUVTab(object_t *object,header_t *ch)
{
	vertex_t*	vert=object->vertices;
	face_t*		face=object->faces;
	word*		num=(word *)(ch+1);
	texel_t*	fnum=(texel_t*)(num+1);
	uint		Q=0;
	int		v,i;
	texel_t*	tempMem;

//	if(object->nvertices!=*num) errexit("LOAD3DS Error : uvtab reader");

//3*object... it's a defaul num of vertex in face
	tempMem=malloc(3*object->nfaces*sizeof(texel_t));

	for(Q=0; Q!=object->nfaces; Q++)
	{
	  for(i=0; i!=3; i++)
	  {
	    v=(int)face->maptexel[i];
	    face->maptexel[i]=tempMem;
	    tempMem->u=fnum[v].u;
	    tempMem->v=1.f - fnum[v].v;
	    vert[v].flags=0x00;
	    tempMem++;
	  }
	  face++;
	}
}
//***************************************************************************
static void ReadMatrix(object_t *object,header_t *ch)
{
	float	*f=(float *)(ch+1);

	object->xform.m[0][0]=f[0];  object->xform.m[0][1]=f[2];  object->xform.m[0][2]=f[1];
	object->xform.m[2][0]=f[0+3];  object->xform.m[2][1]=f[2+3];  object->xform.m[2][2]=f[1+3];
	object->xform.m[1][0]=f[0+6];  object->xform.m[1][1]=f[2+6];  object->xform.m[1][2]=f[1+6];
	object->xform.m[3][0]=f[0+9];  object->xform.m[3][1]=f[2+9];  object->xform.m[3][2]=f[1+9];
	mtrxInvert(&object->xform);
}
//***************************************************************************
static void ReadMaterials(object_t *object,header_t *ch)
{
	material_t	*mat,*materials=SCENE->materials;
	face_t		*faces=object->faces;
	char		*name=(char*)(ch+1);
	word		*num=(word*)SkipAsciiz(ch),*d=num+1;
	uint		Q=0,number=0;

	while(strcmp(materials[number].name,name) && number!=(SCENE->nmaterials+1)) number++;
	mat=&materials[number];

	while(Q!=*num)
	{
	  faces[*d].material=mat;
	  Q++;	d++;
	}
}
//***************************************************************************
static void ReadFaces(object_t *object,header_t *ch)
{
	word		*num=(word *)(ch+1);
	word		*d=num+1;
	uint		Q=0,pos;
	vertex_t	*vert=object->vertices;
	header_t	*tmp;
	int		material;

	object->faces=FACES;
	object->nfaces=*num;

	while(Q!=object->nfaces)
	{
	  FACES->vertices[0]=&vert[d[0]];
	  FACES->vertices[1]=&vert[d[1]];
	  FACES->vertices[2]=&vert[d[2]];
//temp variables
	  FACES->maptexel[0]=(texel_t*)d[0];
	  FACES->maptexel[1]=(texel_t*)d[1];
	  FACES->maptexel[2]=(texel_t*)d[2];
//end
	  FACES->flags=d[3];
	  FACES->xform=&object->xform;
	  FACES->vertnum=3;
	  CalculateNormal(FACES);
	  d+=4;  Q++;  FACES++;
	}

	tmp=(header_t*)d;
	pos=(uint)d-(uint)ch;

	material=0;
        object->flags = 0;
	while(pos<ch->len)
	{
	  if(tmp->id==MATERIALS)
	  {
	    ReadMaterials(object,tmp);
	    material=1;
	  }

          if (tmp->id == SMOOTH_GROUP)
          {
            object->flags = 1;
          }

	  pos += tmp->len;
	  tmp=(header_t*)((uint)tmp+tmp->len);
	}

	if(!material)
	{
	  face_t	*face=object->faces;

	  Q=object->nfaces;


	  while(Q--)
	  {
	    face->material=SCENE->materials;
	    face++;
	  }
	}
}
//***************************************************************************
static void ReadObject(object_t *object,header_t *chmesh)
{
	uint		pos=6;
	header_t	*ch=chmesh+1;


	int		facesDone=0;
	header_t*	uvch=0;

	while(pos<chmesh->len)
	{
	  switch(ch->id)
	  {
	    case VERTICES_TAB:
	      ReadVertices(object,ch);	break;

	    case FACES_TAB:
	    {
	      ReadFaces(object,ch);
	      if(uvch)
		ReadUVTab(object,uvch);

	      CalculateWersors(object);
	      CalculateWrapUV(object);
	    } break;

	    case UV_TAB:
	    {
	      if(facesDone)
		ReadUVTab(object,ch);
	      else
		uvch=ch;

	    } break;

	    case MATRIX:
	      ReadMatrix(object,ch);  break;
	  }

	  pos+=ch->len;
	  ch=(header_t*)((uint)ch+ch->len);
	}
}
//***************************************************************************
static void ReadLight(light_t *light,header_t *chlight)
{
	header_t	*tmp;
	uint		pos=0;
	float	*d=(float *)(chlight+1);

	light->vlocal.x=d[0];
	light->vlocal.y=d[2];
	light->vlocal.z=d[1];

	tmp=(header_t*)&d[3];

	while(pos<chlight->len)
	{
	  switch(tmp->id)
	  {
	    case C_COLOR_F:
	    {
	      d=(float*)(tmp+1);
	      light->color.r= (unsigned char)(d[0]*255.f);
	      light->color.g= (unsigned char)(d[1]*255.f);
	      light->color.b= (unsigned char)(d[2]*255.f);
	      light->fcolor.r= (unsigned char)(d[0]*255.f);
	      light->fcolor.g= (unsigned char)(d[1]*255.f);
	      light->fcolor.b= (unsigned char)(d[2]*255.f);
	    } break;

	    case SPOTLIGHT:
	    {
	      d=(float*)(tmp+1);
	      light->spotlight=1;
	      light->vlocalt.x=d[0];
	      light->vlocalt.y=d[2];
	      light->vlocalt.z=d[1];
	    }
	  }
	  pos+=tmp->len;
	  tmp=(header_t*)((uint)tmp+tmp->len);
	}
}
//***************************************************************************
static void ReadCamera(camera_t *camera,header_t *chcamera)
{
	float	*d=(float*)(chcamera+1);
	float	*d1=(float*)((char*)chcamera+8);

    if ((unsigned int)d & 0x3) {
        memset(&camera->pos, 0, sizeof(vector_t));
        memset(&camera->target, 0, sizeof(vector_t));
        camera->roll = 0;
        camera->fov = 0;
        camera->fZNear = 0;
        camera->fZFar = 0;
        return;
    }

	camera->pos.x=d[0];
	camera->pos.y=d[2];
	camera->pos.z=d[1];
	camera->target.x=d[3];
	camera->target.y=d[5];
	camera->target.z=d[4];
    camera->roll = d[6] * (float)pi/180.0f;
	camera->fov=d[7];
	camera->fZNear=d1[9];
	camera->fZFar=d1[10];
}
//***************************************************************************
void ReadMeshData(scene_t *scene,header_t *chunkmain)
{
	header_t	*chmesh=SearchInside(chunkmain,C_MESH,0);
	header_t	*chelem;
	uint		pos=0,size=chmesh->len;
	uint		nOBJ=0,nLGT=0,nCAM=0,nVERTICES=0,nFACES=0;
	char		*ename;

	object_t	*object;
	light_t 	*light;
	camera_t	*camera;

	SCENE=scene;
	ColectElements(chmesh,&nOBJ,&nLGT,&nCAM,&nVERTICES,&nFACES);

	if(nOBJ) object=scene->objects=malloc(nOBJ*sizeof(object_t));
	scene->nobjects=nOBJ;
	if(nLGT) light=scene->lights=malloc(nLGT*sizeof(light_t));
	scene->nlights=nLGT;
	if(nCAM) camera=scene->cameras=malloc(nCAM*sizeof(camera_t));
	scene->ncameras=nCAM;
	if(nVERTICES) VERTICES=scene->vertices=malloc(nVERTICES*sizeof(vertex_t));
	scene->nvertices=nVERTICES;
	if(nFACES) FACES=scene->faces=malloc(nFACES*sizeof(face_t));
	scene->nfaces=nFACES;

	chmesh++;

	while(pos<size)
	{
	  
	  if(chmesh->id==C_AMB)
	  {
	    scene->ambient.r=10.;
	    scene->ambient.g=10.;
	    scene->ambient.b=10.;
	  }
	
	  if(chmesh->id==ELEMENT_NAME)
	  {
	    ename=(char*)(chmesh+1);
	    chelem=SkipAsciiz(chmesh);

	    switch(chelem->id)
	    {
	      case OBJECT:
	      {
		strcpy(object->name,ename);
		ReadObject(object,chelem);
		object++;
	      } break;

	      case LIGHT:
	      {
		strcpy(light->name,ename);
		ReadLight(light,chelem);
		light++;
	      } break;

	      case CAMERA:
	      {
		strcpy(camera->name,ename);
		ReadCamera(camera,chelem);
		camera++;
	      } break;
	    }
	  }

	  pos+=chmesh->len;
	  chmesh=(header_t*)((uint)chmesh+chmesh->len);
	}


	TransformToLocal(scene);
	CalculateBoundBoxes(scene);
}
//***************************************************************************
