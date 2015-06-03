#include "render.hpp"

#include <SDL_image.h>

#include "base.hpp"
#include "cmn_data.hpp"
#include "utils.hpp"
#include "world.hpp"

namespace render
{

namespace
{

SDL_Window*     sdl_window_     = nullptr;
SDL_Renderer*   sdl_renderer_   = nullptr;
Pos             viewport_       = {0, 0};
bool            font_px_data_[256][128];

const int NR_FONT_IMAGE_GLYPHS_X = 32;

bool is_inited()
{
    return sdl_window_ != nullptr;
}

void set_render_clr(const Clr& clr)
{
    SDL_SetRenderDrawColor(sdl_renderer_, clr.r, clr.g, clr.b, SDL_ALPHA_OPAQUE);
}

Uint32 get_px(const SDL_Surface& surface, int px_x, int px_y)
{
    int bpp = surface.format->BytesPerPixel;
    // Here p is the address to the pixel we want to retrieve
    Uint8* px = (Uint8*)surface.pixels + px_y * surface.pitch + px_x * bpp;

    switch (bpp)
    {
    case 1:   return *px;           break;
    case 2:   return *(Uint16*)px;  break;
    case 3:
    {
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            return px[0] << 16 | px[1] << 8 | px[2];
        }
        else
        {
            return px[0] | px[1] << 8 | px[2] << 16;
        }
    } break;
    case 4:   return *(Uint32*)px;  break;
    default:  return -1;            break;
    }
    return -1;
}

void load_font_data()
{
    TRACE_FUNC_BEGIN;

    SDL_Surface* font_surface_tmp = IMG_Load(font_img_path.c_str());

    assert(font_surface_tmp && "Failed to load font image");

    Uint32 clr_bg = SDL_MapRGB(font_surface_tmp->format, 0, 0, 0);

    for (int x = 0; x < font_surface_tmp->w; ++x)
    {
        for (int y = 0; y < font_surface_tmp->h; ++y)
        {
            font_px_data_[x][y] = get_px(*font_surface_tmp, x, y) != clr_bg;
        }
    }

    SDL_FreeSurface(font_surface_tmp);

    TRACE_FUNC_END;
}

void get_char_sheet_pos(char ch, Pos& dst)
{
    const int Y = ch / NR_FONT_IMAGE_GLYPHS_X;
    const int X = Y == 0 ? ch : (ch % (Y * NR_FONT_IMAGE_GLYPHS_X));
    dst = {X, Y};
}

void put_pxs_for_char(char ch, const Pos& px_p, const Clr& clr)
{
    Pos sheet_p;
    get_char_sheet_pos(ch, sheet_p);

    if (sheet_p.x >= 0)
    {
        Pos sheet_px_p0 = sheet_p * Pos(CELL_PX_W, CELL_PX_H);

        Pos sheet_px_p1 = sheet_px_p0 + Pos(CELL_PX_W - 1, CELL_PX_H - 1);

        Pos scr_px_p = px_p;

        Pos sheet_px_p;

        set_render_clr(clr);

        for (sheet_px_p.x = sheet_px_p0.x; sheet_px_p.x <= sheet_px_p1.x; ++sheet_px_p.x)
        {
            scr_px_p.y = px_p.y;

            for (sheet_px_p.y = sheet_px_p0.y; sheet_px_p.y <= sheet_px_p1.y; ++sheet_px_p.y)
            {
                if (font_px_data_[sheet_px_p.x][sheet_px_p.y])
                {
                    SDL_RenderDrawPoint(sdl_renderer_, scr_px_p.x, scr_px_p.y);
                }
                ++scr_px_p.y;
            }
            ++scr_px_p.x;
        }
    }
}

void draw_rect_px(const Rect& px_r, const Clr& clr)
{
    if (is_inited())
    {
        SDL_Rect sdl_rect =
        {
            (Sint16)px_r.p0.x,
            (Sint16)px_r.p0.y,
            (Uint16)(px_r.p1.x - px_r.p0.x + 1),
            (Uint16)(px_r.p1.y - px_r.p0.y + 1)
        };


        set_render_clr(clr);

        SDL_RenderFillRect(sdl_renderer_, &sdl_rect);
    }
}

void draw_rect(const Rect& r, const Clr& clr)
{
    const Rect px_r(
        r.p0.x * CELL_PX_W,
        r.p0.y * CELL_PX_H,
        r.p1.x * CELL_PX_W,
        r.p1.y * CELL_PX_W
    );

    draw_rect_px(px_r, clr);
}

void get_window_px_size(Pos& dst)
{
    SDL_GetWindowSize(sdl_window_, &dst.x, &dst.y);
}

void draw_char_at_px(char ch, const Pos& px_p, const Clr& clr, const Clr& bg_clr)
{
    const Rect bg_px_r( px_p, {px_p.x + CELL_PX_W - 1, px_p.y + CELL_PX_H - 1} );
    draw_rect_px(bg_px_r, bg_clr);

    put_pxs_for_char(ch, px_p, clr);
}

void draw_char_at(char ch, const Pos& p, const Clr& clr, const Clr& bg_clr = clr_black)
{
    const Pos px_p = {p.x * CELL_PX_W, p.y * CELL_PX_H};

    draw_char_at_px(ch, px_p, clr, bg_clr);
}

//void draw_char_in_map(char ch, const P* p, const Clr* clr, const Clr* bg_clr) {
//  if(is_inited()) {
//    if(p->x >= 0 && p->y >= 0 && p->x < MAP_W && p->y < MAP_H) {
//      P px_p = *p;
//
//      p_multipl_xy(&px_p, CELL_PX_W, CELL_PX_H);
//
//      draw_char_at_px(ch, &px_p, clr, true, bg_clr);
//    }
//  }
//}

} // namespace

void init()
{
    const char title[] = "Fantasy 4x " GAME_VERSION_LABEL;

    TRACE_FUNC_BEGIN;

    cleanup();

    TRACE << "Setting up rendering window" << std::endl;

    sdl_window_ = SDL_CreateWindow(
                      title,
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      SCR_PX_W, SCR_PX_H,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);

    load_font_data();

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    if (sdl_renderer_)
    {
        SDL_DestroyRenderer(sdl_renderer_);
        sdl_renderer_ = nullptr;
    }

    if (sdl_window_)
    {
        SDL_DestroyWindow(sdl_window_);
        sdl_window_ = nullptr;
    }

    TRACE_FUNC_END;
}

void render_present()
{
    if (is_inited())
    {
        SDL_RenderPresent(sdl_renderer_);
    }
}

void clear_scr()
{
    if (is_inited())
    {
        set_render_clr(clr_black);
        SDL_RenderClear(sdl_renderer_);
    }
}

void on_window_resized()
{
    if (is_inited())
    {
        Uint32 sdl_window_flags = SDL_GetWindowFlags(sdl_window_);
        if (
            !(sdl_window_flags & SDL_WINDOW_MAXIMIZED)   &&
            !(sdl_window_flags & SDL_WINDOW_FULLSCREEN)  &&
            !(sdl_window_flags & SDL_WINDOW_FULLSCREEN_DESKTOP))
        {
            Pos px_size;
            get_window_px_size(px_size);
            px_size.x = (px_size.x / CELL_PX_W) * CELL_PX_W;
            px_size.y = (px_size.y / CELL_PX_H) * CELL_PX_H;
            SDL_SetWindowSize(sdl_window_, px_size.x, px_size.y);
        }
    }
    clear_scr();
    draw_normal_mode();
    render_present();
}

void draw_text(const std::string& text, const Pos& p, const Clr& clr, const Clr& bg_clr)
{
    if (!is_inited())
    {
        return;
    }

    if (p.y >= 0 && p.y < SCR_H)
    {
        Pos px_p = p * Pos(CELL_PX_W, CELL_PX_H);

        const int PX_X0 = px_p.x;

        for (auto it = begin(text); it != end(text); ++it)
        {
            bool is_new_line_char = false;
            if (*it == '\n')
            {
                px_p = Pos(PX_X0, px_p.y + CELL_PX_H);
                is_new_line_char = true;
            }
            if (px_p.x < 0 || px_p.x >= SCR_PX_W)
            {
                return;
            }
            if (!is_new_line_char)
            {
                draw_char_at_px(*it, px_p, clr, bg_clr);
                px_p.x += CELL_PX_W;
            }
        }
    }
}

void draw_normal_mode()
{
    Pos window_px_size;
    get_window_px_size(window_px_size);

    const Pos viewport_max_size =
    {
        window_px_size.x / CELL_PX_W,
        window_px_size.y / CELL_PX_H,
    };

    // p1 is either limited to the size of the viewport, or to the size of the map,
    // whichever is smalleest.
    const Pos p1 =
    {
        std::min(viewport_.x + viewport_max_size.x, MAP_W - viewport_.x) - 1,
        std::min(viewport_.y + viewport_max_size.y, MAP_H - viewport_.y) - 1
    };

    for (int x = viewport_.x; x <= p1.x; ++x)
    {
        for (int y = viewport_.y; y <= p1.y; ++y)
        {
            const Pos p(x, y);

            const auto& render_data = world::terrain[p.x][p.y]->get_render_data();

            draw_char_at(render_data.ch, p, render_data.clr);
        }
    }

    for (const auto& mob_ptr : world::mobs)
    {
        const auto& render_data = mob_ptr->get_render_data();
        const auto& p           = mob_ptr->get_pos();

        draw_char_at(render_data.ch, p, render_data.clr);
    }
}

} // render
