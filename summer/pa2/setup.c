#include "defs.h"
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

// Hey future me, sorry I left you this terrible mess to debug -past me
plane* readFile(char* filename) {
  FILE* fptr = fopen(filename, FILE_OPEN_FLAG);
  if (fptr == NULL) return NULL;

  int Npoints = 0;
  char c;
  while (1) {
    c = fgetc(fptr);
    if (feof(fptr)) break;
    if (c == '\n') Npoints++;
  }
  rewind(fptr);
  point* buff = calloc(Npoints, sizeof(point));

  for (int i = 0; i < Npoints; i++) {
    if (fscanf(fptr, "%d %d\n", &buff[i].x, &buff[i].y) == 0) break;
  }
  if (DEBUG) printf("read %d points\n", Npoints);

  point upperRight = {0};
  point lowerLeft = {0};

  // find the corners of the board
  for (int i = 0; i < Npoints; i++) {
    if (buff[i].x > upperRight.x) {
      upperRight.x = buff[i].x;
    }
    if (buff[i].y > upperRight.y) {
      upperRight.y = buff[i].y;
    }

    if (buff[i].x < lowerLeft.x) {
      lowerLeft.x = buff[i].x;
    }
    if (buff[i].y < lowerLeft.y) {
      lowerLeft.y = buff[i].y;
    }
  }

  double boardX = (upperRight.x + abs(lowerLeft.x) + 1);
  double boardY = (upperRight.y + abs(lowerLeft.y) + 1);

  int Nbins = Npoints / TARGET_PPB; // we know how many bins there should be and know the size of the board
  Nbins = MIN(pow(floor(sqrt(Nbins) + 1), 2), pow(ceil(sqrt(Nbins)), 2));
  if (Nbins == 0) Nbins = 1; // there must be at least one bin
  int binWidth = MAX(boardX, boardY) / (sqrt(Nbins));

  /*initialize plane*/
  plane* newPln = newPlane(Npoints, Nbins, binWidth);

  for (int p = 0; p < Npoints; p++) { // loads the points from the buffer to the plane
    insertPoint(newPln, buff[p]);
  }

  free(buff);
  return newPln;
}
