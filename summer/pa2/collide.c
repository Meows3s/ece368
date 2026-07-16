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
}

int pointEqual(point a, point b) {
  if (a.x == b.x && a.y == b.y) return 1;
  return 0;
}

int withinCircle(point center, int radius, point query) {
  float dist = sqrt(pow((query.x - center.x), 2) + pow((query.y - center.y), 2));
  if (dist < radius) {
    return 1;
  } else {
    return 0;
  }
}

// takes the plane and a point, returns an index where the point should be
int hash(plane pln, point input) {
  // shift x over by the number of bits used in y
  long long hashVal = (input.x << __builtin_clz(input.y)) + input.y;
  long long hashVal_compare = hashVal;
  // this is basically the same as a sequential compare on only one sequence
  hashVal = hashVal << 1;
  int hashedTo = ((hashVal ^ hashVal_compare) % pln.Nbins);
  return hashedTo;
}

// takes in a bunch of crap (duh), returns a list of colliding points
plane* collide(plane* pln, point center, int radius) {
  if (DEBUG) printf("Checking for colliding points at <%d,%d> with radius %d\n", center.x, center.y, radius);

  /*step one: determine the bins we need to search*/
  int Noverlaps = (2 * radius) / (pln->binWidth);

  point lowerLeft = center;
  lowerLeft.x -= radius;
  lowerLeft.y -= radius;

  /*step two: search the bins and find the points that are colliding*/
  // note: points must be strictly within circle, not on border!
  // iterate through each bin

  plane* collides = newPlane(TARGET_PPB * Noverlaps, 1, 10);
  point lastInsert = lowerLeft;

  for (int x = lowerLeft.x; x < center.x + radius; x += pln->binWidth) {
    for (int y = lowerLeft.y; y < center.y + radius; y++) {

      point query = (point){.x = x, .y = y};
      int queryHash = hash(*pln, query);
      if (pln->table[queryHash][0].x > 1) { // bin is potentially inside circle and contains points, search it

        printf("checking bin %d\n", queryHash);
        for (int p = 0; p < pln->table[queryHash][0].x; p++) { // check each point in the bin
          if (withinCircle(center, radius, query) && !pointEqual(query, lastInsert)) {
            insertPoint(collides, query); // add it to the collision list
            lastInsert = query;
          }
        }

        y += pln->binWidth;
      } else {
        y += pln->binWidth; // bin is empty, skip it
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
