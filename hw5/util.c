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

int equalNodes(node* A, node* B){
  if(
    A->pos[0] == B->pos[0] &&
    A->pos[1] == B->pos[1] &&
    A->bridge[0] == B->bridge[0] &&
    A->bridge[1] == B->bridge[1] &&
    A->bridge[2] == B->bridge[2] &&
    A->bridge[3] == B->bridge[3] &&
    A->seen[0] == B->seen[0] &&
    A->seen[1] == B->seen[1] &&
    A->seen[2] == B->seen[2] &&
    A->seen[3] == B->seen[3] &&
    A->distFromSource[0] == B->distFromSource[0] &&
    A->distFromSource[1] == B->distFromSource[1] &&
    A->distFromSource[2] == B->distFromSource[2] &&
    A->distFromSource[3] == B->distFromSource[3] &&
    A->nbor[0] == B->nbor[0] &&
    A->nbor[1] == B->nbor[1] &&
    A->nbor[2] == B->nbor[2] &&
    A->nbor[3] == B->nbor[3] &&
    A->closest[0] == B->closest[0] &&
    A->closest[1] == B->closest[1] &&
    A->closest[2] == B->closest[2] &&
    A->closest[3] == B->closest[3] &&
    A->closestDir[0] == B->closestDir[0] &&
    A->closestDir[1] == B->closestDir[1] &&
    A->closestDir[2] == B->closestDir[2] &&
    A->closestDir[3] == B->closestDir[3]
  ){
    return 1;
  }
  return 0;
}

//make a new node
node* newNode(){
  node* toReturn = calloc(1, sizeof(node));

  for(int n = 0; n < 4; n++){
    toReturn->bridge[n] = 0; //assume no bridge unless a bridge is explicitly set
    toReturn->seen[n] = UNSEEN;
    toReturn->distFromSource[n] = MAX_DIST;
    toReturn->closestDir[n] = LEFT;
  }

  toReturn->pos[0] = -1;
  toReturn->pos[1] = -1;

  toReturn->nbor = calloc(4, sizeof(node*));
  toReturn->closest = calloc(4, sizeof(node*));

  return toReturn;
}

//make a new graph initialize all of the nodes in it.
graph* newGraph(int nrow, int ncol){
  graph* G = calloc(1, sizeof(graph));
  
  ncol = ncol + 1; //add an extra column at the end for the end nodes

  G->ncol = ncol;
  G->nrow = nrow;

  //allocate 2D array for nodes
  G->data = calloc(nrow, sizeof(node**)); //make the first column
  for(int r = 0; r < nrow; r++){
    G->data[r] = calloc(ncol, sizeof(node*));
  }

  //initialize nodes in graph
  for(int r = 0; r < nrow; r++){
    for(int c = 0; c < ncol; c++){
      if(DEBUG)printf("init node at (%d,%d)\n", r, c);
      G->data[r][c] = newNode();
      G->data[r][c]->pos[0] = r;
      G->data[r][c]->pos[1] = c;
    }
  }

  //setup neighbors
  for(int r = 0; r < nrow; r++){
    for(int c = 0; c < ncol; c++){
      G->data[r][c]->nbor[LEFT] = (c != 0 ? G->data[r][c-1] : NULL);
      G->data[r][c]->nbor[RIGHT] = (c != ncol-1 ? G->data[r][c+1] : NULL);
      G->data[r][c]->nbor[TOP] = (r != 0 ? G->data[r-1][c] : NULL);
      G->data[r][c]->nbor[BOTTOM] = (r != nrow-1 ? G->data[r+1][c] : NULL);       
    }
  }
  return G;
}

//make a new queue
queue* newQueue(){
  queue* toReturn = calloc(1, sizeof(queue));
  toReturn->data = NULL;
  toReturn->next = NULL;
  return toReturn;
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

  printf("\nnode at (%d,%d)\n",N->pos[0], N->pos[1]);

  if(N->nbor[LEFT] != NULL){
    printf("node left neighbor is at (%d,%d)", N->nbor[LEFT]->pos[0], N->nbor[LEFT]->pos[1]);
    printf(" bridge = %d\n", N->bridge[LEFT]);
  }

  if(N->nbor[RIGHT] != NULL){
    printf("node right neighbor is at (%d,%d)", N->nbor[RIGHT]->pos[0], N->nbor[RIGHT]->pos[1]);
    printf(" bridge = %d\n", N->bridge[RIGHT]);
  }
  
  if(N->nbor[TOP] != NULL){
    printf("node top neighbor is at (%d,%d)", N->nbor[TOP]->pos[0], N->nbor[TOP]->pos[1]);
    printf(" bridge = %d\n", N->bridge[TOP]);
  }

  if(N->nbor[BOTTOM] != NULL){
    printf("node bottom neighbor is at (%d,%d)", N->nbor[BOTTOM]->pos[0], N->nbor[BOTTOM]->pos[1]);
    printf(" bride = %d\n", N->bridge[BOTTOM]);
  }

  }else{
    printf("\nyou just tried to print a NULL node!!! (dummy)\n");
  }
}

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
