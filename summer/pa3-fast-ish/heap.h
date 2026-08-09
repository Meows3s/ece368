#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  int64_t d; // dist (allegedly)
  int32_t x; // state index = vertex*N + phase
} HeapEntry;

typedef struct {
  HeapEntry* a;
  size_t size;
  size_t cap;
} Heap;

int heapInit(Heap* h, size_t cap);
void heapFree(Heap* h);

static inline void heapClear(Heap* h) { h->size = 0; }
static inline int heapEmpty(const Heap* h) { return h->size == 0; }

int heapPush(Heap* h, int64_t d, int32_t x);

HeapEntry heapPop(Heap* h);

#endif
