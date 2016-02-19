#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <cassert>

#include "utils.hpp"

//-----------------------------------------------------------------------------
// OPTIONS
//-----------------------------------------------------------------------------
// Lvl of TRACE output in debug mode
// 0 : Disabled
// 1 : Standard
// 2 : Verbose
#define TRACE_LVL 1

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
// Input data structures
//-----------------------------------------------------------------------------
enum class Mouse_Btn
{
    none,
    left,
    right
};

struct Input_Data
{
    Input_Data() :
        key         (-1),
        mouse_px_p  (),
        mouse_btn   (Mouse_Btn::none) {}

    int key; // NOTE: ASCII symbol

    P mouse_px_p;

    Mouse_Btn mouse_btn;
};

//-----------------------------------------------------------------------------
// Input/output handling
//-----------------------------------------------------------------------------
namespace io
{

void init();

void cleanup();

P scr_px_dim();

P scr_px_mid();

// TODO: This should probably return a rectangle
P viewport();

void update_scr();

void clear_scr();

void draw_ch(const char ch,
             const P& p,
             const Clr& clr,
             const Clr& clr_bg = clr_black);

void draw_text(const std::string& str,
               const P& p,
               const Clr& clr,
               const Clr& clr_bg = clr_black,
               const X_Align x_align = X_Align::left,
               const Y_Align y_align = Y_Align::top);

void draw_rect(const Rect& r, const Clr& clr);

void sleep(const unsigned int ms);

Input_Data wait_input();

} // io

#endif // IO_HPP
