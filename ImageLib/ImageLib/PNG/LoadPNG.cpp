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
