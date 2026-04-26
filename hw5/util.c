#include "defs.h"

//open a file with name "filename" and update the given file pointer if possible
int openFile(char* filename, char* openFlag, FILE** fptr){
  *fptr = fopen(filename, openFlag);

  if(*fptr == NULL){
    return EXIT_FAILURE;
  }else{
    return EXIT_SUCCESS;
  }
}

int min(int a, int b){
  if(a < b){
    return a;
  }else{
    return b; //don't care if they are the same, just need a number
  }
}

//make a new node
node* newNode(){
  node* toReturn = calloc(1, sizeof(node));

  for(int n = 0; n < 4; n++){
    toReturn->bridge[n] = 0; //assume no bridge unless a bridge is explicitly set
    toReturn->seen[n] = UNSEEN;
    toReturn->distFromSource[n] = MAX_DIST;
  }

  toReturn->nbor = calloc(4, sizeof(node*));
  toReturn->closest = calloc(4, sizeof(node*));

  return toReturn;
}

//make a new graph initialize all of the nodes in it.
graph* newGraph(int nrow, int ncol){
  graph* G = calloc(1, sizeof(graph));
  
  G->ncol = ncol;
  G->nrow = nrow;

  //allocate 2D array for nodes
  G->data = calloc(1, nrow * sizeof(node*)); //make the first column
  for(int r = 0; r < nrow; r++){ //then fill the first column with rows
    G->data[r] = calloc(1, ncol * sizeof(node));
  }

  //setup neighbors
  for(int r = 0; r < nrow; r++){
    for(int c = 0; c < ncol; c++){
      G->data[r][c]->nbor[LEFT] = (c != 0 ? G->data[r][c-1] : NULL);
      G->data[r][c]->nbor[RIGHT] = (c != ncol-1 ? G->data[r][c+1] : NULL);
      G->data[r][c]->nbor[TOP] = (r != 0 ? G->data[r-1][c] : NULL);
      G->data[r][c]->nbor[BOTTOM] = (r != nrow-1 ? G->data[r+1][c] : NULL);
        
      G->data[r][c]->distFromSource = MAX_DIST; //default unexplored distance      
    }
  }
  return G;
}

//free the entire graph and all nodes
void freeGraph(graph* G){
  
  //free each node
  for(int r = 0; r < G->nrow; r++){
    for(int c = 0; c < G->ncol; c++){
      freeNode(G->data[r][c]);
    }
  }

  //free the arrays that contained the nodes
  for(int r = 0; r < G->nrow; r++){
    free(G->data[r]);//free each row
  }
  free(G->data); //free the first column
  free(G); //finally, free the graph itself
}

//free an individual graph node
void freeNode(node* N){
  free(N->bridge);
  free(N->pos);
  free(N->nbor);
  free(N->closest);
  free(N);
}

//free the entire queue
void freeQueue(queue* Qhead){
  while(Qhead != NULL){
    queue* next = Qhead->next;
    free(Qhead);
    Qhead = next;
  }
}

int itemsInQueue(queue* Qhead){
  int counter = 0;
  while(Qhead->next != NULL){
    Qhead = Qhead->next;
    counter++;
  }
  return counter;
}

//display the entire graph
void dumpGraph(graph* G){
  for(int r = 0; r < G->nrow; r++){
    for(int c = 0; c < G->ncol; c++){
      dumpNode(G->data[r][c]);
    }
  }
}

//display all node properties
void dumpNode(node* N){
  if(N != NULL){

  printf("\nnode at (%d,%d) with distance %d from source:\n",N->pos[0], N->pos[1], N->distFromSource);

  if(N->nbor[LEFT] != NULL){
    printf("node left neighbor is at (%d,%d)", N->nbor[LEFT]->pos[0], N->nbor[LEFT]->pos[1]);
    printf(" cost: %d\n", N->bridge[LEFT]);
  }

  if(N->nbor[RIGHT] != NULL){
    printf("node right neighbor is at (%d,%d)", N->nbor[RIGHT]->pos[0], N->nbor[RIGHT]->pos[1]);
    printf(" cost: %d\n", N->bridge[RIGHT]);
  }
  
  if(N->nbor[TOP] != NULL){
    printf("node top neighbor is at (%d,%d)", N->nbor[TOP]->pos[0], N->nbor[TOP]->pos[1]);
    printf(" cost: %d\n", N->bridge[TOP]);
  }

  if(N->nbor[BOTTOM] != NULL){
    printf("node bottom neighbor is at (%d,%d)", N->nbor[BOTTOM]->pos[0], N->nbor[BOTTOM]->pos[1]);
    printf(" cost: %d\n", N->bridge[BOTTOM]);
  }

  }else{
    printf("you just tried to print a NULL node!!! (dummy)\n");
  }

}

/*
//fun little tool to disply the graph visually
void visualGraph(graph* G){
  for(int r = 0; r < G->nrow; r++){
    for(int c = 0; c < G->ncol; c++){
      
      thisNode = G->data[r][c];
      printf("(%d,%d)", thisNode->pos[0], thisNode->pos[1]);

      for(int n = 0; n < 3; n++){
        if(thisNode->nbor[n] != NULL){
          if(thisNode->bridge[n] == 1){
            printf("--")
          }
        }
      }
      

    }
  }
}
*/

//display all of the nodes in the queue
void dumpQueue(queue* Qhead){
  
  int counter = 0;
  if(Qhead != NULL){
    Qhead = Qhead->next;
  }

  while(Qhead != NULL){  
    printf("\nitem %d in queue:",counter);
    dumpNode(Qhead->data);

    counter++;
    Qhead = Qhead->next;
  }
  printf("\nend queuedump\n\n");
}
