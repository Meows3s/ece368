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

      G->data[r][c]->bridge[BOTTOM] = isConnected; //0 weight is there is a bridge there
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

  if(DEBUG)printf("done loading bridges\n");

  //set up node neighbor connections and weights
  for(int r = 0; r < nrow; r++){
    for(int c = 0; c < ncol; c++){
      //neighbors
      G->data[r][c]->nbor[LEFT] = (c != 0 ? G->data[r][c-1] : NULL);
      G->data[r][c]->nbor[RIGHT] = (c != ncol-1 ? G->data[r][c+1] : NULL);
      G->data[r][c]->nbor[TOP] = (r != 0 ? G->data[r-1][c] : NULL);
      G->data[r][c]->nbor[BOTTOM] = (r != nrow-1 ? G->data[r+1][c] : NULL);

      /*
      //weights
      if(G->data[r][c]->bridge[TOP] == 0 && G->data[r][c]->bridge[BOTTOM] == 0){
        G->data[r][c]->bridge[LEFT] = 1;
        G->data[r][c]->bridge[RIGHT] = 1;
      }else if(G->data[r][c]->bridge[BOTTOM] == 0){
        G->data[r][c]->bridge[LEFT] = 1;
        G->data[r][c]->bridge[RIGHT] = 1;
        G->data[r][c]->bridge[TOP] = 2;
      }else if(G->data[r][c]->bridge[TOP] == 0){  
        G->data[r][c]->bridge[LEFT] = 1;
        G->data[r][c]->bridge[RIGHT] = 1;
        G->data[r][c]->bridge[BOTTOM] = 2;
      }else{
        //idk
      }
      */
    }
  }
  if(DEBUG)printf("done loading nbors\n");
  
  //if(DEBUG)dumpGraph(G);

  return G;
}


