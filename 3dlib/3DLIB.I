;// programming by Yoghurt/Pulse  v4.0
;// date 31.08.1998
;// copyright (C) by Konrad Zagorowicz
;// 様様様様様様様様様様様様様様様様様

struc vector_t
	.x	RESD	1
	.y	RESD	1
	.z	RESD	1
endstruc

struc color_t
	.r	RESD	1
	.g	RESD	1
	.b	RESD	1
endstruc

struc map_t
	.width	RESD	1
	.height RESD	1
	.bpp	RESD	1
	.modulo RESD	1
	.data	RESD	1
endstruc

struc texel_t
	.u	RESD	1
	.v	RESD	1
endstruc

