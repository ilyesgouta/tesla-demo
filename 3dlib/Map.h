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


#ifndef _MAP_H_INCLUDED_
#define _MAP_H_INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif


typedef struct pixel_s
{
	uint	x,y;
} pixel_t;

typedef struct texel_s
{
	float	u,v;
} texel_t;

typedef union rgb_s
{
	uint	rgb;
	struct{
	  byte	b,g,r,a;
	};
} rgb_t;

typedef struct color_s
{
	float	r,g,b;
} color_t;

typedef struct map_s
{
	uint	width,height;
	int	bpp;
	int	modulo;
	void	*data;	    // pointer to data or GL texture number
} map_t;

#ifdef __cplusplus
};
#endif
#endif