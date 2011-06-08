// programming by Yoghurt/Pulse  v4.0
// date 10.03.1998
// copyright (C) by Konrad Zagorowicz
// **********************************
// load 3ds 4.0 file

#include	<stdio.h>
#include        <stdlib.h>
#include	<string.h>

#include	"../3dlib/3dlib.h"
#include	"Load3ds.h"

extern ReadMaterials(scene_t *scene,void *data3ds);
extern ReadMeshData(scene_t *scene,void *data3ds);
extern ReadKeyFData(scene_t *scene,void *data3ds);

//**************************************************************************
scene_t *Load3ds(char *name)
{
	int	len;
	scene_t *scene;
	void	*data;
	FILE	*openFile;
//**************************************************************************
	if(!(openFile=fopen(name,"rb")))
	{
	  puts("load3ds error!\n");
	  return 0;
	};

        fseek(openFile,0,SEEK_END);
	len=ftell(openFile);
        fseek(openFile,0,SEEK_SET);

	if(!len) return 0;

	data=malloc(len);

	fread(data,len,1,openFile);

	scene=malloc(sizeof(scene_t));
	memset( scene, 0, sizeof(scene_t) );

	strcpy(scene->name,name);

	ReadMaterials(scene,data);
	ReadMeshData(scene,data);
	ReadKeyFData(scene,data);

	scene->curframe=DEFAULT_START_FRAME;
	scene->fps=DEFAULT_FPS;
	scene->pFog=0;

	free(data);
	return	scene;
}
//***************************************************************************
