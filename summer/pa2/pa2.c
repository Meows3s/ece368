#include "defs.h"

int main(int argc, char** argv) {
  if (argc != 2) return EXIT_FAILURE; // fail if no input file

  point* buff;
  int Npoints = readFile(argv[1], &buff);
  if (Npoints == -1) {
    if (DEBUG) printf("failed to open file, quitting program...\n");
    return EXIT_FAILURE;
  }
  // plane* mainPlane = createPlane(buff, Npoints);

  return EXIT_SUCCESS;
}
