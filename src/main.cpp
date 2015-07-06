
/*
int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    lib_wrap::init();

    lib_wrap::draw_text("Testing", {20, 3}, clr_black, clr_white);

    lib_wrap::update_scr();

    lib_wrap::get_key();

    lib_wrap::cleanup();

    return 0;
}
*/

#include "lib_wrap.hpp"
#include "utils.hpp"
#include "render.hpp"
#include "input.hpp"
#include "cmn_data.hpp"
#include "world.hpp"
#include "mon.hpp"

#include <string.h>
#include <stdlib.h>

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

    bool quit_game = false;

    while (!quit_game)
    {
        lib_wrap::clear_scr();

        render::draw_normal_mode();

        lib_wrap::update_scr();

        const auto key = lib_wrap::get_key();

        if (key == 'q') // NOTE: Temporary solution to quit the game nicely
        {
            quit_game = true;
        }

        //input::get_cmd(&quit_game);
    }

    world::cleanup();
    race_data::cleanup();
    render::cleanup();
    lib_wrap::cleanup();

    TRACE_FUNC_END;
    return 0;
}
