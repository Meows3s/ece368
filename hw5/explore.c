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
  
  if(DEBUG){
    printf("\nadded these items to the queue to start:\n");
    dumpQueue(Qhead);
  }

  //while there are still nodes to explore
  //while(!isQueueEmpty(Qhead->next)){
    //get the node with the shortest distance
    node* currentNode = dequeue(Qhead);
    
    if(DEBUG){
      printf("dequeued node:");
      dumpNode(currentNode);
    }


    enqueueNbors(Qhead, currentNode);
    
    dumpQueue(Qhead);

  //}
}

//if a neighbor is unvisited and not NULL, add it to the queue
void enqueueNbors(queue* Qhead, node* N){
  for(int n = 0; n < 3; n++){
    node* thisNbor = N->nbor[n];

    if(thisNbor != NULL){
      enqueue(Qhead, thisNbor);
      
      if(DEBUG){
        printf("added below node to queue:\n");
        dumpNode(thisNbor);
      } 
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
