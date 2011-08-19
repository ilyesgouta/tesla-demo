// programming by Yoghurt/Pulse  v4.0
// date 17.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************
// additional routines

#define MaxValue	268435456.0

#include	"../3dlib/3dlib.h"
#include        "../3dlib/Matrix.h"
#include	"3ds.h"

extern void mtrxVecMulMatrix_(vector_t *v,const matrix_t *m);

//***************************************************************************
void CalculateNormal(face_t *face)
{
	vector_t	vec1,vec2,vec3;

	vSub2(&vec1,&face->vertices[1]->vglobal,&face->vertices[0]->vglobal);
	vSub2(&vec2,&face->vertices[2]->vglobal,&face->vertices[0]->vglobal);
	vCrossProduct(&vec3,&vec1,&vec2);
	vNormalize(&vec3);
	face->normal=vec3;
}
//***************************************************************************
void TransformToLocal(scene_t *scene)
{
	uint		Q,I;
	object_t	*object=scene->objects;
	vertex_t	*vert;
	face_t		*face;

	for(Q=0; Q!=scene->nobjects; Q++)
	{
	  vert=object->vertices;
	  face=object->faces;
	  
	  for(I=0; I!=object->nvertices; I++)
	  {
	    mtrxVecMulMatrix2(&vert->vlocal,&vert->vglobal,&object->xform);
	    mtrxVecMulMatrix_2(&vert->wlocal,&vert->wglobal,&object->xform);
	    vert++;
	  }
	  
	  for(I=0; I!=object->nfaces; I++)
	  {
	    mtrxVecMulMatrix_(&face->normal,&object->xform);
	    face++;
	  }

	  
	  object++;
	}
}
//***************************************************************************
void CalculateWersors(object_t *object)
{
	int		P,Q,N;
	vector_t	NORMAL;
	face_t*		face;
	vertex_t*	vert;
	texel_t*	tempMem;

	if((vert=object->vertices))
	{
	  for(Q=0; Q<object->nvertices; Q++)
	  {
	    N=0; NORMAL.x=0; NORMAL.y=0; NORMAL.z=0;

	    if((face=object->faces))
	    {
	      for(P=0; P<object->nfaces; P++)
	      {
		if((face->vertices[0]==vert || face->vertices[1]==vert || face->vertices[2]==vert))
		{
		  vAdd(&NORMAL,&face->normal);
		  N++;
		}

		face++;
	      }

	      vDiv2(&vert->wglobal,&NORMAL,N);
	    }
	    vert++;
	  }
	}


	face=object->faces;
	for(Q=0; Q!=object->nfaces; Q++)
	{
	  if(face->vertices[0]->flags==0x01 || face->vertices[1]->flags==0x01 || face->vertices[2]->flags==0x01)
	    tempMem=malloc(3*sizeof(texel_t));

	  for(N=0; N!=3; N++)
	  {
	    if(face->vertices[N]->flags==0x01)
	    {
	      face->maptexel[N]=tempMem;
	      face->maptexel[N]->u=(face->vertices[N]->wglobal.x*0.5)+0.5;
	      face->maptexel[N]->v=(face->vertices[N]->wglobal.y*0.5)+0.5;
	      tempMem++;
	    }
	  }
	  face++;
	}
}

//***************************************************************************
header_t *SearchInside(header_t *chunk,word ID,uint num)
{
	uint		size=chunk->len,Q=0,pos=0;
	header_t	*chunkfound=chunk+1;

	while(pos<size)
	{
	  if(chunkfound->id==ID)
	    if(Q==num) return chunkfound;
	    else Q++;
	  pos+=chunkfound->len;
	  chunkfound=(header_t*)((uint)chunkfound+chunkfound->len);
	}

	return	0;
}
//***************************************************************************
header_t *SkipAsciiz(header_t *chunk)
{
	char	*asciiz;

	asciiz=(char *)(chunk+1);
	while(asciiz[0]) asciiz++; asciiz++;
	return (header_t *)asciiz;
}
//***************************************************************************
object_t *FindObject(object_t *list,char *name)
{
	while(list)
	{
	  if(!strcmp(&list->name,name)) return list;
	  list++;
	}

	return	0;
}
//***************************************************************************
camera_t *FindCamera(camera_t *list,char *name)
{
	while(list)
	{
	  if(!strcmp(&list->name,name)) return list;
	  list++;
	}

	return	0;
}
//***************************************************************************
light_t *FindLight(light_t *list,char *name)
{
	while(list)
	{
	  if(!strcmp(&list->name,name)) return list;
	  list++;
	}

	return	0;
}
//***************************************************************************
object_t *FindDummy(object_t *list,char *name)
{
	while(list)
	{
	  if(!strcmp(&list->name,name)) return list;
	  list++;
	}

	return	0;
}
//***************************************************************************
void CalculateBoundBoxes(scene_t *scene)
{
	object_t	*object;
	vertex_t	*vert;
	int		NOBJ,NVERT;
	vector_t	MIN,MAX;
//อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ
	object=scene->objects;


	for(NOBJ=0; NOBJ!=scene->nobjects; NOBJ++)
	{
	  vert=object[NOBJ].vertices;
	  MIN.x=MaxValue; MIN.y=MaxValue; MIN.z=MaxValue;
	  MAX.x=-MaxValue; MAX.y=-MaxValue; MAX.z=-MaxValue;
	  for(NVERT=0; NVERT!=object[NOBJ].nvertices; NVERT++)
	  {
	    if(vert[NVERT].vlocal.x<MIN.x) MIN.x=vert[NVERT].vlocal.x;
	    if(vert[NVERT].vlocal.y<MIN.y) MIN.y=vert[NVERT].vlocal.y;
	    if(vert[NVERT].vlocal.z<MIN.z) MIN.z=vert[NVERT].vlocal.z;

	    if(vert[NVERT].vlocal.x>MAX.x) MAX.x=vert[NVERT].vlocal.x;
	    if(vert[NVERT].vlocal.y>MAX.y) MAX.y=vert[NVERT].vlocal.y;
	    if(vert[NVERT].vlocal.z>MAX.z) MAX.z=vert[NVERT].vlocal.z;
	  }

	  object[NOBJ].boundv1.x=MIN.x;
	  object[NOBJ].boundv1.y=MIN.y;
	  object[NOBJ].boundv1.z=MIN.z;
	  object[NOBJ].boundv2.x=MAX.x;
	  object[NOBJ].boundv2.y=MAX.y;
	  object[NOBJ].boundv2.z=MAX.z;
	}
}
//***************************************************************************
#define	U_WRAP_MIN  (208.0f/256.0f)

void  CalculateWrapUV(object_t* pObject)
{
	face_t*	pFace=pObject->faces;
	int	   f;

	float	fTileX=7.0f,fTileY=7.0f;

	float	fDelU;

	for(f=0; f!=pObject->nfaces; f++)
	{
	  if(pFace->flags&0x8)
	  {

	    fDelU=pFace->maptexel[1]->u - pFace->maptexel[0]->u;
	    if(fabs(fDelU) > U_WRAP_MIN*fTileX)
	    {
	      if(fDelU > 0.0)
		pFace->maptexel[1]->u -= 1.0*fTileX;
	      else
		pFace->maptexel[1]->u += 1.0*fTileX;
	    }

	    fDelU=pFace->maptexel[2]->u - pFace->maptexel[1]->u;
	    if(fabs(fDelU) > U_WRAP_MIN*fTileX)
	    {
	      if(fDelU > 0.0)
		pFace->maptexel[2]->u -= 1.0*fTileX;
	      else
		pFace->maptexel[2]->u += 1.0*fTileX;
	    }

	    fDelU=pFace->maptexel[0]->u - pFace->maptexel[2]->u;
	    if(fabs(fDelU) > U_WRAP_MIN*fTileX)
	    {
	      if(fDelU > 0.0)
		pFace->maptexel[0]->u -= 1.0*fTileX;
	      else
		pFace->maptexel[0]->u += 1.0*fTileX;
	    }

	  }

	  pFace++;
	}




}
//***************************************************************************
