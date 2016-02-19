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

const bool  is_fullscreen = false;

#endif // CMN_DATA_HPP
