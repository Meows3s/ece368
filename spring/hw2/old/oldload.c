#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

tree* createNode();
int freeTree(tree*);
int loadHelper(tree*, FILE*);

tree* loadPreorder(char* filename){ //input file is stored as pre-order traversal
  //leaf nodes have to have a number, conversely branch nodes have no number
  tree* root = createNode(); //allocate top node
  FILE* fptr = fopen(filename, "r+");

  if(fptr == NULL){
    if(DEBUG)printf("failed to open file\n");
    return NULL;
  }else{
    if(DEBUG)printf("file opened successfully!\n");
  }

  int nodeNum = loadHelper(root, fptr); //call recursive loader function
  if(DEBUG)printf("%d nodes loaded\n",nodeNum);

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
    
    return loadHelper(node->left, fptr) + loadHelper(node->right, fptr); //only count leaf nodes, not branch nodes
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

int freeTree(tree* root){
  if(root == NULL){return 1;}
  int leftSide = freeTree(root->left);
  int rightSide = freeTree(root->right);
  free(root);
  return leftSide + rightSide;
}
