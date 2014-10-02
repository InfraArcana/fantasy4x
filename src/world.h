#ifndef WORLD_H //Note: "MAP_H" is reserved for map height
#define WORLD_H

#include "cmn_utils.h"

struct map_cell {
  struct pos  p;
  char        ch;
  const Clr*  clr; //Pointer to a color in colors.h
};

void world_init();

void get_map_cell_render_data(const struct pos* p, struct char_and_clr* data_ptr);

#endif // MAP_H
