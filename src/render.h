#ifndef RENDER_H
#define RENDER_H

#include "colors.h"
#include "cmn_utils.h"

void render_init();

void render_cleanup();

void render_present();

void draw_text(const char* text, const P* p, const Clr* clr, const Clr* bg_clr);
void draw_text_xy(const char* text, const int X, const int Y, const Clr* clr,
                  const Clr* bg_clr);

void clear_scr();

#endif
