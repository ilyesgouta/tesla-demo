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

#include <stdio.h>
#include <string.h>

extern "C" {

#include <jpeglib.h>
#include <jerror.h>

}

#include "../../ImageLib.hpp"

typedef struct {

  struct jpeg_source_mgr pub;	/* public fields */
  JOCTET * buffer;		/* start of buffer */
  char	*name;			/* my file name */

} my_source_mgr;

struct my_error_mgr
{
	struct jpeg_error_mgr pub;	/* "public" fields */
};

/*******************************************************************************************/
void term_source(j_decompress_ptr cinfo) {

}
/*******************************************************************************************/
void skip_input_data(j_decompress_ptr cinfo,long bytes_to_skip) {

	my_source_mgr* src;

	src= (my_source_mgr*)cinfo->src;
	src->pub.bytes_in_buffer-=bytes_to_skip;
	src->pub.next_input_byte+=bytes_to_skip;
}
/*******************************************************************************************/
int fill_input_buffer(j_decompress_ptr cinfo)
{
	return 0;
}
/*******************************************************************************************/
void init_source(j_decompress_ptr cinfo) {

}
/*******************************************************************************************/
void my_error_exit( j_common_ptr cinfo ) {
	
}
/*******************************************************************************************/
CImage* ReadJPG( FILE* hFile, unsigned int dwFileLen ) {

        struct jpeg_decompress_struct cinfo;
        struct my_error_mgr jerr;
        JSAMPARRAY buffer; /* Output row buffer */
        int row_stride;    /* physical row width in output buffer */

        CImage* pResult = 0;

        unsigned int dwWidth, dwHeight, dwBPP;
        unsigned char* pRawData;

        /* init error handler */
        cinfo.err = jpeg_std_error( &jerr.pub );
        jerr.pub.error_exit = my_error_exit;


        /* init decompression */
        jpeg_create_decompress( &cinfo );

	my_source_mgr* src;

	if ( cinfo.src == 0 )
	{
      cinfo.src=(struct jpeg_source_mgr*)(*cinfo.mem->alloc_small)((j_common_ptr)&cinfo,JPOOL_PERMANENT,sizeof(my_source_mgr));
	  src = (my_source_mgr*)cinfo.src;
      src->buffer=(JOCTET *)(*cinfo.mem->alloc_small)((j_common_ptr)&cinfo,JPOOL_PERMANENT,dwFileLen*sizeof(JOCTET));
	}

        fseek( hFile, 0, SEEK_SET );
        fread( src->buffer, dwFileLen, 1, hFile );

	src = (my_source_mgr*)cinfo.src;
	src->pub.init_source = init_source;
	src->pub.fill_input_buffer = fill_input_buffer;
	src->pub.skip_input_data = skip_input_data;
	src->pub.resync_to_restart = jpeg_resync_to_restart;
	src->pub.term_source = term_source;
	src->pub.bytes_in_buffer = dwFileLen;   /* forces fill_input_buffer on first read */
	src->pub.next_input_byte = src->buffer; /* until buffer loaded */

        /* get info about jpeg file */
        jpeg_read_header( &cinfo, 1 );

        if ( cinfo.num_components == 1 ) dwBPP = 8;
        else if ( cinfo.num_components == 3 ) dwBPP = 24;
        else return 0;

        dwWidth = cinfo.image_width;
        dwHeight = cinfo.image_height;
        pRawData = new unsigned char[dwWidth*dwHeight*(dwBPP>>3)];

        /* decompress data */
        jpeg_start_decompress( &cinfo );
        row_stride = cinfo.output_width*cinfo.output_components;

        buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
        unsigned int dwRow = 0;

	while( cinfo.output_scanline < cinfo.output_height )
	{
	  jpeg_read_scanlines( &cinfo, buffer, 1 );
          memcpy( pRawData + dwRow*dwWidth*(dwBPP>>3), buffer[0], row_stride );
          dwRow++;
	}

        jpeg_finish_decompress( &cinfo );
        jpeg_destroy_decompress( &cinfo );

        /* create image */
        pResult = new CImage( dwWidth, dwHeight, dwBPP, pRawData );

        return pResult;
}
/*******************************************************************************************/

