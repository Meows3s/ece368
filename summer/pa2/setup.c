#include "defs.h"

// reads file into point buffer, returns number of points in buffer
int readFile(char* filename, point** buff) {
  FILE* fptr = fopen(filename, FILE_OPEN_FLAG);
  if (fptr == NULL) return -1;

  // count lines
  int Npoints = 0;
  char c;
  while (1) {
    c = fgetc(fptr);
    if (feof(fptr)) break;
    if (c == '\n') Npoints++;
  }
  rewind(fptr);

  *buff = calloc(Npoints, sizeof(point));

  // read in data
  for (int i = 0; i < Npoints - 1; i++) {
    if (fscanf(fptr, "%d %d\n", &buff[i]->x, &buff[i]->y) == 0) break;
  }

  if (DEBUG) printf("read %d points\n", Npoints);

  return Npoints;
}

// initializes a plane from a given buffer
plane* createPlane(point* buff, int Npoints) {
  point upperRight = {0};
  point lowerLeft = {0};

  // find the corners of the board
  int i = 0;
  while (i != Npoints) {
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
    i++;
  }

  int boardX = (upperRight.x + abs(lowerLeft.x));
  int boardY = (upperRight.y + abs(lowerLeft.y));
  int pointDensity = Npoints / (boardX * boardY);
  int Nbins = pointDensity / TARGET_PPB; // we know how many bins there should be and know the size of the board
  int binWidth = boardX / (sqrt(Nbins));

  if (DEBUG) {
    printf("boardX: %d\nboardY: %d\npoint density: %d\nNbins: %d\nbin width: %d\n", boardX, boardY, pointDensity, Nbins,
           binWidth);
  }

  /*initialize plane*/
  plane* newPlane = calloc(1, sizeof(plane));
  newPlane->Nbins = Nbins;
  newPlane->binWidth = binWidth;
  newPlane->table = calloc(Nbins, sizeof(point*));

  for (int b = 0; b < Nbins; b++) {
    newPlane->table[b] = calloc(TARGET_PPB, sizeof(point));
    newPlane->table[b][0].x = TARGET_PPB; // initialize array sizes
  }

  for (int i = 0; i < Npoints; i++) { // this is probably a segfault magnet lolol
    int tableIdx = hash(*newPlane, buff[i]);
  }

  return newPlane;
}
