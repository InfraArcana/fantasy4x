#include "actor.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "list.h"
#include "cmn_utils.h"
#include "file_handling.h"

struct l_node* races = NULL;

void race_data_init() {
  TRACE_FUNC_BEGIN;

  const char*   PATH  = "data/races.dat";
  const size_t  SIZE  = file_length(PATH);
  char*         str   = malloc(SIZE);
  file_read(str, SIZE, PATH);

  const char* DELIM = ";\n";

  char* line = strtok(str, DELIM);

  while(line) {
    struct race* race = malloc(sizeof(struct race));

    str_alloc(&race->name, line);

    line = strtok(NULL, DELIM);
    str_alloc(&race->name_plural, line);

    line = strtok(NULL, DELIM);
    str_alloc(&race->name_a, line);

    l_add(&races, race);

    //Note: This is either the first line of a new race, or NULL
    line = strtok(NULL, DELIM);
  }

  free(str);

  TRACE_FUNC_END;
}

void race_data_cleanup() {
  TRACE_FUNC_BEGIN;

  struct l_node* node = races;
  while(node) {
    struct race* race = node->data;

    free(race->name);
    free(race->name_plural);
    free(race->name_a);

    free(race);

    node = node->next;
  }

  l_free(races);

  TRACE_FUNC_END;
}

struct actor* actor_init(struct actor* actor) {
  assert(actor);

  actor->name = NULL;

  return actor;
}

void actor_free(struct actor* actor) {
  assert(actor);
  if(actor->name) {free(actor->name);}
  free(actor);
}
