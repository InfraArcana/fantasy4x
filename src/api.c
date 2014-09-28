#include "api.h"

#include "base.h"

#include <SDL_image.h>

bool api_inited_ = false;

void api_init() {
  TRACE_FUNC_BEGIN;

  api_inited_ = true;

  if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    TRACE("Failed to init SDL");
    TRACE(SDL_GetError());
    assert(false);
  }

  if(IMG_Init(IMG_INIT_PNG) == -1) {
    TRACE("Failed to init SDL_image");
    TRACE(IMG_GetError());
    assert(false);
  }

  TRACE_FUNC_END;
}

void api_cleanup() {
  TRACE_FUNC_BEGIN;
  api_inited_ = false;
  IMG_Quit();
  SDL_Quit();
  TRACE_FUNC_END;
}

void sleep(const Uint32 DURATION) {
  if(api_inited_) {
    if(DURATION == 1) {
      SDL_Delay(1);
    } else {
      const Uint32 WAIT_UNTIL = SDL_GetTicks() + DURATION;
      while(SDL_GetTicks() < WAIT_UNTIL) {SDL_PumpEvents();}
    }
  }
}
