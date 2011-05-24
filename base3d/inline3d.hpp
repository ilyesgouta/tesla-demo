// programing by Yoghurt
// copyright (C) 1999 by Konrad Zagorowicz

#if !defined _INLINE_3D_HPP_
#define _INLINE_3D_HPP_

static inline void clamp(float* pData) {
        __asm  {
          mov eax, [pData]
          cmp dword ptr [eax], 0x3f800000
          jbe __skip
          test dword ptr [eax], 0x80000000
          jz __setone
          mov dword ptr [eax], 0
          jmp __skip
__setone: mov dword ptr [eax], 0x3f800000
__skip:
        }
}

#endif

