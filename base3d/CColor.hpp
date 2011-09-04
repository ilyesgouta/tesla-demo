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


#if !defined(CColor_hpp)
#define CColor_hpp

//************************************************************************************
class CColor
{
public:
	CColor() {}
	CColor(float R, float G, float B, float A) {
	  fR = R; fG = G; fB = B; fA = A;
	}
	CColor(float R, float G, float B) {
	  fR = R; fG = G; fB = B; fA = 1.0f;
	}

        float fR, fG, fB, fA;

};
//************************************************************************************

#endif