#include "io.hpp"

#include <SDL_ttf.h>
#include <SDL_image.h>

#include "cmn_data.hpp"
#include "script.hpp"

namespace io
{

namespace
{

bool            is_inited_      = false;
SDL_Window*     sdl_window_     = nullptr;
SDL_Renderer*   sdl_renderer_   = nullptr;

SDL_Event sdl_event_;

P viewport_(0, 0);

P cell_px_dim_  (0, 0);
P scr_px_dim_   (0, 0);

TTF_Font* font_ = nullptr;

int scale_ = 1;

P scr_px_mid_           (0, 0);
P scr_px_dim_scaled_    (0, 0);


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

void set_render_clr(const Clr& clr)
{
    SDL_SetRenderDrawColor(sdl_renderer_, clr.r, clr.g, clr.b, SDL_ALPHA_OPAQUE);
}

} // namespace

void init()
{
    TRACE_FUNC_BEGIN;

    cleanup();

    //-----------------------------------------------------------------------------
    // Set up scripted parameters
    //-----------------------------------------------------------------------------
    script::load("ui.lua");

    cell_px_dim_.x              = script::get_int("cell_width");
    cell_px_dim_.y              = script::get_int("cell_height");

    scr_px_dim_.x               = script::get_int("screen_width");
    scr_px_dim_.y               = script::get_int("screen_height");

    scale_                      = script::get_int("scale");

    const std::string font_name = script::get_str("font");

    const int font_size         = script::get_int("font_size");

    scr_px_mid_                 = scr_px_dim_ / 2;
    scr_px_dim_scaled_          = scr_px_dim_ * scale_;


    //-----------------------------------------------------------------------------
    // SDL
    //-----------------------------------------------------------------------------
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
          << "Size: " << scr_px_dim_scaled_.x << "x" << scr_px_dim_scaled_.y
          << std::endl;

    sdl_window_ = SDL_CreateWindow(
                      title.c_str(),
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      scr_px_dim_scaled_.x,
                      scr_px_dim_scaled_.y,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);

    TRACE << "Setting logical render size" << std::endl
          << "Size: " << scr_px_dim_.x << "x" << scr_px_dim_.y
          << std::endl;

    SDL_RenderSetLogicalSize(sdl_renderer_,
                             scr_px_dim_.x,
                             scr_px_dim_.y);

    //-----------------------------------------------------------------------------
    // Font
    //-----------------------------------------------------------------------------
    const std::string font_path = "fonts/" + font_name;

    TRACE << "Loading font: " + font_path << std::endl;

    font_ = TTF_OpenFont(font_path.c_str(), font_size);

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

P scr_px_dim()
{
//    P ret;
//
//    SDL_GetWindowSize(sdl_window_, &ret.x, &ret.y);

    return scr_px_dim_;
}

P scr_px_mid()
{
    return scr_px_mid_;
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

        // Text keyboard input (i.e. letter characters and such)
        case SDL_TEXTINPUT:
            d.key   = sdl_event_.text.text[0];
            is_done = true;
            break;

        // Misc keyboard input (i.e. function keys)
        case SDL_KEYDOWN:
            d.key   = sdl_event_.key.keysym.sym;
            is_done = true;

            // Re-initialize the io module (including script parsing)?
            if (d.key == SDLK_F5)
            {
                // Clear the input data first
                d = Input_Data();

                init();
            }
            break;

        default:
            break;
        } // switch

        sleep(1);

    } // while

    return d;
}

} // io
