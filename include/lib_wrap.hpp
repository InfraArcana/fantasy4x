#ifndef TRACE_HPP
#define TRACE_HPP

#include <assert.h>
#include <iostream>

struct P;

//-----------------------------------------------------------------------------
// OPTIONS
//-----------------------------------------------------------------------------
// Lvl of TRACE output in debug mode
// 0 : Disabled
// 1 : Standard
// 2 : Verbose
#define TRACE_LVL 1
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Debug
//-----------------------------------------------------------------------------
#ifdef NDEBUG

#define TRACE                     if (1) ; else std::cerr
#define TRACE_FUNC_BEGIN          if (1) ; else std::cerr
#define TRACE_FUNC_END            if (1) ; else std::cerr
#define TRACE_VERBOSE             if (1) ; else std::cerr
#define TRACE_FUNC_BEGIN_VERBOSE  if (1) ; else std::cerr
#define TRACE_FUNC_END_VERBOSE    if (1) ; else std::cerr

#else // Debug mode

#define TRACE if (TRACE_LVL < 1) ; else std::cerr \
  << "---" \
  << std::endl \
  << __FILE__ << ", " \
  << __LINE__ << ", " \
  << __func__ << "():" << std::endl

#define TRACE_FUNC_BEGIN if (TRACE_LVL < 1) ; else std::cerr \
  << "---" \
  << std::endl \
  << __FILE__ << ", " \
  << __LINE__ << ", " \
  << __func__ << "()..." << std::endl

#define TRACE_FUNC_END if (TRACE_LVL < 1) ; else std::cerr \
  << "---" \
  << std::endl \
  << __FILE__ << ", " \
  << __LINE__ << ", " \
  << __func__ << "() [DONE]" << std::endl

#define TRACE_VERBOSE             if (TRACE_LVL < 2) ; else TRACE
#define TRACE_FUNC_BEGIN_VERBOSE  if (TRACE_LVL < 2) ; else TRACE_FUNC_BEGIN
#define TRACE_FUNC_END_VERBOSE    if (TRACE_LVL < 2) ; else TRACE_FUNC_END

#endif // NDEBUG

//-----------------------------------------------------------------------------
// Colors
//-----------------------------------------------------------------------------
#ifdef CONSOLE_MODE

#include <curses.h>

typedef short Clr;

const Clr clr_black     = COLOR_BLACK;
const Clr clr_red       = COLOR_RED;
const Clr clr_green     = COLOR_GREEN;
const Clr clr_yellow    = COLOR_YELLOW;
const Clr clr_blue      = COLOR_BLUE;
const Clr clr_magenta   = COLOR_MAGENTA;
const Clr clr_cyan      = COLOR_CYAN;
const Clr clr_white     = COLOR_WHITE;

#elif defined SDL_MODE

#include <SDL.h>

typedef SDL_Color Clr;

const Clr clr_black         = {  0,   0,   0, SDL_ALPHA_OPAQUE};
//const Clr clr_gray          = {128, 128, 128, SDL_ALPHA_OPAQUE};
const Clr clr_white         = {192, 192, 192, SDL_ALPHA_OPAQUE};
//const Clr clr_white_high    = {255, 255, 255, SDL_ALPHA_OPAQUE};

const Clr clr_red           = {128,   0,   0, SDL_ALPHA_OPAQUE};
//const Clr clr_red_lgt       = {255,   0,   0, SDL_ALPHA_OPAQUE};

const Clr clr_green         = {  0, 128,   0, SDL_ALPHA_OPAQUE};
//const Clr clr_green_lgt     = {  0, 255,   0, SDL_ALPHA_OPAQUE};

const Clr clr_yellow        = {255, 255,   0, SDL_ALPHA_OPAQUE};

const Clr clr_blue          = {  0,   0, 139, SDL_ALPHA_OPAQUE};
//const Clr clr_blue_lgt      = { 92,  92, 255, SDL_ALPHA_OPAQUE};

const Clr clr_magenta       = {139,   0, 139, SDL_ALPHA_OPAQUE};
//const Clr clr_magenta_lgt   = {255,   0, 255, SDL_ALPHA_OPAQUE};

const Clr clr_cyan          = {  0, 128, 128, SDL_ALPHA_OPAQUE};
//const Clr clr_cyanLgt       = {  0, 255, 255, SDL_ALPHA_OPAQUE};

//const Clr clr_brown         = {153, 102,  61, SDL_ALPHA_OPAQUE};
//const Clr clr_brown_drk     = { 96,  64,  32, SDL_ALPHA_OPAQUE};
//const Clr clr_brown_xdrk    = { 48,  32,  16, SDL_ALPHA_OPAQUE};

//const Clr clr_violet        = {128,   0, 255, SDL_ALPHA_OPAQUE};

//const Clr clr_orange        = {255, 128,   0, SDL_ALPHA_OPAQUE};

#endif

//-----------------------------------------------------------------------------
// Lib wrap interface
//-----------------------------------------------------------------------------
namespace lib_wrap
{

void init();

void cleanup();

void update_scr();

void clear_scr();

P scr_size();

void draw_ch(const char ch,
             const P& p,
             const Clr& clr,
             const Clr& clr_bg = clr_black);

void draw_text(const std::string& str,
               const P& p,
               const Clr& clr,
               const Clr& clr_bg = clr_black);

void sleep(const unsigned int ms);

int key();

} // lib_wrap

#endif // TRACE_HPP
