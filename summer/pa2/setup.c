#include "defs.h"
#include <limits.h>
#include <stdlib.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

plane* newPlane(int Npoints, int Nbins, int binWidth) {
  plane* toReturn = calloc(1, sizeof(plane));

  toReturn->table = calloc(Nbins, sizeof(point*));
  for (int i = 0; i < Nbins; i++) {
    toReturn->table[i] = calloc(1, sizeof(point)); // basic init
    toReturn->table[i][0].x = 1;
    toReturn->table[i][0].y = 1;
  }

  toReturn->Npoints = Npoints;
  toReturn->Nbins = Nbins;
  toReturn->binWidth = binWidth;
  return toReturn;
}

void freePlane(plane* pln) {
  for (int i = 0; i < pln->Nbins; i++) {
    free(pln->table[i]); // free each bin
  }
  free(pln->table); // free parent array
  free(pln);
}

// Hey future me, sorry I left you this terrible mess to debug -past me
plane* readFile(char* filename) {
  FILE* fptr = fopen(filename, FILE_OPEN_FLAG);
  if (fptr == NULL) return NULL;

  int cap = 1024, Npoints = 0;
  point* buff = malloc(cap * sizeof(point));
  int px, py;
  while (fscanf(fptr, "%d %d", &px, &py) == 2) {
    if (Npoints == cap) {
      cap *= 2;
      buff = realloc(buff, cap * sizeof(point));
    }
    buff[Npoints].x = px;
    buff[Npoints].y = py;
    Npoints++;
  }
  if (DEBUG) printf("read %d points\n", Npoints);

  point upperRight = {0};
  point lowerLeft = {0};

  // find the corners of the board
  for (int i = 0; i < Npoints; i++) {
    if (buff[i].x > upperRight.x) upperRight.x = buff[i].x;
    if (buff[i].y > upperRight.y) upperRight.y = buff[i].y;
    if (buff[i].x < lowerLeft.x) lowerLeft.x = buff[i].x;
    if (buff[i].y < lowerLeft.y) lowerLeft.y = buff[i].y;
  }

  double boardX = (double)((long long)upperRight.x - lowerLeft.x) + 1.0;
  double boardY = (double)((long long)upperRight.y - lowerLeft.y) + 1.0;

  int Nbins = Npoints / TARGET_PPB; // we know how many bins there should be and know the size of the board
  Nbins = MIN(pow(floor(sqrt(Nbins) + 1), 2), pow(ceil(sqrt(Nbins)), 2));
  if (Nbins == 0) Nbins = 1; // there must be at least one bin

  double bw = MAX(boardX, boardY) / sqrt(Nbins);
  if (bw > (double)INT_MAX) bw = (double)INT_MAX;
  int binWidth = (int)bw;
  if (binWidth < 1) binWidth = 1;

  /*initialize plane*/
  plane* newPln = newPlane(0, Nbins, binWidth);

  for (int p = 0; p < Npoints; p++) { // loads the points from the buffer to the plane
    insertPoint(newPln, buff[p]);
  }

  fclose(fptr);
  free(buff);
  return newPln;
}
