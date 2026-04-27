#include "defs.h"

//program flow:
//
//step 1: load graph of nodes from text file
//step 2: update node neighbors
//step 3: update weights based on bridge positions
//step 4: run dijkstra's on the graph to update distances (and also update weights depending on approach direction)
//step 5: starting at the end, follow the shortest path back to the beginning while keeping track of what nodes are in this path
//step 6: using the path generated in step 5, generate the list of board rotations used to actually get there
//step 7: save this list of board positions to the output file
//

int main(int argc, char** argv){
  char* inputFile = argv[1];
  char* outputFile1 = argv[2];
  char* outputFile2 = argv[3];
  
  //output file one
  graph* G = getNodesFromFile(inputFile);
  shortestFromAny(&G);
  queue* path = buildPath(G);
  writePath(outputFile1, G, path);
  freeQueue(path);
  freeGraph(G);

  //output file two
  /*graph* G = getNodesFromFile(inputFile);
  for(int r = 0; r < G->nrow; r++){
    shortestFromOne(&G);
    queue* thisRowPath = buildPath(G);
    writePath(outputFile2, thisRowPath);
    freeQueue(thisRowPath);
  }
  freeGraph(G);
*/

  return 0;
}
