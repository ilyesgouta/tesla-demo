
#ifndef _3DS_H_INCLUDED_
#define _3DS_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push,1)

#define	MAX_ELEMENTS	8192
#define MAX_MATERIALS	256
#define MAX_DUMMYS	256

typedef struct{
	word	id;
	uint	len;
}header_t;


enum{
	C_COLOR_F	=	0x0010,
	C_COLOR 	=	0x0011,
	C_PERCENT	=	0x0030,
	C_PRECENT_F	=	0x0031,
};

enum{
	C_MAIN	=	0x4d4d,
	C_MESH	=	0x3d3d,
	C_KEYF	=	0xb000,
	C_AMB	=	0x2100,
};

enum{
	C_MATERIAL	=	0xAFFF,
	  C_MATNAME	=	0xA000,
	  C_AMBIENT	=	0xA010,
	  C_DIFFUSE	=	0xA020,
	  C_SPECULAR	=	0xA030,
	  C_TWOSIDED	=	0xA081,
	  C_WIRED	=	0xA085,
	  C_TEXTMAP	=	0xA200,
	  C_TRANSMAP	=	0xA210,
	  C_REFLMAP	=	0xA220,
	  C_BUMPMAP	=	0xA230,
	   C_MAPFILE	 =	 0xA300,
};

enum{
	ELEMENT_NAME		= 0x4000,
	 OBJECT 		= 0x4100,
	  VERTICES_TAB		= 0x4110,
	  UV_TAB		= 0x4140,
	  FACES_TAB		= 0x4120,
	   MATERIALS		= 0x4130,
           SMOOTH_GROUP         = 0x4150,
	  MATRIX		= 0x4160,
	 LIGHT			= 0x4600,
	  SPOTLIGHT		= 0x4610,
	 CAMERA			= 0x4700,
};

enum{
	KFFRAMES		=	0xb008,
	AMBIENT_NODE_TAG	=	0xb001,
	OBJECT_NODE_TAG 	=	0xb002,
	CAMERA_NODE_TAG 	=	0xb003,
	TARGET_NODE_TAG 	=	0xb004,
	LIGHT_NODE_TAG		=	0xb005,
	L_TARGET_NODE_TAG	=	0xb006,
	SPOTLIGHT_NODE_TAG	=	0xb007,

	NODE_HDR	=	0xb010,
	INNAME		=	0xb011,
	PIVOT		=	0xb013,

	MORPH_SMOOTH	=	0xb015,
	POS_TRACK_TAG	=	0xb020,
	ROT_TRACK_TAG	=	0xb021,
	SCALE_TRACK_TAG =	0xb022,
	FOV_TRACK_TAG	=	0xb023,
	ROLL_TRACK_TAG	=	0xb024,
	COL_TRACK_TAG	=	0xb025,
	MORPH_TRACK_TAG =	0xb026,
	HOT_TRACK_TAG	=	0xb027,
	FALL_TRACK_TAG	=	0xb028,
	HIDE_TRACK_TAG	=	0xb029,
	NODE_ID 	=	0xb030,
};

#pragma pack(pop)

#ifdef __cplusplus
};
#endif
#endif