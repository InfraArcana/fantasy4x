#include "base.h"

#include <SDL.h>

#include "api.h"
#include "render.h"
#include "input.h"
#include "cmn_data.h"
#include "world.h"

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
  input_init();
  world_init();

  bool quit_game = false;

  clear_scr();

  while(!quit_game) {
    clear_scr();

    draw_normal_mode();

    //draw_text_xy("Hm?", 10, 5, &clr_white, NULL);

    render_present();

    input_get_cmd(&quit_game);
  }

  world_cleanup();
  render_cleanup();
  api_cleanup();

  TRACE_FUNC_END;
  return 0;
}
