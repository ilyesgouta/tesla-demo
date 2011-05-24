;code by yoghurt/pulse

GLOBAL _fMathInit
GLOBAL _fSqrt
GLOBAL _fReciSqrt
GLOBAL _vDist

%ifndef __COFF__
%define __COFF__
%endif

%include "macros.i"

MODEL_CCALL

BiasPos 	equ	23

ReciSqrtBits	equ	15
ReciTableSize	equ	(2 << (ReciSqrtBits-1))


;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께 uDATA
section _DATA
d05	dd	0.5
;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께 uDATA
section _BSS BSS

Sqrt2		resd	1
ReciSqrt2	resd	1

ReciSqrtTable	resd	ReciTableSize
SqrtTable	resd	ReciTableSize

tempFloat	resd	1

;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께� CODE
section _TEXT
%include  "3dlib.i"
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
InitSqrt

		push	eax
		push	ebx
		push	edi
		push	esi

		mov	esi,SqrtTable
		xor	edi,edi
		mov	ebx,07fh
		shl	ebx,BiasPos
		mov	ecx,ReciTableSize

.loop:		mov	eax,edi
		shl	eax,BiasPos-ReciSqrtBits
		or	eax,ebx
		mov	[tempFloat],eax
		fld	dword [tempFloat]
		fsqrt
		fstp	dword [esi]
		and	dword [esi],011111111111111111111111b

		inc	edi
		add	esi,4
		dec	ecx
		jnz	.loop

		pop	esi
		pop	edi
		pop	ebx
		pop	eax
		ret
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
InitReciprocalSqrt

		push	eax
		push	ebx
		push	edi
		push	esi

		mov	esi,ReciSqrtTable
		xor	edi,edi
		mov	ebx,07fh
		shl	ebx,BiasPos
		mov	ecx,ReciTableSize

.loop:		mov	eax,edi
		shl	eax,BiasPos-ReciSqrtBits
		or	eax,ebx
		mov	[tempFloat],eax
		fld	dword [tempFloat]
		fsqrt
		fld1
		fdivrp	st1,st0
		fstp	dword [esi]
		and	dword [esi],011111111111111111111111b

		inc	edi
		add	esi,4
		dec	ecx
		jnz	.loop

		pop	esi
		pop	edi
		pop	ebx
		pop	eax
		ret
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
_fMathInit
		fld1
		fld1
		faddp	st1,st0
		fsqrt
		fst	dword [Sqrt2]
		fld1
		fdivrp	st1,st0
		fmul	dword [d05]
		fstp	dword [ReciSqrt2]

		call	InitReciprocalSqrt
		call	InitSqrt
		ret
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
_fSqrt
		push	eax
		push	ebx

		mov	eax,[esp+12]
		mov	ebx,[esp+12]

		shr	eax,BiasPos-ReciSqrtBits
		shr	ebx,BiasPos

		and	eax,0111111111111111b
		and	ebx,$0ff
		sub	ebx,$7f
		test	ebx,1
		jz	.skip1
		fld	dword [Sqrt2]
		jmp	.cont
.skip1: 	fld1
.cont:		shr	ebx,1
		add	ebx,$7f
		shl	ebx,23
		or	ebx,[SqrtTable+eax*4]
		mov	[tempFloat],ebx
		fmul	dword [tempFloat]

		pop	ebx
		pop	eax
		ret
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
_fReciSqrt
		push	eax
		push	ebx

		mov	eax,[esp+12]
		mov	ebx,[esp+12]

		shr	eax,BiasPos-ReciSqrtBits
		shr	ebx,BiasPos

		and	eax,0111111111111111b
		and	ebx,$0ff
		sub	ebx,$7f
		test	ebx,1
		jz	.skip1
		fld	dword [ReciSqrt2]
		jmp	.cont
.skip1: 	fld	dword [d05]
.cont:		shr	ebx,1
		neg	ebx
		add	ebx,$7f
		shl	ebx,23
		or	ebx,[ReciSqrtTable+eax*4]
		mov	[tempFloat],ebx
		fmul	dword [tempFloat]

		pop	ebx
		pop	eax
		ret
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
_vDist
		push	eax
		push	ebx
		
		mov	eax,[esp+12]
		mov	ebx,[esp+16]

		fld	dword [eax+vector_t.x]
		fsub	dword [ebx+vector_t.x]    ; dx
		fld	dword [eax+vector_t.y]
		fld	dword [ebx+vector_t.y]
		fsubp	st1,st0		    ; dy dx
		fld	dword [eax+vector_t.z]
		fld	dword [ebx+vector_t.z]
		fsubp	st1,st0		    ; dz dy dx
		fld	st1		    ; dy dz dy dx
		fld	st3		    ; dx dy dz dy dx
		fmulp	st4,st0		    ; dy dz dy dx2
		fmulp	st2,st0		    ; dz dy2 dx2
		fld	st0
		fmulp	st1,st0		    ; dz2 dy2 dx2
		faddp	st1,st0
		faddp	st1,st0
		fstp	dword [tempFloat]
		push	dword [tempFloat]
		call	_fSqrt
		pop	eax

		pop	ebx
		pop	eax
		ret
;같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같

;께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께

