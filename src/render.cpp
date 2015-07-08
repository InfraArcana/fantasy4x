#include "render.hpp"

#include "lib_wrap.hpp"
#include "cmn_data.hpp"
#include "utils.hpp"
#include "world.hpp"

namespace render
{

namespace
{

P viewport_(0, 0);

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;

    cleanup();

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    viewport_.set(0, 0);

    TRACE_FUNC_END;
}

/*
void draw_text(const std::string& text, const P& p, const Clr& clr, const Clr& bg_clr)
{
    if (p.y >= 0 && p.y < SCR_H)
    {
        P px_p = p * P(CELL_PX_W, cell_px_h);

        const int px_x0 = px_p.x;

        for (auto it = begin(text); it != end(text); ++it)
        {
            bool is_new_line_char = false;
            if (*it == '\n')
            {
                px_p = P(px_x0, px_p.y + cell_px_h);
                is_new_line_char = true;
            }
            if (px_p.x < 0 || px_p.x >= scr_px_w)
            {
                return;
            }
            if (!is_new_line_char)
            {
                draw_char_at_px(*it, px_p, clr, bg_clr);
                px_p.x += cell_px_w;
            }
        }
    }
}
*/

void draw_normal_mode()
{
    const P viewport_size(lib_wrap::scr_size()); // TODO: This is true for now...

    const P p1(viewport_ + viewport_size - 1);

    for (int x = viewport_.x; x <= p1.x; ++x)
    {
        for (int y = viewport_.y; y <= p1.y; ++y)
        {
            const P p(x, y);

            const auto& render_data = world::terrain[p.x][p.y]->render_data();

            lib_wrap::draw_ch(render_data.ch, p, render_data.clr);
        }
    }

    for (const auto& mob_ptr : world::mobs)
    {
        const auto& p           = mob_ptr->pos();
        const auto& render_data = mob_ptr->render_data();

        lib_wrap::draw_ch(render_data.ch, p, render_data.clr);
    }
}

} // render
