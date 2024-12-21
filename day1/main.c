#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define BUFFERSIZE 128

typedef struct vector {
  int idx;
  int size;
  int *elements;
} vector;

void add_to_vector(vector *arr, int num);

int answer1(vector arr1, vector arr2);
int answer2(vector arr1, vector arr2);

int main(void) {
  FILE *f = fopen("input.txt", "r");
  if (!f) {
    printf("Error opening file\n");
    return 1;
  }

  char buffer[BUFFERSIZE];
  int num1, num2;
  vector l1 = {0, 1, malloc(sizeof(int))};
  vector l2 = {0, 1, malloc(sizeof(int))};

  while (fgets(buffer, BUFFERSIZE, f)) {
    sscanf(buffer, "%d   %d", &num1, &num2);

    add_to_vector(&l1, num1);
    add_to_vector(&l2, num2);
  }
  
  fclose(f);

  printf("%d\n", answer1(l1, l2));
  printf("%d\n", answer2(l1, l2));
  free(l1.elements);
  free(l2.elements);
  return 0;
}

void add_to_vector(vector *v, int num) {
  v->elements[v->idx++] = num;

  if (v->idx == v->size) {
    int size = v->size * 2;
    v->elements = realloc(v->elements, size * sizeof(int));
    v->size = size;
  }

}

int increasing(const void *num1, const void *num2) {
  return *(int *)num1 - *(int *)num2;
}

int answer1(vector arr1, vector arr2) {
  qsort(arr1.elements, arr1.idx, sizeof(int), increasing);
  qsort(arr2.elements, arr2.idx, sizeof(int), increasing);

  int sum = 0;
  for (int i = 0; i < arr1.idx; i++) {
    sum += abs(arr1.elements[i] - arr2.elements[i]);
  }

  return sum;
};

bool contains(int check, vector v) {
  for (int i = 0; i < v.idx; i++) {
    if (check == v.elements[i]) return true;
  }

  return false;
}

int answer2(vector arr1, vector arr2) {
  int sum = 0;
  for (int i = 0; i < arr2.idx; i++) {
    int current_value = arr2.elements[i];
    if (contains(current_value, arr1)) {
      sum += current_value;
    }
  }

  return sum;
};
