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
// date 16.01.1998
// copyright (C) by Konrad Zagorowicz
// **********************************

#ifndef _QUAT_H_INCLUDED_
#define _QUAT_H_INCLUDED_

#include	<math.h>

//#pragma warning(disable : 4201)

#include	"Vector.h"
#include	"Matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
#ifdef _DEBUG
#pragma comment (lib,"3dlibD.lib")
#else
#pragma comment (lib,"3dlib.lib")
#endif
*/

typedef union quat_u
{
	struct{
	 float	w,x,y,z;
	};

	struct	{
	  float 	angle;
	  vector_t	vector;
	};
} quat_t;

extern void qtConvert(const quat_t *q,quat_t *q1);
extern void qtMul(const quat_t *qL,const quat_t *qR,quat_t *qq);
extern void qtInvMatrix(const quat_t *q,matrix_t *mat);
extern void qtToMatrix(const quat_t *a,matrix_t *mat);

#ifdef __cplusplus
};
#endif
#endif

