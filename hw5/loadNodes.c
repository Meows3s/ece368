#include "defs.h"

graph* getNodesFromFile(char* filename){
  FILE* fptr = NULL;
  if(openFile(filename, OPEN_FLAG, &fptr));

  //make a new graph of size x by y
  int nrow = 0, ncol = 0;
  if(fscanf(fptr, "%d %d\n", &nrow, &ncol));
  
  graph* G = newGraph(nrow, ncol);
  
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

      G->data[r][c]->bridge[BOTTOM] = isConnected; //1 for bridge, 0 for no bridge
      G->data[r+1][c]->bridge[TOP] = isConnected;

      G->data[r][c]->pos[0] = r;
      G->data[r][c]->pos[1] = c;

      G->data[r+1][c]->pos[0] = r+1;
      G->data[r+1][c]->pos[1] = c;

      if(DEBUG){
        printf("bridge = %d at (%d,%d)\n",isConnected, r, c);
        printf("bridge = %d at (%d,%d)\n",isConnected, r+1, c);
      }
    }
    if(fscanf(fptr, "\n")); //move to next line
  }
  if(DEBUG)printf("done loading bridges\n");
  
  fclose(fptr);
  return G;
}


