#include <ncurses.h>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    initscr();
    printw("Hello world!");
    refresh();
    getch();
    endwin();

    return 0;
}

/*
#include "base.hpp"

#include <SDL.h>

#include "api.hpp"
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

    api::init();
    render::init();
    input::init();
    race_data::init();
    world::init();

    bool quit_game = false;

    render::clear_scr();

    while (!quit_game)
    {
        render::clear_scr();

        render::draw_normal_mode();

        //draw_text_xy(str, 10, 5, &clr_white, nullptr);

        render::render_present();

        input::get_cmd(&quit_game);
    }

    world::cleanup();
    race_data::cleanup();
    render::cleanup();
    api::cleanup();

    TRACE_FUNC_END;
    return 0;
}
*/
