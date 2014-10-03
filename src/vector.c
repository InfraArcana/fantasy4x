#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

#include "base.h"

#define VECTOR_INITIAL_CAPACITY 100

static void v_double_capacity_if_full(struct vec* v) {
  if(v->size >= v->capacity) {
    //Double v->capacity and resize the allocated memory accordingly
    v->capacity *= 2;
    v->data = realloc(v->data, sizeof(int) * v->capacity);
  }
}

void v_init(struct vec* v) {
  //Initialize size and capacity
  v->size     = 0;
  v->capacity = VECTOR_INITIAL_CAPACITY;

  //Allocate memory for v->data
  v->data = malloc(sizeof(int) * v->capacity);
}

void v_append(struct vec* v, int value) {
  //Make sure there's room to expand into
  v_double_capacity_if_full(v);

  //Append the value and increment v->size
  v->data[v->size++] = value;
}

int v_get(struct vec* v, int index) {
  if(index >= v->size || index < 0) {
    TRACE("Vector index ouf of bounds");
    assert(false);
  }
  return v->data[index];
}

void v_set(struct vec* v, int index, int value) {
  //Zero fill the vector up to the desired index
  while(index >= v->size) {v_append(v, 0);}

  //Set the value at the desired index
  v->data[index] = value;
}

void v_free(struct vec* v) {
  free(v->data);
}
