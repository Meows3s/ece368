
#include "defs.h"
#include <stdlib.h>

int readFile(char* filename, graph* G) {
  FILE* fptr = fopen(filename, FILE_READ_FLAG);
  if (fptr == NULL) return EXIT_FAILURE;

  G->

      fscanf(fptr, "", );

  fclose(fptr);
  return EXIT_SUCCESS;
}
