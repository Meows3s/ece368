#include "defs.h"

//program flow:
//
//step 1: load graph of nodes from text file
//step 2: update node neighbors
//step 3: update weights based on bridge positions
//step 4: run dijkstra's on the graph to update distances
//step 5: starting at the end, follow the shortest path back to the beginning while keeping track of what nodes are in this path
//step 6: using the path generated in step 5, generate the list of board rotations used to actually get there
//step 7: save this list of board positions to the output file
//

int main(){


  char* inputFile;
  char* outputFile1;

  
  graph* G = getNodesFromFile("examples/river.in0");
  
  //dumpGraph(G);
  printf("starting pathfinding\n");
  shortestFromAny(G);  

  return 0;
}
