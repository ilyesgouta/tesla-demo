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