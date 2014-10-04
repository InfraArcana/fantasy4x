#include "actor.h"

#include <assert.h>
#include <stdlib.h>

void actor_init(struct actor* actor) {
  assert(actor);
  actor->name = NULL;
}
