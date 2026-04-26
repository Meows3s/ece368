#include "defs.h"

//general logic
//step 1: traverse through the entire graph and update nodes with the shortest distance to them from their neighbors
//step 2: go from the end back to the front by following the shortest distances at each node. build a list of nodes while doing this
//step 3: take in the shortest path list and generate the board rotations used
//step 4: profit

//find overall shortest path from left to right
void shortestFromAny(graph** G){
  queue* Qhead = newQueue(); //make the queue
  //can start from anywhere, queue all nodes on the left bank
  for(int r = 0; r < (*G)->nrow; r++){
    node* nodeToQueue = (*G)->data[r][0];
    nodeToQueue->distFromSource = 0; //directly adjacent to source
    enqueue(Qhead, nodeToQueue);
  }  
  traverse(G, Qhead); //update node distances
  freeQueue(Qhead); //done with this queue, free it
}

//find shortest path from row X on the left to any row on the right
void shortestFromRow(graph** G, int startRow){
  queue* Qhead = newQueue();
  enqueue(Qhead, (*G)->data[startRow][0]);
  traverse(G, Qhead);
  freeQueue(Qhead);
}

void traverse(graph** G, queue* Qhead){
  
  if(DEBUG){
    printf("\nadded these items to the queue to start:\n");
    dumpQueue(Qhead);
  }

  node* currentNode = NULL;
  
  while(itemsInQueue(Qhead)){
    //get the node with the shortest distance
    currentNode = dequeue(&Qhead);
    currentNode->seen = SEEN; //mark it as visited

    if(DEBUG){
      printf("\ndequeued node:");
      dumpNode(currentNode);
    }

    enqueueNbors(Qhead, currentNode);
    dumpQueue(Qhead);
  }
}

//if a neighbor is unvisited and not NULL, add it to the queue
void enqueueNbors(queue* Qhead, node* N){
  for(int n = 0; n < 4; n++){
    node* thisNbor = N->nbor[n];  
    int newDist = N->distFromSource + N->bridge[n];

    //only enqueue nodes that are unseen and if the new path is shorter
    if(thisNbor != NULL && thisNbor->seen == UNSEEN && newDist < thisNbor-> distFromSource){
      
      thisNbor->distFromSource = newDist; //node dist is total dist plus any dist added to get to the new node
      thisNbor->closest = N; //closest neighbor node for path traceback

      enqueue(Qhead, thisNbor);
      
      if(DEBUG){
        printf("\n\nenqueued nbor node:");
        dumpNode(thisNbor);
      } 
    }
  }
}

//create a shortest path, return it as a list (queue*)
queue* buildPath(graph* G){
  queue* path = newQueue(); //make a new queue to store the shortest path
  int minDist = MAX_DIST;
  node* endNode = NULL;

  //find the node at the end to start tracing back from
  for(int r = 0; r < G->nrow; r++){
    if(G->data[r][G->ncol-1]->distFromSource < minDist){
      minDist = G->data[r][G->ncol-1]->distFromSource;
      endNode = G->data[r][G->ncol-1];
    }
  }

  if(DEBUG){
    printf("\nstarting traceback at node:");
    dumpNode(endNode);
  }
  
  //follow the closest pointer back the the left edge of the board
  while(endNode != NULL){
    enqueue(path, endNode);
    endNode = endNode->closest;
  }
  return path;
}

//write the path to a file
void writePath(char* filename, queue* path){
  FILE* fptr = NULL;
  openFile(filename, WRITE_FLAG, &fptr);

  //write the start and end positions of the board to fptr
  
  fclose(fptr);
}
