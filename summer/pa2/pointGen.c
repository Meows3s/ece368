#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {

  int n = atoi(argv[1]);
  int min = atoi(argv[2]);
  int max = atoi(argv[3]);

  FILE* fptr = fopen(argv[4], "w");
  if (fptr == NULL) {
    perror("fopen");
    return 1;
  }

  srand(time(NULL));

  int range = max - min + 1;
  for (int i = 0; i < n; i++) {
    int x = min + rand() % range;
    int y = min + rand() % range;
    fprintf(fptr, "%d %d\n", x, y);
  }

  fclose(fptr);
  return 0;
}
