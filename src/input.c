#include "input.h"

#include <SDL.h>

#include "render.h"
#include "api.h"

bool      inited_ = false;
SDL_Event sdl_event_;

void input_init() {
  TRACE_FUNC_BEGIN;
  inited_ = true;
  TRACE_FUNC_END;
}

static void key_pressed_(SDL_Keycode sdl_keycode, bool* quit_game) {
  switch(sdl_keycode) {
    case SDLK_ESCAPE: {*quit_game = true;}

    default: {} break;
  }
}

void input_get_cmd(bool* quit_game) {
  if(inited_) {

    bool done = false;

    while(!done) {

      SDL_PollEvent(&sdl_event_);

      switch(sdl_event_.type) {
        case SDL_QUIT: {
          *quit_game  = true;
          done        = true;
        } break;

        case SDL_WINDOWEVENT: {
          switch(sdl_event_.window.event) {
            case SDL_WINDOWEVENT_RESIZED: {on_window_resized();} break;
          }
        } break;

        case SDL_KEYDOWN: {
          key_pressed_(sdl_event_.key.keysym.sym, quit_game);
          done = true;
        } break;

        default: {} break;
      }

      sleep(1);
    }
  }
}
