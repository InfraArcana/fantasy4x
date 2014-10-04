#include "world.h"

#include <stdlib.h>

#include "list.h"
#include "actor.h"

struct map_cell cells[MAP_W][MAP_H];
struct l_node   actors;

static void init_cell(struct map_cell* cell) {
  p_set_xy(&cell->p, 0, 0);
  cell->ch  = 0;
  cell->clr = NULL;
}

void world_init() {
  struct map_cell* cell = NULL;

  for(int y = 0; y < MAP_H; ++y) {
    for(int x = 0; x < MAP_W; ++x) {
      cell = &cells[x][y];
      init_cell(cell);
      cell->ch  = '~';
      cell->clr = &clr_blue;
    }
  }

  l_init(&actors);
  for(int i = 0; i < 1000; ++i) {
    struct actor* actor = malloc(sizeof(actor));
    actor_init(actor);
    l_add()
  }
  l_free(&actors);
}

void get_map_cell_render_data(const struct pos* p, struct char_and_clr* data_ptr) {
  struct map_cell* cell = &cells[p->x][p->y];
  data_ptr->ch          = cell->ch;
  data_ptr->clr         = cell->clr;
  data_ptr->clr_bg      = NULL;
}
