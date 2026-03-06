#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

#define VERT 'V'
#define HORIZ 'H'
#define LEAF 'E'

tree* createNode();
int loadHelper(tree*, FILE*);


tree* loadTree(char* filename){ //input file is stored as pre-order traversal
  //leaf nodes have to have a number, conversely branch nodes have no number
  tree* root = createNode(); //allocate top node
  FILE* fptr = fopen(filename, "r+");

  if(fptr == NULL){
    printf("failed to open file\n");
    return NULL;
  }else{
    printf("file opened successfully!\n");
  }

  int nodeNum = loadHelper(root, fptr); //call recursive loader function
  printf("%d nodes loaded\n",nodeNum);

  fclose(fptr);
  return root;
}

int loadHelper(tree* node, FILE* fptr){
  //pre order traversal means root, left, right
  if(feof(fptr)){
    printf("end of file reached\n");
    return 0;
  }
  
  char mode;
  fscanf(fptr, "%c\n", &mode);

  if(mode == VERT || mode == HORIZ){ //if we are not yet at the bottom of this branch...

    printf("loading branch with mode %c\n", mode);

    node->div = mode;
    node->left = createNode();
    node->right = createNode();
    
    return loadHelper(node->left, fptr) + loadHelper(node->right, fptr) + 1; //plus one for the branch node
  }

  //if we are at the bottom of this branch
  fseek(fptr, -1, SEEK_CUR); //go back
  node->div = LEAF;
  
  //int fscanf ( FILE * stream, const char * format, ... );
  fscanf(fptr, "%d(%d,%d)\n", &node->blockNum, &node->xPos, &node->yPos);

  printf("found node with blocknum %d\n", node->blockNum);

  return 1;
}

tree* createNode(){ //allocate space for a new empty node
  tree* node = calloc(1, sizeof(tree));

  //node->div = ;
  node->blockNum = -1;
  node->xPos = -1;
  node->yPos = -1;
  node->left = NULL;
  node->right = NULL;

  return node;
}
