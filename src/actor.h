#ifndef ACTOR_H
#define ACTOR_H

struct actor {
  char* name;
};

struct actor* actor_init(struct actor* actor, char* name);

void actor_free(struct actor* actor);

#endif // ACTOR_H
