#include "defs.h"

//general logic
//step 1: traverse through the entire graph and update nodes with the shortest distance to them from their neighbors
//step 2: go from the end back to the front by following the shortest distances at each node. build a list of nodes while doing this
//step 3: take in the shortest path list and generate the board rotations used
//step 4: profit


//find overall shortest path from left to right
void shortestFromAny(graph* G){
  queue* Qhead = newQueue(); //make the queue

  //can start from anywhere, queue all nodes on the left bank
  for(int r = 0; r < G->nrow; r++){
    node* nodeToQueue = G->data[r][0];
    enqueue(Qhead, nodeToQueue);
  }
  traverse(G, Qhead);
}

//find shortest path from row X on the left to any row on the right
void shortestFromRow(graph* G, int startRow){
  queue* Qhead = newQueue();
  enqueue(Qhead, G->data[startRow][0]);
  traverse(G, Qhead);
}

void traverse(graph* G, queue* Qhead){
  
  //while there are still nodes to explore
  while(!isQueueEmpty(Qhead)){
    //get the node with the shortest distance
    node* currentNode = dequeue(Qhead);
    
    if(currentNode->pos[1] == 0){ //left edge case
      
    }else if(currentNode->pos[1] == G->ncol){ //right edge case

    }else if(currentNode->pos[0] == 0){ //top edge case

    }else if(currentNode->pos[0] == G->nrow){ //bottom edge case
      
    }else{ //not on edge, queue all
      
    }

  }

}

int buildPath(graph* G){
  queue* path = newQueue(); //make a new queue to store the shortest path
  
  return 1;
}

int generatePositions(queue* path){
  return 1;
}
