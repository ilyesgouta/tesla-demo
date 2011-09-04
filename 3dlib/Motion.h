//
// tesla-demo, an OpenGL|ES 1.1 port of Sunflower's original Tesla demo.
//
// Original Tesla code, Copyright (C) 2000 Sunflower
// Linux EGL/X11 port by Ilyes Gouta, ilyes.gouta@gmail.com
//
// Port released under GNU General Public License with permission from
// Konrad Zagorowicz, original developer from Sunflower.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
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
} track_key_t;

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
    track_key_t		*track;
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
