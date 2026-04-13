#include "defs.h"

int balancedHelper(Tnode*);
int isBSTHelper(FILE*, int, int);

//returns 1 if the tree is height balanced, returns 0 otherwise
int isBalanced(char* filename){
  FILE* fptr = fopen(filename, "r");
  if(fptr == NULL){return 0;} //check failed
  
  

  fclose(fptr);
  return 1; //fix
}

//recursive helper func
int balancedHelper(Tnode* thisNode){
  
}

//check if the FILE (not tree) given is a valid BST; that is the left node is always smaller than the right
int isBST(char* filename){
  FILE* fptr = fopen(filename, "r");
  if(fptr == NULL){return 0;} //check failed
  
  isBSTHelper(fptr, 0, 0); //start recursive helper

  fclose(fptr);
  return 1; //succeed
}

//helper to determine if tree is a BST
int isBSTHelper(FILE* fptr, int dir, int parentVal){
  int leftSide = 1, rightSide = 1;
  int key = 0, balance = 0;
  int pass = fscanf(fptr, "%d %d\n", &key, &balance);

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

int isGoodFile(char* filename, char* mode){
  FILE* fptr = fopen(filename, mode);
  if(fptr == NULL){return 0;} //check failed
  fclose(fptr);
  return 1;
}
