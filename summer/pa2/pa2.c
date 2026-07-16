#include "defs.h"

int main(int argc, char** argv) {
  if (argc != 2) return EXIT_FAILURE; // fail if no input file

  plane* mainPlane = readFile(argv[1]);

  if (mainPlane == NULL) {
    if (DEBUG) printf("failed to open file, quitting program...\n");
    return EXIT_FAILURE;
  }

  if (DEBUG) dumpPlane(*mainPlane);

  int x = 0, y = 0, radius = 1;
  int read = 1;

  while (read) {

    // input parser (reused from pa1)
    char input[32] = {0};
    char* args[8] = {0};
    if (!fgets(input, sizeof(input), stdin)) {
      return 1;
    }

    char* tok = strtok(input, " \n");
    for (int i = 0; tok != NULL; i++) {
      args[i] = tok;
      tok = strtok(NULL, " \n");
    }

    char* end;
    if (args[1] != NULL) {
      x = strtol(args[0], &end, 10);
      y = strtol(args[1], &end, 10);
      radius = strtol(args[2], &end, 10);
    }

    plane* collides = collide(mainPlane, (point){.x = x, .y = y}, radius);

    for (int i = 1; i < collides->table[0][0].x; i++) {
      printf("point at <%d,%d> collides with circle\n", collides->table[0][i].x, collides->table[0][i].y);
    }

    free(collides);
  }

  return EXIT_SUCCESS;
}
