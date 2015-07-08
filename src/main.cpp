#include <string.h>
#include <stdlib.h>

#include "lib_wrap.hpp"
#include "utils.hpp"
#include "render.hpp"
#include "input.hpp"
#include "cmn_data.hpp"
#include "world.hpp"
#include "mon.hpp"

#ifdef _WIN32
#undef main
#endif

int main(int argc, char* argv[])
{
    TRACE_FUNC_BEGIN;

    (void)argc;
    (void)argv;

    lib_wrap::init();
    render::init();
    //input::init();
    race_data::init();
    world::init();

    int     key         = 0;
    bool    quit_game   = false;

    while (!quit_game)
    {
        lib_wrap::clear_scr();

        render::draw_normal_mode();

        lib_wrap::update_scr();

        if (key == 'q') // NOTE: Temporary solution to quit the game nicely
        {
            quit_game = true;
        }

        //input::cmd(&quit_game);

        world::process();

        lib_wrap::sleep(1);
    }

    world::cleanup();
    race_data::cleanup();
    //input::cleanup();
    render::cleanup();
    lib_wrap::cleanup();

    TRACE_FUNC_END;
    return 0;
}
