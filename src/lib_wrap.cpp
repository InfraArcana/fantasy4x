#include "lib_wrap.hpp"

#include <fstream>

#include "utils.hpp"
#include "cmn_data.hpp"

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

int get_clr_pair(const Clr& clr, const Clr& clr_bg)
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

Pos get_scr_size()
{
    Pos ret;

    getmaxyx(window_, ret.y, ret.x);

    return ret;
}

void draw_ch(const char ch,
             const Pos& p,
             const Clr& clr,
             const Clr& clr_bg)
{
    if (!is_inited_)
    {
        return;
    }

    const auto clr_pair = get_clr_pair(clr, clr_bg);

    attron(clr_pair);

    mvaddch(p.y, p.x, ch);

    attroff(clr_pair);
}

void draw_text(const std::string& str,
               const Pos& p,
               const Clr& clr,
               const Clr& clr_bg)
{
    if (!is_inited_)
    {
        return;
    }

    const auto clr_pair = get_clr_pair(clr, clr_bg);

    attron(clr_pair);

    mvprintw(p.y, p.x, str.c_str());

    attroff(clr_pair);
}

void sleep(unsigned int ms)
{
    if (!is_inited_)
    {
        return;
    }

    // TODO
}

int get_key()
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
// NOTE: Not yet supported
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
const int           scr_px_w                = SCR_W* CELL_PX_W;
const int           scr_px_h                = SCR_H* CELL_PX_H;

const std::string   font_img_path           = "images/curses_8x16.png";

bool            font_px_data_[256][128];

void get_char_sheet_pos(char ch, Pos& dst)
{
    const int y = ch / nr_font_img_glyphs_x;
    const int x = y == 0 ? ch : (ch % (y * nr_font_img_glyphs_x));
    dst.set(x, y);
}

void set_render_clr(const Clr& clr)
{
    /*
    SDL_SetRenderDrawColor(sdl_renderer_, clr.r, clr.g, clr.b, SDL_ALPHA_OPAQUE);
    */
}

/*
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
*/

/*
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
*/

/*
void put_pxs_for_char(char ch, const Pos& px_p, const Clr& clr)
{
    Pos sheet_p;
    get_char_sheet_pos(ch, sheet_p);

    if (sheet_p.x >= 0)
    {
        Pos sheet_px_p0 = sheet_p * Pos(cell_px_w, cell_px_h);

        Pos sheet_px_p1 = sheet_px_p0 + Pos(cell_px_w - 1, cell_px_h - 1);

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
*/

void draw_rect_px(const Rect& px_r, const Clr& clr)
{
    /*
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
    */
}

void draw_rect(const Rect& r, const Clr& clr)
{
    /*
    const Rect px_r(
        r.p0.x * cell_px_w,
        r.p0.y * cell_px_h,
        r.p1.x * cell_px_w,
        r.p1.y * cell_px_w
    );

    draw_rect_px(px_r, clr);
    */
}

const Pos get_scr_size()
{
    Pos ret;

    SDL_GetWindowSize(sdl_window_, &ret.x, &ret.y);

    ret /= Pos(SCR_W, SCR_H);

    return ret;
}

void draw_char_at_px(char ch, const Pos& px_p, const Clr& clr, const Clr& bg_clr)
{
    /*
    const Rect bg_px_r( px_p, {px_p.x + cell_px_w - 1, px_p.y + cell_px_h - 1} );
    draw_rect_px(bg_px_r, bg_clr);

    put_pxs_for_char(ch, px_p, clr);
    */
}

void draw_char_at(char ch, const Pos& p, const Clr& clr, const Clr& bg_clr = clr_black)
{
    /*
    const Pos px_p = {p.x * cell_px_w, p.y * cell_px_h};

    draw_char_at_px(ch, px_p, clr, bg_clr);
    */
}

//void draw_char_in_map(char ch, const P* p, const Clr* clr, const Clr* bg_clr) {
//  if(is_inited()) {
//    if(p->x >= 0 && p->y >= 0 && p->x < MAP_W && p->y < MAP_H) {
//      P px_p = *p;
//
//      p_multipl_xy(&px_p, cell_px_w, CELL_PX_H);
//
//      draw_char_at_px(ch, &px_p, clr, true, bg_clr);
//    }
//  }
//}

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
                      title,
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      SCR_PX_W, SCR_PX_H,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);

    load_font_data();

    is_inited_ = true;

    TRACE_FUNC_END;
}

void cleanup()
{
    TRACE_FUNC_BEGIN;

    if (!is_inited)
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
    if (!is_inited)
    {
        return;
    }

    // TODO
}

void clear_scr()
{
    if (!is_inited)
    {
        return;
    }

    set_render_clr(clr_black);

    SDL_RenderClear(sdl_renderer_);
}

/*
void on_window_resized()
{
    if (!is_inited())
    {
        return;
    }
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

    clear_scr();
    draw_normal_mode();
    render_present();
}
*/

void sleep(unsigned int ms)
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

void draw_ch(const char ch, const Clr& clr, const Clr& clr_bg = clr_black)
{
    if (!is_inited)
    {
        return;
    }

    // TODO
}

void draw_text(const std::string& str, const Clr& clr)
{
    if (!is_inited)
    {
        return;
    }

    // TODO
}

void get_key()
{
    if (!is_inited)
    {
        return;
    }

    SDL_RenderPresent(sdl_renderer_);
}

} // lib_wrap (SDL_MODE)

#else
#error CONSOLE_MODE or SDL_MODE must be defined
#endif
