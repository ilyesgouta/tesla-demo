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

#ifdef WIN32
#include "stdafx.h"
#endif

#include "CMatrix.hpp"

/******************************************************************************************/
void CMatrix::Inverse() {

        double a,b,c,d,e,f,g,h,i,j,k,l;
        register double dW;

        a = m_.aMatrix[ 0]; b = m_.aMatrix[ 1]; c = m_.aMatrix[ 2];
        d = m_.aMatrix[ 4]; e = m_.aMatrix[ 5]; f = m_.aMatrix[ 6];
        g = m_.aMatrix[ 8]; h = m_.aMatrix[ 9]; i = m_.aMatrix[10];
        j = m_.aMatrix[12]; k = m_.aMatrix[13]; l = m_.aMatrix[14];

        dW = 1.0 / (a*(e*i - f*h) 
                   - (b*(d*i - f*g) 
                   + c*(e*g - d*h)));

        m_.aMatrix[ 0]= (float)((e*i - f*h) * dW);
        m_.aMatrix[ 1]= (float)((c*h - b*i) * dW);
        m_.aMatrix[ 2]= (float)((b*f - c*e) * dW);

        m_.aMatrix[ 4]= (float)((f*g - d*i) * dW);
        m_.aMatrix[ 5]= (float)((a*i - c*g) * dW);
        m_.aMatrix[ 6]= (float)((c*d - a*f) * dW);

        m_.aMatrix[ 8]= (float)((d*h - e*g) * dW);
        m_.aMatrix[ 9]= (float)((b*g - a*h) * dW);
        m_.aMatrix[10]= (float)((a*e - b*d) * dW);

        m_.aMatrix[12]= (float)((e*(g*l - i*j)
                             + f*(h*j - g*k)
                             - d*(h*l - i*k)) * dW);
        m_.aMatrix[13]= (float)((a*(h*l - i*k)
                            + b*(i*j - g*l)
                            + c*(g*k - h*j)) * dW);
        m_.aMatrix[14]= (float)((b*(d*l - f*j)
                             + c*(e*j - d*k)
                             - a*(e*l - f*k)) * dW);
}
/******************************************************************************************/
void CMatrix::Transpose() {

        CMatrix cTmp;

        for ( int y = 0; y != 4; y++ )
        {
          for ( int x = 0; x != 4; x++ )
            cTmp.m_.aMatrix[x*4 + y] = m_.aMatrix[y*4 + x];
        }
        
        (*this) = cTmp;
}
/******************************************************************************************/
void CMatrix::MulVertices( CVector* pDestVertices, CVector* pSrcVertices, int iCount ) {

        for ( int i = 0; i != iCount; i++ )
        {
          pDestVertices[i] = (*this)*pSrcVertices[i];
        }
}
/******************************************************************************************/
void CMatrix::MulVectors( CVector* pDestVectors, CVector* pSrcVectors, int iCount ) {

        for ( int i = 0; i != iCount; i++ )
        {
          pDestVectors[i] = (*this) << pSrcVectors[i];
        }
}
/******************************************************************************************/

