#ifndef CMN_DATA_HPP
#define CMN_DATA_HPP

#include <string>

//TODO: A lot of this stuff should not be hard coded

const std::string game_name         = "Post-apoc strategy";
const std::string game_version_str  = "v0.0.1";

const int   scr_bpp = 32;

const int   map_w = 250;
const int   map_h = 250;

const int   map_mid_x = map_w / 2;
const int   map_mid_h = map_h / 2;

const int   viewport_cells_w = 30;
const int   viewport_cells_h = 20;

const int   cell_px_w = 16;
const int   cell_px_h = 16;

const int   scr_px_w = viewport_cells_w * cell_px_w; // TODO: For now...
const int   scr_px_h = viewport_cells_h * cell_px_h; // TODO: For now...

const int   scr_px_w_half = scr_px_w / 2;
const int   scr_px_h_half = scr_px_h / 2;

const int   scale = 1;

const int   scr_px_w_scaled = scr_px_w * scale;
const int   scr_px_h_scaled = scr_px_h * scale;

const bool  is_fullscreen = false;

#endif // CMN_DATA_HPP
