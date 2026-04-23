#include "defs.h"

int getNodesFromFile(char* filename, graph* G){
  FILE* fptr = NULL;
  if(openFile(filename, OPEN_FLAG, &fptr)){
    return EXIT_FAILURE;
  }

  //make a new graph of size x by y
  int nrow = 0, ncol = 0;
  if(fscanf(fptr, "%d %d\n", &nrow, &ncol) != 2){return EXIT_FAILURE;};
  G = newGraph(nrow, ncol);
  
  if(DEBUG)printf("setting up graph of size (%d,%d)\n",nrow, ncol);

  //initialize nodes in graph
  for(int r = 0; r < nrow; r++){
    for(int c = 0; c < ncol; c++){
      if(DEBUG)printf("init node at (%d,%d)\n", r, c);
      G->data[r][c] = newNode();
    }
  }

  //for each row, load all of the columns
  int isConnected = 0;

  for(int r = 0; r < nrow-1; r++){
    for(int c = 0; c < ncol; c++){

      isConnected = fgetc(fptr) - 48; //convert to int

      G->data[r][c]->bridge[BOTTOM] = isConnected;
      G->data[r+1][c]->bridge[TOP] = isConnected;

      G->data[r][c]->pos[0] = r;
      G->data[r][c]->pos[1] = c;

      G->data[r+1][c]->pos[0] = r+1;
      G->data[r+1][c]->pos[1] = c;

      if(DEBUG){
        isConnected ? printf("bridge at (%d,%d)\n", r, c) : printf("no bridge at (%d,%d)\n", r, c);
      }

    }
    if(fscanf(fptr, "\n")); //move to next line
  }

  dumpGraph(G);

  return EXIT_SUCCESS;
}


