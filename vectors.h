#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
typedef struct vector {
  int idx;
  int size;
  void **elements;
} vector;

static inline void add_to_vector(vector *v, void *num) {
  v->elements[v->idx++] = num;

  if (v->idx == v->size) {
    int size = v->size * 2;
    v->elements = (void **) realloc(v->elements, size * sizeof(void *));
    v->size = size;
  }
}

static inline void free_vector(vector v) {
  void **elems = v.elements;
  for (int i = 0; i < v.idx; i++) free(elems[i]);
  free(elems);
}
#endif
