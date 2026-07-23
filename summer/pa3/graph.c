#include "defs.h"

edge* newEdge(int period) {
  edge* toReturn = calloc(1, sizeof(edge));
  toReturn->to = -1;
  toReturn->from = -1;
  toReturn->weights = calloc(period, sizeof(int));
  return toReturn;
}

graph* newGraph(void) {
  graph* toReturn = calloc(1, sizeof(graph));
  toReturn->period = -1;
  toReturn->n = -1;
  return toReturn;
}

path* newPath(void) {
  path* toReturn = calloc(1, sizeof(path));
  toReturn->size = 0;
  toReturn->cap = INIT_PATH_CAP;
  return toReturn;
}
