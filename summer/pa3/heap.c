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

int heapPush(Heap* h, int64_t d, int32_t x) {
  if (h->size == h->cap && heapGrow(h) != 0) return -1;

  /* TODO: sift up.
   *
   * Hole-based: start with i = h->size++, then walk toward the root
   * while the parent's key is greater than d, moving the parent DOWN
   * into slot i each time. Write the new entry once, into the final
   * hole. Do not swap.
   *
   * parent of i is (i-1)/2; stop at i == 0.
   */

  for (int i = h->size++; i < d;) {
  }

  (void)d;
  (void)x;
  return 0;
}

HeapEntry heapPop(Heap* h) {
  HeapEntry top = h->a[0];

  /* TODO: sift down.
   *
   * Take `last = h->a[--h->size]`, then walk from the root choosing the
   * SMALLER of the two children each step (guard the right child against
   * h->size), moving that child UP into the hole while its key is less
   * than last.d. Write `last` into the final hole.
   *
   * children of i are 2*i+1 and 2*i+2.
   *
   * Careful: if the heap had exactly one entry, h->size is now 0 and
   * `last` IS `top` — make sure that path doesn't write past the end.
   */

  return top;
}
