#include "file_handling.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "base.h"
#include "cmn_utils.h"

char* file_read(char* dest, size_t size, const char* path) {
  TRACE_FUNC_BEGIN;

  assert(dest);

  //Make sure the string will be null terminated
  str_fill_nul(dest, size);

  FILE* stream = fopen(path, "r");

  if(!stream) {
    char error_msg[80] = "Failed to open file: ";
    str_app(error_msg, 80, path);
    TRACE(error_msg);
    assert(false);
  }

  const size_t FREAD_STATUS = fread(dest, size, 1, stream);

  printf("feof: %d, ferror: %d\n", feof(stream), ferror(stream));

  if(FREAD_STATUS == 0) {
    if(feof(stream)) {
      TRACE("Reached end of file.");
    }
    if(ferror(stream)) {
      TRACE("An error occurred while reading file.");
      assert(false);
    }
  }

  fclose(stream);

  TRACE_FUNC_END;
  return dest;
}

size_t file_length(const char* path) {
  TRACE_FUNC_BEGIN;

  struct stat stat_result;

  const int STATUS = stat(path, &stat_result);

  if(STATUS != 0) {
    char error_msg[80] = "Failed to read file: ";
    str_app(error_msg, 80, path);
    TRACE(error_msg);
    assert(false);
  }

  TRACE_FUNC_END;
  return stat_result.st_size;
}
