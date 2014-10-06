#ifndef ACTOR_H
#define ACTOR_H

struct race {
  char* name;
  char* name_plural;
  char* name_a;
};

struct actor {
  struct race*  race;
  char*         name;
};

void race_data_init();

void race_data_cleanup();

struct actor* actor_init(struct actor* actor);

void          actor_free(struct actor* actor);

#endif // ACTOR_H
