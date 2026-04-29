#include "defs.h"

//general logic
//step 1: traverse through the entire graph and update nodes with the shortest distance to them from their neighbors
//step 2: go from the end back to the front by following the shortest distances at each node. build a list of nodes while doing this
//step 3: take in the shortest path list and generate the board rotations used
//step 4: profit

//lastNode--->inDir--->thisNode--->outDir--->nbor[x]


//find overall shortest path from left to right
void shortestFromAny(graph** G){
  queue* Qhead = newQueue(); //make the queue
  //can start from anywhere, queue all nodes on the left bank
  for(int r = 0; r < (*G)->nrow; r++){
    node* nodeToQueue = (*G)->data[r][0];
    nodeToQueue->distFromSource[LEFT] = 0; //directly adjacent to source
    enqueue(Qhead, nodeToQueue, LEFT);
  }  
  traverse(G, Qhead); //update node distances
  freeQueue(Qhead); //done with this queue, free it
}

//find shortest path from row X on the left to any row on the right
void shortestFromRow(graph** G, int startRow){
  queue* Qhead = newQueue();
  (*G)->data[startRow][0]->distFromSource[LEFT] = 0;
  enqueue(Qhead, (*G)->data[startRow][0], LEFT);
  traverse(G, Qhead);
  freeQueue(Qhead);
}

void traverse(graph** G, queue* Qhead){
  
  if(DEBUG){
    printf("\nadded these items to the queue to start:\n");
    dumpQueue(Qhead);
  }

  queue dequeuedData;
  node* currentNode;
  int incomingDir = 0;

  while(itemsInQueue(Qhead)){
    //get the node with the shortest distance
    dequeuedData = dequeue(&Qhead);
    currentNode = dequeuedData.data;
    incomingDir = dequeuedData.dir;

    currentNode->seen[incomingDir] = SEEN;

    if(DEBUG){
      printf("\ndequeued node:");
      dumpNode(currentNode);
    }
    enqueueNbors(Qhead, currentNode, incomingDir);
  }
}

//if a neighbor is unvisited and not NULL, add it to the queue
void enqueueNbors(queue* Qhead, node* N, int inDir){
  for(int outDir = 0; outDir < 4; outDir++){

    if(outDir == inDir){continue;} //do not go backwards on the same node

    node* thisNbor = N->nbor[outDir];
    int thisMoveCost = rotCost(N, inDir, outDir);
    int newDist = N->distFromSource[inDir] + thisMoveCost;

    //only enqueue nodes that are unseen and if the new path is shorter
    if(thisNbor != NULL && thisNbor != N->closest[inDir] && thisNbor->seen[outDir] == UNSEEN && newDist < thisNbor-> distFromSource[outDir]){
      
      thisNbor->distFromSource[outDir] = newDist; //node dist is total dist plus any dist added to get to the new node
      thisNbor->closest[outDir] = N; //closest neighbor node for path traceback
      thisNbor->closestDir[outDir] = inDir; //save the direction of the closest node for each

      enqueue(Qhead, thisNbor, outDir);
      
      if(DEBUG){
        printf("\n\nenqueued nbor node:");
        dumpNode(thisNbor);
      } 
    }
  }
}

int rotCost(node* currentNode, int inDir, int outDir){ 
  //if there is already a board in the desired direction, cost is zero

  if(currentNode->bridge[outDir]){
    return 0;
  }
  /*else if(currentNode->bridge[outDir == 3 ? 0 : outDir + 1] || currentNode->bridge[outDir == 0 ? 3 :outDir - 1] || ((inDir == 3 ? 0 : inDir + 1) == outDir) || ((inDir == 0 ? 3 : inDir - 1) == outDir)){ //check adjacent bridge connections
    return 1;
  }else{
    return 2; //otherwise 2 rotations are required
  }*/

  int minCost = 2; //worst case
  for(int d = 0; d < 4; d++){ //check every direction
    if(d == outDir)continue; //already covered
    if(d == inDir || currentNode->bridge[d] == 1){ // inDir is always a bridge
      int diff = abs(d - outDir);
      int cost = min(diff, 4 - diff);
      if(cost < minCost) minCost = cost;
    }
  }
  if(DEBUG)printf("found path of %d cost\n", minCost);
  return minCost;
}

//create a shortest path, return it as a list (queue*)
queue* buildPath(graph* G){
  queue* path = newQueue(); //make a new queue to store the shortest path
  int minDist = MAX_DIST;
  node* endNode = NULL;

  //find the node at the end to start tracing back from as well as the direction
  int endDir = 0;
  for(int r = 0; r < G->nrow; r++){
    for(int d = 0; d < 4; d++){ //check each direction
      if(G->data[r][G->ncol-1]->distFromSource[d] < minDist){
        minDist = G->data[r][G->ncol-1]->distFromSource[d];
        endNode = G->data[r][G->ncol-1];
        endDir = d;
      }
    }    
  }

  if(DEBUG){
    printf("\nstarting traceback with direction %d and distance %d at node:", endDir, minDist);
    dumpNode(endNode);
  }
  
  //follow the closest pointer back the the left edge of the board
  int pathIndex = itemsInQueue(path);
  while(endNode != NULL){
    enqueue(path, endNode, pathIndex); //reusing queue to store the path, dir is always 1 so that items are always appended to the end
    pathIndex--; //makes the priority queue act as a stack

    int nextDir = endNode->closestDir[endDir]; //gets the direction
    endNode = endNode->closest[endDir]; //move the node down the path
    endDir = nextDir; //update the closest direction
  }
  return path;
}

int travelDir(node* from, node* to){
  if(to->pos[0] < from->pos[0]) return TOP;
  if(to->pos[0] > from->pos[0]) return BOTTOM;
  if(to->pos[1] < from->pos[1]) return LEFT;
  return RIGHT;
}

//write the path to a file
void writePath(char* filename, graph* G, queue* path){
  FILE* fptr = NULL;
  openFile(filename, WRITE_FLAG, &fptr);

  if(DEBUG){
    printf("\nsaving the following queue to file:");
    dumpQueue(path);
  }

  queue thisStep = dequeue(&path);
  queue nextStep = dequeue(&path);
  int inDir = RIGHT; //always move right initially

  fprintf(fptr, "(%d,%d)(%d,%d)\n",thisStep.data->pos[0], -1, thisStep.data->pos[0], 0);//initial board

  while(nextStep.data != NULL){
    node* thisNode = thisStep.data;
    node* nextNode = nextStep.data;
    //int outDir = nextStep.dir; //direction to get to "next"
    //int inDir = thisStep.dir;  WRONG!! THIS IS THE PRIOR INDEX NOT THE DIR //direction to get to "this"
    //this cost me several hours btw :((((
     
    int outDir = travelDir();
        inDir = travelDir(thisNode, nextNode);

    int cost = rotCost(thisNode, inDir, outDir);

    printf("writing this node to path: \n");
    dumpNode(nextNode);
    printf("cost = %d\n", cost);


    if(cost == 2){//more complex, need to consider intermediate node used to rotate
      
      int plusOne = (outDir == 3 ? 0 : outDir + 1);
      int minusOne = (outDir == 0 ? 3 : outDir - 1);
      int intermediateDir = minusOne;

      if(thisNode->nbor[intermediateDir] == NULL){intermediateDir = plusOne;}
      if(thisNode->nbor[intermediateDir] == NULL){printf("WTF\n\n\n\n");}

      node* intermediate = thisNode->nbor[intermediateDir];
      fprintf(fptr, "(%d,%d)(%d,%d)\n", thisNode->pos[0], thisNode->pos[1], intermediate->pos[0], intermediate->pos[1]);
      printf("intermediate NODE!!!!!!\n");
    }

    if(cost != 0){ //always do this when rotating
      fprintf(fptr, "(%d,%d)(%d,%d)\n",thisNode->pos[0], thisNode->pos[1], nextNode->pos[0], nextNode->pos[1]); //where the board was before
    }

    //update steps
    thisStep = nextStep;
    nextStep = dequeue(&path);
  }
  fclose(fptr);
}
