#include "defs.h"

// insert a point into a given index in the table
void insertPoint(plane* pln, point pnt) {
  if (pln == NULL) return;

  int tableIdx = hash(*pln, pnt); // add one to not overwrite the metadata point
  int arrayIdx = pln->table[tableIdx][0].x;
  int arrayCap = pln->table[tableIdx][0].y;

  // printf("trying to insert a point at bin index %d, array index %d\n", tableIdx, arrayIdx);

  if (arrayIdx >= arrayCap) {
    arrayCap *= 2;                                                                  // update the size
    pln->table[tableIdx] = realloc(pln->table[tableIdx], arrayCap * sizeof(point)); // make the array bigger
  }

  pln->table[tableIdx][arrayIdx] = pnt; // set point
  pln->table[tableIdx][0].x++;          // update length tracker
  pln->table[tableIdx][0].y = arrayCap;
  pln->Npoints++;
}

int pointEqual(point a, point b) {
  if (a.x == b.x && a.y == b.y) return 1;
  return 0;
}

int pointInPlane(plane pln, point pnt) {
  for (int i = 1; i < pln.table[0][0].x; i++) {
    if (pln.table[0][i].x == pnt.x && pln.table[0][i].y == pnt.y) {
      return 1;
    }
  }
  return 0;
}

int withinCircle(point center, int radius, point query) {
  float dist = sqrt(pow((query.x - center.x), 2) + pow((query.y - center.y), 2));
  if (dist <= radius) {
    return 1;
  } else {
    return 0;
  }
}

// takes the plane and a point, returns an index where the point should be
int hash(plane pln, point input) {
  int cellX = input.x / pln.binWidth;
  int cellY = input.y / pln.binWidth;
  if (input.x < 0 && input.x % pln.binWidth != 0) cellX--;
  if (input.y < 0 && input.y % pln.binWidth != 0) cellY--;

  unsigned long long hashX = (unsigned int)cellX;
  unsigned long long hashY = (unsigned int)cellY;
  unsigned long long combined = hashX * 2654435761ULL + hashY * 2654435761ULL; // knuths hash multiplier

  return (int)(combined % (unsigned long long)pln.Nbins); // scale to number of bins
}

// takes in a bunch of crap (duh), returns a list of colliding points
plane* collide(plane* pln, point center, int radius) {
  if (DEBUG) printf("Checking for colliding points at <%d,%d> with radius %d\n", center.x, center.y, radius);
  plane* collides = newPlane(0, 1, 10);

  int xLo = center.x - radius, xHi = center.x + radius - 1; // last included x
  int yLo = center.y - radius, yHi = center.y + radius - 1;

  int cellXLo = xLo / pln->binWidth; // fix off by one things
  if (xLo < 0 && xLo % pln->binWidth != 0) cellXLo--;
  int cellXHi = xHi / pln->binWidth;
  if (xHi < 0 && xHi % pln->binWidth != 0) cellXHi--;
  int cellYLo = yLo / pln->binWidth;
  if (yLo < 0 && yLo % pln->binWidth != 0) cellYLo--;
  int cellYHi = yHi / pln->binWidth;
  if (yHi < 0 && yHi % pln->binWidth != 0) cellYHi--;

  for (int cx = cellXLo; cx <= cellXHi; cx++) {
    for (int cy = cellYLo; cy <= cellYHi; cy++) {
      point query = (point){.x = cx * pln->binWidth, .y = cy * pln->binWidth};
      int queryHash = hash(*pln, query);

      for (int p = 1; p < pln->table[queryHash][0].x; p++) {

        point binPoint = (point){.x = pln->table[queryHash][p].x, .y = pln->table[queryHash][p].y};
        if (DEBUG) printf("checking point <%d,%d> in bin %d\n", binPoint.x, binPoint.y, queryHash);

        if (withinCircle(center, radius, binPoint) && !pointInPlane(*collides, binPoint)) {
          insertPoint(collides, binPoint);
        }
      }
    }
  }

  return collides;
}

void dumpPlane(plane pln) {
  // basic stats
  printf("Plane stats:\n");
  printf("Npoints: %d\n", pln.Npoints);
  printf("Nbins: %d\n", pln.Nbins);
  printf("Bin Width: %d\n", pln.binWidth);

  // bin stats
  for (int i = 0; i < pln.Nbins; i++) {
    printf("Bin %d has %d points\n", i, pln.table[i][0].x - 1); // we are not including the metadata point
  }
}
