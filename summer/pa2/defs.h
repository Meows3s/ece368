#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_OPEN_FLAG "r"
#define TARGET_PPB 100 // target points per bin
#define DEBUG 1

typedef struct point_ {
  int x;
  int y;
} point;

typedef struct plane_ {
  point** table;
  int Nbins;
  int binWidth;
} plane;

// setup.c
plane* createPlane(point*, int);
int readFile(char*, point**);

// collide.c
int hash(plane, point);
point* overlap(plane*, point, int);

// util.c
int max(int, int);
