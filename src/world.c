#include "world.h"

#include <stdlib.h>

#include "list.h"
#include "actor.h"

struct map_cell cells[MAP_W][MAP_H];
struct l_node*  actors = NULL;

static void init_cell(struct map_cell* cell) {
  p_set_xy(&cell->p, 0, 0);
  cell->ch  = 0;
  cell->clr = NULL;
}

void world_init() {
  TRACE_FUNC_BEGIN;

  struct map_cell* cell = NULL;

  for(int y = 0; y < MAP_H; ++y) {
    for(int x = 0; x < MAP_W; ++x) {
      cell = &cells[x][y];
      init_cell(cell);
      cell->ch  = '~';
      cell->clr = &clr_blue;
    }
  }

  TRACE_FUNC_END;
}

void world_cleanup() {
  TRACE_FUNC_BEGIN;

  struct l_node* l_node = actors;
  while(l_node) {
    struct actor* actor = l_node->data;
    actor_free(actor);
    l_node = l_node->next;
  }

  l_free(actors);

  TRACE_FUNC_END;
}

void get_map_cell_render_data(const struct pos* p, struct char_and_clr* data_ptr) {
  struct map_cell* cell = &cells[p->x][p->y];
  data_ptr->ch          = cell->ch;
  data_ptr->clr         = cell->clr;
  data_ptr->clr_bg      = NULL;
}
