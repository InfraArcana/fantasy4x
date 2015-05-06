#include "world.hpp"

#include <vector>

#include "actor.hpp"

namespace world
{

namespace
{

Map_Cell            cells_[MAP_W][MAP_H];
std::vector<Actor>  actors_;

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;

    for (int x = 0; x < MAP_W; ++x)
    {
        for (int y = 0; y < MAP_H; ++y)
        {
            Map_Cell& cell  = cells_[x][y];

            cell.p          = {x, y};
            cell.ch         = '.';
            cell.clr        = clr_green_lgt;
        }
    }

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    actors_.resize(0);

    TRACE_FUNC_END;
}

Char_And_Clr get_map_cell_render_data(const Pos& p)
{
    Map_Cell& cell  = cells_[p.x][p.y];

    return Char_And_Clr(cell.ch, cell.clr, clr_black);
}

} // world
