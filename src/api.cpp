#include "api.hpp"

#include "base.hpp"

#include <SDL_image.h>

namespace api
{

namespace
{

bool inited_ = false;

}

void init()
{
    TRACE_FUNC_BEGIN;

    inited_ = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        TRACE << "Failed to init SDL" << std::endl
              << SDL_GetError() << std::endl;
        assert(false);
    }

    if (IMG_Init(IMG_INIT_PNG) == -1)
    {
        TRACE << "Failed to init SDL_image" << std::endl
              << IMG_GetError() << std::endl;
        assert(false);
    }

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;
    inited_ = false;
    IMG_Quit();
    SDL_Quit();
    TRACE_FUNC_END;
}

void sleep(Uint32 duration)
{
    if (inited_)
    {
        if (duration == 1)
        {
            SDL_Delay(1);
        }
        else
        {
            const Uint32 WAIT_UNTIL = SDL_GetTicks() + duration;

            while (SDL_GetTicks() < WAIT_UNTIL)
            {
                SDL_PumpEvents();
            }
        }
    }
}

} // api
