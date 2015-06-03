#ifndef COLORS_HPP
#define COLORS_HPP

#include <SDL.h>

typedef SDL_Color Clr;

const Clr clr_black         = {  0,   0,   0, SDL_ALPHA_OPAQUE};
const Clr clr_gray          = {128, 128, 128, SDL_ALPHA_OPAQUE};
const Clr clr_white         = {192, 192, 192, SDL_ALPHA_OPAQUE};
const Clr clr_white_high    = {255, 255, 255, SDL_ALPHA_OPAQUE};

const Clr clr_red           = {128,   0,   0, SDL_ALPHA_OPAQUE};
const Clr clr_red_lgt       = {255,   0,   0, SDL_ALPHA_OPAQUE};

const Clr clr_green         = {  0, 128,   0, SDL_ALPHA_OPAQUE};
const Clr clr_green_lgt     = {  0, 255,   0, SDL_ALPHA_OPAQUE};

const Clr clr_yellow        = {255, 255,   0, SDL_ALPHA_OPAQUE};

const Clr clr_blue          = {  0,   0, 139, SDL_ALPHA_OPAQUE};
const Clr clr_blue_lgt      = { 92,  92, 255, SDL_ALPHA_OPAQUE};

const Clr clr_magenta       = {139,   0, 139, SDL_ALPHA_OPAQUE};
const Clr clr_magenta_lgt   = {255,   0, 255, SDL_ALPHA_OPAQUE};

const Clr clr_cyan          = {  0, 128, 128, SDL_ALPHA_OPAQUE};
const Clr clr_cyanLgt       = {  0, 255, 255, SDL_ALPHA_OPAQUE};

const Clr clr_brown         = {153, 102,  61, SDL_ALPHA_OPAQUE};
const Clr clr_brown_drk     = { 96,  64,  32, SDL_ALPHA_OPAQUE};
const Clr clr_brown_xdrk    = { 48,  32,  16, SDL_ALPHA_OPAQUE};

const Clr clr_violet        = {128,   0, 255, SDL_ALPHA_OPAQUE};

const Clr clr_orange        = {255, 128,   0, SDL_ALPHA_OPAQUE};

#endif // COLORS_HPP
