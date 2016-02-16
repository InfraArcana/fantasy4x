#include "world.hpp"

#include <vector>

#include "io.hpp"
#include "mon.hpp"

namespace world
{

std::unique_ptr<Map_Ent> terrain[map_w][map_h];
std::vector< std::unique_ptr<Map_Ent> > mobs;

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

            terrain[x][y] = std::unique_ptr<Map_Ent>(new Map_Ent(p, render_data));
        }
    }

    auto castle_ptr = std::unique_ptr<Map_Ent>(new Castle(P(1, 1)));
    terrain[1][1]   = std::move(castle_ptr);

    auto army_ptr   = std::unique_ptr<Map_Ent>(new Army(P(5, 3)));
    mobs.push_back(std::move(army_ptr));

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    mobs.resize(0);

    TRACE_FUNC_END;
}

void render()
{
//    const P viewport_size(io::scr_px_size()); // TODO: This is true for now...

    const P viewport_size(viewport_cells_w, viewport_cells_h);

    const P viewport = io::viewport();

    const P p1(viewport + viewport_size - 1);

    for (int x = viewport.x; x <= p1.x; ++x)
    {
        for (int y = viewport.y; y <= p1.y; ++y)
        {
            const P p(x, y);

            const auto& render_data = world::terrain[p.x][p.y]->render_data();

            io::draw_ch(render_data.ch, p, render_data.clr);
        }
    }

    for (const auto& mob_ptr : world::mobs)
    {
        const auto& p           = mob_ptr->pos();
        const auto& render_data = mob_ptr->render_data();

        io::draw_ch(render_data.ch, p, render_data.clr);
    }
}

void process()
{
    const P& old_pos = mobs[0]->pos();
    const P  new_pos = old_pos.x == 5 ? P(6, 3) : P(5, 3);

    mobs[0]->set_pos(new_pos);
}

} // world
