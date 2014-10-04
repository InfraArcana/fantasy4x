#include "actor.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct actor* actor_init(struct actor* actor, char* name) {
  assert(actor);

  actor->name = NULL;

  if(name) {
    actor->name = malloc(strlen(name) + 1);
    strcpy(actor->name, name);
  }

  return actor;
}

void actor_free(struct actor* actor) {
  assert(actor);
  if(actor->name) {free(actor->name);}
  free(actor);
}
