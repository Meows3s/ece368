#include "heap.h"

#include <stdlib.h>

int heapInit(Heap* h, size_t cap) {
  if (cap < 16) cap = 16;
  h->a = malloc(cap * sizeof *h->a);
  if (!h->a) return -1;
  h->size = 0;
  h->cap = cap;
  return 0;
}

void heapFree(Heap* h) {
  free(h->a);
  h->a = NULL;
  h->size = h->cap = 0;
}

static int heapGrow(Heap* h) {
  size_t cap = h->cap * 2;
  HeapEntry* a = realloc(h->a, cap * sizeof *a);
  if (!a) return -1;
  h->a = a;
  h->cap = cap;
  return 0;
}

// uses a hole sift for speeeeeeed
int heapPush(Heap* h, int64_t d, int32_t x) {
  if (h->size == h->cap && heapGrow(h) != 0) return -1;

  size_t i = h->size++;
  while (i > 0) {
    size_t parent = (i - 1) / 2;
    if (h->a[parent].d <= d) break;
    h->a[i] = h->a[parent];
    i = parent;
  }

  h->a[i].d = d;
  h->a[i].x = x;
  return 0;
}

HeapEntry heapPop(Heap* h) {
  HeapEntry top = h->a[0];
  HeapEntry last = h->a[--h->size];
  if (h->size == 0) return top;

  size_t i = 0;
  for (;;) {
    size_t c = 2 * i + 1;
    if (c >= h->size) break;
    if (c + 1 < h->size && h->a[c + 1].d < h->a[c].d) c++;
    if (h->a[c].d >= last.d) break;
    h->a[i] = h->a[c];
    i = c;
  }

  h->a[i] = last;
  return top;
}
