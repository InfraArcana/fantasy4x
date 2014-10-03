#ifndef VECTOR_H
#define VECTOR_H

struct vec {
  int*  data;     //Array of integers we're storing
  int   size;     //Number of slots used so far
  int   capacity; //Total available slots
};

void  v_init(struct vec* v);

void  v_append(struct vec* v, int value);

int   v_get(struct vec* v, int index);

void  v_set(struct vec* v, int index, int value);

void  v_free(struct vec* v);

#endif // VECTOR_H
