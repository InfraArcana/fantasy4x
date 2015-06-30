#include "world.hpp"

#include <vector>

#include "mon.hpp"

namespace world
{

Map_Ent_Ptr               terrain[MAP_W][MAP_H];
std::vector<Map_Ent_Ptr>  mobs;

void init()
{
    TRACE_FUNC_BEGIN;

    cleanup();

    for (int x = 0; x < MAP_W; ++x)
    {
        for (int y = 0; y < MAP_H; ++y)
        {
            Pos p(x, y);
            Char_And_Clr render_data('.', clr_green);

            terrain[x][y] = Map_Ent_Ptr(new Map_Ent(p, render_data));
        }
    }

    auto castle_ptr = Map_Ent_Ptr(new Castle(Pos(1, 1)));
    terrain[1][1]   = std::move(castle_ptr);

    auto army_ptr   = Map_Ent_Ptr(new Army(Pos(5, 3)));
    mobs.push_back(std::move(army_ptr));

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    mobs.resize(0);

    TRACE_FUNC_END;
}

} // world
