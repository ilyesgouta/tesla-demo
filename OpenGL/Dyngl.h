#ifndef __gl_h_
#ifndef __GL_H__

#define __gl_h_
#define __GL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
** Copyright 1996 Silicon Graphics, Inc.
** All Rights Reserved.
**
** This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
** the contents of this file may not be disclosed to third parties, copied or
** duplicated in any form, in whole or in part, without the prior written
** permission of Silicon Graphics, Inc.
**
** RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
** and Computer Software clause at DFARS 252.227-7013, and/or in similar or
** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
** rights reserved under the Copyright Laws of the United States.
*/

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;

/*************************************************************/

/* Version */
#define GL_VERSION_1_1                    1

/* AccumOp */
#define GL_ACCUM                          0x0100
#define GL_LOAD                           0x0101
#define GL_RETURN                         0x0102
#define GL_MULT                           0x0103
#define GL_ADD                            0x0104

/* AlphaFunction */
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

/* AttribMask */
#define GL_CURRENT_BIT                    0x00000001
#define GL_POINT_BIT                      0x00000002
#define GL_LINE_BIT                       0x00000004
#define GL_POLYGON_BIT                    0x00000008
#define GL_POLYGON_STIPPLE_BIT            0x00000010
#define GL_PIXEL_MODE_BIT                 0x00000020
#define GL_LIGHTING_BIT                   0x00000040
#define GL_FOG_BIT                        0x00000080
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_ACCUM_BUFFER_BIT               0x00000200
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_VIEWPORT_BIT                   0x00000800
#define GL_TRANSFORM_BIT                  0x00001000
#define GL_ENABLE_BIT                     0x00002000
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_HINT_BIT                       0x00008000
#define GL_EVAL_BIT                       0x00010000
#define GL_LIST_BIT                       0x00020000
#define GL_TEXTURE_BIT                    0x00040000
#define GL_SCISSOR_BIT                    0x00080000
#define GL_ALL_ATTRIB_BITS                0x000fffff

/* BeginMode */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
#define GL_QUAD_STRIP                     0x0008
#define GL_POLYGON                        0x0009

/* BlendingFactorDest */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */

/* Boolean */
#define GL_TRUE                           1
#define GL_FALSE                          0

/* ClearBufferMask */
/*      GL_COLOR_BUFFER_BIT */
/*      GL_ACCUM_BUFFER_BIT */
/*      GL_STENCIL_BUFFER_BIT */
/*      GL_DEPTH_BUFFER_BIT */

/* ClientArrayType */
/*      GL_VERTEX_ARRAY */
/*      GL_NORMAL_ARRAY */
/*      GL_COLOR_ARRAY */
/*      GL_INDEX_ARRAY */
/*      GL_TEXTURE_COORD_ARRAY */
/*      GL_EDGE_FLAG_ARRAY */

/* ClipPlaneName */
#define GL_CLIP_PLANE0                    0x3000
#define GL_CLIP_PLANE1                    0x3001
#define GL_CLIP_PLANE2                    0x3002
#define GL_CLIP_PLANE3                    0x3003
#define GL_CLIP_PLANE4                    0x3004
#define GL_CLIP_PLANE5                    0x3005

/* ColorMaterialFace */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_FRONT_AND_BACK */

/* ColorMaterialParameter */
/*      GL_AMBIENT */
/*      GL_DIFFUSE */
/*      GL_SPECULAR */
/*      GL_EMISSION */
/*      GL_AMBIENT_AND_DIFFUSE */

/* ColorPointerType */
/*      GL_BYTE */
/*      GL_UNSIGNED_BYTE */
/*      GL_SHORT */
/*      GL_UNSIGNED_SHORT */
/*      GL_INT */
/*      GL_UNSIGNED_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* CullFaceMode */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_FRONT_AND_BACK */

/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_2_BYTES                        0x1407
#define GL_3_BYTES                        0x1408
#define GL_4_BYTES                        0x1409
#define GL_DOUBLE                         0x140A

/* DepthFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* DrawBufferMode */
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
#define GL_AUX0                           0x0409
#define GL_AUX1                           0x040A
#define GL_AUX2                           0x040B
#define GL_AUX3                           0x040C

/* Enable */
/*      GL_FOG */
/*      GL_LIGHTING */
/*      GL_TEXTURE_1D */
/*      GL_TEXTURE_2D */
/*      GL_LINE_STIPPLE */
/*      GL_POLYGON_STIPPLE */
/*      GL_CULL_FACE */
/*      GL_ALPHA_TEST */
/*      GL_BLEND */
/*      GL_INDEX_LOGIC_OP */
/*      GL_COLOR_LOGIC_OP */
/*      GL_DITHER */
/*      GL_STENCIL_TEST */
/*      GL_DEPTH_TEST */
/*      GL_CLIP_PLANE0 */
/*      GL_CLIP_PLANE1 */
/*      GL_CLIP_PLANE2 */
/*      GL_CLIP_PLANE3 */
/*      GL_CLIP_PLANE4 */
/*      GL_CLIP_PLANE5 */
/*      GL_LIGHT0 */
/*      GL_LIGHT1 */
/*      GL_LIGHT2 */
/*      GL_LIGHT3 */
/*      GL_LIGHT4 */
/*      GL_LIGHT5 */
/*      GL_LIGHT6 */
/*      GL_LIGHT7 */
/*      GL_TEXTURE_GEN_S */
/*      GL_TEXTURE_GEN_T */
/*      GL_TEXTURE_GEN_R */
/*      GL_TEXTURE_GEN_Q */
/*      GL_MAP1_VERTEX_3 */
/*      GL_MAP1_VERTEX_4 */
/*      GL_MAP1_COLOR_4 */
/*      GL_MAP1_INDEX */
/*      GL_MAP1_NORMAL */
/*      GL_MAP1_TEXTURE_COORD_1 */
/*      GL_MAP1_TEXTURE_COORD_2 */
/*      GL_MAP1_TEXTURE_COORD_3 */
/*      GL_MAP1_TEXTURE_COORD_4 */
/*      GL_MAP2_VERTEX_3 */
/*      GL_MAP2_VERTEX_4 */
/*      GL_MAP2_COLOR_4 */
/*      GL_MAP2_INDEX */
/*      GL_MAP2_NORMAL */
/*      GL_MAP2_TEXTURE_COORD_1 */
/*      GL_MAP2_TEXTURE_COORD_2 */
/*      GL_MAP2_TEXTURE_COORD_3 */
/*      GL_MAP2_TEXTURE_COORD_4 */
/*      GL_POINT_SMOOTH */
/*      GL_LINE_SMOOTH */
/*      GL_POLYGON_SMOOTH */
/*      GL_SCISSOR_TEST */
/*      GL_COLOR_MATERIAL */
/*      GL_NORMALIZE */
/*      GL_AUTO_NORMAL */
/*      GL_VERTEX_ARRAY */
/*      GL_NORMAL_ARRAY */
/*      GL_COLOR_ARRAY */
/*      GL_INDEX_ARRAY */
/*      GL_TEXTURE_COORD_ARRAY */
/*      GL_EDGE_FLAG_ARRAY */
/*      GL_POLYGON_OFFSET_POINT */
/*      GL_POLYGON_OFFSET_LINE */
/*      GL_POLYGON_OFFSET_FILL */

/* ErrorCode */
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_OUT_OF_MEMORY                  0x0505

/* FeedBackMode */
#define GL_2D                             0x0600
#define GL_3D                             0x0601
#define GL_3D_COLOR                       0x0602
#define GL_3D_COLOR_TEXTURE               0x0603
#define GL_4D_COLOR_TEXTURE               0x0604

/* FeedBackToken */
#define GL_PASS_THROUGH_TOKEN             0x0700
#define GL_POINT_TOKEN                    0x0701
#define GL_LINE_TOKEN                     0x0702
#define GL_POLYGON_TOKEN                  0x0703
#define GL_BITMAP_TOKEN                   0x0704
#define GL_DRAW_PIXEL_TOKEN               0x0705
#define GL_COPY_PIXEL_TOKEN               0x0706
#define GL_LINE_RESET_TOKEN               0x0707

/* FogMode */
/*      GL_LINEAR */
#define GL_EXP                            0x0800
#define GL_EXP2                           0x0801


/* FogParameter */
/*      GL_FOG_COLOR */
/*      GL_FOG_DENSITY */
/*      GL_FOG_END */
/*      GL_FOG_INDEX */
/*      GL_FOG_MODE */
/*      GL_FOG_START */

/* FrontFaceDirection */
#define GL_CW                             0x0900
#define GL_CCW                            0x0901

/* GetMapTarget */
#define GL_COEFF                          0x0A00
#define GL_ORDER                          0x0A01
#define GL_DOMAIN                         0x0A02

/* GetPixelMap */
/*      GL_PIXEL_MAP_I_TO_I */
/*      GL_PIXEL_MAP_S_TO_S */
/*      GL_PIXEL_MAP_I_TO_R */
/*      GL_PIXEL_MAP_I_TO_G */
/*      GL_PIXEL_MAP_I_TO_B */
/*      GL_PIXEL_MAP_I_TO_A */
/*      GL_PIXEL_MAP_R_TO_R */
/*      GL_PIXEL_MAP_G_TO_G */
/*      GL_PIXEL_MAP_B_TO_B */
/*      GL_PIXEL_MAP_A_TO_A */

/* GetPointerTarget */
/*      GL_VERTEX_ARRAY_POINTER */
/*      GL_NORMAL_ARRAY_POINTER */
/*      GL_COLOR_ARRAY_POINTER */
/*      GL_INDEX_ARRAY_POINTER */
/*      GL_TEXTURE_COORD_ARRAY_POINTER */
/*      GL_EDGE_FLAG_ARRAY_POINTER */

/* GetTarget */
#define GL_CURRENT_COLOR                  0x0B00
#define GL_CURRENT_INDEX                  0x0B01
#define GL_CURRENT_NORMAL                 0x0B02
#define GL_CURRENT_TEXTURE_COORDS         0x0B03
#define GL_CURRENT_RASTER_COLOR           0x0B04
#define GL_CURRENT_RASTER_INDEX           0x0B05
#define GL_CURRENT_RASTER_TEXTURE_COORDS  0x0B06
#define GL_CURRENT_RASTER_POSITION        0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID  0x0B08
#define GL_CURRENT_RASTER_DISTANCE        0x0B09
#define GL_POINT_SMOOTH                   0x0B10
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_RANGE               0x0B12
#define GL_POINT_SIZE_GRANULARITY         0x0B13
#define GL_LINE_SMOOTH                    0x0B20
#define GL_LINE_WIDTH                     0x0B21
#define GL_LINE_WIDTH_RANGE               0x0B22
#define GL_LINE_WIDTH_GRANULARITY         0x0B23
#define GL_LINE_STIPPLE                   0x0B24
#define GL_LINE_STIPPLE_PATTERN           0x0B25
#define GL_LINE_STIPPLE_REPEAT            0x0B26
#define GL_LIST_MODE                      0x0B30
#define GL_MAX_LIST_NESTING               0x0B31
#define GL_LIST_BASE                      0x0B32
#define GL_LIST_INDEX                     0x0B33
#define GL_POLYGON_MODE                   0x0B40
#define GL_POLYGON_SMOOTH                 0x0B41
#define GL_POLYGON_STIPPLE                0x0B42
#define GL_EDGE_FLAG                      0x0B43
#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_LIGHTING                       0x0B50
#define GL_LIGHT_MODEL_LOCAL_VIEWER       0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#define GL_LIGHT_MODEL_AMBIENT            0x0B53
#define GL_SHADE_MODEL                    0x0B54
#define GL_COLOR_MATERIAL_FACE            0x0B55
#define GL_COLOR_MATERIAL_PARAMETER       0x0B56
#define GL_COLOR_MATERIAL                 0x0B57
#define GL_FOG                            0x0B60
#define GL_FOG_INDEX                      0x0B61
#define GL_FOG_DENSITY                    0x0B62
#define GL_FOG_START                      0x0B63
#define GL_FOG_END                        0x0B64
#define GL_FOG_MODE                       0x0B65
#define GL_FOG_COLOR                      0x0B66
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_ACCUM_CLEAR_VALUE              0x0B80
#define GL_STENCIL_TEST                   0x0B90
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_MATRIX_MODE                    0x0BA0
#define GL_NORMALIZE                      0x0BA1
#define GL_VIEWPORT                       0x0BA2
#define GL_MODELVIEW_STACK_DEPTH          0x0BA3
#define GL_PROJECTION_STACK_DEPTH         0x0BA4
#define GL_TEXTURE_STACK_DEPTH            0x0BA5
#define GL_MODELVIEW_MATRIX               0x0BA6
#define GL_PROJECTION_MATRIX              0x0BA7
#define GL_TEXTURE_MATRIX                 0x0BA8
#define GL_ATTRIB_STACK_DEPTH             0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH      0x0BB1
#define GL_ALPHA_TEST                     0x0BC0
#define GL_ALPHA_TEST_FUNC                0x0BC1
#define GL_ALPHA_TEST_REF                 0x0BC2
#define GL_DITHER                         0x0BD0
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_BLEND                          0x0BE2
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_INDEX_LOGIC_OP                 0x0BF1
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_AUX_BUFFERS                    0x0C00
#define GL_DRAW_BUFFER                    0x0C01
#define GL_READ_BUFFER                    0x0C02
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_INDEX_CLEAR_VALUE              0x0C20
#define GL_INDEX_WRITEMASK                0x0C21
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_INDEX_MODE                     0x0C30
#define GL_RGBA_MODE                      0x0C31
#define GL_DOUBLEBUFFER                   0x0C32
#define GL_STEREO                         0x0C33
#define GL_RENDER_MODE                    0x0C40
#define GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#define GL_POINT_SMOOTH_HINT              0x0C51
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_POLYGON_SMOOTH_HINT            0x0C53
#define GL_FOG_HINT                       0x0C54
#define GL_TEXTURE_GEN_S                  0x0C60
#define GL_TEXTURE_GEN_T                  0x0C61
#define GL_TEXTURE_GEN_R                  0x0C62
#define GL_TEXTURE_GEN_Q                  0x0C63
#define GL_PIXEL_MAP_I_TO_I               0x0C70
#define GL_PIXEL_MAP_S_TO_S               0x0C71
#define GL_PIXEL_MAP_I_TO_R               0x0C72
#define GL_PIXEL_MAP_I_TO_G               0x0C73
#define GL_PIXEL_MAP_I_TO_B               0x0C74
#define GL_PIXEL_MAP_I_TO_A               0x0C75
#define GL_PIXEL_MAP_R_TO_R               0x0C76
#define GL_PIXEL_MAP_G_TO_G               0x0C77
#define GL_PIXEL_MAP_B_TO_B               0x0C78
#define GL_PIXEL_MAP_A_TO_A               0x0C79
#define GL_PIXEL_MAP_I_TO_I_SIZE          0x0CB0
#define GL_PIXEL_MAP_S_TO_S_SIZE          0x0CB1
#define GL_PIXEL_MAP_I_TO_R_SIZE          0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE          0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE          0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE          0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE          0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE          0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE          0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE          0x0CB9
#define GL_UNPACK_SWAP_BYTES              0x0CF0
#define GL_UNPACK_LSB_FIRST               0x0CF1
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_SWAP_BYTES                0x0D00
#define GL_PACK_LSB_FIRST                 0x0D01
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAP_COLOR                      0x0D10
#define GL_MAP_STENCIL                    0x0D11
#define GL_INDEX_SHIFT                    0x0D12
#define GL_INDEX_OFFSET                   0x0D13
#define GL_RED_SCALE                      0x0D14
#define GL_RED_BIAS                       0x0D15
#define GL_ZOOM_X                         0x0D16
#define GL_ZOOM_Y                         0x0D17
#define GL_GREEN_SCALE                    0x0D18
#define GL_GREEN_BIAS                     0x0D19
#define GL_BLUE_SCALE                     0x0D1A
#define GL_BLUE_BIAS                      0x0D1B
#define GL_ALPHA_SCALE                    0x0D1C
#define GL_ALPHA_BIAS                     0x0D1D
#define GL_DEPTH_SCALE                    0x0D1E
#define GL_DEPTH_BIAS                     0x0D1F
#define GL_MAX_EVAL_ORDER                 0x0D30
#define GL_MAX_LIGHTS                     0x0D31
#define GL_MAX_CLIP_PLANES                0x0D32
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_PIXEL_MAP_TABLE            0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH         0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH      0x0D36
#define GL_MAX_NAME_STACK_DEPTH           0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH     0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH        0x0D39
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH  0x0D3B
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_INDEX_BITS                     0x0D51
#define GL_RED_BITS                       0x0D52
#define GL_GREEN_BITS                     0x0D53
#define GL_BLUE_BITS                      0x0D54
#define GL_ALPHA_BITS                     0x0D55
#define GL_DEPTH_BITS                     0x0D56
#define GL_STENCIL_BITS                   0x0D57
#define GL_ACCUM_RED_BITS                 0x0D58
#define GL_ACCUM_GREEN_BITS               0x0D59
#define GL_ACCUM_BLUE_BITS                0x0D5A
#define GL_ACCUM_ALPHA_BITS               0x0D5B
#define GL_NAME_STACK_DEPTH               0x0D70
#define GL_AUTO_NORMAL                    0x0D80
#define GL_MAP1_COLOR_4                   0x0D90
#define GL_MAP1_INDEX                     0x0D91
#define GL_MAP1_NORMAL                    0x0D92
#define GL_MAP1_TEXTURE_COORD_1           0x0D93
#define GL_MAP1_TEXTURE_COORD_2           0x0D94
#define GL_MAP1_TEXTURE_COORD_3           0x0D95
#define GL_MAP1_TEXTURE_COORD_4           0x0D96
#define GL_MAP1_VERTEX_3                  0x0D97
#define GL_MAP1_VERTEX_4                  0x0D98
#define GL_MAP2_COLOR_4                   0x0DB0
#define GL_MAP2_INDEX                     0x0DB1
#define GL_MAP2_NORMAL                    0x0DB2
#define GL_MAP2_TEXTURE_COORD_1           0x0DB3
#define GL_MAP2_TEXTURE_COORD_2           0x0DB4
#define GL_MAP2_TEXTURE_COORD_3           0x0DB5
#define GL_MAP2_TEXTURE_COORD_4           0x0DB6
#define GL_MAP2_VERTEX_3                  0x0DB7
#define GL_MAP2_VERTEX_4                  0x0DB8
#define GL_MAP1_GRID_DOMAIN               0x0DD0
#define GL_MAP1_GRID_SEGMENTS             0x0DD1
#define GL_MAP2_GRID_DOMAIN               0x0DD2
#define GL_MAP2_GRID_SEGMENTS             0x0DD3
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_FEEDBACK_BUFFER_POINTER        0x0DF0
#define GL_FEEDBACK_BUFFER_SIZE           0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE           0x0DF2
#define GL_SELECTION_BUFFER_POINTER       0x0DF3
#define GL_SELECTION_BUFFER_SIZE          0x0DF4
/*      GL_TEXTURE_BINDING_1D */
/*      GL_TEXTURE_BINDING_2D */
/*      GL_VERTEX_ARRAY */
/*      GL_NORMAL_ARRAY */
/*      GL_COLOR_ARRAY */
/*      GL_INDEX_ARRAY */
/*      GL_TEXTURE_COORD_ARRAY */
/*      GL_EDGE_FLAG_ARRAY */
/*      GL_VERTEX_ARRAY_SIZE */
/*      GL_VERTEX_ARRAY_TYPE */
/*      GL_VERTEX_ARRAY_STRIDE */
/*      GL_NORMAL_ARRAY_TYPE */
/*      GL_NORMAL_ARRAY_STRIDE */
/*      GL_COLOR_ARRAY_SIZE */
/*      GL_COLOR_ARRAY_TYPE */
/*      GL_COLOR_ARRAY_STRIDE */
/*      GL_INDEX_ARRAY_TYPE */
/*      GL_INDEX_ARRAY_STRIDE */
/*      GL_TEXTURE_COORD_ARRAY_SIZE */
/*      GL_TEXTURE_COORD_ARRAY_TYPE */
/*      GL_TEXTURE_COORD_ARRAY_STRIDE */
/*      GL_EDGE_FLAG_ARRAY_STRIDE */
/*      GL_POLYGON_OFFSET_FACTOR */
/*      GL_POLYGON_OFFSET_UNITS */

/* GetTextureParameter */
/*      GL_TEXTURE_MAG_FILTER */
/*      GL_TEXTURE_MIN_FILTER */
/*      GL_TEXTURE_WRAP_S */
/*      GL_TEXTURE_WRAP_T */
#define GL_TEXTURE_WIDTH                  0x1000
#define GL_TEXTURE_HEIGHT                 0x1001
#define GL_TEXTURE_INTERNAL_FORMAT        0x1003
#define GL_TEXTURE_BORDER_COLOR           0x1004
#define GL_TEXTURE_BORDER                 0x1005
/*      GL_TEXTURE_RED_SIZE */
/*      GL_TEXTURE_GREEN_SIZE */
/*      GL_TEXTURE_BLUE_SIZE */
/*      GL_TEXTURE_ALPHA_SIZE */
/*      GL_TEXTURE_LUMINANCE_SIZE */
/*      GL_TEXTURE_INTENSITY_SIZE */
/*      GL_TEXTURE_PRIORITY */
/*      GL_TEXTURE_RESIDENT */

/* HintMode */
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102

/* HintTarget */
/*      GL_PERSPECTIVE_CORRECTION_HINT */
/*      GL_POINT_SMOOTH_HINT */
/*      GL_LINE_SMOOTH_HINT */
/*      GL_POLYGON_SMOOTH_HINT */
/*      GL_FOG_HINT */
/*      GL_PHONG_HINT */

/* IndexPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* LightModelParameter */
/*      GL_LIGHT_MODEL_AMBIENT */
/*      GL_LIGHT_MODEL_LOCAL_VIEWER */
/*      GL_LIGHT_MODEL_TWO_SIDE */

/* LightName */
#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001
#define GL_LIGHT2                         0x4002
#define GL_LIGHT3                         0x4003
#define GL_LIGHT4                         0x4004
#define GL_LIGHT5                         0x4005
#define GL_LIGHT6                         0x4006
#define GL_LIGHT7                         0x4007

/* LightParameter */
#define GL_AMBIENT                        0x1200
#define GL_DIFFUSE                        0x1201
#define GL_SPECULAR                       0x1202
#define GL_POSITION                       0x1203
#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209

/* InterleavedArrays */
/*      GL_V2F */
/*      GL_V3F */
/*      GL_C4UB_V2F */
/*      GL_C4UB_V3F */
/*      GL_C3F_V3F */
/*      GL_N3F_V3F */
/*      GL_C4F_N3F_V3F */
/*      GL_T2F_V3F */
/*      GL_T4F_V4F */
/*      GL_T2F_C4UB_V3F */
/*      GL_T2F_C3F_V3F */
/*      GL_T2F_N3F_V3F */
/*      GL_T2F_C4F_N3F_V3F */
/*      GL_T4F_C4F_N3F_V4F */

/* ListMode */
#define GL_COMPILE                        0x1300
#define GL_COMPILE_AND_EXECUTE            0x1301

/* ListNameType */
/*      GL_BYTE */
/*      GL_UNSIGNED_BYTE */
/*      GL_SHORT */
/*      GL_UNSIGNED_SHORT */
/*      GL_INT */
/*      GL_UNSIGNED_INT */
/*      GL_FLOAT */
/*      GL_2_BYTES */
/*      GL_3_BYTES */
/*      GL_4_BYTES */

/* LogicOp */
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F

/* MapTarget */
/*      GL_MAP1_COLOR_4 */
/*      GL_MAP1_INDEX */
/*      GL_MAP1_NORMAL */
/*      GL_MAP1_TEXTURE_COORD_1 */
/*      GL_MAP1_TEXTURE_COORD_2 */
/*      GL_MAP1_TEXTURE_COORD_3 */
/*      GL_MAP1_TEXTURE_COORD_4 */
/*      GL_MAP1_VERTEX_3 */
/*      GL_MAP1_VERTEX_4 */
/*      GL_MAP2_COLOR_4 */
/*      GL_MAP2_INDEX */
/*      GL_MAP2_NORMAL */
/*      GL_MAP2_TEXTURE_COORD_1 */
/*      GL_MAP2_TEXTURE_COORD_2 */
/*      GL_MAP2_TEXTURE_COORD_3 */
/*      GL_MAP2_TEXTURE_COORD_4 */
/*      GL_MAP2_VERTEX_3 */
/*      GL_MAP2_VERTEX_4 */

/* MaterialFace */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_FRONT_AND_BACK */

/* MaterialParameter */
#define GL_EMISSION                       0x1600
#define GL_SHININESS                      0x1601
#define GL_AMBIENT_AND_DIFFUSE            0x1602
#define GL_COLOR_INDEXES                  0x1603
/*      GL_AMBIENT */
/*      GL_DIFFUSE */
/*      GL_SPECULAR */

/* MatrixMode */
#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701
#define GL_TEXTURE                        0x1702

/* MeshMode1 */
/*      GL_POINT */
/*      GL_LINE */

/* MeshMode2 */
/*      GL_POINT */
/*      GL_LINE */
/*      GL_FILL */

/* NormalPointerType */
/*      GL_BYTE */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* PixelCopyType */
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802

/* PixelFormat */
#define GL_COLOR_INDEX                    0x1900
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A

/* PixelMap */
/*      GL_PIXEL_MAP_I_TO_I */
/*      GL_PIXEL_MAP_S_TO_S */
/*      GL_PIXEL_MAP_I_TO_R */
/*      GL_PIXEL_MAP_I_TO_G */
/*      GL_PIXEL_MAP_I_TO_B */
/*      GL_PIXEL_MAP_I_TO_A */
/*      GL_PIXEL_MAP_R_TO_R */
/*      GL_PIXEL_MAP_G_TO_G */
/*      GL_PIXEL_MAP_B_TO_B */
/*      GL_PIXEL_MAP_A_TO_A */

/* PixelStore */
/*      GL_UNPACK_SWAP_BYTES */
/*      GL_UNPACK_LSB_FIRST */
/*      GL_UNPACK_ROW_LENGTH */
/*      GL_UNPACK_SKIP_ROWS */
/*      GL_UNPACK_SKIP_PIXELS */
/*      GL_UNPACK_ALIGNMENT */
/*      GL_PACK_SWAP_BYTES */
/*      GL_PACK_LSB_FIRST */
/*      GL_PACK_ROW_LENGTH */
/*      GL_PACK_SKIP_ROWS */
/*      GL_PACK_SKIP_PIXELS */
/*      GL_PACK_ALIGNMENT */

/* PixelTransfer */
/*      GL_MAP_COLOR */
/*      GL_MAP_STENCIL */
/*      GL_INDEX_SHIFT */
/*      GL_INDEX_OFFSET */
/*      GL_RED_SCALE */
/*      GL_RED_BIAS */
/*      GL_GREEN_SCALE */
/*      GL_GREEN_BIAS */
/*      GL_BLUE_SCALE */
/*      GL_BLUE_BIAS */
/*      GL_ALPHA_SCALE */
/*      GL_ALPHA_BIAS */
/*      GL_DEPTH_SCALE */
/*      GL_DEPTH_BIAS */

/* PixelType */
#define GL_BITMAP                         0x1A00
/*      GL_BYTE */
/*      GL_UNSIGNED_BYTE */
/*      GL_SHORT */
/*      GL_UNSIGNED_SHORT */
/*      GL_INT */
/*      GL_UNSIGNED_INT */
/*      GL_FLOAT */

/* PolygonMode */
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02

/* ReadBufferMode */
/*      GL_FRONT_LEFT */
/*      GL_FRONT_RIGHT */
/*      GL_BACK_LEFT */
/*      GL_BACK_RIGHT */
/*      GL_FRONT */
/*      GL_BACK */
/*      GL_LEFT */
/*      GL_RIGHT */
/*      GL_AUX0 */
/*      GL_AUX1 */
/*      GL_AUX2 */
/*      GL_AUX3 */

/* RenderingMode */
#define GL_RENDER                         0x1C00
#define GL_FEEDBACK                       0x1C01
#define GL_SELECT                         0x1C02

/* ShadingModel */
#define GL_FLAT                           0x1D00
#define GL_SMOOTH                         0x1D01


/* StencilFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* StencilOp */
/*      GL_ZERO */
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
/*      GL_INVERT */

/* StringName */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03

/* TextureCoordName */
#define GL_S                              0x2000
#define GL_T                              0x2001
#define GL_R                              0x2002
#define GL_Q                              0x2003

/* TexCoordPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* TextureEnvMode */
#define GL_MODULATE                       0x2100
#define GL_DECAL                          0x2101
/*      GL_BLEND */
/*      GL_REPLACE */

/* TextureEnvParameter */
#define GL_TEXTURE_ENV_MODE               0x2200
#define GL_TEXTURE_ENV_COLOR              0x2201

/* TextureEnvTarget */
#define GL_TEXTURE_ENV                    0x2300

/* TextureGenMode */
#define GL_EYE_LINEAR                     0x2400
#define GL_OBJECT_LINEAR                  0x2401
#define GL_SPHERE_MAP                     0x2402

/* TextureGenParameter */
#define GL_TEXTURE_GEN_MODE               0x2500
#define GL_OBJECT_PLANE                   0x2501
#define GL_EYE_PLANE                      0x2502

/* TextureMagFilter */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601

/* TextureMinFilter */
/*      GL_NEAREST */
/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
/*      GL_TEXTURE_BORDER_COLOR */
/*      GL_TEXTURE_PRIORITY */

/* TextureTarget */
/*      GL_TEXTURE_1D */
/*      GL_TEXTURE_2D */
/*      GL_PROXY_TEXTURE_1D */
/*      GL_PROXY_TEXTURE_2D */

/* TextureWrapMode */
#define GL_CLAMP                          0x2900
#define GL_REPEAT                         0x2901

/* VertexPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* ClientAttribMask */
#define GL_CLIENT_PIXEL_STORE_BIT         0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT        0x00000002
#define GL_CLIENT_ALL_ATTRIB_BITS         0xffffffff

/* polygon_offset */
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_POINT           0x2A01
#define GL_POLYGON_OFFSET_LINE            0x2A02
#define GL_POLYGON_OFFSET_FILL            0x8037

/* texture */
#define GL_ALPHA4                         0x803B
#define GL_ALPHA8                         0x803C
#define GL_ALPHA12                        0x803D
#define GL_ALPHA16                        0x803E
#define GL_LUMINANCE4                     0x803F
#define GL_LUMINANCE8                     0x8040
#define GL_LUMINANCE12                    0x8041
#define GL_LUMINANCE16                    0x8042
#define GL_LUMINANCE4_ALPHA4              0x8043
#define GL_LUMINANCE6_ALPHA2              0x8044
#define GL_LUMINANCE8_ALPHA8              0x8045
#define GL_LUMINANCE12_ALPHA4             0x8046
#define GL_LUMINANCE12_ALPHA12            0x8047
#define GL_LUMINANCE16_ALPHA16            0x8048
#define GL_INTENSITY                      0x8049
#define GL_INTENSITY4                     0x804A
#define GL_INTENSITY8                     0x804B
#define GL_INTENSITY12                    0x804C
#define GL_INTENSITY16                    0x804D
#define GL_R3_G3_B2                       0x2A10
#define GL_RGB4                           0x804F
#define GL_RGB5                           0x8050
#define GL_RGB8                           0x8051
#define GL_RGB10                          0x8052
#define GL_RGB12                          0x8053
#define GL_RGB16                          0x8054
#define GL_RGBA2                          0x8055
#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_RGBA12                         0x805A
#define GL_RGBA16                         0x805B
#define GL_TEXTURE_RED_SIZE               0x805C
#define GL_TEXTURE_GREEN_SIZE             0x805D
#define GL_TEXTURE_BLUE_SIZE              0x805E
#define GL_TEXTURE_ALPHA_SIZE             0x805F
#define GL_TEXTURE_LUMINANCE_SIZE         0x8060
#define GL_TEXTURE_INTENSITY_SIZE         0x8061
#define GL_PROXY_TEXTURE_1D               0x8063
#define GL_PROXY_TEXTURE_2D               0x8064

/* texture_object */
#define GL_TEXTURE_PRIORITY               0x8066
#define GL_TEXTURE_RESIDENT               0x8067
#define GL_TEXTURE_BINDING_1D             0x8068
#define GL_TEXTURE_BINDING_2D             0x8069

/* vertex_array */
#define GL_VERTEX_ARRAY                   0x8074
#define GL_NORMAL_ARRAY                   0x8075
#define GL_COLOR_ARRAY                    0x8076
#define GL_INDEX_ARRAY                    0x8077
#define GL_TEXTURE_COORD_ARRAY            0x8078
#define GL_EDGE_FLAG_ARRAY                0x8079
#define GL_VERTEX_ARRAY_SIZE              0x807A
#define GL_VERTEX_ARRAY_TYPE              0x807B
#define GL_VERTEX_ARRAY_STRIDE            0x807C
#define GL_NORMAL_ARRAY_TYPE              0x807E
#define GL_NORMAL_ARRAY_STRIDE            0x807F
#define GL_COLOR_ARRAY_SIZE               0x8081
#define GL_COLOR_ARRAY_TYPE               0x8082
#define GL_COLOR_ARRAY_STRIDE             0x8083
#define GL_INDEX_ARRAY_TYPE               0x8085
#define GL_INDEX_ARRAY_STRIDE             0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE       0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE         0x808C
#define GL_VERTEX_ARRAY_POINTER           0x808E
#define GL_NORMAL_ARRAY_POINTER           0x808F
#define GL_COLOR_ARRAY_POINTER            0x8090
#define GL_INDEX_ARRAY_POINTER            0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER    0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER        0x8093
#define GL_V2F                            0x2A20
#define GL_V3F                            0x2A21
#define GL_C4UB_V2F                       0x2A22
#define GL_C4UB_V3F                       0x2A23
#define GL_C3F_V3F                        0x2A24
#define GL_N3F_V3F                        0x2A25
#define GL_C4F_N3F_V3F                    0x2A26
#define GL_T2F_V3F                        0x2A27
#define GL_T4F_V4F                        0x2A28
#define GL_T2F_C4UB_V3F                   0x2A29
#define GL_T2F_C3F_V3F                    0x2A2A
#define GL_T2F_N3F_V3F                    0x2A2B
#define GL_T2F_C4F_N3F_V3F                0x2A2C
#define GL_T4F_C4F_N3F_V4F                0x2A2D

/* Extensions */
#define GL_EXT_vertex_array               1
#define GL_EXT_bgra                       1
#define GL_EXT_paletted_texture           1
#define GL_WIN_swap_hint                  1
#define GL_WIN_draw_range_elements        1
// #define GL_WIN_phong_shading              1
// #define GL_WIN_specular_fog               1

/* EXT_vertex_array */
#define GL_VERTEX_ARRAY_EXT               0x8074
#define GL_NORMAL_ARRAY_EXT               0x8075
#define GL_COLOR_ARRAY_EXT                0x8076
#define GL_INDEX_ARRAY_EXT                0x8077
#define GL_TEXTURE_COORD_ARRAY_EXT        0x8078
#define GL_EDGE_FLAG_ARRAY_EXT            0x8079
#define GL_VERTEX_ARRAY_SIZE_EXT          0x807A
#define GL_VERTEX_ARRAY_TYPE_EXT          0x807B
#define GL_VERTEX_ARRAY_STRIDE_EXT        0x807C
#define GL_VERTEX_ARRAY_COUNT_EXT         0x807D
#define GL_NORMAL_ARRAY_TYPE_EXT          0x807E
#define GL_NORMAL_ARRAY_STRIDE_EXT        0x807F
#define GL_NORMAL_ARRAY_COUNT_EXT         0x8080
#define GL_COLOR_ARRAY_SIZE_EXT           0x8081
#define GL_COLOR_ARRAY_TYPE_EXT           0x8082
#define GL_COLOR_ARRAY_STRIDE_EXT         0x8083
#define GL_COLOR_ARRAY_COUNT_EXT          0x8084
#define GL_INDEX_ARRAY_TYPE_EXT           0x8085
#define GL_INDEX_ARRAY_STRIDE_EXT         0x8086
#define GL_INDEX_ARRAY_COUNT_EXT          0x8087
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT   0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT   0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT 0x808A
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT  0x808B
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT     0x808C
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT      0x808D
#define GL_VERTEX_ARRAY_POINTER_EXT       0x808E
#define GL_NORMAL_ARRAY_POINTER_EXT       0x808F
#define GL_COLOR_ARRAY_POINTER_EXT        0x8090
#define GL_INDEX_ARRAY_POINTER_EXT        0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT 0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT    0x8093
#define GL_DOUBLE_EXT                     GL_DOUBLE

/* EXT_bgra */
#define GL_BGR_EXT                        0x80E0
#define GL_BGRA_EXT                       0x80E1

/* EXT_paletted_texture */

/* These must match the GL_COLOR_TABLE_*_SGI enumerants */
#define GL_COLOR_TABLE_FORMAT_EXT         0x80D8
#define GL_COLOR_TABLE_WIDTH_EXT          0x80D9
#define GL_COLOR_TABLE_RED_SIZE_EXT       0x80DA
#define GL_COLOR_TABLE_GREEN_SIZE_EXT     0x80DB
#define GL_COLOR_TABLE_BLUE_SIZE_EXT      0x80DC
#define GL_COLOR_TABLE_ALPHA_SIZE_EXT     0x80DD
#define GL_COLOR_TABLE_LUMINANCE_SIZE_EXT 0x80DE
#define GL_COLOR_TABLE_INTENSITY_SIZE_EXT 0x80DF

#define GL_COLOR_INDEX1_EXT               0x80E2
#define GL_COLOR_INDEX2_EXT               0x80E3
#define GL_COLOR_INDEX4_EXT               0x80E4
#define GL_COLOR_INDEX8_EXT               0x80E5
#define GL_COLOR_INDEX12_EXT              0x80E6
#define GL_COLOR_INDEX16_EXT              0x80E7

/* WIN_draw_range_elements */
#define GL_MAX_ELEMENTS_VERTICES_WIN      0x80E8
#define GL_MAX_ELEMENTS_INDICES_WIN       0x80E9

/* WIN_phong_shading */
#define GL_PHONG_WIN                      0x80EA 
#define GL_PHONG_HINT_WIN                 0x80EB 

/* WIN_specular_fog */
#define GL_FOG_SPECULAR_TEXTURE_WIN       0x80EC

/* For compatibility with OpenGL v1.0 */
#define GL_LOGIC_OP GL_INDEX_LOGIC_OP
#define GL_TEXTURE_COMPONENTS GL_TEXTURE_INTERNAL_FORMAT

#ifndef WIN32
#define APIENTRY
#endif

/*************************************************************/
typedef   void        (APIENTRY* pfnglAccum)                    (GLenum op, GLfloat value);
typedef   void        (APIENTRY* pfnglAlphaFunc)                (GLenum func, GLclampf ref);
typedef   GLboolean   (APIENTRY* pfnglAreTexturesResident)      (GLsizei n, const GLuint *textures, GLboolean *residences);
typedef   void        (APIENTRY* pfnglArrayElement)             (GLint i);
typedef   void        (APIENTRY* pfnglBegin)                    (GLenum mode);
typedef   void        (APIENTRY* pfnglBindTexture)              (GLenum target, GLuint texture);
typedef   void        (APIENTRY* pfnglBitmap)                   (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
typedef   void        (APIENTRY* pfnglBlendFunc)                (GLenum sfactor, GLenum dfactor);
typedef   void        (APIENTRY* pfnglCallList)                 (GLuint list);
typedef   void        (APIENTRY* pfnglCallLists)                (GLsizei n, GLenum type, const GLvoid *lists);
typedef   void        (APIENTRY* pfnglClear)                    (GLbitfield mask);
typedef   void        (APIENTRY* pfnglClearAccum)               (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef   void        (APIENTRY* pfnglClearColor)               (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
typedef   void        (APIENTRY* pfnglClearDepth)               (GLclampd depth);
typedef   void        (APIENTRY* pfnglClearIndex)               (GLfloat c);
typedef   void        (APIENTRY* pfnglClearStencil)             (GLint s);
typedef   void        (APIENTRY* pfnglClipPlane)                (GLenum plane, const GLdouble *equation);
typedef   void        (APIENTRY* pfnglColor3b)                  (GLbyte red, GLbyte green, GLbyte blue);
typedef   void        (APIENTRY* pfnglColor3bv)                 (const GLbyte *v);
typedef   void        (APIENTRY* pfnglColor3d)                  (GLdouble red, GLdouble green, GLdouble blue);
typedef   void        (APIENTRY* pfnglColor3dv)                 (const GLdouble *v);
typedef   void        (APIENTRY* pfnglColor3f)                  (GLfloat red, GLfloat green, GLfloat blue);
typedef   void        (APIENTRY* pfnglColor3fv)                 (const GLfloat *v);
typedef   void        (APIENTRY* pfnglColor3i)                  (GLint red, GLint green, GLint blue);
typedef   void        (APIENTRY* pfnglColor3iv)                 (const GLint *v);
typedef   void        (APIENTRY* pfnglColor3s)                  (GLshort red, GLshort green, GLshort blue);
typedef   void        (APIENTRY* pfnglColor3sv)                 (const GLshort *v);
typedef   void        (APIENTRY* pfnglColor3ub)                 (GLubyte red, GLubyte green, GLubyte blue);
typedef   void        (APIENTRY* pfnglColor3ubv)                (const GLubyte *v);
typedef   void        (APIENTRY* pfnglColor3ui)                 (GLuint red, GLuint green, GLuint blue);
typedef   void        (APIENTRY* pfnglColor3uiv)                (const GLuint *v);
typedef   void        (APIENTRY* pfnglColor3us)                 (GLushort red, GLushort green, GLushort blue);
typedef   void        (APIENTRY* pfnglColor3usv)                (const GLushort *v);
typedef   void        (APIENTRY* pfnglColor4b)                  (GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
typedef   void        (APIENTRY* pfnglColor4bv)                 (const GLbyte *v);
typedef   void        (APIENTRY* pfnglColor4d)                  (GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
typedef   void        (APIENTRY* pfnglColor4dv)                 (const GLdouble *v);
typedef   void        (APIENTRY* pfnglColor4f)                  (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef   void        (APIENTRY* pfnglColor4fv)                 (const GLfloat *v);
typedef   void        (APIENTRY* pfnglColor4i)                  (GLint red, GLint green, GLint blue, GLint alpha);
typedef   void        (APIENTRY* pfnglColor4iv)                 (const GLint *v);
typedef   void        (APIENTRY* pfnglColor4s)                  (GLshort red, GLshort green, GLshort blue, GLshort alpha);
typedef   void        (APIENTRY* pfnglColor4sv)                 (const GLshort *v);
typedef   void        (APIENTRY* pfnglColor4ub)                 (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
typedef   void        (APIENTRY* pfnglColor4ubv)                (const GLubyte *v);
typedef   void        (APIENTRY* pfnglColor4ui)                 (GLuint red, GLuint green, GLuint blue, GLuint alpha);
typedef   void        (APIENTRY* pfnglColor4uiv)                (const GLuint *v);
typedef   void        (APIENTRY* pfnglColor4us)                 (GLushort red, GLushort green, GLushort blue, GLushort alpha);
typedef   void        (APIENTRY* pfnglColor4usv)                (const GLushort *v);
typedef   void        (APIENTRY* pfnglColorMask)                (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef   void        (APIENTRY* pfnglColorMaterial)            (GLenum face, GLenum mode);
typedef   void        (APIENTRY* pfnglColorPointer)             (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef   void        (APIENTRY* pfnglCopyPixels)               (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
typedef   void        (APIENTRY* pfnglCopyTexImage1D)           (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
typedef   void        (APIENTRY* pfnglCopyTexImage2D)           (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef   void        (APIENTRY* pfnglCopyTexSubImage1D)        (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef   void        (APIENTRY* pfnglCopyTexSubImage2D)        (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef   void        (APIENTRY* pfnglCullFace)                 (GLenum mode);
typedef   void        (APIENTRY* pfnglDeleteLists)              (GLuint list, GLsizei range);
typedef   void        (APIENTRY* pfnglDeleteTextures)           (GLsizei n, const GLuint *textures);
typedef   void        (APIENTRY* pfnglDepthFunc)                (GLenum func);
typedef   void        (APIENTRY* pfnglDepthMask)                (GLboolean flag);
typedef   void        (APIENTRY* pfnglDepthRange)               (GLclampd zNear, GLclampd zFar);
typedef   void        (APIENTRY* pfnglDisable)                  (GLenum cap);
typedef   void        (APIENTRY* pfnglDisableClientState)       (GLenum array);
typedef   void        (APIENTRY* pfnglDrawArrays)               (GLenum mode, GLint first, GLsizei count);
typedef   void        (APIENTRY* pfnglDrawBuffer)               (GLenum mode);
typedef   void        (APIENTRY* pfnglDrawElements)             (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
typedef   void        (APIENTRY* pfnglDrawPixels)               (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
typedef   void        (APIENTRY* pfnglEdgeFlag)                 (GLboolean flag);
typedef   void        (APIENTRY* pfnglEdgeFlagPointer)          (GLsizei stride, const GLvoid *pointer);
typedef   void        (APIENTRY* pfnglEdgeFlagv)                (const GLboolean *flag);
typedef   void        (APIENTRY* pfnglEnable)                   (GLenum cap);
typedef   void        (APIENTRY* pfnglEnableClientState)        (GLenum array);
typedef   void        (APIENTRY* pfnglEnd)                      (void);
typedef   void        (APIENTRY* pfnglEndList)                  (void);
typedef   void        (APIENTRY* pfnglEvalCoord1d)              (GLdouble u);
typedef   void        (APIENTRY* pfnglEvalCoord1dv)             (const GLdouble *u);
typedef   void        (APIENTRY* pfnglEvalCoord1f)              (GLfloat u);
typedef   void        (APIENTRY* pfnglEvalCoord1fv)             (const GLfloat *u);
typedef   void        (APIENTRY* pfnglEvalCoord2d)              (GLdouble u, GLdouble v);
typedef   void        (APIENTRY* pfnglEvalCoord2dv)             (const GLdouble *u);
typedef   void        (APIENTRY* pfnglEvalCoord2f)              (GLfloat u, GLfloat v);
typedef   void        (APIENTRY* pfnglEvalCoord2fv)             (const GLfloat *u);
typedef   void        (APIENTRY* pfnglEvalMesh1)                (GLenum mode, GLint i1, GLint i2);
typedef   void        (APIENTRY* pfnglEvalMesh2)                (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
typedef   void        (APIENTRY* pfnglEvalPoint1)               (GLint i);
typedef   void        (APIENTRY* pfnglEvalPoint2)               (GLint i, GLint j);
typedef   void        (APIENTRY* pfnglFeedbackBuffer)           (GLsizei size, GLenum type, GLfloat *buffer);
typedef   void        (APIENTRY* pfnglFinish)                   (void);
typedef   void        (APIENTRY* pfnglFlush)                    (void);
typedef   void        (APIENTRY* pfnglFogf)                     (GLenum pname, GLfloat param);
typedef   void        (APIENTRY* pfnglFogfv)                    (GLenum pname, const GLfloat *params);
typedef   void        (APIENTRY* pfnglFogi)                     (GLenum pname, GLint param);
typedef   void        (APIENTRY* pfnglFogiv)                    (GLenum pname, const GLint *params);
typedef   void        (APIENTRY* pfnglFrontFace)                (GLenum mode);
typedef   void        (APIENTRY* pfnglFrustum)                  (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef   GLuint      (APIENTRY* pfnglGenLists)                 (GLsizei range);
typedef   void        (APIENTRY* pfnglGenTextures)              (GLsizei n, GLuint *textures);
typedef   void        (APIENTRY* pfnglGetBooleanv)              (GLenum pname, GLboolean *params);
typedef   void        (APIENTRY* pfnglGetClipPlane)             (GLenum plane, GLdouble *equation);
typedef   void        (APIENTRY* pfnglGetDoublev)               (GLenum pname, GLdouble *params);
typedef   GLenum      (APIENTRY* pfnglGetError)                 (void);
typedef   void        (APIENTRY* pfnglGetFloatv)                (GLenum pname, GLfloat *params);
typedef   void        (APIENTRY* pfnglGetIntegerv)              (GLenum pname, GLint *params);
typedef   void        (APIENTRY* pfnglGetLightfv)               (GLenum light, GLenum pname, GLfloat *params);
typedef   void        (APIENTRY* pfnglGetLightiv)               (GLenum light, GLenum pname, GLint *params);
typedef   void        (APIENTRY* pfnglGetMapdv)                 (GLenum target, GLenum query, GLdouble *v);
typedef   void        (APIENTRY* pfnglGetMapfv)                 (GLenum target, GLenum query, GLfloat *v);
typedef   void        (APIENTRY* pfnglGetMapiv)                 (GLenum target, GLenum query, GLint *v);
typedef   void        (APIENTRY* pfnglGetMaterialfv)            (GLenum face, GLenum pname, GLfloat *params);
typedef   void        (APIENTRY* pfnglGetMaterialiv)            (GLenum face, GLenum pname, GLint *params);
typedef   void        (APIENTRY* pfnglGetPixelMapfv)            (GLenum map, GLfloat *values);
typedef   void        (APIENTRY* pfnglGetPixelMapuiv)           (GLenum map, GLuint *values);
typedef   void        (APIENTRY* pfnglGetPixelMapusv)           (GLenum map, GLushort *values);
typedef   void        (APIENTRY* pfnglGetPointerv)              (GLenum pname, GLvoid* *params);
typedef   void        (APIENTRY* pfnglGetPolygonStipple)        (GLubyte *mask);
typedef   const GLubyte* (APIENTRY* pfnglGetString)                (GLenum name);
typedef   void        (APIENTRY* pfnglGetTexEnvfv)              (GLenum target, GLenum pname, GLfloat *params);
typedef   void        (APIENTRY* pfnglGetTexEnviv)              (GLenum target, GLenum pname, GLint *params);
typedef   void        (APIENTRY* pfnglGetTexGendv)              (GLenum coord, GLenum pname, GLdouble *params);
typedef   void        (APIENTRY* pfnglGetTexGenfv)              (GLenum coord, GLenum pname, GLfloat *params);
typedef   void        (APIENTRY* pfnglGetTexGeniv)              (GLenum coord, GLenum pname, GLint *params);
typedef   void        (APIENTRY* pfnglGetTexImage)              (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
typedef   void        (APIENTRY* pfnglGetTexLevelParameterfv)   (GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef   void        (APIENTRY* pfnglGetTexLevelParameteriv)   (GLenum target, GLint level, GLenum pname, GLint *params);
typedef   void        (APIENTRY* pfnglGetTexParameterfv)        (GLenum target, GLenum pname, GLfloat *params);
typedef   void        (APIENTRY* pfnglGetTexParameteriv)        (GLenum target, GLenum pname, GLint *params);
typedef   void        (APIENTRY* pfnglHint)                     (GLenum target, GLenum mode);
typedef   void        (APIENTRY* pfnglIndexMask)                (GLuint mask);
typedef   void        (APIENTRY* pfnglIndexPointer)             (GLenum type, GLsizei stride, const GLvoid *pointer);
typedef   void        (APIENTRY* pfnglIndexd)                   (GLdouble c);
typedef   void        (APIENTRY* pfnglIndexdv)                  (const GLdouble *c);
typedef   void        (APIENTRY* pfnglIndexf)                   (GLfloat c);
typedef   void        (APIENTRY* pfnglIndexfv)                  (const GLfloat *c);
typedef   void        (APIENTRY* pfnglIndexi)                   (GLint c);
typedef   void        (APIENTRY* pfnglIndexiv)                  (const GLint *c);
typedef   void        (APIENTRY* pfnglIndexs)                   (GLshort c);
typedef   void        (APIENTRY* pfnglIndexsv)                  (const GLshort *c);
typedef   void        (APIENTRY* pfnglIndexub)                  (GLubyte c);
typedef   void        (APIENTRY* pfnglIndexubv)                 (const GLubyte *c);
typedef   void        (APIENTRY* pfnglInitNames)                (void);
typedef   void        (APIENTRY* pfnglInterleavedArrays)        (GLenum format, GLsizei stride, const GLvoid *pointer);
typedef   GLboolean   (APIENTRY* pfnglIsEnabled)                (GLenum cap);
typedef   GLboolean   (APIENTRY* pfnglIsList)                   (GLuint list);
typedef   GLboolean   (APIENTRY* pfnglIsTexture)                (GLuint texture);
typedef   void        (APIENTRY* pfnglLightModelf)              (GLenum pname, GLfloat param);
typedef   void        (APIENTRY* pfnglLightModelfv)             (GLenum pname, const GLfloat *params);
typedef   void        (APIENTRY* pfnglLightModeli)              (GLenum pname, GLint param);
typedef   void        (APIENTRY* pfnglLightModeliv)             (GLenum pname, const GLint *params);
typedef   void        (APIENTRY* pfnglLightf)                   (GLenum light, GLenum pname, GLfloat param);
typedef   void        (APIENTRY* pfnglLightfv)                  (GLenum light, GLenum pname, const GLfloat *params);
typedef   void        (APIENTRY* pfnglLighti)                   (GLenum light, GLenum pname, GLint param);
typedef   void        (APIENTRY* pfnglLightiv)                  (GLenum light, GLenum pname, const GLint *params);
typedef   void        (APIENTRY* pfnglLineStipple)              (GLint factor, GLushort pattern);
typedef   void        (APIENTRY* pfnglLineWidth)                (GLfloat width);
typedef   void        (APIENTRY* pfnglListBase)                 (GLuint base);
typedef   void        (APIENTRY* pfnglLoadIdentity)             (void);
typedef   void        (APIENTRY* pfnglLoadMatrixd)              (const GLdouble *m);
typedef   void        (APIENTRY* pfnglLoadMatrixf)              (const GLfloat *m);
typedef   void        (APIENTRY* pfnglLoadName)                 (GLuint name);
typedef   void        (APIENTRY* pfnglLogicOp)                  (GLenum opcode);
typedef   void        (APIENTRY* pfnglMap1d)                    (GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
typedef   void        (APIENTRY* pfnglMap1f)                    (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
typedef   void        (APIENTRY* pfnglMap2d)                    (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
typedef   void        (APIENTRY* pfnglMap2f)                    (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
typedef   void        (APIENTRY* pfnglMapGrid1d)                (GLint un, GLdouble u1, GLdouble u2);
typedef   void        (APIENTRY* pfnglMapGrid1f)                (GLint un, GLfloat u1, GLfloat u2);
typedef   void        (APIENTRY* pfnglMapGrid2d)                (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
typedef   void        (APIENTRY* pfnglMapGrid2f)                (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
typedef   void        (APIENTRY* pfnglMaterialf)                (GLenum face, GLenum pname, GLfloat param);
typedef   void        (APIENTRY* pfnglMaterialfv)               (GLenum face, GLenum pname, const GLfloat *params);
typedef   void        (APIENTRY* pfnglMateriali)                (GLenum face, GLenum pname, GLint param);
typedef   void        (APIENTRY* pfnglMaterialiv)               (GLenum face, GLenum pname, const GLint *params);
typedef   void        (APIENTRY* pfnglMatrixMode)               (GLenum mode);
typedef   void        (APIENTRY* pfnglMultMatrixd)              (const GLdouble *m);
typedef   void        (APIENTRY* pfnglMultMatrixf)              (const GLfloat *m);
typedef   void        (APIENTRY* pfnglNewList)                  (GLuint list, GLenum mode);
typedef   void        (APIENTRY* pfnglNormal3b)                 (GLbyte nx, GLbyte ny, GLbyte nz);
typedef   void        (APIENTRY* pfnglNormal3bv)                (const GLbyte *v);
typedef   void        (APIENTRY* pfnglNormal3d)                 (GLdouble nx, GLdouble ny, GLdouble nz);
typedef   void        (APIENTRY* pfnglNormal3dv)                (const GLdouble *v);
typedef   void        (APIENTRY* pfnglNormal3f)                 (GLfloat nx, GLfloat ny, GLfloat nz);
typedef   void        (APIENTRY* pfnglNormal3fv)                (const GLfloat *v);
typedef   void        (APIENTRY* pfnglNormal3i)                 (GLint nx, GLint ny, GLint nz);
typedef   void        (APIENTRY* pfnglNormal3iv)                (const GLint *v);
typedef   void        (APIENTRY* pfnglNormal3s)                 (GLshort nx, GLshort ny, GLshort nz);
typedef   void        (APIENTRY* pfnglNormal3sv)                (const GLshort *v);
typedef   void        (APIENTRY* pfnglNormalPointer)            (GLenum type, GLsizei stride, const GLvoid *pointer);
typedef   void        (APIENTRY* pfnglOrtho)                    (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef   void        (APIENTRY* pfnglPassThrough)              (GLfloat token);
typedef   void        (APIENTRY* pfnglPixelMapfv)               (GLenum map, GLsizei mapsize, const GLfloat *values);
typedef   void        (APIENTRY* pfnglPixelMapuiv)              (GLenum map, GLsizei mapsize, const GLuint *values);
typedef   void        (APIENTRY* pfnglPixelMapusv)              (GLenum map, GLsizei mapsize, const GLushort *values);
typedef   void        (APIENTRY* pfnglPixelStoref)              (GLenum pname, GLfloat param);
typedef   void        (APIENTRY* pfnglPixelStorei)              (GLenum pname, GLint param);
typedef   void        (APIENTRY* pfnglPixelTransferf)           (GLenum pname, GLfloat param);
typedef   void        (APIENTRY* pfnglPixelTransferi)           (GLenum pname, GLint param);
typedef   void        (APIENTRY* pfnglPixelZoom)                (GLfloat xfactor, GLfloat yfactor);
typedef   void        (APIENTRY* pfnglPointSize)                (GLfloat size);
typedef   void        (APIENTRY* pfnglPolygonMode)              (GLenum face, GLenum mode);
typedef   void        (APIENTRY* pfnglPolygonOffset)            (GLfloat factor, GLfloat units);
typedef   void        (APIENTRY* pfnglPolygonStipple)           (const GLubyte *mask);
typedef   void        (APIENTRY* pfnglPopAttrib)                (void);
typedef   void        (APIENTRY* pfnglPopClientAttrib)          (void);
typedef   void        (APIENTRY* pfnglPopMatrix)                (void);
typedef   void        (APIENTRY* pfnglPopName)                  (void);
typedef   void        (APIENTRY* pfnglPrioritizeTextures)       (GLsizei n, const GLuint *textures, const GLclampf *priorities);
typedef   void        (APIENTRY* pfnglPushAttrib)               (GLbitfield mask);
typedef   void        (APIENTRY* pfnglPushClientAttrib)         (GLbitfield mask);
typedef   void        (APIENTRY* pfnglPushMatrix)               (void);
typedef   void        (APIENTRY* pfnglPushName)                 (GLuint name);
typedef   void        (APIENTRY* pfnglRasterPos2d)              (GLdouble x, GLdouble y);
typedef   void        (APIENTRY* pfnglRasterPos2dv)             (const GLdouble *v);
typedef   void        (APIENTRY* pfnglRasterPos2f)              (GLfloat x, GLfloat y);
typedef   void        (APIENTRY* pfnglRasterPos2fv)             (const GLfloat *v);
typedef   void        (APIENTRY* pfnglRasterPos2i)              (GLint x, GLint y);
typedef   void        (APIENTRY* pfnglRasterPos2iv)             (const GLint *v);
typedef   void        (APIENTRY* pfnglRasterPos2s)              (GLshort x, GLshort y);
typedef   void        (APIENTRY* pfnglRasterPos2sv)             (const GLshort *v);
typedef   void        (APIENTRY* pfnglRasterPos3d)              (GLdouble x, GLdouble y, GLdouble z);
typedef   void        (APIENTRY* pfnglRasterPos3dv)             (const GLdouble *v);
typedef   void        (APIENTRY* pfnglRasterPos3f)              (GLfloat x, GLfloat y, GLfloat z);
typedef   void        (APIENTRY* pfnglRasterPos3fv)             (const GLfloat *v);
typedef   void        (APIENTRY* pfnglRasterPos3i)              (GLint x, GLint y, GLint z);
typedef   void        (APIENTRY* pfnglRasterPos3iv)             (const GLint *v);
typedef   void        (APIENTRY* pfnglRasterPos3s)              (GLshort x, GLshort y, GLshort z);
typedef   void        (APIENTRY* pfnglRasterPos3sv)             (const GLshort *v);
typedef   void        (APIENTRY* pfnglRasterPos4d)              (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef   void        (APIENTRY* pfnglRasterPos4dv)             (const GLdouble *v);
typedef   void        (APIENTRY* pfnglRasterPos4f)              (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef   void        (APIENTRY* pfnglRasterPos4fv)             (const GLfloat *v);
typedef   void        (APIENTRY* pfnglRasterPos4i)              (GLint x, GLint y, GLint z, GLint w);
typedef   void        (APIENTRY* pfnglRasterPos4iv)             (const GLint *v);
typedef   void        (APIENTRY* pfnglRasterPos4s)              (GLshort x, GLshort y, GLshort z, GLshort w);
typedef   void        (APIENTRY* pfnglRasterPos4sv)             (const GLshort *v);
typedef   void        (APIENTRY* pfnglReadBuffer)               (GLenum mode);
typedef   void        (APIENTRY* pfnglReadPixels)               (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
typedef   void        (APIENTRY* pfnglRectd)                    (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
typedef   void        (APIENTRY* pfnglRectdv)                   (const GLdouble *v1, const GLdouble *v2);
typedef   void        (APIENTRY* pfnglRectf)                    (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
typedef   void        (APIENTRY* pfnglRectfv)                   (const GLfloat *v1, const GLfloat *v2);
typedef   void        (APIENTRY* pfnglRecti)                    (GLint x1, GLint y1, GLint x2, GLint y2);
typedef   void        (APIENTRY* pfnglRectiv)                   (const GLint *v1, const GLint *v2);
typedef   void        (APIENTRY* pfnglRects)                    (GLshort x1, GLshort y1, GLshort x2, GLshort y2);
typedef   void        (APIENTRY* pfnglRectsv)                   (const GLshort *v1, const GLshort *v2);
typedef   GLint       (APIENTRY* pfnglRenderMode)               (GLenum mode);
typedef   void        (APIENTRY* pfnglRotated)                  (GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
typedef   void        (APIENTRY* pfnglRotatef)                  (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef   void        (APIENTRY* pfnglScaled)                   (GLdouble x, GLdouble y, GLdouble z);
typedef   void        (APIENTRY* pfnglScalef)                   (GLfloat x, GLfloat y, GLfloat z);
typedef   void        (APIENTRY* pfnglScissor)                  (GLint x, GLint y, GLsizei width, GLsizei height);
typedef   void        (APIENTRY* pfnglSelectBuffer)             (GLsizei size, GLuint *buffer);
typedef   void        (APIENTRY* pfnglShadeModel)               (GLenum mode);
typedef   void        (APIENTRY* pfnglStencilFunc)              (GLenum func, GLint ref, GLuint mask);
typedef   void        (APIENTRY* pfnglStencilMask)              (GLuint mask);
typedef   void        (APIENTRY* pfnglStencilOp)                (GLenum fail, GLenum zfail, GLenum zpass);
typedef   void        (APIENTRY* pfnglTexCoord1d)               (GLdouble s);
typedef   void        (APIENTRY* pfnglTexCoord1dv)              (const GLdouble *v);
typedef   void        (APIENTRY* pfnglTexCoord1f)               (GLfloat s);
typedef   void        (APIENTRY* pfnglTexCoord1fv)              (const GLfloat *v);
typedef   void        (APIENTRY* pfnglTexCoord1i)               (GLint s);
typedef   void        (APIENTRY* pfnglTexCoord1iv)              (const GLint *v);
typedef   void        (APIENTRY* pfnglTexCoord1s)               (GLshort s);
typedef   void        (APIENTRY* pfnglTexCoord1sv)              (const GLshort *v);
typedef   void        (APIENTRY* pfnglTexCoord2d)               (GLdouble s, GLdouble t);
typedef   void        (APIENTRY* pfnglTexCoord2dv)              (const GLdouble *v);
typedef   void        (APIENTRY* pfnglTexCoord2f)               (GLfloat s, GLfloat t);
typedef   void        (APIENTRY* pfnglTexCoord2fv)              (const GLfloat *v);
typedef   void        (APIENTRY* pfnglTexCoord2i)               (GLint s, GLint t);
typedef   void        (APIENTRY* pfnglTexCoord2iv)              (const GLint *v);
typedef   void        (APIENTRY* pfnglTexCoord2s)               (GLshort s, GLshort t);
typedef   void        (APIENTRY* pfnglTexCoord2sv)              (const GLshort *v);
typedef   void        (APIENTRY* pfnglTexCoord3d)               (GLdouble s, GLdouble t, GLdouble r);
typedef   void        (APIENTRY* pfnglTexCoord3dv)              (const GLdouble *v);
typedef   void        (APIENTRY* pfnglTexCoord3f)               (GLfloat s, GLfloat t, GLfloat r);
typedef   void        (APIENTRY* pfnglTexCoord3fv)              (const GLfloat *v);
typedef   void        (APIENTRY* pfnglTexCoord3i)               (GLint s, GLint t, GLint r);
typedef   void        (APIENTRY* pfnglTexCoord3iv)              (const GLint *v);
typedef   void        (APIENTRY* pfnglTexCoord3s)               (GLshort s, GLshort t, GLshort r);
typedef   void        (APIENTRY* pfnglTexCoord3sv)              (const GLshort *v);
typedef   void        (APIENTRY* pfnglTexCoord4d)               (GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef   void        (APIENTRY* pfnglTexCoord4dv)              (const GLdouble *v);
typedef   void        (APIENTRY* pfnglTexCoord4f)               (GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef   void        (APIENTRY* pfnglTexCoord4fv)              (const GLfloat *v);
typedef   void        (APIENTRY* pfnglTexCoord4i)               (GLint s, GLint t, GLint r, GLint q);
typedef   void        (APIENTRY* pfnglTexCoord4iv)              (const GLint *v);
typedef   void        (APIENTRY* pfnglTexCoord4s)               (GLshort s, GLshort t, GLshort r, GLshort q);
typedef   void        (APIENTRY* pfnglTexCoord4sv)              (const GLshort *v);
typedef   void        (APIENTRY* pfnglTexCoordPointer)          (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef   void        (APIENTRY* pfnglTexEnvf)                  (GLenum target, GLenum pname, GLfloat param);
typedef   void        (APIENTRY* pfnglTexEnvfv)                 (GLenum target, GLenum pname, const GLfloat *params);
typedef   void        (APIENTRY* pfnglTexEnvi)                  (GLenum target, GLenum pname, GLint param);
typedef   void        (APIENTRY* pfnglTexEnviv)                 (GLenum target, GLenum pname, const GLint *params);
typedef   void        (APIENTRY* pfnglTexGend)                  (GLenum coord, GLenum pname, GLdouble param);
typedef   void        (APIENTRY* pfnglTexGendv)                 (GLenum coord, GLenum pname, const GLdouble *params);
typedef   void        (APIENTRY* pfnglTexGenf)                  (GLenum coord, GLenum pname, GLfloat param);
typedef   void        (APIENTRY* pfnglTexGenfv)                 (GLenum coord, GLenum pname, const GLfloat *params);
typedef   void        (APIENTRY* pfnglTexGeni)                  (GLenum coord, GLenum pname, GLint param);
typedef   void        (APIENTRY* pfnglTexGeniv)                 (GLenum coord, GLenum pname, const GLint *params);
typedef   void        (APIENTRY* pfnglTexImage1D)               (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef   void        (APIENTRY* pfnglTexImage2D)               (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
typedef   void        (APIENTRY* pfnglTexParameterf)            (GLenum target, GLenum pname, GLfloat param);
typedef   void        (APIENTRY* pfnglTexParameterfv)           (GLenum target, GLenum pname, const GLfloat *params);
typedef   void        (APIENTRY* pfnglTexParameteri)            (GLenum target, GLenum pname, GLint param);
typedef   void        (APIENTRY* pfnglTexParameteriv)           (GLenum target, GLenum pname, const GLint *params);
typedef   void        (APIENTRY* pfnglTexSubImage1D)            (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
typedef   void        (APIENTRY* pfnglTexSubImage2D)            (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
typedef   void        (APIENTRY* pfnglTranslated)               (GLdouble x, GLdouble y, GLdouble z);
typedef   void        (APIENTRY* pfnglTranslatef)               (GLfloat x, GLfloat y, GLfloat z);
typedef   void        (APIENTRY* pfnglVertex2d)                 (GLdouble x, GLdouble y);
typedef   void        (APIENTRY* pfnglVertex2dv)                (const GLdouble *v);
typedef   void        (APIENTRY* pfnglVertex2f)                 (GLfloat x, GLfloat y);
typedef   void        (APIENTRY* pfnglVertex2fv)                (const GLfloat *v);
typedef   void        (APIENTRY* pfnglVertex2i)                 (GLint x, GLint y);
typedef   void        (APIENTRY* pfnglVertex2iv)                (const GLint *v);
typedef   void        (APIENTRY* pfnglVertex2s)                 (GLshort x, GLshort y);
typedef   void        (APIENTRY* pfnglVertex2sv)                (const GLshort *v);
typedef   void        (APIENTRY* pfnglVertex3d)                 (GLdouble x, GLdouble y, GLdouble z);
typedef   void        (APIENTRY* pfnglVertex3dv)                (const GLdouble *v);
typedef   void        (APIENTRY* pfnglVertex3f)                 (GLfloat x, GLfloat y, GLfloat z);
typedef   void        (APIENTRY* pfnglVertex3fv)                (const GLfloat *v);
typedef   void        (APIENTRY* pfnglVertex3i)                 (GLint x, GLint y, GLint z);
typedef   void        (APIENTRY* pfnglVertex3iv)                (const GLint *v);
typedef   void        (APIENTRY* pfnglVertex3s)                 (GLshort x, GLshort y, GLshort z);
typedef   void        (APIENTRY* pfnglVertex3sv)                (const GLshort *v);
typedef   void        (APIENTRY* pfnglVertex4d)                 (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef   void        (APIENTRY* pfnglVertex4dv)                (const GLdouble *v);
typedef   void        (APIENTRY* pfnglVertex4f)                 (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef   void        (APIENTRY* pfnglVertex4fv)                (const GLfloat *v);
typedef   void        (APIENTRY* pfnglVertex4i)                 (GLint x, GLint y, GLint z, GLint w);
typedef   void        (APIENTRY* pfnglVertex4iv)                (const GLint *v);
typedef   void        (APIENTRY* pfnglVertex4s)                 (GLshort x, GLshort y, GLshort z, GLshort w);
typedef   void        (APIENTRY* pfnglVertex4sv)                (const GLshort *v);
typedef   void        (APIENTRY* pfnglVertexPointer)            (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef   void        (APIENTRY* pfnglViewport)                 (GLint x, GLint y, GLsizei width, GLsizei height);

#ifdef WIN32
typedef   BOOL        (WINAPI*   pfnwglCopyContext)             (HGLRC, HGLRC, UINT);
typedef   HGLRC       (WINAPI*   pfnwglCreateContext)           (HDC);
typedef   HGLRC       (WINAPI*   pfnwglCreateLayerContext)      (HDC, int);
typedef   BOOL        (WINAPI*   pfnwglDeleteContext)           (HGLRC);
typedef   HGLRC       (WINAPI*   pfnwglGetCurrentContext)       (VOID);
typedef   HDC         (WINAPI*   pfnwglGetCurrentDC)            (VOID);
typedef   PROC        (WINAPI*   pfnwglGetProcAddress)          (LPCSTR);
typedef   BOOL        (WINAPI*   pfnwglMakeCurrent)             (HDC, HGLRC);
typedef   BOOL        (WINAPI*   pfnwglShareLists)              (HGLRC, HGLRC);
typedef   BOOL        (WINAPI*   pfnwglUseFontBitmapsA)         (HDC, DWORD, DWORD, DWORD);
typedef   BOOL        (WINAPI*   pfnwglUseFontBitmapsW)         (HDC, DWORD, DWORD, DWORD);
typedef   BOOL        (WINAPI*   pfnwglSwapBuffers)             (HDC);
#endif

/*******************************************************************************/
/* extensions */
/* EXT_vertex_array */
typedef void (APIENTRY * PFNGLARRAYELEMENTEXTPROC) (GLint i);
typedef void (APIENTRY * PFNGLDRAWARRAYSEXTPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRY * PFNGLVERTEXPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLNORMALPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLCOLORPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLINDEXPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLTEXCOORDPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLEDGEFLAGPOINTEREXTPROC) (GLsizei stride, GLsizei count, const GLboolean *pointer);
typedef void (APIENTRY * PFNGLGETPOINTERVEXTPROC) (GLenum pname, GLvoid* *params);
//typedef void (APIENTRY * PFNGLARRAYELEMENTARRAYEXTPROC)(GLenum mode, GLsizei count, const GLvoid* pi);

/* WIN_draw_range_elements */
typedef void (APIENTRY * PFNGLDRAWRANGEELEMENTSWINPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);

/* WIN_swap_hint */
typedef void (APIENTRY * PFNGLADDSWAPHINTRECTWINPROC)  (GLint x, GLint y, GLsizei width, GLsizei height);

/* EXT_paletted_texture */
typedef void (APIENTRY * PFNGLCOLORTABLEEXTPROC)
    (GLenum target, GLenum internalFormat, GLsizei width, GLenum format,
     GLenum type, const GLvoid *data);
typedef void (APIENTRY * PFNGLCOLORSUBTABLEEXTPROC)
    (GLenum target, GLsizei start, GLsizei count, GLenum format,
     GLenum type, const GLvoid *data);
typedef void (APIENTRY * PFNGLGETCOLORTABLEEXTPROC)
    (GLenum target, GLenum format, GLenum type, GLvoid *data);
typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)
    (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)
    (GLenum target, GLenum pname, GLfloat *params);

#if WIN32
typedef int   (WINAPI * pfnwglGetPixelFormat)(HDC);
typedef BOOL  (WINAPI * pfnwglSetPixelFormat)(HDC, int, CONST PIXELFORMATDESCRIPTOR *);
typedef int   (WINAPI * pfnwglDescribePixelFormat)(HDC, int, UINT, LPPIXELFORMATDESCRIPTOR);
typedef int   (WINAPI * pfnwglChoosePixelFormat)(HDC, CONST PIXELFORMATDESCRIPTOR *);
#endif

extern pfnglAccum glAccum;
extern pfnglAlphaFunc glAlphaFunc;
extern pfnglAreTexturesResident glAreTexturesResident;
extern pfnglArrayElement glArrayElement;
extern pfnglBegin glBegin;
extern pfnglBindTexture glBindTexture;
extern pfnglBitmap glBitmap;
extern pfnglBlendFunc glBlendFunc;
extern pfnglCallList glCallList;
extern pfnglCallLists glCallLists;
extern pfnglClear glClear;
extern pfnglClearAccum glClearAccum;
extern pfnglClearColor glClearColor;
extern pfnglClearDepth glClearDepth;
extern pfnglClearIndex glClearIndex;
extern pfnglClearStencil glClearStencil;
extern pfnglClipPlane glClipPlane;
extern pfnglColor3b glColor3b;
extern pfnglColor3bv glColor3bv;
extern pfnglColor3d glColor3d;
extern pfnglColor3dv glColor3dv;
extern pfnglColor3f glColor3f;
extern pfnglColor3fv glColor3fv;
extern pfnglColor3i glColor3i;
extern pfnglColor3iv glColor3iv;
extern pfnglColor3s glColor3s;
extern pfnglColor3sv glColor3sv;
extern pfnglColor3ub glColor3ub;
extern pfnglColor3ubv glColor3ubv;
extern pfnglColor3ui glColor3ui;
extern pfnglColor3uiv glColor3uiv;
extern pfnglColor3us glColor3us;
extern pfnglColor3usv glColor3usv;
extern pfnglColor4b glColor4b;
extern pfnglColor4bv glColor4bv;
extern pfnglColor4d glColor4d;
extern pfnglColor4dv glColor4dv;
extern pfnglColor4f glColor4f;
extern pfnglColor4fv glColor4fv;
extern pfnglColor4i glColor4i;
extern pfnglColor4iv glColor4iv;
extern pfnglColor4s glColor4s;
extern pfnglColor4sv glColor4sv;
extern pfnglColor4ub glColor4ub;
extern pfnglColor4ubv glColor4ubv;
extern pfnglColor4ui glColor4ui;
extern pfnglColor4uiv glColor4uiv;
extern pfnglColor4us glColor4us;
extern pfnglColor4usv glColor4usv;
extern pfnglColorMask glColorMask;
extern pfnglColorMaterial glColorMaterial;
extern pfnglColorPointer glColorPointer;
extern pfnglCopyPixels glCopyPixels;
extern pfnglCopyTexImage1D glCopyTexImage1D;
extern pfnglCopyTexImage2D glCopyTexImage2D;
extern pfnglCopyTexSubImage1D glCopyTexSubImage1D;
extern pfnglCopyTexSubImage2D glCopyTexSubImage2D;
extern pfnglCullFace glCullFace;
extern pfnglDeleteLists glDeleteLists;
extern pfnglDeleteTextures glDeleteTextures;
extern pfnglDepthFunc glDepthFunc;
extern pfnglDepthMask glDepthMask;
extern pfnglDepthRange glDepthRange;
extern pfnglDisable glDisable;
extern pfnglDisableClientState glDisableClientState;
extern pfnglDrawArrays glDrawArrays;
extern pfnglDrawBuffer glDrawBuffer;
extern pfnglDrawElements glDrawElements;
extern pfnglDrawPixels glDrawPixels;
extern pfnglEdgeFlag glEdgeFlag;
extern pfnglEdgeFlagPointer glEdgeFlagPointer;
extern pfnglEdgeFlagv glEdgeFlagv;
extern pfnglEnable glEnable;
extern pfnglEnableClientState glEnableClientState;
extern pfnglEnd glEnd;
extern pfnglEndList glEndList;
extern pfnglEvalCoord1d glEvalCoord1d;
extern pfnglEvalCoord1dv glEvalCoord1dv;
extern pfnglEvalCoord1f glEvalCoord1f;
extern pfnglEvalCoord1fv glEvalCoord1fv;
extern pfnglEvalCoord2d glEvalCoord2d;
extern pfnglEvalCoord2dv glEvalCoord2dv;
extern pfnglEvalCoord2f glEvalCoord2f;
extern pfnglEvalCoord2fv glEvalCoord2fv;
extern pfnglEvalMesh1 glEvalMesh1;
extern pfnglEvalMesh2 glEvalMesh2;
extern pfnglEvalPoint1 glEvalPoint1;
extern pfnglEvalPoint2 glEvalPoint2;
extern pfnglFeedbackBuffer glFeedbackBuffer;
extern pfnglFinish glFinish;
extern pfnglFlush glFlush;
extern pfnglFogf glFogf;
extern pfnglFogfv glFogfv;
extern pfnglFogi glFogi;
extern pfnglFogiv glFogiv;
extern pfnglFrontFace glFrontFace;
extern pfnglFrustum glFrustum;
extern pfnglGenLists glGenLists;
extern pfnglGenTextures glGenTextures;
extern pfnglGetBooleanv glGetBooleanv;
extern pfnglGetClipPlane glGetClipPlane;
extern pfnglGetDoublev glGetDoublev;
extern pfnglGetError glGetError;
extern pfnglGetFloatv glGetFloatv;
extern pfnglGetIntegerv glGetIntegerv;
extern pfnglGetLightfv glGetLightfv;
extern pfnglGetLightiv glGetLightiv;
extern pfnglGetMapdv glGetMapdv;
extern pfnglGetMapfv glGetMapfv;
extern pfnglGetMapiv glGetMapiv;
extern pfnglGetMaterialfv glGetMaterialfv;
extern pfnglGetMaterialiv glGetMaterialiv;
extern pfnglGetPixelMapfv glGetPixelMapfv;
extern pfnglGetPixelMapuiv glGetPixelMapuiv;
extern pfnglGetPixelMapusv glGetPixelMapusv;
extern pfnglGetPointerv glGetPointerv;
extern pfnglGetPolygonStipple glGetPolygonStipple;
extern pfnglGetString glGetString;
extern pfnglGetTexEnvfv glGetTexEnvfv;
extern pfnglGetTexEnviv glGetTexEnviv;
extern pfnglGetTexGendv glGetTexGendv;
extern pfnglGetTexGenfv glGetTexGenfv;
extern pfnglGetTexGeniv glGetTexGeniv;
extern pfnglGetTexImage glGetTexImage;
extern pfnglGetTexLevelParameterfv glGetTexLevelParameterfv;
extern pfnglGetTexLevelParameteriv glGetTexLevelParameteriv;
extern pfnglGetTexParameterfv glGetTexParameterfv;
extern pfnglGetTexParameteriv glGetTexParameteriv;
extern pfnglHint glHint;
extern pfnglIndexd glIndexd;
extern pfnglIndexdv glIndexdv;
extern pfnglIndexf glIndexf;
extern pfnglIndexfv glIndexfv;
extern pfnglIndexi glIndexi;
extern pfnglIndexiv glIndexiv;
extern pfnglIndexMask glIndexMask;
extern pfnglIndexPointer glIndexPointer;
extern pfnglIndexs glIndexs;
extern pfnglIndexsv glIndexsv;
extern pfnglIndexub glIndexub;
extern pfnglIndexubv glIndexubv;
extern pfnglInitNames glInitNames;
extern pfnglInterleavedArrays glInterleavedArrays;
extern pfnglIsEnabled glIsEnabled;
extern pfnglIsList glIsList;
extern pfnglIsTexture glIsTexture;
extern pfnglLightf glLightf;
extern pfnglLightfv glLightfv;
extern pfnglLighti glLighti;
extern pfnglLightiv glLightiv;
extern pfnglLightModelf glLightModelf;
extern pfnglLightModelfv glLightModelfv;
extern pfnglLightModeli glLightModeli;
extern pfnglLightModeliv glLightModeliv;
extern pfnglLineStipple glLineStipple;
extern pfnglLineWidth glLineWidth;
extern pfnglListBase glListBase;
extern pfnglLoadIdentity glLoadIdentity;
extern pfnglLoadMatrixd glLoadMatrixd;
extern pfnglLoadMatrixf glLoadMatrixf;
extern pfnglLoadName glLoadName;
extern pfnglLogicOp glLogicOp;
extern pfnglMap1d glMap1d;
extern pfnglMap1f glMap1f;
extern pfnglMap2d glMap2d;
extern pfnglMap2f glMap2f;
extern pfnglMapGrid1d glMapGrid1d;
extern pfnglMapGrid1f glMapGrid1f;
extern pfnglMapGrid2d glMapGrid2d;
extern pfnglMapGrid2f glMapGrid2f;
extern pfnglMaterialf glMaterialf;
extern pfnglMaterialfv glMaterialfv;
extern pfnglMateriali glMateriali;
extern pfnglMaterialiv glMaterialiv;
extern pfnglMatrixMode glMatrixMode;
extern pfnglMultMatrixd glMultMatrixd;
extern pfnglMultMatrixf glMultMatrixf;
extern pfnglNewList glNewList;
extern pfnglNormal3b glNormal3b;
extern pfnglNormal3bv glNormal3bv;
extern pfnglNormal3d glNormal3d;
extern pfnglNormal3dv glNormal3dv;
extern pfnglNormal3f glNormal3f;
extern pfnglNormal3fv glNormal3fv;
extern pfnglNormal3i glNormal3i;
extern pfnglNormal3iv glNormal3iv;
extern pfnglNormal3s glNormal3s;
extern pfnglNormal3sv glNormal3sv;
extern pfnglNormalPointer glNormalPointer;
extern pfnglOrtho glOrtho;
extern pfnglPassThrough glPassThrough;
extern pfnglPixelMapfv glPixelMapfv;
extern pfnglPixelMapuiv glPixelMapuiv;
extern pfnglPixelMapusv glPixelMapusv;
extern pfnglPixelStoref glPixelStoref;
extern pfnglPixelStorei glPixelStorei;
extern pfnglPixelTransferf glPixelTransferf;
extern pfnglPixelTransferi glPixelTransferi;
extern pfnglPixelZoom glPixelZoom;
extern pfnglPointSize glPointSize;
extern pfnglPolygonMode glPolygonMode;
extern pfnglPolygonOffset glPolygonOffset;
extern pfnglPolygonStipple glPolygonStipple;
extern pfnglPopAttrib glPopAttrib;
extern pfnglPopClientAttrib glPopClientAttrib;
extern pfnglPopMatrix glPopMatrix;
extern pfnglPopName glPopName;
extern pfnglPrioritizeTextures glPrioritizeTextures;
extern pfnglPushAttrib glPushAttrib;
extern pfnglPushClientAttrib glPushClientAttrib;
extern pfnglPushMatrix glPushMatrix;
extern pfnglPushName glPushName;
extern pfnglRasterPos2d glRasterPos2d;
extern pfnglRasterPos2dv glRasterPos2dv;
extern pfnglRasterPos2f glRasterPos2f;
extern pfnglRasterPos2fv glRasterPos2fv;
extern pfnglRasterPos2i glRasterPos2i;
extern pfnglRasterPos2iv glRasterPos2iv;
extern pfnglRasterPos2s glRasterPos2s;
extern pfnglRasterPos2sv glRasterPos2sv;
extern pfnglRasterPos3d glRasterPos3d;
extern pfnglRasterPos3dv glRasterPos3dv;
extern pfnglRasterPos3f glRasterPos3f;
extern pfnglRasterPos3fv glRasterPos3fv;
extern pfnglRasterPos3i glRasterPos3i;
extern pfnglRasterPos3iv glRasterPos3iv;
extern pfnglRasterPos3s glRasterPos3s;
extern pfnglRasterPos3sv glRasterPos3sv;
extern pfnglRasterPos4d glRasterPos4d;
extern pfnglRasterPos4dv glRasterPos4dv;
extern pfnglRasterPos4f glRasterPos4f;
extern pfnglRasterPos4fv glRasterPos4fv;
extern pfnglRasterPos4i glRasterPos4i;
extern pfnglRasterPos4iv glRasterPos4iv;
extern pfnglRasterPos4s glRasterPos4s;
extern pfnglRasterPos4sv glRasterPos4sv;
extern pfnglReadBuffer glReadBuffer;
extern pfnglReadPixels glReadPixels;
extern pfnglRectd glRectd;
extern pfnglRectdv glRectdv;
extern pfnglRectf glRectf;
extern pfnglRectfv glRectfv;
extern pfnglRecti glRecti;
extern pfnglRectiv glRectiv;
extern pfnglRects glRects;
extern pfnglRectsv glRectsv;
extern pfnglRenderMode glRenderMode;
extern pfnglRotated glRotated;
extern pfnglRotatef glRotatef;
extern pfnglScaled glScaled;
extern pfnglScalef glScalef;
extern pfnglScissor glScissor;
extern pfnglSelectBuffer glSelectBuffer;
extern pfnglShadeModel glShadeModel;
extern pfnglStencilFunc glStencilFunc;
extern pfnglStencilMask glStencilMask;
extern pfnglStencilOp glStencilOp;
extern pfnglTexCoord1d glTexCoord1d;
extern pfnglTexCoord1dv glTexCoord1dv;
extern pfnglTexCoord1f glTexCoord1f;
extern pfnglTexCoord1fv glTexCoord1fv;
extern pfnglTexCoord1i glTexCoord1i;
extern pfnglTexCoord1iv glTexCoord1iv;
extern pfnglTexCoord1s glTexCoord1s;
extern pfnglTexCoord1sv glTexCoord1sv;
extern pfnglTexCoord2d glTexCoord2d;
extern pfnglTexCoord2dv glTexCoord2dv;
extern pfnglTexCoord2f glTexCoord2f;
extern pfnglTexCoord2fv glTexCoord2fv;
extern pfnglTexCoord2i glTexCoord2i;
extern pfnglTexCoord2iv glTexCoord2iv;
extern pfnglTexCoord2s glTexCoord2s;
extern pfnglTexCoord2sv glTexCoord2sv;
extern pfnglTexCoord3d glTexCoord3d;
extern pfnglTexCoord3dv glTexCoord3dv;
extern pfnglTexCoord3f glTexCoord3f;
extern pfnglTexCoord3fv glTexCoord3fv;
extern pfnglTexCoord3i glTexCoord3i;
extern pfnglTexCoord3iv glTexCoord3iv;
extern pfnglTexCoord3s glTexCoord3s;
extern pfnglTexCoord3sv glTexCoord3sv;
extern pfnglTexCoord4d glTexCoord4d;
extern pfnglTexCoord4dv glTexCoord4dv;
extern pfnglTexCoord4f glTexCoord4f;
extern pfnglTexCoord4fv glTexCoord4fv;
extern pfnglTexCoord4i glTexCoord4i;
extern pfnglTexCoord4iv glTexCoord4iv;
extern pfnglTexCoord4s glTexCoord4s;
extern pfnglTexCoord4sv glTexCoord4sv;
extern pfnglTexCoordPointer glTexCoordPointer;
extern pfnglTexEnvf glTexEnvf;
extern pfnglTexEnvfv glTexEnvfv;
extern pfnglTexEnvi glTexEnvi;
extern pfnglTexEnviv glTexEnviv;
extern pfnglTexGend glTexGend;
extern pfnglTexGendv glTexGendv;
extern pfnglTexGenf glTexGenf;
extern pfnglTexGenfv glTexGenfv;
extern pfnglTexGeni glTexGeni;
extern pfnglTexGeniv glTexGeniv;
extern pfnglTexImage1D glTexImage1D;
extern pfnglTexImage2D glTexImage2D;
extern pfnglTexParameterf glTexParameterf;
extern pfnglTexParameterfv glTexParameterfv;
extern pfnglTexParameteri glTexParameteri;
extern pfnglTexParameteriv glTexParameteriv;
extern pfnglTexSubImage1D glTexSubImage1D;
extern pfnglTexSubImage2D glTexSubImage2D;
extern pfnglTranslated glTranslated;
extern pfnglTranslatef glTranslatef;
extern pfnglVertex2d glVertex2d;
extern pfnglVertex2dv glVertex2dv;
extern pfnglVertex2f glVertex2f;
extern pfnglVertex2fv glVertex2fv;
extern pfnglVertex2i glVertex2i;
extern pfnglVertex2iv glVertex2iv;
extern pfnglVertex2s glVertex2s;
extern pfnglVertex2sv glVertex2sv;
extern pfnglVertex3d glVertex3d;
extern pfnglVertex3dv glVertex3dv;
extern pfnglVertex3f glVertex3f;
extern pfnglVertex3fv glVertex3fv;
extern pfnglVertex3i glVertex3i;
extern pfnglVertex3iv glVertex3iv;
extern pfnglVertex3s glVertex3s;
extern pfnglVertex3sv glVertex3sv;
extern pfnglVertex4d glVertex4d;
extern pfnglVertex4dv glVertex4dv;
extern pfnglVertex4f glVertex4f;
extern pfnglVertex4fv glVertex4fv;
extern pfnglVertex4i glVertex4i;
extern pfnglVertex4iv glVertex4iv;
extern pfnglVertex4s glVertex4s;
extern pfnglVertex4sv glVertex4sv;
extern pfnglVertexPointer glVertexPointer;
extern pfnglViewport glViewport;

#ifdef WIN32
extern pfnwglCopyContext dynwglCopyContext;
extern pfnwglCreateContext dynwglCreateContext;
extern pfnwglCreateLayerContext dynwglCreateLayerContext;
extern pfnwglDeleteContext dynwglDeleteContext;
extern pfnwglGetCurrentContext dynwglGetCurrentContext;
extern pfnwglGetCurrentDC dynwglGetCurrentDC;
extern pfnwglGetProcAddress dynwglGetProcAddress;
extern pfnwglMakeCurrent dynwglMakeCurrent;
extern pfnwglShareLists dynwglShareLists;
extern pfnwglSwapBuffers dynwglSwapBuffers;
extern pfnwglUseFontBitmapsA dynwglUseFontBitmapsA;
extern pfnwglUseFontBitmapsW dynwglUseFontBitmapsW;

extern pfnwglGetPixelFormat dynwglGetPixelFormat;
extern pfnwglSetPixelFormat dynwglSetPixelFormat;
extern pfnwglDescribePixelFormat dynwglDescribePixelFormat;
extern pfnwglChoosePixelFormat dynwglChoosePixelFormat;
#endif

/* extra fns */
int
dynglLoad(char *pszDllName);

int
dynglUnload(void);

void
dynglCheckExtensions(void);

extern int dyngl_GL_EXT_clip_volume_hint;
extern int dyngl_GL_EXT_texture_env_add;
extern int dyngl_GL_EXT_texture_env_combine;
extern int dyngl_GL_NV_texture_env_combine4;
extern int dyngl_GL_ARB_multitexture;

/* extensions */
#define GL_CLIP_VOLUME_CLIPPING_HINT_EXT        0x80F0

/* EXT_texture_env_combine */
#define GL_COMBINE_EXT                      0x8570
#define GL_COMBINE_RGB_EXT                  0x8571
#define GL_COMBINE_ALPHA_EXT                0x8572
#define GL_RGB_SCALE_EXT                    0x8573
#define GL_ADD_SIGNED_EXT                   0x8574
#define GL_INTERPOLATE_EXT                  0x8575
#define GL_CONSTANT_EXT                     0x8576
#define GL_PRIMARY_COLOR_EXT                0x8577
#define GL_PREVIOUS_EXT                     0x8578
#define GL_SOURCE0_RGB_EXT                  0x8580
#define GL_SOURCE1_RGB_EXT                  0x8581
#define GL_SOURCE2_RGB_EXT                  0x8582
#define GL_SOURCE0_ALPHA_EXT                0x8588
#define GL_SOURCE1_ALPHA_EXT                0x8589
#define GL_SOURCE2_ALPHA_EXT                0x858A
#define GL_OPERAND0_RGB_EXT                 0x8590
#define GL_OPERAND1_RGB_EXT                 0x8591
#define GL_OPERAND2_RGB_EXT                 0x8592
#define GL_OPERAND0_ALPHA_EXT               0x8598
#define GL_OPERAND1_ALPHA_EXT               0x8599
#define GL_OPERAND2_ALPHA_EXT               0x859A

/* NV_texture_env_combine4 */
#define GL_COMBINE4_NV                      0x8503
#define GL_SOURCE3_RGB_NV                   0x8583
#define GL_SOURCE3_ALPHA_NV                 0x858B
#define GL_OPERAND3_RGB_NV                  0x8593
#define GL_OPERAND3_ALPHA_NV                0x859B


/* ARB_multitexture */
#define GL_ACTIVE_TEXTURE_ARB               0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB        0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB            0x84E2
#define GL_TEXTURE0_ARB                     0x84C0
#define GL_TEXTURE1_ARB                     0x84C1
#define GL_TEXTURE2_ARB                     0x84C2
#define GL_TEXTURE3_ARB                     0x84C3
#define GL_TEXTURE4_ARB                     0x84C4
#define GL_TEXTURE5_ARB                     0x84C5
#define GL_TEXTURE6_ARB                     0x84C6
#define GL_TEXTURE7_ARB                     0x84C7
#define GL_TEXTURE8_ARB                     0x84C8
#define GL_TEXTURE9_ARB                     0x84C9
#define GL_TEXTURE10_ARB                    0x84CA
#define GL_TEXTURE11_ARB                    0x84CB
#define GL_TEXTURE12_ARB                    0x84CC
#define GL_TEXTURE13_ARB                    0x84CD
#define GL_TEXTURE14_ARB                    0x84CE
#define GL_TEXTURE15_ARB                    0x84CF
#define GL_TEXTURE16_ARB                    0x84D0
#define GL_TEXTURE17_ARB                    0x84D1
#define GL_TEXTURE18_ARB                    0x84D2
#define GL_TEXTURE19_ARB                    0x84D3
#define GL_TEXTURE20_ARB                    0x84D4
#define GL_TEXTURE21_ARB                    0x84D5
#define GL_TEXTURE22_ARB                    0x84D6
#define GL_TEXTURE23_ARB                    0x84D7
#define GL_TEXTURE24_ARB                    0x84D8
#define GL_TEXTURE25_ARB                    0x84D9
#define GL_TEXTURE26_ARB                    0x84DA
#define GL_TEXTURE27_ARB                    0x84DB
#define GL_TEXTURE28_ARB                    0x84DC
#define GL_TEXTURE29_ARB                    0x84DD
#define GL_TEXTURE30_ARB                    0x84CE
#define GL_TEXTURE31_ARB                    0x84DF

/* ARB_multitexture */
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DARBPROC) (GLenum target, GLdouble s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FARBPROC) (GLenum target, GLfloat s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IARBPROC) (GLenum target, GLint s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SARBPROC) (GLenum target, GLshort s);
typedef void (APIENTRY * PFNGLMULTITEXCOORD1SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DARBPROC) (GLenum target, GLdouble s, GLdouble t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FARBPROC) (GLenum target, GLfloat s, GLfloat t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IARBPROC) (GLenum target, GLint s, GLint t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SARBPROC) (GLenum target, GLshort s, GLshort t);
typedef void (APIENTRY * PFNGLMULTITEXCOORD2SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IARBPROC) (GLenum target, GLint s, GLint t, GLint r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (APIENTRY * PFNGLMULTITEXCOORD3SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DARBPROC) (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4DVARBPROC) (GLenum target, const GLdouble *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4FVARBPROC) (GLenum target, const GLfloat *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IARBPROC) (GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4IVARBPROC) (GLenum target, const GLint *v);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SARBPROC) (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (APIENTRY * PFNGLMULTITEXCOORD4SVARBPROC) (GLenum target, const GLshort *v);
typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC) (GLenum target);
typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREARBPROC) (GLenum target);

extern PFNGLMULTITEXCOORD1DARBPROC glMultiTexCoord1dARB;
extern PFNGLMULTITEXCOORD1DVARBPROC glMultiTexCoord1dvARB;
extern PFNGLMULTITEXCOORD1FARBPROC glMultiTexCoord1fARB;
extern PFNGLMULTITEXCOORD1FVARBPROC glMultiTexCoord1fvARB;
extern PFNGLMULTITEXCOORD1IARBPROC glMultiTexCoord1iARB;
extern PFNGLMULTITEXCOORD1IVARBPROC glMultiTexCoord1ivARB;
extern PFNGLMULTITEXCOORD1SARBPROC glMultiTexCoord1sARB;
extern PFNGLMULTITEXCOORD1SVARBPROC glMultiTexCoord1svARB;
extern PFNGLMULTITEXCOORD2DARBPROC glMultiTexCoord2dARB;
extern PFNGLMULTITEXCOORD2DVARBPROC glMultiTexCoord2dvARB;
extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern PFNGLMULTITEXCOORD2FVARBPROC glMultiTexCoord2fvARB;
extern PFNGLMULTITEXCOORD2IARBPROC glMultiTexCoord2iARB;
extern PFNGLMULTITEXCOORD2IVARBPROC glMultiTexCoord2ivARB;
extern PFNGLMULTITEXCOORD2SARBPROC glMultiTexCoord2sARB;
extern PFNGLMULTITEXCOORD2SVARBPROC glMultiTexCoord2svARB;
extern PFNGLMULTITEXCOORD3DARBPROC glMultiTexCoord3dARB;
extern PFNGLMULTITEXCOORD3DVARBPROC glMultiTexCoord3dvARB;
extern PFNGLMULTITEXCOORD3FARBPROC glMultiTexCoord3fARB;
extern PFNGLMULTITEXCOORD3FVARBPROC glMultiTexCoord3fvARB;
extern PFNGLMULTITEXCOORD3IARBPROC glMultiTexCoord3iARB;
extern PFNGLMULTITEXCOORD3IVARBPROC glMultiTexCoord3ivARB;
extern PFNGLMULTITEXCOORD3SARBPROC glMultiTexCoord3sARB;
extern PFNGLMULTITEXCOORD3SVARBPROC glMultiTexCoord3svARB;
extern PFNGLMULTITEXCOORD4DARBPROC glMultiTexCoord4dARB;
extern PFNGLMULTITEXCOORD4DVARBPROC glMultiTexCoord4dvARB;
extern PFNGLMULTITEXCOORD4FARBPROC glMultiTexCoord4fARB;
extern PFNGLMULTITEXCOORD4FVARBPROC glMultiTexCoord4fvARB;
extern PFNGLMULTITEXCOORD4IARBPROC glMultiTexCoord4iARB;
extern PFNGLMULTITEXCOORD4IVARBPROC glMultiTexCoord4ivARB;
extern PFNGLMULTITEXCOORD4SARBPROC glMultiTexCoord4sARB;
extern PFNGLMULTITEXCOORD4SVARBPROC glMultiTexCoord4svARB;
extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;


#ifdef __cplusplus
}
#endif

#endif /* __GL_H__ */
#endif /* __gl_h_ */
