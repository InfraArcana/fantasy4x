#ifndef WORLD_H //Note: "MAP_H" is reserved for map height
#define WORLD_H

#include "cmn_utils.hpp"

struct Map_Cell
{
    Map_Cell() :
        p       (Pos(0, 0)),
        ch      (0),
        clr     (clr_black) {}

    Pos     p;
    char    ch;
    Clr     clr;
};

namespace world
{

void init();

void cleanup();

Char_And_Clr get_map_cell_render_data(const Pos& p);

} // world

#endif // MAP_H
