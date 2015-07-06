#ifndef CMN_DATA_HPP
#define CMN_DATA_HPP

#include "lib_wrap.hpp"

#include <string>

//TODO: A lot of this stuff should not be hard coded

const std::string   game_name           = "Fantasy4x";
const std::string   game_version_str    = "v0.01";

const int           map_w               = 250;
const int           map_h               = 250;
const int           map_mid_x           = map_w / 2;
const int           map_mid_y           = map_h / 2;

const int           scr_w               = 80;
const int           scr_h               = 25;
const int           scr_mid_x           = scr_w / 2;
const int           scr_mid_y           = scr_h / 2;

const bool          is_fullscreen       = false;

#endif // CMN_DATA_HPP
