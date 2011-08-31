//
// (c) Copyright 2011 Ilyes Gouta, ilyes.gouta@gmail.com
//
// This utility unpacks the tesla demo assets used for rendering.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//

#include <stdio.h>
#include <libgen.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{
    FILE *file;

    if (argc < 2)
        return -1;

    file = fopen(argv[1], "rb");

    if (!file)
        return -2;

    int res_offset;
    int res_count;

    int i;

    fseek(file, -4, SEEK_END);
    fread(&res_offset, 1, sizeof(res_offset), file);

    fseek(file, res_offset, SEEK_SET);
    fread(&res_count, 1, sizeof(res_count), file);

    printf("found %d resources ..\n", res_count);

    for (i = 0; i < res_count; i++)
    {
        int start_offset, length, zeros, path_len;
        char path[64], *c;

        fread(&start_offset, 1, sizeof(start_offset), file);
        fread(&length, 1, sizeof(length), file);
        fread(&zeros, 1, sizeof(zeros), file);
        fread(&path_len, 1, sizeof(path_len), file);
        fread(path, 1, path_len, file);

        c = path;

        while (*c)
        {
            if (*c == '\\')
                *c = '/';
            else
                *c = tolower(*c);
            c++;
        }

        printf("%s is %d bytes at offset %d\n", path, length, start_offset);

        char path2[64];
        strcpy(path2, path); // path gets truncated in dirname() */

        char *dir = dirname(path);

        c = dir;

        while (*c)
        {
            char *d = strstr(c, "/");

            if (d) {
                *d = 0;
                mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                *d = '/';
                c = d + 1;
            } else {
                mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                break;
            }
        }

        int cur_offset = ftell(file);

        char *data = (char*)calloc(1, length);

        if (data)
        {
            FILE* res = fopen(path2, "wb");

            if (res) {
                fseek(file, start_offset, SEEK_SET);
                fread(data, 1, length, file);

                fwrite(data, 1, length, res);
                fclose(res);
            } else
                printf("couldn't open destination file! %s\n", path);

            free(data);
        } else
            printf("couldn't allocate buffer!\n");

        fseek(file, cur_offset, SEEK_SET);
    }

    fclose(file);

    return 0;
}
