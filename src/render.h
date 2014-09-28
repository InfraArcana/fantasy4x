#ifndef RENDER_H
#define RENDER_H

#include "colors.h"
#include "cmn_types.h"

void render_init();

void render_cleanup();

void draw_text(const char text[], const P* p, const Clr* clr, const Clr* bg_clr);

#endif
