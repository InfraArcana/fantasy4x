#ifndef RENDER_H
#define RENDER_H

#include "colors.h"
#include "cmn_utils.h"

void render_init();

void render_cleanup();

void render_present();

//Adjusts the window size to a multiple of the cell size (if not maximized or fullscreen)
void on_window_resized();

//TODO This function currently assumes that the map is in the top left corner of the
//screen, and that the map fills the whole screen.
void draw_normal_mode();

void draw_text(const char* text, const struct pos* p, const Clr* clr, const Clr* bg_clr);

void draw_text_xy(const char* text, int x, int y, const Clr* clr, const Clr* bg_clr);

void clear_scr();

#endif // RENDER_H
