

#if !defined _LOAD_TGA_HPP_
#define _LOAD_TGA_HPP_

#include <stdio.h>

class CImage;

extern CImage* ReadTGA( FILE* hFile, unsigned int dwFileLen );

#endif /*_LOAD_TGA_HPP_*/