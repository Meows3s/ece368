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
int shortestFromRow(graph** G, int startRow){
  queue* Qhead = newQueue();
  (*G)->data[startRow][0]->distFromSource[LEFT] = 0;
  enqueue(Qhead, (*G)->data[startRow][0], LEFT);
  traverse(G, Qhead);
  freeQueue(Qhead);

  int minDist = MAX_DIST;
  for(int r = 0; r < (*G)->nrow; r++){
    for(int d = 0; d < 4; d++){ //check each direction
      if((*G)->data[r][(*G)->ncol-1]->distFromSource[d] < minDist && d != LEFT){
          minDist = (*G)->data[r][(*G)->ncol-1]->distFromSource[d];
      }
    } 
  }

  return minDist; 
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
    //printf("cost 0: inDir=%d outDir=%d at (%d,%d)\n", inDir, outDir, currentNode->pos[0], currentNode->pos[1]); 
    return 0;
    
  }

  int minCost = 2; //worst case
  for(int d = 0; d < 4; d++){ //check every direction
    if(d == outDir)continue; //already covered
    if(d == inDir || currentNode->bridge[d] == 1){ // inDir is always a bridge
      int diff = abs(d - outDir);
      int cost = min(diff, 4 - diff);
      if(cost < minCost) minCost = cost;
    }
  }

  //printf("cost %d: inDir=%d outDir=%d at (%d,%d)\n", minCost, inDir, outDir, currentNode->pos[0], currentNode->pos[1]);
  return minCost;
}

int findUsedBoard(node* N, int inDir, int outDir){
  int minCost = 2;
  int bestDir = inDir; // default to incoming board
  for(int d = 0; d < 4; d++){
    if(d == outDir) continue;
    if(d == inDir || N->bridge[d] == 1){
      int diff = abs(d - outDir);
      int cost = min(diff, 4 - diff);
      if(cost < minCost){
        minCost = cost;
        bestDir = d;
      }
    }
  }
  return bestDir;
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
  int pathIndex = G->nrow * G->ncol * 3;

while(endNode != NULL){
 
  enqueue(path, endNode, pathIndex);
  pathIndex--;
 
  node* prevNode = endNode->closest[endDir];
  if(prevNode != NULL){
      int moveDir = travelDir(prevNode, endNode);
      int prevInDir = endNode->closestDir[endDir];
      int usedBoardDir = findUsedBoard(prevNode, prevInDir, moveDir);
  
      if(usedBoardDir != prevInDir && prevNode->nbor[usedBoardDir] != NULL){
        enqueue(path, prevNode, pathIndex);
        pathIndex--;
        enqueue(path, prevNode->nbor[usedBoardDir], pathIndex);
        pathIndex--;
      }
    } 

    int nextDir = endNode->closestDir[endDir];
    endNode = endNode->closest[endDir];
    endDir = nextDir;
  }

  if(DEBUG){dumpQueue(path);}

  return path;
}

int travelDir(node* from, node* to){
  if(to->pos[0] < from->pos[0]) return TOP;
  if(to->pos[0] > from->pos[0]) return BOTTOM;
  if(to->pos[1] < from->pos[1]) return LEFT;
  return RIGHT;
}

//helper to ensure boards are printed with the correct spec
void writeBoard(FILE* fptr, node* a, node* b){
  if(a->pos[0] > b->pos[0] || a->pos[1] > b->pos[1]){
    node* tempNode = a;
    a = b;
    b = tempNode;
  }
  fprintf(fptr, "(%d,%d)(%d,%d)\n",a->pos[0], a->pos[1], b->pos[0], b->pos[1]); //where the board was before
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

  fprintf(fptr, "(%d,%d)(%d,%d)\n",thisStep.data->pos[0], -1, thisStep.data->pos[0], 0);//initial boards

  node* lastA = NULL;
  node* lastB = NULL;

  while(nextStep.data != NULL){
    node* thisNode = thisStep.data;
    node* nextNode = nextStep.data;
    
    //skip if this is a duplicate of the last written board
    if((thisNode == lastA && nextNode == lastB) || (thisNode == lastB && nextNode == lastA)){
        thisStep = nextStep;
        nextStep = dequeue(&path);
        continue;
    }
    
    writeBoard(fptr, thisNode, nextNode);
    
    lastA = thisNode;
    lastB = nextNode;
    thisStep = nextStep;
    nextStep = dequeue(&path);
  }

fclose(fptr);
}
