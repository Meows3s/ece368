#include "defs.h"
#include <stdio.h>

#define VERBOSE "-v"

int main(int argc, char** argv) {
  if (argc != 2) return EXIT_FAILURE; // fail if no input file

  plane* mainPlane = readFile(argv[1]);

  if (mainPlane == NULL) {
    if (DEBUG) printf("failed to open file, quitting program...\n");
    return EXIT_FAILURE;
  }
  if (DEBUG) dumpPlane(*mainPlane);

  int x = 0, y = 0, radius = 1, verbose = 0;
  while (1) {

    // input parser (reused from pa1)
    char input[128] = {0};
    char* args[64] = {0};
    if (!fgets(input, sizeof(input), stdin)) {
      break;
    }

    int nargs = 0;
    char* tok = strtok(input, " \n");
    for (nargs = 0; tok != NULL; nargs++) {
      args[nargs] = tok;
      tok = strtok(NULL, " \n");
    }

    char* end;
    if (args[1] != NULL) {
      x = strtol(args[0], &end, 10);
      y = strtol(args[1], &end, 10);
      radius = strtol(args[2], &end, 10);
      if (nargs >= 4) {
        verbose = !strcmp(args[3], VERBOSE); // set verbose mode
      } else {
        verbose = 0;
      }
    }

    plane* collides = collide(mainPlane, (point){.x = x, .y = y}, radius);

    if (verbose) {
      for (int i = 1; i < collides->table[0][0].x; i++) {
        printf("point at <%d,%d> collides with circle\n", collides->table[0][i].x, collides->table[0][i].y);
      }
    }
    printf("%d\n", collides->Npoints);

    freePlane(collides);
  }
  freePlane(mainPlane);

  return EXIT_SUCCESS;
}
