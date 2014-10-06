#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdlib.h>

/*  Example: Reading game data from text file.
    ---------------------------------------------
    char*         path  = "data/names.dat";
    const size_t  size  = file_get_size(path);
    char*         str   = malloc(size);
    file_read(str, size, path);

    (Do stuff with the string...)

    free(str);
    ---------------------------------------------
*/

//Note: "dest" must have memory allocated first. Use "file_size()" for correct size.
char* file_read(char* dest, size_t size, const char* path);

size_t file_length(const char* path);

#endif // FILE_HANDLING_H
