#include "defs.h"

int openFile(char* filename, char* openFlag, FILE** fptr){
  *fptr = fopen(filename, openFlag);

  if(fptr == NULL){
    return EXIT_FAILURE;
  }else{
    return EXIT_SUCCESS;
  }
}

node* newNode(){
  node* toReturn = calloc(1, sizeof(node));
  toReturn->bridge = calloc(1, 4 * sizeof(int));
  toReturn->pos = calloc(1, 2 * sizeof(int));
  toReturn->seen = UNSEEN; //initialize to unseen
  return toReturn;
}

graph* newGraph(int nrow, int ncol){
  graph* G = calloc(1, sizeof(graph));
  
  G->nrow = nrow;
  G->ncol = ncol;

  //allocate 2D array for nodes
  G->data = calloc(1, nrow * sizeof(node*)); //make the first column
  for(int i = 0; i < ncol; i++){ //then fill those columns with rows
    G->data[i] = calloc(1, nrow * sizeof(node));
  }
  return G;
}

//todo
void freeGraph(graph* G){
  
}

void freeNode(node* N){

}

void dumpGraph(graph* G){
  for(int r = 0; r < G->nrow; r++){
    for(int c = 0; c < G->ncol; c++){
      dumpNode(G->data[r][c]);
    }
  }
}

void dumpNode(node* N){
  printf("\n\nnode at (%d,%d):\n",N->pos[0], N->pos[1]);
  printf("node bridge connections:\n");
  printf("LEFT: %d\n", N->bridge[LEFT]);
  printf("RIGHT: %d\n", N->bridge[RIGHT]);
  printf("TOP: %d\n", N->bridge[TOP]);
  printf("BOTTOM: %d\n", N->bridge[BOTTOM]);
}


