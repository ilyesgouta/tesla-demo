// programming by Yoghurt/Pulse  v4.0
// date 16.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************

#ifndef _LOAD3DS_H_INCLUDED_
#define _LOAD3DS_H_INCLUDED_

#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib,"load3dsD.lib")
#else
#pragma comment(lib,"load3ds.lib")
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_FPS		60
#define DEFAULT_START_FRAME	0

extern scene_t *Load3ds(char *name);
//extern void Save3d(char *name,scene_t *scene);

#ifdef __cplusplus
};
#endif
#endif
