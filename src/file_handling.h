#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdlib.h>

/*  Example: Reading game data from text file.
    ---------------------------------------------
    const char*   PATH  = "data/races.dat";
    const size_t  SIZE  = file_length(PATH);
    char*         str   = malloc(SIZE);
    file_read(str, SIZE, PATH);

    (Do stuff with the string...)

    free(str);
    ---------------------------------------------
*/

//Note: "dest" must have memory allocated first. Use "file_size()" for correct size.
char* file_read(char* dest, size_t size, const char* path);

size_t file_length(const char* path);

#endif // FILE_HANDLING_H
