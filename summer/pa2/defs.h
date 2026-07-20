#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_OPEN_FLAG "r"
#define TARGET_PPB 50 // target points per bin
#define DEBUG 0

typedef struct point_ {
  int x;
  int y;
} point;

typedef struct plane_ {
  point** table;
  int Npoints;
  int Nbins;
  int binWidth;
} plane;

// setup.c
plane* newPlane(int, int, int);
void freePlane(plane*);
plane* readFile(char*);

// collide.c
void insertPoint(plane*, point);
int hash(plane, point);
plane* collide(plane*, point, int);
void dumpPlane(plane);
