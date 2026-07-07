#include "defs.h"

int main(int argc, char** argv) {
  if (argc != 2) return EXIT_FAILURE; // fail if no input file

  FILE* fptr = fopen(argv[1], FILE_OPEN_FLAG);
  if (fptr == NULL) return EXIT_FAILURE; // bad file name

  // setup stuff
  point* buff;
  readFile("test", &buff);

  return EXIT_SUCCESS;
}
