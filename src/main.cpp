#include <string.h>
#include <stdlib.h>

#include "io.hpp"
#include "mon.hpp"
#include "world.hpp"
#include "ui.hpp"
#include "utils.hpp"
#include "state.hpp"

#ifdef _WIN32
#undef main
#endif

int main(int argc, char* argv[])
{
    TRACE_FUNC_BEGIN;

    (void)argc;
    (void)argv;

    io::init();
    race_data::init();
    world::init();
    states::init();

    auto main_menu_state    = std::make_unique<Main_Menu_State>();
    auto state              = std::make_unique<State>(std::move(main_menu_state));
    states::push_state(std::move(state));

    bool quit_game = false;

    while (!quit_game)
    {
        io::clear_scr();

        states::render();

        io::update_scr();

        Input_Data input = io::wait_input();

        if (input.key == 'q') // NOTE: Temporary solution to quit the game nicely
        {
            quit_game = true;
        }

        states::handle_input(input);
    }

    states::cleanup();
    world::cleanup();
    race_data::cleanup();
    io::cleanup();

    TRACE_FUNC_END;
    return 0;
}
