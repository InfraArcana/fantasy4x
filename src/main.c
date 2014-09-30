#include "base.h"

#include <SDL.h>

#include "api.h"
#include "render.h"
#include "input.h"
#include "cmn_data.h"

#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#undef main
#endif
int main(int argc, char* argv[]) {
  TRACE_FUNC_BEGIN;

  (void)argc;
  (void)argv;

  api_init();
  render_init();

  clear_scr();
  draw_text_xy("Weeoo", 1, 1, &clr_white, &clr_black);

  char str_buffer[80];

  strcpy(str_buffer, "Oh hello!");
  draw_text_xy(str_buffer, 1, 2, &clr_white, &clr_black);

  draw_text_xy(to_str(str_buffer, 20, 3), 1, 3, &clr_white, &clr_black);

  draw_text_xy(str_app(str_buffer, 20, " Hi?"), 1, 3, &clr_white, &clr_black);

  render_present();

  sleep(2000);

  render_cleanup();
  api_cleanup();

  TRACE_FUNC_END;
  return 0;
}
