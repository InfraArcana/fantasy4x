#ifndef RENDER_HPP
#define RENDER_HPP

#include "lib_wrap.hpp"
#include "utils.hpp"

namespace render
{

void init();

void cleanup();

void clear_scr();

// Adjusts the window size to a multiple of the cell size (if not maximized or fullscreen)
// void on_window_resized();

// TODO: This function currently assumes that the map is in the top left corner of the
// screen, and that the map fills the whole screen.
void draw_normal_mode();

//void draw_text(const std::string& text, const Pos& p, const Clr& clr,
//               const Clr& bg_clr = clr_black);

} // render

#endif // RENDER_HPP
