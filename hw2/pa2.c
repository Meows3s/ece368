#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define DEBUG 1

int main(){

  char* file = "/home/mo/ece368/hw2/pa2_examples/examples/8.pr";
  printf("testing program on input file: %s\n", file);

  tree* root = loadTree(file);
  
  return 0;
}
