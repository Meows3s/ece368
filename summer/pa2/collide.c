#include "defs.h"

// insert a point into a given index in the table
void insertPoint(plane* pln, point pnt) {
  if (pln == NULL) return;

  int tableIdx = hash(*pln, pnt);
  int arrayIdx = pln->table[tableIdx][0].x;
  int arrayCap = pln->table[tableIdx][0].y;

  if (arrayIdx >= arrayCap) {
    arrayCap *= 2;
    pln->table[tableIdx] = realloc(pln->table[tableIdx], arrayCap * sizeof(point));
  }

  pln->table[tableIdx][arrayIdx] = pnt;
  pln->table[tableIdx][0].x++;
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
  long long dx = (long long)query.x - center.x;
  long long dy = (long long)query.y - center.y;
  __int128 dist2 = (__int128)dx * dx + (__int128)dy * dy;
  __int128 r2 = (__int128)radius * radius;
  return dist2 <= r2;
}

static int hashCell(plane pln, long long cellX, long long cellY) {
  unsigned long long hashX = (unsigned int)(int)cellX;
  unsigned long long hashY = (unsigned int)(int)cellY;
  unsigned long long combined = hashX * 2654435761ULL + hashY * 2654435761ULL;
  return (int)(combined % (unsigned long long)pln.Nbins);
}

// takes the plane and a point, returns an index where the point should be
int hash(plane pln, point input) {
  long long cellX = (long long)input.x / pln.binWidth;
  long long cellY = (long long)input.y / pln.binWidth;
  if (input.x < 0 && input.x % pln.binWidth != 0) cellX--;
  if (input.y < 0 && input.y % pln.binWidth != 0) cellY--;
  return hashCell(pln, cellX, cellY);
}

// takes in a bunch of crap (duh), returns a list of colliding points
plane* collide(plane* pln, point center, int radius) {
  if (DEBUG) printf("Checking for colliding points at <%d,%d> with radius %d\n", center.x, center.y, radius);
  plane* collides = newPlane(0, 1, 10);

  long long xLo = (long long)center.x - radius, xHi = (long long)center.x + radius;
  long long yLo = (long long)center.y - radius, yHi = (long long)center.y + radius;

  long long cellXLo = xLo / pln->binWidth;
  if (xLo < 0 && xLo % pln->binWidth != 0) cellXLo--;
  long long cellXHi = xHi / pln->binWidth;
  if (xHi < 0 && xHi % pln->binWidth != 0) cellXHi--;
  long long cellYLo = yLo / pln->binWidth;
  if (yLo < 0 && yLo % pln->binWidth != 0) cellYLo--;
  long long cellYHi = yHi / pln->binWidth;
  if (yHi < 0 && yHi % pln->binWidth != 0) cellYHi--;

  for (long long cx = cellXLo; cx <= cellXHi; cx++) {
    for (long long cy = cellYLo; cy <= cellYHi; cy++) {
      int queryHash = hashCell(*pln, cx, cy);

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
  printf("Plane stats:\n");
  printf("Npoints: %d\n", pln.Npoints);
  printf("Nbins: %d\n", pln.Nbins);
  printf("Bin Width: %d\n", pln.binWidth);

  for (int i = 0; i < pln.Nbins; i++) {
    printf("Bin %d has %d points\n", i, pln.table[i][0].x - 1);
  }
}
