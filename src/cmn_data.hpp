#ifndef CMN_DATA_HPP
#define CMN_DATA_HPP

#include "base.hpp"

#include <string>

#define GAME_VERSION_LABEL "v0.01"

extern const int SCR_BPP;

#define MAP_W       250
#define MAP_H       250
#define MAP_MID_X   MAP_W / 2
#define MAP_MID_Y   MAP_H / 2

#define SCR_W       80
#define SCR_H       24
#define SCR_MID_X   SCR_W / 2
#define SCR_MID_Y   SCR_H / 2

#define STR_BUFFER_SIZE SCR_W

//-----------------------------------------------------------------------------
//TODO: Move to Config
#define CELL_PX_W   8
#define CELL_PX_H   16
#define SCR_PX_W    SCR_W * CELL_PX_W
#define SCR_PX_H    SCR_H * CELL_PX_H
extern const std::string    font_img_path;
extern const bool           IS_FULLSCREEN;
//-----------------------------------------------------------------------------

#endif // CMN_DATA_HPP
