#include "world.hpp"

#include <vector>

#include "mon.hpp"

namespace world
{

Map_Ent_Ptr               terrain[map_w][map_h];
std::vector<Map_Ent_Ptr>  mobs;

void init()
{
    TRACE_FUNC_BEGIN;

    cleanup();

    for (int x = 0; x < map_w; ++x)
    {
        for (int y = 0; y < map_h; ++y)
        {
            P p(x, y);
            Char_And_Clr render_data('.', clr_green);

            terrain[x][y] = Map_Ent_Ptr(new Map_Ent(p, render_data));
        }
    }

    auto castle_ptr = Map_Ent_Ptr(new Castle(P(1, 1)));
    terrain[1][1]   = std::move(castle_ptr);

    auto army_ptr   = Map_Ent_Ptr(new Army(P(5, 3)));
    mobs.push_back(std::move(army_ptr));

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    mobs.resize(0);

    TRACE_FUNC_END;
}

void process()
{
    const P& old_pos = mobs[0]->pos();
    const P  new_pos = old_pos.x == 5 ? P(6, 3) : P(5, 3);

    mobs[0]->set_pos(new_pos);
}

} // world
