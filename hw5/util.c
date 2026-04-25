#include "defs.h"

//open a file with name "filename" and update the given file pointer if possible
int openFile(char* filename, char* openFlag, FILE** fptr){
  *fptr = fopen(filename, openFlag);

  if(fptr == NULL){
    return EXIT_FAILURE;
  }else{
    return EXIT_SUCCESS;
  }
}

//make a new node
node* newNode(){
  node* toReturn = calloc(1, sizeof(node));
  toReturn->bridge = calloc(1, 4 * sizeof(int));
  toReturn->pos = calloc(1, 2 * sizeof(int));
  toReturn->seen = UNSEEN; //initialize to unseen
  toReturn->nbor = calloc(1, 4 * sizeof(node*));

  return toReturn;
}

//make a new graph and but don't initialize all of the nodes in it.
graph* newGraph(int nrow, int ncol){
  graph* G = calloc(1, sizeof(graph));
  
  G->nrow = nrow;
  G->ncol = ncol;

  //allocate 2D array for nodes
  G->data = calloc(1, nrow * sizeof(node*)); //make the first column
  for(int r = 0; r < nrow; r++){ //then fill the first column with rows
    G->data[r] = calloc(1, ncol * sizeof(node));
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
  free(N->closest);
  free(N);
}

//free the entire queue by dequeuing every item
void freeQueue(queue* Qhead){
  while(Qhead != NULL){
    queue* nextQNode = Qhead->next;
    dequeue(Qhead); //delete the top node
    Qhead = nextQNode;
  }
  free(Qhead); //finish by freeing the head
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
  printf("\nnode at (%d,%d):\n",N->pos[0], N->pos[1]);

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
  queue* nextQ = Qhead->next; //do this so we don't move the actual head lol
  int counter = 0;
  while(nextQ != NULL && nextQ->data != NULL){
    printf("\nitem %d in queue:",counter);
    dumpNode(nextQ->data);

    nextQ = nextQ->next;
    counter++;
  }
  printf("\nend queuedump\n\n");
}
