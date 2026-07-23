typedef struct {
  int from;
  int to;
  int* weights;
} edge;

typedef struct {
  edge* edges;
  int n;
  int period;
} graph;

typedef struct {
  edge* edges;
  int size; // current number of elements in the array
  int cap;  // current capacity of the array
} path;

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1;
#define INIT_PATH_CAP 64;
