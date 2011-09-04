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

#ifndef _3DLIB_H_INCLUDED_
#define _3DLIB_H_INCLUDED_

/*
#ifdef _DEBUG
#pragma comment (lib,"3dlibD.lib")
#else
#pragma comment (lib,"3dlib.lib")
#endif
*/

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned short int word;

#define TITLE_VERSION_MARK	"SCENE_3d v4.0"
#define AllNamesSize	20
#define BitsPerPixel	16
#define Bpp		BitsPerPixel


enum
{
	_OBJECT 	=	0x01,
	_CAMERA 	=	0x02,
	_LIGHT		=	0x03,
	_TCAMERA	=	0x04,
	_TLIGHT 	=	0x05,
	_DUMMY		=	0x06,
};

#include	"Vector.h"
#include	"Matrix.h"
#include	"Quater.h"
#include	"Map.h"
#include	"Motion.h"


#ifdef	__cplusplus

extern "C" {
#endif

typedef struct element_s
{
	void	*element;
	int	type;
	int	done;
} element_t;


typedef struct material_s
{
	char	name[AllNamesSize];
	rgb_t	color;
	color_t ambient;
	color_t diffuse;
	color_t specular;
	char	*textmappath;
	map_t	textmap;
	char	*reflmappath;
	map_t	reflmap;
	char	*transpmappath;
	map_t	transpmap;
	char	*bumpmappath;
	map_t	bumpmap;
	uint	twosided,wired;
	uint	flags;
} material_t;

typedef struct fog_s
{
	color_t	  stColor;
	float	   fDensity;
	float	   fNearRange;
	float	   fFarRange;
} fog_t;

typedef struct vertex_s
{
	vector_t	vlocal;
	vector_t	vglobal;
	vector_t	wlocal;
	vector_t	wglobal;
	texel_t 	envtexel;
	uint		flags;
} vertex_t;


typedef struct face_s
{
	texel_t* 	maptexel[3];
	vertex_t*	vertices[3];
        color_t         diffuse[3];
	vector_t	normal;
	matrix_t	*xform;
	material_t	*material;
	rgb_t		color;
	int		visible;
	uint		vertnum;
	uint		flags;
} face_t;

typedef struct object_s
{
	char		name[AllNamesSize];
	vertex_t	*vertices;
	uint		nvertices;
	face_t		*faces;
	uint		nfaces;
	vector_t	boundv1;
	vector_t	boundv2;
	vector_t	pivot;
	matrix_t	xform;
	objectKF_t	kfinfo;
	int		hierarchy;
	int		visible;
	int		morphing;	// if morphing flag set
	struct object_s *object1;	// use object1 & object2
	struct object_s *object2;
	float		morphT;
	uint		flags;
} object_t;

typedef struct light_s
{
	char		name[AllNamesSize];
	rgb_t		color;
	color_t		fcolor;
	vector_t	vlocal;
	vector_t	vlocalt;
	vector_t	vglobal;
	vector_t	vglobalt;
	vector_t	vscreen;
	matrix_t	xform;
	word		spotlight,flare;
	lightKF_t	kfinfo;
	int		hierarchy1;
	int		hierarchy2;
	uint		flags;
} light_t;

typedef struct camera_s
{
	char		name[AllNamesSize];
	vector_t	pos;
	vector_t	target;
	float		fov;
	float		roll;
	matrix_t	xform;
	cameraKF_t	kfinfo;
	int		hierarchy1;
	int		hierarchy2;
	float		fZNear;
	float		fZFar;
	uint		flags;
} camera_t;

typedef struct sceneo_s
{
	char		name[AllNamesSize];
	material_t	*materials;
	uint		nmaterials;
	vertex_t	*vertices;
	uint		nvertices;
	face_t		*faces;
	uint		nfaces;
	object_t	*objects;
	uint		nobjects;
	light_t 	*lights;
	uint		nlights;
	camera_t	*cameras;
	uint		ncameras;
	object_t	*dummys;
	uint		ndummys;
	element_t	*elements;
	uint		nelements;
	color_t		ambient;
	uint		frames;
	fog_t*	        pFog;
	float		curframe;
	float		fps;
	uint		flags;
	vertex_t	*_VERTICES_;
	vertex_t	**_VERTEX_;
	face_t		**_FACES_LIST_;
	face_t		**_SORTED_FACES_LIST_;

} scene_t;

#ifdef	__cplusplus
};
#endif
#endif
