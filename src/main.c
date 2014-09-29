#include "base.h"

#include <SDL.h>

#include "api.h"
#include "render.h"
#include "input.h"
#include "cmn_data.h"

#include <limits.h>

#ifdef _WIN32
#undef main
#endif
int main(int argc, char* argv[]) {
  str_buffer_t str_buffer = "First part.";

  TRACE_FUNC_BEGIN;

  (void)argc;
  (void)argv;

  api_init();
  render_init();

  clear_scr();
  draw_text_xy("Weeoo", 1, 1, &clr_white, &clr_black);

  str_append(&str_buffer, " Second part.");
  draw_text_xy(str_buffer, 1, 2, &clr_white, &clr_black);

  str_set(&str_buffer, "Hi!");
  draw_text_xy(str_buffer, 1, 3, &clr_white, &clr_black);

  render_present();

  sleep(4000);

  render_cleanup();
  api_cleanup();

  TRACE_FUNC_END;
  return 0;
}
