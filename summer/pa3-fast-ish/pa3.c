#include "graph.h"
#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

#define INF INT64_MAX

typedef struct {
  int64_t* dist;
  int32_t* prev;
  int32_t* endState;
  Heap h;
  int src;
  int exhausted;
} Solver;

static int solverInit(Solver* S, const Graph* g) {
  size_t states = (size_t)g->V * (size_t)g->N;
  S->dist = malloc(states * sizeof *S->dist);
  S->prev = malloc(states * sizeof *S->prev);
  S->endState = malloc((size_t)g->V * sizeof *S->endState);
  if (!S->dist || !S->prev || !S->endState) return -1;
  if (heapInit(&S->h, states) != 0) return -1;
  S->src = -1;
  return 0;
}

static void solverFree(Solver* S) {
  free(S->dist); free(S->prev); free(S->endState); heapFree(&S->h);
}

static void dijkstraReset(Solver* S, const Graph* g, int src) {
  size_t states = (size_t)g->V * (size_t)g->N;
  for (size_t i = 0; i < states; i++) { S->dist[i] = INF; S->prev[i] = -1; }
  for (int v = 0; v < g->V; v++) S->endState[v] = -1;
  heapClear(&S->h);
  int32_t start = (int32_t)((size_t)src * g->N);
  S->dist[start] = 0;
  heapPush(&S->h, 0, start);
  S->src = src;
  S->exhausted = 0;
}

//resume search until dst is settled but don't break the heap so we can reuse
static void dijkstraUntil(Solver* S, const Graph* g, int dst) {
  const int N = g->N;
  while (!heapEmpty(&S->h)) {
    HeapEntry e = heapPop(&S->h);
    if (e.d > S->dist[e.x]) continue;

    int v = e.x / N;
    int p = e.x % N;
    int np = (p + 1 == N) ? 0 : p + 1;

    if (S->endState[v] < 0) S->endState[v] = e.x;

    for (int i = g->head[v]; i < g->head[v + 1]; i++) {
      int64_t nd = e.d + g->w[(size_t)i * N + p];
      int32_t nx = (int32_t)((size_t)g->to[i] * N + np);
      if (nd < S->dist[nx]) {
        S->dist[nx] = nd; S->prev[nx] = e.x;
        heapPush(&S->h, nd, nx);
      }
    }
    if (v == dst) return;
  }
  S->exhausted = 1;
}

static void printPath(const Solver* S, const Graph* g, int dst, int32_t* buf) {
  int32_t best = S->endState[dst];
  if (best < 0) { putchar('\n'); return; }
  int n = 0;
  for (int32_t x = best; x != -1; x = S->prev[x]) buf[n++] = x / g->N;
  for (int i = n - 1; i >= 0; i--) printf("%d%c", buf[i], i ? ' ' : '\n');
}

int main(int argc, char** argv) {
  if (argc < 2) return EXIT_FAILURE;
  Graph* G = graphLoad(argv[1]);
  if (!G) return EXIT_FAILURE;
  Solver S;
  if (solverInit(&S, G) != 0) { graphFree(G); return EXIT_FAILURE; }
  int32_t* buf = malloc((size_t)G->V * (size_t)G->N * sizeof *buf);
  if (!buf) { solverFree(&S); graphFree(G); return EXIT_FAILURE; }

  int s, t;
  while (scanf("%d %d", &s, &t) == 2) {
    if (s < 0 || s >= G->V || t < 0 || t >= G->V) { putchar('\n'); continue; }
    if (s != S.src) dijkstraReset(&S, G, s);
    if (S.endState[t] < 0 && !S.exhausted) dijkstraUntil(&S, G, t);
    printPath(&S, G, t, buf);
  }
  free(buf); solverFree(&S); graphFree(G);
  return EXIT_SUCCESS;
}
