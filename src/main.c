#include "base.h"

#include <SDL.h>

#include "api.h"
#include "render.h"
#include "input.h"

#ifdef _WIN32
#undef main
#endif
int main(int argc, char* argv[]) {
  TRACE_FUNC_BEGIN;

  (void)argc;
  (void)argv;

  api_init();
  render_init();

  sleep(1000);

  render_cleanup();
  api_cleanup();

  TRACE_FUNC_END;
  return 0;
}
