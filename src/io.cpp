#include "io.hpp"

#include <SDL_ttf.h>
#include <SDL_image.h>

#include "cmn_data.hpp"

namespace io
{

namespace
{

bool            is_inited_      = false;
SDL_Window*     sdl_window_     = nullptr;
SDL_Renderer*   sdl_renderer_   = nullptr;
TTF_Font*       font_           = nullptr;

P viewport_(0, 0);

SDL_Event       sdl_event_;

// Adjusts the window size to a multiple of the cell size (if not maximized or fullscreen)
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

//void char_sheet_pos(char ch, P& dst)
//{
//    const int y = ch / nr_font_img_glyphs_x;
//
//    const int x = y == 0 ? ch :
//                  (ch % (y * nr_font_img_glyphs_x));
//
//    dst.set(x, y);
//}

void set_render_clr(const Clr& clr)
{
    SDL_SetRenderDrawColor(sdl_renderer_, clr.r, clr.g, clr.b, SDL_ALPHA_OPAQUE);
}

//Uint32 px(const SDL_Surface& surface, int px_x, int px_y)
//{
//    int bpp = surface.format->BytesPerPixel;
//    // Here p is the address to the pixel we want to retrieve
//    Uint8* px = (Uint8*)surface.pixels + px_y * surface.pitch + px_x * bpp;
//
//    switch (bpp)
//    {
//    case 1:   return *px;           break;
//    case 2:   return *(Uint16*)px;  break;
//    case 3:
//    {
//        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
//        {
//            return px[0] << 16 | px[1] << 8 | px[2];
//        }
//        else
//        {
//            return px[0] | px[1] << 8 | px[2] << 16;
//        }
//    } break;
//    case 4:   return *(Uint32*)px;  break;
//    default:  return -1;            break;
//    }
//    return -1;
//}

//void load_font_data()
//{
//    TRACE_FUNC_BEGIN;
//
//    SDL_Surface* font_surface_tmp = IMG_Load(font_img_path.c_str());
//
//    assert(font_surface_tmp && "Failed to load font image");
//
//    Uint32 clr_bg = SDL_MapRGB(font_surface_tmp->format, 0, 0, 0);
//
//    for (int x = 0; x < font_surface_tmp->w; ++x)
//    {
//        for (int y = 0; y < font_surface_tmp->h; ++y)
//        {
//            font_px_data_[x][y] = px(*font_surface_tmp, x, y) != clr_bg;
//        }
//    }
//
//    SDL_FreeSurface(font_surface_tmp);
//
//    TRACE_FUNC_END;
//}

//void put_pxs_for_char(char ch, const P& px_p, const Clr& clr)
//{
//    P sheet_p;
//    char_sheet_pos(ch, sheet_p);
//
//    if (sheet_p.x >= 0)
//    {
//        P sheet_px_p0 = sheet_p * P(cell_px_w, cell_px_h);
//
//        P sheet_px_p1 = sheet_px_p0 + P(cell_px_w - 1, cell_px_h - 1);
//
//        P scr_px_p = px_p;
//
//        P sheet_px_p;
//
//        set_render_clr(clr);
//
//        for (sheet_px_p.x = sheet_px_p0.x; sheet_px_p.x <= sheet_px_p1.x; ++sheet_px_p.x)
//        {
//            scr_px_p.y = px_p.y;
//
//            for (sheet_px_p.y = sheet_px_p0.y; sheet_px_p.y <= sheet_px_p1.y; ++sheet_px_p.y)
//            {
//                if (font_px_data_[sheet_px_p.x][sheet_px_p.y])
//                {
//                    SDL_RenderDrawPoint(sdl_renderer_, scr_px_p.x, scr_px_p.y);
//                }
//                ++scr_px_p.y;
//            }
//            ++scr_px_p.x;
//        }
//    }
//}

//void draw_char_at_px(const char ch,
//                     const P& px_p,
//                     const Clr& clr,
//                     const Clr& bg_clr)
//{
//    const Rect bg_px_r( px_p, {px_p.x + cell_px_w - 1, px_p.y + cell_px_h - 1} );
//    draw_rect_px(bg_px_r, bg_clr);
//
//    put_pxs_for_char(ch, px_p, clr);
//}

//void draw_char_at(const char ch,
//                  const P& p,
//                  const Clr& clr,
//                  const Clr& bg_clr)
//{
//    const P px_p = {p.x * cell_px_w, p.y * cell_px_h};
//
//    draw_char_at_px(ch, px_p, clr, bg_clr);
//}

//void draw_char_in_map(char ch, const P* p, const Clr* clr, const Clr* bg_clr)
//{
//    if (!is_inited_)
//    {
//        return;
//    }
//
//    if (p->x >= 0 && p->y >= 0 && p->x < map_w && p->y < map_h)
//    {
//        P px_p = *p;
//
//        p_multipl_xy(&px_p, cell_px_w, cell_px_h);
//
//        draw_char_at_px(ch, &px_p, clr, true, bg_clr);
//    }
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

    if (TTF_Init() == -1)
    {
        TRACE << "Failed to init SDL_ttf" << std::endl;
        assert(false);
    }

    const std::string title = game_name + " " + game_version_str;

    TRACE << "Setting up rendering window (scaled)" << std::endl
          << "Size: " << scr_px_w_scaled << "x" << scr_px_h_scaled
          << std::endl;

    sdl_window_ = SDL_CreateWindow(
                      title.c_str(),
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      scr_px_w_scaled,
                      scr_px_h_scaled,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);

    TRACE << "Setting logical render size" << std::endl
          << "Size: " << scr_px_w << "x" << scr_px_h
          << std::endl;

    SDL_RenderSetLogicalSize(sdl_renderer_,
                             scr_px_w,
                             scr_px_h);

    TRACE << "Loading font" << std::endl;

    const std::string font_path = "fonts/Anonymous.ttf";

    font_ = TTF_OpenFont(font_path.c_str(), 12);

    if (font_ == nullptr)
    {
        TRACE << "Failed to load font: " << font_path << std::endl;
        assert(false);
    }

    TTF_SetFontKerning(font_, 0);
    TTF_SetFontOutline(font_, 0);
    TTF_SetFontHinting(font_, TTF_HINTING_NONE);

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

    TTF_CloseFont(font_);
    font_ = nullptr;

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

    TTF_Quit();
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

P scr_px_size()
{
    P ret;

    SDL_GetWindowSize(sdl_window_, &ret.x, &ret.y);

    return ret;
}

P viewport()
{
    return viewport_;
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

void draw_text(const std::string& str,
               const P& p,
               const Clr& clr,
               const Clr& clr_bg,
               const X_Align x_align,
               const Y_Align y_align)
{
    if (!is_inited_)
    {
        return;
    }

    assert(!str.empty());

//    int window_w, window_h;
//    SDL_GetWindowSize(sdl_window_, &window_w, &window_h);

    SDL_Surface* font_srf = nullptr;

//    if (allow_wrap == Allow_Wrap_Text::yes)
//    {
//        font_srf = TTF_RenderText_Blended_Wrapped(font, str.c_str(), clr, window_w);
//    }
//    else // Wrap not allowed
//    {
//    font_srf = TTF_RenderText_Blended(font, str.c_str(), clr);
    font_srf = TTF_RenderText_Solid(font_, str.c_str(), clr);
//    }

    assert(font_srf);

    SDL_Rect sdl_dst_rect = {p.x, p.y, font_srf->w, font_srf->h};

    if (x_align == X_Align::center)
    {
        sdl_dst_rect.x = p.x - (sdl_dst_rect.w / 2);
    }

    if (y_align == Y_Align::mid)
    {
        sdl_dst_rect.y = p.y - (sdl_dst_rect.h / 2);
    }

//    Rect ret_area(sdl_dst_rect.x,
//                  sdl_dst_rect.y,
//                  sdl_dst_rect.x + sdl_dst_rect.w - 1,
//                  sdl_dst_rect.y + sdl_dst_rect.h - 1);

    SDL_Texture* font_texture = SDL_CreateTextureFromSurface(sdl_renderer_, font_srf);

    SDL_RenderCopy(sdl_renderer_, font_texture, nullptr, &sdl_dst_rect);

    SDL_FreeSurface(font_srf);

    SDL_DestroyTexture(font_texture);

//    return ret_area;
}

void draw_rect(const Rect& r, const Clr& clr)
{
    if (!is_inited_)
    {
        return;
    }

    SDL_Rect sdl_rect =
    {
        (Sint16)r.p0.x,
        (Sint16)r.p0.y,
        (Uint16)(r.p1.x - r.p0.x + 1),
        (Uint16)(r.p1.y - r.p0.y + 1)
    };

    set_render_clr(clr);

    SDL_RenderFillRect(sdl_renderer_, &sdl_rect);
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

Input_Data wait_input()
{
    Input_Data d;

    if (!is_inited_)
    {
        return d;
    }

    bool is_done = false;

    while (!is_done)
    {
        SDL_PollEvent(&sdl_event_);

        switch (sdl_event_.type)
        {
        case SDL_QUIT:
            break;

        case SDL_WINDOWEVENT:
            switch (sdl_event_.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
                on_window_resized();
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
        {
            const auto button = sdl_event_.button.button;

            if (button == SDL_BUTTON_LEFT || button == SDL_BUTTON_RIGHT)
            {
                d.mouse_btn = button == SDL_BUTTON_LEFT ?
                              Mouse_Btn::left :
                              Mouse_Btn::right;

                d.mouse_px_p.set(sdl_event_.button.x, sdl_event_.button.y);

                is_done = true;
            }
        }
        break;


        case SDL_MOUSEMOTION:
            d.mouse_px_p.set(sdl_event_.motion.x, sdl_event_.motion.y);
            is_done = true;
            break;

        case SDL_TEXTINPUT:
            d.key   = sdl_event_.text.text[0];
            is_done = true;
            break;

//        case SDL_KEYDOWN:
//            d.key =
//            key_pressed(sdl_event_.key.keysym.sym, quit_game);
//            done = true;
//            break;

        default:
            break;
        }

        sleep(1);
    }

    return d;
}

} // io
