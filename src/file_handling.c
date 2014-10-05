#include "file_handling.h"

#include <stdio.h>

#include "base.h"
#include "cmn_utils.h"

char* file_read(char* dest, size_t size, const char* path) {
  TRACE_FUNC_BEGIN;

  assert(dest);

  FILE* stream = fopen(path, "r");

  if(!stream) {
    char error_msg[80] = "Failed to open file: ";
    str_app(error_msg, 80, path);
    TRACE(error_msg);
    assert(false);
  }

  fread(dest, size, 1, stream);

  fclose(stream);

  TRACE_FUNC_END;
  return dest;
}

size_t file_size(const char* path) {
  TRACE_FUNC_BEGIN;

  FILE* stream = fopen(path, "r");

  if(!stream) {
    char error_msg[80] = "Failed to open file: ";
    str_app(error_msg, 80, path);
    TRACE(error_msg);
    assert(false);
  }

  fseek(stream, 0L, SEEK_END);  //Seek to the end of the file
  size_t size = ftell(stream);  //Get size
  fseek(stream, 0L, SEEK_SET);  //Seek back to beginning

  fclose(stream);

  TRACE_FUNC_END;
  return size;
}
