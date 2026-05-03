#include "defs.h"

int isBST(char*);
int isBSTHelper(FILE*, int, int);

int isBal(char*);

//do some checks on the input tree FILE (not actually a tree)
int eval(char* inputFile){
  FILE* fptr = fopen(inputFile, FILE_READ_FLAG);

  int goodFile = ((fptr == NULL) ? -1 : 1);
  int goodBst = isBST(inputFile);
  int goodBal = isBal(inputFile);

  printf("%d,%d,%d\n", goodFile, goodBst, goodBal);
  
  return EXIT_SUCCESS;
}


//check if the FILE (not tree) given is a valid BST; that is the left node is always smaller than the right
int isBST(char* filename){
  FILE* fptr = fopen(filename, FILE_READ_FLAG);
  
  isBSTHelper(fptr, 0, 0); //start recursive helper

  fclose(fptr);
  return 1; //succeed
}

//helper to determine if tree is a BST
int isBSTHelper(FILE* fptr, int dir, int parentVal){
  int leftSide = 1, rightSide = 1;
  int key = 0, balance = 0;
  if(fscanf(fptr, "%d %d\n", &key, &balance));

  //if we are at a branch
  if(balance == BRANCH){

    leftSide = isBSTHelper(fptr + STEP, 0, key);
    rightSide = isBSTHelper(fptr + 2*STEP, 1, key);

  //if we are at a leaf
  }else if(balance == LEAF){
    if(!dir){ //left leaf
      return parentVal >= key; //true if previous node is >= this one
    }else{ //right leaf
      return parentVal < key; //true if previous node is < this one
    }
  } 
  return leftSide * rightSide; //returns zero if either side failed (whole tree fails)
}

int isBal(char* inputFile){
  return 0;
}
