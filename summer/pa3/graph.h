#include <stddef.h>

typedef struct {
  int V;     // number of verts
  int N;     // edge weight period
  int E;     // number of edges
  int* head; // len is V+1
  int* to;   // len is E
  int* w;    // len is E*N
} Graph;

Graph* graphLoad(const char* path);
void graphFree(Graph* g);
