#include "input.hpp"

#include <SDL.h>

#include "render.hpp"
#include "api.hpp"

namespace input
{

namespace
{

bool      inited_ = false;
SDL_Event sdl_event_;

void key_pressed(SDL_Keycode sdl_keycode, bool* quit_game)
{
    switch (sdl_keycode)
    {
    case SDLK_ESCAPE: {*quit_game = true;}

    default: break;
    }
}

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;
    inited_ = true;
    TRACE_FUNC_END;
}

void get_cmd(bool* quit_game)
{
    if (inited_)
    {
        bool done = false;

        while (!done)
        {
            SDL_PollEvent(&sdl_event_);

            switch (sdl_event_.type)
            {
            case SDL_QUIT:
                *quit_game  = true;
                done        = true;
                break;

            case SDL_WINDOWEVENT:
                switch (sdl_event_.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    render::on_window_resized();
                    break;
                }
                break;

            case SDL_KEYDOWN:
                key_pressed(sdl_event_.key.keysym.sym, quit_game);
                done = true;
                break;

            default:
                break;
            }

            api::sleep(1);
        }
    }
}

} // input
