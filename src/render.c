#include "render.h"

#include <SDL_image.h>

#include "base.h"
#include "cmn_data.h"

SDL_Window*   sdl_window_   = NULL;
SDL_Renderer* sdl_renderer_ = NULL;

bool font_px_data_[258][176];

static bool is_inited_() {
  return sdl_window_ != NULL;
}

static void set_render_clr_(const Clr* const clr) {
  SDL_SetRenderDrawColor(sdl_renderer_, clr->r, clr->g, clr->b, SDL_ALPHA_OPAQUE);
}

static Uint32 get_px_(SDL_Surface* const surface, const int PX_X, const int PX_Y) {
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  Uint8* p = (Uint8*)surface->pixels + PX_Y * surface->pitch + PX_X * bpp;

  switch(bpp) {
    case 1:   return *p;          break;
    case 2:   return *(Uint16*)p; break;
    case 3: {
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        return p[0] << 16 | p[1] << 8 | p[2];
      }   else {
        return p[0] | p[1] << 8 | p[2] << 16;
      }
    } break;
    case 4:   return *(Uint32*)p; break;
    default:  return -1;          break;
  }
  return -1;
}

static void put_px_(const P* const px_p) {
  SDL_RenderDrawPoint(sdl_renderer_, px_p->x, px_p->y);
}

static void load_font_data_() {
  SDL_Surface*  font_surface_tmp  = NULL;
  Uint32        clr_bg            = 0;
  int x, y;

  TRACE_FUNC_BEGIN;

  font_surface_tmp  = IMG_Load(font_img_path);
  assert(font_surface_tmp && "Failed to load font image");
  clr_bg            = SDL_MapRGB(font_surface_tmp->format, 0, 0, 0);

  for(y = 0; y < font_surface_tmp->h; ++y) {
    for(x = 0; x < font_surface_tmp->w; ++x) {
      font_px_data_[x][y] = get_px_(font_surface_tmp, x, y) != clr_bg;
    }
  }

  SDL_FreeSurface(font_surface_tmp);

  TRACE_FUNC_END;
}

static void get_glyph_sheet_pos_(const char GLYPH, P* const p_ptr) {
  p_set_xy(p_ptr, -1, -1);

  switch(GLYPH) {
    default:  {} break;
    case ' ': p_set_xy(p_ptr, 0, 0);    break;
    case '!': p_set_xy(p_ptr, 1, 0);    break;
    case '"': p_set_xy(p_ptr, 2, 0);    break;
    case '#': p_set_xy(p_ptr, 3, 0);    break;
    case '%': p_set_xy(p_ptr, 4, 0);    break;
    case '&': p_set_xy(p_ptr, 5, 0);    break;
    case  39: p_set_xy(p_ptr, 6, 0);    break;
    case '(': p_set_xy(p_ptr, 7, 0);    break;
    case ')': p_set_xy(p_ptr, 8, 0);    break;
    case '*': p_set_xy(p_ptr, 9, 0);    break;
    case '+': p_set_xy(p_ptr, 10, 0);   break;
    case ',': p_set_xy(p_ptr, 11, 0);   break;
    case '-': p_set_xy(p_ptr, 12, 0);   break;
    case '.': p_set_xy(p_ptr, 13, 0);   break;
    case '/': p_set_xy(p_ptr, 14, 0);   break;
    case '0': p_set_xy(p_ptr, 15, 0);   break;
    case '1': p_set_xy(p_ptr, 0, 1);    break;
    case '2': p_set_xy(p_ptr, 1, 1);    break;
    case '3': p_set_xy(p_ptr, 2, 1);    break;
    case '4': p_set_xy(p_ptr, 3, 1);    break;
    case '5': p_set_xy(p_ptr, 4, 1);    break;
    case '6': p_set_xy(p_ptr, 5, 1);    break;
    case '7': p_set_xy(p_ptr, 6, 1);    break;
    case '8': p_set_xy(p_ptr, 7, 1);    break;
    case '9': p_set_xy(p_ptr, 8, 1);    break;
    case ':': p_set_xy(p_ptr, 9, 1);    break;
    case ';': p_set_xy(p_ptr, 10, 1);   break;
    case '<': p_set_xy(p_ptr, 11, 1);   break;
    case '=': p_set_xy(p_ptr, 12, 1);   break;
    case '>': p_set_xy(p_ptr, 13, 1);   break;
    case '?': p_set_xy(p_ptr, 14, 1);   break;
    case '@': p_set_xy(p_ptr, 15, 1);   break;
    case 'A': p_set_xy(p_ptr, 0, 2);    break;
    case 'B': p_set_xy(p_ptr, 1, 2);    break;
    case 'C': p_set_xy(p_ptr, 2, 2);    break;
    case 'D': p_set_xy(p_ptr, 3, 2);    break;
    case 'E': p_set_xy(p_ptr, 4, 2);    break;
    case 'F': p_set_xy(p_ptr, 5, 2);    break;
    case 'G': p_set_xy(p_ptr, 6, 2);    break;
    case 'H': p_set_xy(p_ptr, 7, 2);    break;
    case 'I': p_set_xy(p_ptr, 8, 2);    break;
    case 'J': p_set_xy(p_ptr, 9, 2);    break;
    case 'K': p_set_xy(p_ptr, 10, 2);   break;
    case 'L': p_set_xy(p_ptr, 11, 2);   break;
    case 'M': p_set_xy(p_ptr, 12, 2);   break;
    case 'N': p_set_xy(p_ptr, 13, 2);   break;
    case 'O': p_set_xy(p_ptr, 14, 2);   break;
    case 'P': p_set_xy(p_ptr, 15, 2);   break;
    case 'Q': p_set_xy(p_ptr, 0, 3);    break;
    case 'R': p_set_xy(p_ptr, 1, 3);    break;
    case 'S': p_set_xy(p_ptr, 2, 3);    break;
    case 'T': p_set_xy(p_ptr, 3, 3);    break;
    case 'U': p_set_xy(p_ptr, 4, 3);    break;
    case 'V': p_set_xy(p_ptr, 5, 3);    break;
    case 'W': p_set_xy(p_ptr, 6, 3);    break;
    case 'X': p_set_xy(p_ptr, 7, 3);    break;
    case 'Y': p_set_xy(p_ptr, 8, 3);    break;
    case 'Z': p_set_xy(p_ptr, 9, 3);    break;
    case '[': p_set_xy(p_ptr, 10, 3);   break;
    case  92: p_set_xy(p_ptr, 11, 3);   break;
    case ']': p_set_xy(p_ptr, 12, 3);   break;
    case '^': p_set_xy(p_ptr, 13, 3);   break;
    case '_': p_set_xy(p_ptr, 14, 3);   break;
    case '`': p_set_xy(p_ptr, 15, 3);   break;
    case 'a': p_set_xy(p_ptr, 0, 4);    break;
    case 'b': p_set_xy(p_ptr, 1, 4);    break;
    case 'c': p_set_xy(p_ptr, 2, 4);    break;
    case 'd': p_set_xy(p_ptr, 3, 4);    break;
    case 'e': p_set_xy(p_ptr, 4, 4);    break;
    case 'f': p_set_xy(p_ptr, 5, 4);    break;
    case 'g': p_set_xy(p_ptr, 6, 4);    break;
    case 'h': p_set_xy(p_ptr, 7, 4);    break;
    case 'i': p_set_xy(p_ptr, 8, 4);    break;
    case 'j': p_set_xy(p_ptr, 9, 4);    break;
    case 'k': p_set_xy(p_ptr, 10, 4);   break;
    case 'l': p_set_xy(p_ptr, 11, 4);   break;
    case 'm': p_set_xy(p_ptr, 12, 4);   break;
    case 'n': p_set_xy(p_ptr, 13, 4);   break;
    case 'o': p_set_xy(p_ptr, 14, 4);   break;
    case 'p': p_set_xy(p_ptr, 15, 4);   break;
    case 'q': p_set_xy(p_ptr, 0, 5);    break;
    case 'r': p_set_xy(p_ptr, 1, 5);    break;
    case 's': p_set_xy(p_ptr, 2, 5);    break;
    case 't': p_set_xy(p_ptr, 3, 5);    break;
    case 'u': p_set_xy(p_ptr, 4, 5);    break;
    case 'v': p_set_xy(p_ptr, 5, 5);    break;
    case 'w': p_set_xy(p_ptr, 6, 5);    break;
    case 'x': p_set_xy(p_ptr, 7, 5);    break;
    case 'y': p_set_xy(p_ptr, 8, 5);    break;
    case 'z': p_set_xy(p_ptr, 9, 5);    break;
    case '{': p_set_xy(p_ptr, 10, 5);   break;
    case '|': p_set_xy(p_ptr, 11, 5);   break;
    case '}': p_set_xy(p_ptr, 12, 5);   break;
    case '~': p_set_xy(p_ptr, 13, 5);   break;
    case   1: p_set_xy(p_ptr, 14, 5);   break;
    case   2: p_set_xy(p_ptr, 0, 6);    break;
    case   3: p_set_xy(p_ptr, 1, 6);    break;
    case   4: p_set_xy(p_ptr, 2, 6);    break;
    case   5: p_set_xy(p_ptr, 3, 6);    break;
    case   6: p_set_xy(p_ptr, 4, 6);    break;
    case   7: p_set_xy(p_ptr, 5, 6);    break;
    case   8: p_set_xy(p_ptr, 6, 6);    break;
    case   9: p_set_xy(p_ptr, 7, 6);    break;
    case  10: p_set_xy(p_ptr, 8, 6);    break;
  }
  assert(p_ptr->x >= 0 && "Illegal glyph");
}

static void put_pxs_for_glyph_(const char GLYPH, const P* const px_p,
                               const Clr* const clr) {
  P sheet_p, sheet_px_p0, sheet_px_p1, sheet_px_p, scr_px_p;

  get_glyph_sheet_pos_(GLYPH, &sheet_p);

  if(sheet_p.x >= 0) {
    sheet_px_p0 = sheet_p;
    p_multipl_xy(&sheet_px_p0, CELL_PX_W, CELL_PX_H);

    sheet_px_p1 = sheet_px_p0;
    p_offset_xy(&sheet_px_p1, CELL_PX_W - 1, CELL_PX_H - 1);

    scr_px_p = *px_p;

    set_render_clr_(clr);

    for(sheet_px_p.y = sheet_px_p0.y; sheet_px_p.y <= sheet_px_p1.y; ++sheet_px_p.y) {
      scr_px_p.x = px_p->x;
      for(sheet_px_p.x = sheet_px_p0.x; sheet_px_p.x <= sheet_px_p1.x; ++sheet_px_p.x) {
        if(font_px_data_[sheet_px_p.x][sheet_px_p.y]) {put_px_(&scr_px_p);}
        ++scr_px_p.x;
      }
      ++scr_px_p.y;
    }
  }
}

static void draw_glyph_at_px(const char GLYPH, const P* px_p, const Clr* clr,
                             const bool DRAW_BG_CLR, const Clr* bg_clr) {
  /* TODO Background color
  if(DRAW_BG_CLR) {
    draw_rect(px_p, P(CELL_PX_W, CELL_PX_H), bgClr, RectType::filled);
  }
  */
  put_pxs_for_glyph_(GLYPH, px_p, clr);
}

/*
static void draw_glyph_in_map_(const char GLYPH, const P* p, const Clr* clr,
                               const Clr* bg_clr) {
  if(is_inited_()) {
    if(p->x >= 0 && p->y >= 0 && p->x < MAP_W && p->y < MAP_H) {
      P px_p = *p;

      p_multipl_xy(&px_p, CELL_PX_W, CELL_PX_H);

      draw_glyph_at_px(GLYPH, &px_p, clr, true, bg_clr);
    }
  }
}
*/

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
                  SDL_WINDOW_SHOWN);

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

void draw_text(const char* text, const P* p, const Clr* clr, const Clr* bg_clr) {
  if(is_inited_()) {
    if(p->y >= 0 && p->y < SCR_H) {
      const char* str_ptr = text;
      P           px_p;

      px_p = *p;
      p_multipl_xy(&px_p, CELL_PX_W, CELL_PX_H);

      /*drawRect(pxPos, P(LEN * CELL_PX_W, CELL_PX_H), bgClr, RectType::filled);*/

      while(*str_ptr != '\0') {
        if(px_p.x < 0 || px_p.x >= SCR_PX_W) {
          return;
        }
        draw_glyph_at_px(*str_ptr, &px_p, clr, false, &clr_black);
        p_offset_xy(&px_p, CELL_PX_W, 0);
        ++str_ptr;
      }
    }
  }
}

void draw_text_xy(const char* text, const int X, const int Y, const Clr* clr,
                  const Clr* bg_clr) {
  P p;
  p_set_xy(&p, X, Y);
  draw_text(text, &p, clr, bg_clr);
}
