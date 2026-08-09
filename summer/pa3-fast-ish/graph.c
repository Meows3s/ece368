#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const char* p;
  const char* end;
} Scanner;

// read the entire file into memory
static char* slurpFile(const char* path, size_t* outLen) {
  FILE* fptr = fopen(path, "rb");
  if (!fptr) return NULL;

  if (fseek(fptr, 0, SEEK_END) != 0) {
    fclose(fptr);
    return NULL;
  }
  long sz = ftell(fptr);
  if (sz < 0) {
    fclose(fptr);
    return NULL;
  }
  rewind(fptr);

  char* buf = malloc((size_t)sz + 1);
  if (!buf) {
    fclose(fptr);
    return NULL;
  }

  size_t got = fread(buf, 1, (size_t)sz, fptr);
  fclose(fptr);

  buf[got] = '\0';
  *outLen = got;
  return buf;
}

static inline int isDigitChar(char c) { return (unsigned char)(c - '0') <= 9u; }

static inline int scanSeek(Scanner* s) {
  while (s->p < s->end && !isDigitChar(*s->p) && *s->p != '-')
    s->p++;
  return s->p < s->end;
}

// scanSeek() just returned 1
static inline int scanInt(Scanner* s) {
  int neg = 0;
  if (*s->p == '-') {
    neg = 1;
    s->p++;
  }
  int x = 0;
  while (s->p < s->end && isDigitChar(*s->p))
    x = x * 10 + (*s->p++ - '0');
  return neg ? -x : x;
}

// does what it says on the box
void graphFree(Graph* g) {
  if (!g) return;
  free(g->head);
  free(g->to);
  free(g->w);
  free(g);
}

Graph* graphLoad(const char* path) {
  size_t len = 0;
  char* buf = slurpFile(path, &len);
  if (!buf) return NULL;

  Scanner s = {buf, buf + len};

  if (!scanSeek(&s)) {
    free(buf);
    return NULL;
  }
  int V = scanInt(&s);
  if (!scanSeek(&s)) {
    free(buf);
    return NULL;
  }
  int N = scanInt(&s);
  if (V <= 0 || N <= 0) {
    free(buf);
    return NULL;
  }

  size_t cap = 1;
  for (const char* q = s.p; q < s.end; q++)
    cap += (*q == '\n');

  int* esrc = malloc(cap * sizeof *esrc);
  int* edst = malloc(cap * sizeof *edst);
  int* ew = malloc(cap * (size_t)N * sizeof *ew);
  if (!esrc || !edst || !ew) {
    free(esrc);
    free(edst);
    free(ew);
    free(buf);
    return NULL;
  }

  int E = 0;
  while (scanSeek(&s)) {
    int u = scanInt(&s);
    if (!scanSeek(&s)) break;
    int v = scanInt(&s);

    esrc[E] = u;
    edst[E] = v;
    int* row = ew + (size_t)E * N;
    int i = 0;
    for (; i < N && scanSeek(&s); i++)
      row[i] = scanInt(&s);
    while (i < N)
      row[i++] = 0; // short line protection
    E++;
  }
  free(buf);

  // counting sort of the edge list by source vertex -> CSR
  int* head = calloc((size_t)V + 1, sizeof *head);
  int* to = malloc((size_t)E * sizeof *to);
  int* w = malloc((size_t)E * (size_t)N * sizeof *w);
  int* fill = malloc((size_t)V * sizeof *fill);
  Graph* g = malloc(sizeof *g);
  if (!head || !to || !w || !fill || !g) {
    free(head);
    free(to);
    free(w);
    free(fill);
    free(g);
    free(esrc);
    free(edst);
    free(ew);
    return NULL;
  }

  for (int e = 0; e < E; e++)
    head[esrc[e] + 1]++;
  for (int v = 0; v < V; v++)
    head[v + 1] += head[v];
  memcpy(fill, head, (size_t)V * sizeof *fill);

  for (int e = 0; e < E; e++) {
    int slot = fill[esrc[e]]++;
    to[slot] = edst[e];
    memcpy(w + (size_t)slot * N, ew + (size_t)e * N, (size_t)N * sizeof *w);
  }

  free(esrc);
  free(edst);
  free(ew);
  free(fill);

  g->V = V;
  g->N = N;
  g->E = E;
  g->head = head;
  g->to = to;
  g->w = w;
  return g;
}
