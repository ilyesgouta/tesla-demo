// programming by Yoghurt/Pulse  v4.0
// date 19.02.1998
// copyright (C) by Konrad Zagorowicz
// 様様様様様様様様様様様様様様様様様

#ifndef _MOTION_H_INCLUDED_
#define _MOTION_H_INCLUDED_

#include	"3dlib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	int	frame;
	int	visible;
	float	t,c,b;
	float	eto,efrom;
	quat_t	quat;
	quat_t	ds,dd;
} key_t;

typedef struct
{
	int	frame;
	float	t,c,b;
	float	eto,efrom;
	void	*morph; 		// it is pointer to object_t;
} morphkey_t;


typedef struct
{
	int		keys;
	key_t		*track;
} track_t;

typedef struct
{
	int		keys;
	morphkey_t	*track;
} morphtrack_t;

typedef struct
{
	track_t 	postrack;
	track_t 	rottrack;
	track_t 	scltrack;
	track_t 	hidetrack;
	morphtrack_t	morphtrack;
} objectKF_t;

typedef struct
{
	track_t 	postrack;
	track_t 	fovtrack;
	track_t 	rolltrack;
	track_t 	targettrack;
} cameraKF_t;

typedef struct
{
	track_t 	postrack;
	track_t 	coltrack;
	track_t 	falltrack;
	track_t 	hottrack;
	track_t 	rolltrack;
	track_t 	targettrack;
} lightKF_t;

#ifdef __cplusplus
};
#endif
#endif
