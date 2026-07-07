#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_OPEN_FLAG "r"
#define N_BINS -1
#define DEBUG 0

typedef struct point_ {
  int32_t x;
  int32_t y;
} point;

typedef struct bin_ {
  int32_t x; // location of the lower left corner of the bin
  int32_t y;
  int32_t size; // bins are always squares
  point* points;
} bin;

typedef struct plane_ {
  bin** bins;
  int32_t size; // the plane is also a square
} plane;

plane* createPlane(point*, int);
int calcBins(point*, int, point, point);
int readFile(char*, point**);
