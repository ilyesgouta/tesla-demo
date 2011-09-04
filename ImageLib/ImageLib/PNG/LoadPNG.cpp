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
// y.

#include "../../ImageLib.hpp"
#include "LoadPNG.hpp"

#include <png.h>

CImage* ReadPNG( FILE* hFile, unsigned int dwFileLen ) {

        CImage* pResult = 0;

        png_structp read_ptr;
        png_infop info_ptr;
        png_infop end_info;
        png_uint_32 rowbytes;
        int channels, num_pass, pass;

        read_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
        info_ptr = png_create_info_struct( read_ptr );
        end_info = png_create_info_struct( read_ptr );

        if ( setjmp(read_ptr->jmpbuf) )
        {
          png_destroy_read_struct( &read_ptr, &info_ptr, &end_info );
          return pResult;
        }

        png_init_io( read_ptr, hFile );
        png_read_info( read_ptr, info_ptr );

        if ( (info_ptr->color_type&PNG_COLOR_TYPE_PALETTE) == PNG_COLOR_TYPE_PALETTE )
        {
          channels = 1;
        }
        else
          channels = 3;

        if ( info_ptr->color_type&PNG_COLOR_MASK_ALPHA ) channels++;

        rowbytes = ((info_ptr->width*info_ptr->bit_depth*channels + 7) >> 3);

        if ( info_ptr->interlace_type )
        {
          num_pass = png_set_interlace_handling(read_ptr);
        }
        else
          num_pass = 1;


        unsigned char* pRaw = new unsigned char[info_ptr->width*info_ptr->height*channels];
        unsigned char* pRow;


        for ( pass = 0; pass < num_pass; pass++ )
        {
          for ( unsigned int i = 0; i != info_ptr->height; i++ ) 
          {
            pRow = &pRaw[rowbytes*i];
            png_read_rows( read_ptr, &pRow, 0, 1 );
          }
        }

        pResult = new CImage( info_ptr->width, info_ptr->height, channels<<3, pRaw );

        png_read_end( read_ptr, end_info );
        png_destroy_read_struct( &read_ptr, &info_ptr, &end_info );


        return pResult;
}
