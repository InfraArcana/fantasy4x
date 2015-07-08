#include "lib_wrap.hpp"

#include <fstream>

#include "utils.hpp"
#include "cmn_data.hpp"

#ifdef SDL_MODE
#include <SDL_image.h>
#endif // SDL_MODE

//-----------------------------------------------------------------------------
// Console mode
//-----------------------------------------------------------------------------
#ifdef CONSOLE_MODE

namespace lib_wrap
{

namespace
{

bool    is_inited_  = false;
WINDOW* window_     = nullptr;

std::ofstream log_f;

int clr_pair(const Clr& clr, const Clr& clr_bg)
{
    const auto clr_pair_idx = (clr * COLORS) + clr_bg;

    return COLOR_PAIR(clr_pair_idx);
}

} //namespace

void init()
{
    log_f.open("cerr.txt", std::ios_base::out); // NOTE: Must be done before first trace output

    std::cerr.rdbuf(log_f.rdbuf()); //redirect std::cerr

    TRACE_FUNC_BEGIN;

    cleanup();

    window_ = initscr();

    curs_set(0); // Hide the cursor

    resize_term(scr_h, scr_w);

    start_color();

    if (!has_colors())
    {
        endwin();
        TRACE << "Your terminal does not support color" << std::endl;
        assert(false);
    }

    const auto nr_clr_cmb = COLORS * COLORS;

    TRACE << "Nr color pairs available : " << COLOR_PAIRS   << std::endl
          << "Nr colors                : " << COLORS        << std::endl
          << "Nr color combinations    : " << nr_clr_cmb    << std::endl;

    if (COLOR_PAIRS < nr_clr_cmb)
    {
        endwin();
        TRACE << "Supported color pairs is " << COLOR_PAIRS
              << ", need at least "          << nr_clr_cmb << std::endl;
        assert(false);
    }

    for (short f = 0; f < COLORS; ++f )
    {
        for (short b = 0; b < COLORS; ++b )
        {
            init_pair(f * COLORS + b, f, b);
        }
    }

    is_inited_ = true;

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    if (!is_inited_)
    {
        return;
    }

    is_inited_ = false;

    endwin();

    window_ = nullptr;

    TRACE_FUNC_END;

    log_f.close(); // NOTE: Must be done after last trace output
}

void update_scr()
{
    if (!is_inited_)
    {
        return;
    }

    refresh();
}

void clear_scr()
{
    if (!is_inited_)
    {
        return;
    }

    // TODO
}

P scr_size()
{
    P ret;

    getmaxyx(window_, ret.y, ret.x);

    return ret;
}

void draw_ch(const char ch,
             const P& p,
             const Clr& clr,
             const Clr& clr_bg)
{
    if (!is_inited_)
    {
        return;
    }

    const auto clr_pair_used = clr_pair(clr, clr_bg);

    attron(clr_pair_used);

    mvaddch(p.y, p.x, ch);

    attroff(clr_pair_used);
}

void draw_text(const std::string& str, const P& p, const Clr& clr, const Clr& clr_bg)
{
    if (!is_inited_)
    {
        return;
    }

    const auto clr_pair_used = clr_pair(clr, clr_bg);

    attron(clr_pair_used);

    mvprintw(p.y, p.x, str.c_str());

    attroff(clr_pair_used);
}

void sleep(unsigned int ms)
{
    if (!is_inited_)
    {
        return;
    }

    // TODO
}

int key()
{
    if (!is_inited_)
    {
        return 0;
    }

    return getch();
}

} // lib_wrap (CONSOLE_MODE)

//-----------------------------------------------------------------------------
// SDL mode
//-----------------------------------------------------------------------------
#elif defined SDL_MODE

namespace lib_wrap
{

namespace
{

bool                is_inited_              = false;
SDL_Window*         sdl_window_             = nullptr;
SDL_Renderer*       sdl_renderer_           = nullptr;
const int           nr_font_img_glyphs_x    = 32;

const int           scr_bpp                 = 32;
const int           cell_px_w               = 8;
const int           cell_px_h               = 16;
const int           scr_px_w                = scr_w* cell_px_w;
const int           scr_px_h                = scr_h* cell_px_h;

const std::string   font_img_path           = "images/curses_8x16.png";

bool font_px_data_[256][128];

void char_sheet_pos(char ch, P& dst)
{
    const int y = ch / nr_font_img_glyphs_x;

    const int x = y == 0 ? ch :
                  (ch % (y * nr_font_img_glyphs_x));

    dst.set(x, y);
}

void set_render_clr(const Clr& clr)
{
    SDL_SetRenderDrawColor(sdl_renderer_, clr.r, clr.g, clr.b, SDL_ALPHA_OPAQUE);
}

Uint32 px(const SDL_Surface& surface, int px_x, int px_y)
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
            font_px_data_[x][y] = px(*font_surface_tmp, x, y) != clr_bg;
        }
    }

    SDL_FreeSurface(font_surface_tmp);

    TRACE_FUNC_END;
}

void put_pxs_for_char(char ch, const P& px_p, const Clr& clr)
{
    P sheet_p;
    char_sheet_pos(ch, sheet_p);

    if (sheet_p.x >= 0)
    {
        P sheet_px_p0 = sheet_p * P(cell_px_w, cell_px_h);

        P sheet_px_p1 = sheet_px_p0 + P(cell_px_w - 1, cell_px_h - 1);

        P scr_px_p = px_p;

        P sheet_px_p;

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
    if (!is_inited_)
    {
        return;
    }

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

void draw_rect(const Rect& r, const Clr& clr)
{
    const Rect px_r(
        r.p0.x * cell_px_w,
        r.p0.y * cell_px_h,
        r.p1.x * cell_px_w,
        r.p1.y * cell_px_w
    );

    draw_rect_px(px_r, clr);
}

void draw_char_at_px(const char ch,
                     const P& px_p,
                     const Clr& clr,
                     const Clr& bg_clr)
{
    const Rect bg_px_r( px_p, {px_p.x + cell_px_w - 1, px_p.y + cell_px_h - 1} );
    draw_rect_px(bg_px_r, bg_clr);

    put_pxs_for_char(ch, px_p, clr);
}

void draw_char_at(const char ch,
                  const P& p,
                  const Clr& clr,
                  const Clr& bg_clr)
{
    const P px_p = {p.x * cell_px_w, p.y * cell_px_h};

    draw_char_at_px(ch, px_p, clr, bg_clr);
}

/*
void draw_char_in_map(char ch, const P* p, const Clr* clr, const Clr* bg_clr)
{
    if (!is_inited_)
    {
        return;
    }

    if (p->x >= 0 && p->y >= 0 && p->x < map_w && p->y < map_h)
    {
        P px_p = *p;

        p_multipl_xy(&px_p, cell_px_w, cell_px_h);

        draw_char_at_px(ch, &px_p, clr, true, bg_clr);
    }
}
*/

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;

    cleanup();

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        TRACE << "Failed to init SDL"   << std::endl
              << SDL_GetError()         << std::endl;
        assert(false);
    }

    if (IMG_Init(IMG_INIT_PNG) == -1)
    {
        TRACE << "Failed to init SDL_image" << std::endl
              << IMG_GetError()             << std::endl;
        assert(false);
    }

    const std::string title = game_name + " " + game_version_str;

    TRACE << "Setting up rendering window" << std::endl;

    sdl_window_ = SDL_CreateWindow(
                      title.c_str(),
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      scr_px_w, scr_px_h,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);

    load_font_data();

    is_inited_ = true;

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    if (!is_inited_)
    {
        return;
    }

    is_inited_ = false;

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

    IMG_Quit();
    SDL_Quit();

    TRACE_FUNC_END;
}

void update_scr()
{
    if (!is_inited_)
    {
        return;
    }

    SDL_RenderPresent(sdl_renderer_);
}

void clear_scr()
{
    if (!is_inited_)
    {
        return;
    }

    set_render_clr(clr_black);

    SDL_RenderClear(sdl_renderer_);
}

P scr_size()
{
    P ret;

    SDL_GetWindowSize(sdl_window_, &ret.x, &ret.y);

    ret /= P(scr_w, scr_h);

    return ret;
}

void on_window_resized()
{
    /*
    if (!is_inited_)
    {
        return;
    }

    Uint32 sdl_window_flags = SDL_GetWindowFlags(sdl_window_);

    if (
        !(sdl_window_flags & SDL_WINDOW_MAXIMIZED)   &&
        !(sdl_window_flags & SDL_WINDOW_FULLSCREEN)  &&
        !(sdl_window_flags & SDL_WINDOW_FULLSCREEN_DESKTOP))
    {
        P px_size = scr_size();

        px_size.x = (px_size.x / cell_px_w) * cell_px_w;
        px_size.y = (px_size.y / cell_px_h) * cell_px_h;

        SDL_SetWindowSize(sdl_window_, px_size.x, px_size.y);
    }

    clear_scr();
    draw_normal_mode();
    render_present();
    */
}

void sleep(const unsigned int ms)
{
    if (!is_inited_)
    {
        return;
    }

    if (ms == 1)
    {
        SDL_Delay(1);
    }
    else // ms > 1
    {
        const Uint32 wait_until = SDL_GetTicks() + ms;

        while (SDL_GetTicks() < wait_until)
        {
            SDL_PumpEvents();
        }
    }
}

void draw_ch(const char ch,
             const P& p,
             const Clr& clr,
             const Clr& clr_bg)
{
    if (!is_inited_)
    {
        return;
    }

    // TODO
}

void draw_text(const std::string& str, const P& p, const Clr& clr)
{
    if (!is_inited_)
    {
        return;
    }

    // TODO
}

int key()
{
    if (!is_inited_)
    {
        return 0;
    }

}

} // lib_wrap (SDL_MODE)

#else
#error CONSOLE_MODE or SDL_MODE must be defined
#endif
