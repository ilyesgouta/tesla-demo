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
// programing by Yoghurt
// copyright (C) 1999 by Konrad Zagorowicz

#if !defined _INLINE_3D_HPP_
#define _INLINE_3D_HPP_

static inline void clamp(float* pData) {
#ifdef WIN32
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
#else
    float f = *pData;

    if (f > 1.0f)
        f = 1.0f;

    if (f < 0.0f)
        f = 0.0f;

    *pData = f;
#endif
}

#endif

