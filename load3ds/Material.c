// programming by Yoghurt/Pulse  v4.0
// date 17.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************
// materials reader

#include        <stdio.h>
#include        <stdlib.h>
#include	<string.h>

#include	"../3dlib/3dlib.h"
#include	"3ds.h"

extern header_t *SearchInside(header_t *chunk,word ID,uint num);

material_t	default_material={
		"default",
		0x00f0f0f0,
		{1,1,1},
		{1,1,1},
		{1,1,1},
		};
//***************************************************************************
static void ReadRGB(header_t *chcol,color_t *color)
{
	header_t	*ch;
	uint		ps=0;

	ch=chcol+1;

	while(ps<chcol->len)
	{
	  if(ch->id==C_COLOR)
	  {
	    unsigned char	*c=(char*)(ch+1);
	    color->r=c[0]/255.f;
	    color->g=c[1]/255.f;
	    color->b=c[2]/255.f;
	  }
	  ps+=ch->len;
	  ch=(header_t*)((uint)ch+ch->len);
	}
}
//***************************************************************************
static void ReadMap(header_t *chmap,char **mappath)
{
	header_t	*ch=chmap+1;
	uint		ps=0;

	while	(ps<chmap->len)
	{
	  if(ch->id==C_MAPFILE)
	  {
	    *mappath=malloc(1+strlen((char*)(ch+1)));
	    strcpy(*mappath,(char*)(ch+1));
	  }
	  ps+=ch->len;
	  ch=(header_t*)((uint)ch+ch->len);
	}
}
//***************************************************************************
static void ReadMaterial(header_t *chunkmat,material_t *material)
{
	header_t	*chunk=chunkmat+1;
	uint		size=chunkmat->len,pos=0;

	while(pos<size)
	{

	  switch(chunk->id)
	  {
	    case C_MATNAME: strcpy(material->name,(char*)(chunk+1)); break;
	    case C_AMBIENT: ReadRGB(chunk,&material->ambient); break;
	    case C_SPECULAR: ReadRGB(chunk,&material->specular); break;
	    case C_DIFFUSE: ReadRGB(chunk,&material->diffuse); break;
	    case C_TWOSIDED: material->twosided=1; break;
	    case C_WIRED: material->wired=1; break;
	    case C_TEXTMAP: ReadMap(chunk,&material->textmappath); break;
	    case C_REFLMAP: ReadMap(chunk,&material->reflmappath); break;
	    case C_BUMPMAP: ReadMap(chunk,&material->bumpmappath); break;
	    case C_TRANSMAP: ReadMap(chunk,&material->transpmappath); break;
	  }

	  pos+=chunk->len;
	  chunk=(header_t*)((uint)chunk+chunk->len);
	}

}
//***************************************************************************
static header_t **ColectMaterials(header_t *chunkmain,uint *num)
{
	header_t	**temp,*chunk;
	uint	Q=0;
//อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ

	temp=malloc(MAX_MATERIALS*4);
	chunk=SearchInside(chunkmain,C_MESH,0);
	while((temp[*num]=SearchInside(chunk,C_MATERIAL,(*num)))) (*num)++;
	return	temp;
}
//***************************************************************************
void ReadMaterials(scene_t *scene,void *chunkmain)
{
	header_t	**temp;
	uint		nMATERIALS=0,Q;
	material_t	*material;
//อออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ

	temp=ColectMaterials(chunkmain,&nMATERIALS);
	material=scene->materials=malloc(sizeof(material_t)*(nMATERIALS+1)); // +1 coz there is default material too
	scene->nmaterials=nMATERIALS+1;

	memcpy(material,&default_material,sizeof(material_t));

	for(Q=0; Q!=nMATERIALS; Q++)
	  ReadMaterial(temp[Q],&material[Q+1]);

	free(temp);
}
//***************************************************************************
