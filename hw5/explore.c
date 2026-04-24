#include "defs.h"


//general logic
//step 1: traverse through the entire graph and update nodes with the shortest distance to them from their neighbors
//step 2: go from the end back to the front by following the shortest distances at each node. build a list of nodes while doing this
//step 3: take in the shortest path list and generate the board rotations used
//step 4: profit

void traverse(graph* G){
  queue* Qhead = newQueue(); //make a new queue to store nodes

  //start by queue-ing all nodes on the left side of the river, top to bottom
  for(int r = 0; r < G->nrow; r++){
    node* nodeToQueue = G->data[r][0];
    enqueue(Qhead, nodeToQueue);
  }

  while(!isQueueEmpty(Qhead)){
         
  }
  
  
}

int buildPath(graph* G){
  return 0;
}

int generatePositions(){
  return 0;
}
