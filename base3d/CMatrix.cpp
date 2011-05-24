
#include "stdafx.h"

/******************************************************************************************/
void CMatrix::Inverse() {

        double a,b,c,d,e,f,g,h,i,j,k,l;
        register double dW;

        a = aMatrix[ 0]; b = aMatrix[ 1]; c = aMatrix[ 2];
        d = aMatrix[ 4]; e = aMatrix[ 5]; f = aMatrix[ 6];
        g = aMatrix[ 8]; h = aMatrix[ 9]; i = aMatrix[10];
        j = aMatrix[12]; k = aMatrix[13]; l = aMatrix[14];

        dW = 1.0 / (a*(e*i - f*h) 
                   - (b*(d*i - f*g) 
                   + c*(e*g - d*h)));

        aMatrix[ 0]= (float)((e*i - f*h) * dW);
        aMatrix[ 1]= (float)((c*h - b*i) * dW);
        aMatrix[ 2]= (float)((b*f - c*e) * dW);

        aMatrix[ 4]= (float)((f*g - d*i) * dW);
        aMatrix[ 5]= (float)((a*i - c*g) * dW);
        aMatrix[ 6]= (float)((c*d - a*f) * dW);

        aMatrix[ 8]= (float)((d*h - e*g) * dW);
        aMatrix[ 9]= (float)((b*g - a*h) * dW);
        aMatrix[10]= (float)((a*e - b*d) * dW);

        aMatrix[12]= (float)((e*(g*l - i*j)
                             + f*(h*j - g*k)
                             - d*(h*l - i*k)) * dW);
        aMatrix[13]= (float)((a*(h*l - i*k)
                            + b*(i*j - g*l)
                            + c*(g*k - h*j)) * dW);
        aMatrix[14]= (float)((b*(d*l - f*j)
                             + c*(e*j - d*k)
                             - a*(e*l - f*k)) * dW);
}
/******************************************************************************************/
void CMatrix::Transpose() {

        CMatrix cTmp;

        for ( int y = 0; y != 4; y++ )
        {
          for ( int x = 0; x != 4; x++ )
            cTmp.aMatrix[x*4 + y] = aMatrix[y*4 + x];
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

