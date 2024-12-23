#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../vectors.h"
#define BUFFERSIZE 128

bool test_safe(vector v) {
  int first = *(int *) v.elements[0];
  int second = *(int *) v.elements[1];

  bool increasing = first < second;
  for (int j = 1; j < v.idx; j++) {
    first = *(int *) v.elements[j - 1];
    second = *(int *) v.elements[j];
    int result = abs(second - first);
    if (result < 1 || result > 3 || !(increasing ? first < second : first > second)) {
      return false;
    }
  }

  return true;
}

int answer1(vector arr) {
  int safe = 0;

  for (int i = 0; i < arr.idx; i++) {
    if (test_safe(*(vector *) arr.elements[i])) safe++;
  }

  return safe;
}

bool test_safe_with_skip(vector arr, int skip) {
  int first = *(int *) arr.elements[skip == 0 ? 1 : 0];
  int second = *(int *) arr.elements[skip <= 1 ? 2 : 1];

  bool increasing = first < second;
  for (int j = 1; j < arr.idx; j++) {
    // skips the comparison for the skipped index
    // special case: if j is the last elem and skip == j
    if (j - 1 == skip || (j == arr.idx - 1 && skip == j)) continue;

    first = *(int *) arr.elements[j - 1];
    second = *(int *) arr.elements[j + (j == skip ? 1 : 0)];
    int result = abs(second - first);
    if (result < 1 || result > 3 || !(increasing ? first < second : first > second)) {
      return false;
    }
  }

  return true;
}

int answer2(vector arr) {
  int safe = 0;

  for (int i = 0; i < arr.idx; i++) {
    vector v = *(vector *) arr.elements[i];
    for (int k = 0; k < arr.idx; k++) { // k indicates the idx to "remove" or basically skip
      if (test_safe(v) || test_safe_with_skip(v, k)) {
        safe++;
        break;
      }
    }
  }

  return safe;
}

int main(void) {
  FILE *f = fopen("input.txt", "r");
  if (!f) {
    printf("Error opening file\n");
    return 1;
  }

  char buffer[BUFFERSIZE];
  vector arr = {0, 1, malloc(sizeof(vector *))};

  while (fgets(buffer, BUFFERSIZE, f)) {
    vector *subarr = malloc(sizeof(vector));
    subarr->idx = 0;
    subarr->size = 1;
    subarr->elements = malloc(sizeof(void *));

    char *token = strtok(buffer, " ");
    int *num = malloc(sizeof(int));
    sscanf(token, "%d", num);
    add_to_vector(subarr, num);

    while ((token = strtok(NULL, " "))) {
      num = malloc(sizeof(int));
      sscanf(token, "%d", num);
      add_to_vector(subarr, num);
    }

    add_to_vector(&arr, subarr);
  }

  fclose(f);

  printf("%d\n", answer1(arr));
  printf("%d\n", answer2(arr));

  for (int i = 0; i < arr.idx; i++) free_vector(*(vector *) arr.elements[i]);
  
  free_vector(arr);
  return 0;
}