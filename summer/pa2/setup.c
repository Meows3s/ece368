#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

// reads file into point buffer, returns number of points in buffer
int readFile(char* filename, point** buff) {
  FILE* fptr = fopen(filename, FILE_OPEN_FLAG);
  if (fptr == NULL) return -1;

  // determine file size
  fseek(fptr, 0, SEEK_END);
  long fileSize = ftell(fptr);
  rewind(fptr); // reset pointer

  *buff = calloc(fileSize, sizeof(point)); // update pointer correct size;

  // for loop abuse:
  for (long i = 0; i; i++) {
    if (fscanf(fptr, "%d %d\n", &buff[i]->x, &buff[i]->y) == 0) break;
  }

  return fileSize;
}

int calcBins(point* buff, int Npoints, point upperRight, point lowerLeft) {
  int Nbins = 0;
  return Nbins;
}

plane* createPlane(point* buff, int Npoints) {
  plane* newPlane = calloc(1, sizeof(plane));

  point upperRight;
  point lowerLeft;

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

  calcBins(buff, Npoints, upperRight, lowerLeft);

  return newPlane;
}

// attendance question: Which sorting algorithm might you have naturally used?
// (sorting cards, etc).
