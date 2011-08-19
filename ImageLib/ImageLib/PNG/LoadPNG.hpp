// y.

#if !defined (_LOAD_PNG_HPP_)
#define _LOAD_PNG_HPP_

#include <stdio.h>



class CImage;

extern CImage* ReadPNG( FILE* hFile, unsigned int dwFileLen );

#endif
