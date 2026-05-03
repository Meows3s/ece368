#include "defs.h"

graph* getNodesFromFile(char* filename){
  FILE* fptr = NULL;
  if(openFile(filename, OPEN_FLAG, &fptr));

  //make a new graph of size x by y
  int nrow = 0, ncol = 0;
  if(fscanf(fptr, "%d %d\n", &nrow, &ncol));
  
  graph* G = newGraph(nrow, ncol);
  
  if(DEBUG)printf("setting up graph of size (%d,%d)\n",G->nrow, G->ncol);
  
  //for each row, load all of the columns
  int isConnected = 0;

  for(int r = 0; r < G->nrow-1; r++){
    for(int c = 0; c < G->ncol-1; c++){

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

    //last column of row is the end node and will never have a bridge but we still want to set the pos

    if(fscanf(fptr, "\n")); //move to next line
  }

  if(DEBUG)printf("done loading bridges\n");
  
  fclose(fptr);
  return G;
}


