#include "render.h"

#include <SDL_image.h>

#include "base.h"
#include "cmn_data.h"
#include "cmn_utils.h"
#include "world.h"

SDL_Window*   sdl_window_   = NULL;
SDL_Renderer* sdl_renderer_ = NULL;
struct pos    viewport_     = {0, 0};
bool          font_px_data_[256][128];

const int NR_FONT_IMAGE_GLYPHS_X = 32;

static bool is_inited_() {
  return sdl_window_ != NULL;
}

static void set_render_clr_(const Clr* clr) {
  SDL_SetRenderDrawColor(sdl_renderer_, clr->r, clr->g, clr->b, SDL_ALPHA_OPAQUE);
}

static Uint32 get_px_(const SDL_Surface* surface, int px_x, int px_y) {
  int bpp = surface->format->BytesPerPixel;
  //Here p is the address to the pixel we want to retrieve
  Uint8* px = (Uint8*)surface->pixels + px_y * surface->pitch + px_x * bpp;

  switch(bpp) {
    case 1:   return *px;           break;
    case 2:   return *(Uint16*)px;  break;
    case 3: {
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        return px[0] << 16 | px[1] << 8 | px[2];
      }   else {
        return px[0] | px[1] << 8 | px[2] << 16;
      }
    } break;
    case 4:   return *(Uint32*)px;  break;
    default:  return -1;            break;
  }
  return -1;
}

static void load_font_data_() {
  TRACE_FUNC_BEGIN;

  SDL_Surface* font_surface_tmp = IMG_Load(font_img_path);
  assert(font_surface_tmp && "Failed to load font image");
  Uint32 clr_bg = SDL_MapRGB(font_surface_tmp->format, 0, 0, 0);

  for(int y = 0; y < font_surface_tmp->h; ++y) {
    for(int x = 0; x < font_surface_tmp->w; ++x) {
      font_px_data_[x][y] = get_px_(font_surface_tmp, x, y) != clr_bg;
    }
  }

  SDL_FreeSurface(font_surface_tmp);

  TRACE_FUNC_END;
}

static void get_char_sheet_pos_(char ch, struct pos* p_ptr) {
  const int Y = ch / NR_FONT_IMAGE_GLYPHS_X;
  const int X = Y == 0 ? ch : (ch % (Y * NR_FONT_IMAGE_GLYPHS_X));
  p_set_xy(p_ptr, X, Y);
}

static void put_pxs_for_char_(char ch, const struct pos* px_p, const Clr* clr) {
  struct pos sheet_p;
  get_char_sheet_pos_(ch, &sheet_p);

  if(sheet_p.x >= 0) {
    struct pos sheet_px_p0 = sheet_p;
    p_multipl_xy(&sheet_px_p0, CELL_PX_W, CELL_PX_H);

    struct pos sheet_px_p1 = sheet_px_p0;
    p_offset_xy(&sheet_px_p1, CELL_PX_W - 1, CELL_PX_H - 1);

    struct pos scr_px_p = *px_p;

    struct pos sheet_px_p;

    set_render_clr_(clr);

    for(sheet_px_p.y = sheet_px_p0.y; sheet_px_p.y <= sheet_px_p1.y; ++sheet_px_p.y) {
      scr_px_p.x = px_p->x;
      for(sheet_px_p.x = sheet_px_p0.x; sheet_px_p.x <= sheet_px_p1.x; ++sheet_px_p.x) {
        if(font_px_data_[sheet_px_p.x][sheet_px_p.y]) {
          SDL_RenderDrawPoint(sdl_renderer_, scr_px_p.x, scr_px_p.y);
        }
        ++scr_px_p.x;
      }
      ++scr_px_p.y;
    }
  }
}

static void get_window_px_size(struct pos* p_ptr) {
  SDL_GetWindowSize(sdl_window_, &p_ptr->x, &p_ptr->y);
}

static void draw_char_at_px(char ch, const struct pos* px_p, const Clr* clr,
                            const Clr* bg_clr) {
  //TODO Background color
//  if(bg_clr != NULL) {
//    draw_rect(px_p, P(CELL_PX_W, CELL_PX_H), bgClr, RectType::filled);
//  }

  put_pxs_for_char_(ch, px_p, clr);
}

static void draw_char_at(char ch, const struct pos* p, const Clr* clr,
                         const Clr* bg_clr) {
  struct pos px_p = {p->x * CELL_PX_W, p->y * CELL_PX_H};
  draw_char_at_px(ch, &px_p, clr, bg_clr);
}

//static void draw_char_in_map_(char ch, const P* p, const Clr* clr, const Clr* bg_clr) {
//  if(is_inited_()) {
//    if(p->x >= 0 && p->y >= 0 && p->x < MAP_W && p->y < MAP_H) {
//      P px_p = *p;
//
//      p_multipl_xy(&px_p, CELL_PX_W, CELL_PX_H);
//
//      draw_char_at_px(ch, &px_p, clr, true, bg_clr);
//    }
//  }
//}

void render_init() {
  const char title[] = "Fantasy 4x " GAME_VERSION_LABEL;

  TRACE_FUNC_BEGIN;

  render_cleanup();

  TRACE("Setting up rendering window");

  sdl_window_ = SDL_CreateWindow(
                  title,
                  SDL_WINDOWPOS_UNDEFINED,
                  SDL_WINDOWPOS_UNDEFINED,
                  SCR_PX_W, SCR_PX_H,
                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);

  load_font_data_();

  TRACE_FUNC_END;
}

void render_cleanup() {
  TRACE_FUNC_BEGIN;

  if(sdl_renderer_) {
    SDL_DestroyRenderer(sdl_renderer_);
    sdl_renderer_ = NULL;
  }

  if(sdl_window_) {
    SDL_DestroyWindow(sdl_window_);
    sdl_window_ = NULL;
  }

  TRACE_FUNC_END;
}

void clear_scr() {
  if(is_inited_()) {
    set_render_clr_(&clr_black);
    SDL_RenderClear(sdl_renderer_);
  }
}

void render_present() {
  if(is_inited_()) {
    SDL_RenderPresent(sdl_renderer_);
  }
}

void on_window_resized() {
  if(is_inited_()) {
    Uint32 sdl_window_flags = SDL_GetWindowFlags(sdl_window_);
    if(
      !(sdl_window_flags & SDL_WINDOW_MAXIMIZED)   &&
      !(sdl_window_flags & SDL_WINDOW_FULLSCREEN)  &&
      !(sdl_window_flags & SDL_WINDOW_FULLSCREEN_DESKTOP)) {
      struct pos px_size;
      get_window_px_size(&px_size);
      px_size.x = (px_size.x / CELL_PX_W) * CELL_PX_W;
      px_size.y = (px_size.y / CELL_PX_H) * CELL_PX_H;
      SDL_SetWindowSize(sdl_window_, px_size.x, px_size.y);
    }
  }
  clear_scr();
  draw_normal_mode();
  render_present();
}

void draw_text(const char* text, struct pos* p, const Clr* clr, const Clr* bg_clr) {
  if(is_inited_()) {
    if(p->y >= 0 && p->y < SCR_H) {
      struct pos px_p = *p;
      p_multipl_xy(&px_p, CELL_PX_W, CELL_PX_H);

      /*drawRect(pxPos, P(LEN * CELL_PX_W, CELL_PX_H), bgClr, RectType::filled);*/

      const char* str_ptr = text;

      const int PX_X0 = px_p.x;

      while(*str_ptr != '\0') {
        bool is_new_line_char = false;
        if(*str_ptr == '\n') {
          p_set_xy(&px_p, PX_X0, px_p.y + CELL_PX_H);
          is_new_line_char = true;
        }
        if(px_p.x < 0 || px_p.x >= SCR_PX_W) {
          return;
        }
        if(!is_new_line_char) {
          draw_char_at_px(*str_ptr, &px_p, clr, NULL);
          p_offset_xy(&px_p, CELL_PX_W, 0);
        }
        ++str_ptr;
      }
    }
  }
}

void draw_text_xy(const char* text, int x, int y, const Clr* clr, const Clr* bg_clr) {
  struct pos p = { x, y };
  draw_text(text, &p, clr, bg_clr);
}

void draw_normal_mode() {
  struct pos window_px_size = {0, 0};
  get_window_px_size(&window_px_size);

  const struct pos viewport_max_size = {
    window_px_size.x / CELL_PX_W,
    window_px_size.y / CELL_PX_H,
  };

  //p1 is either limited to the size of the viewport, or to the size of the map,
  //whichever is smalleest.
  const struct pos p1 = {
    min(viewport_.x + viewport_max_size.x, MAP_W - viewport_.x) - 1,
    min(viewport_.y + viewport_max_size.y, MAP_H - viewport_.y) - 1
  };

  struct char_and_clr render_data = {.ch = 0, .clr = NULL, .clr_bg = NULL};;
  struct pos          p           = {0, 0};

  for(int y = viewport_.y; y <= p1.y; ++y) {
    for(int x = viewport_.x; x <= p1.x; ++x) {
      p_set_xy(&p, x, y);
      get_map_cell_render_data(&p, &render_data);
      if(render_data.clr != NULL) {
        draw_char_at(render_data.ch, &p, render_data.clr, NULL);
      }
    }
  }
}
