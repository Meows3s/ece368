#include "defs.h"

int balancedHelper(Tnode*);
int isBSTHelper(Tnode*);

//returns 1 if the tree is height balanced, returns 0 otherwise
int isBalanced(Tnode *root){
  
  int depthDelta = balancedHelper(root);
  depthDelta = depthDelta * depthDelta; //square delta to remove negatives
  if(depthDelta <= 1){
    return 0; //succeed!
  }
  return 0; //fail
}

//recursive helper func
int balancedHelper(Tnode *thisNode){
  if(thisNode == NULL){return -1;}
  
  int leftDepth = balancedHelper(thisNode->left) + 1;
  int rightDepth = balancedHelper(thisNode->right) + 1;

  //return the difference between the depth of the right and left branches
  return leftDepth - rightDepth;
}

//check if the tree given is a valid BST; that is the left node is always smaller than the right
int isBST(Tnode* root){
  return isBSTHelper(root);
}

//helper to determine if tree is a BST
int isBSTHelper(Tnode* root){
  //check self, check left and right, done
  if(root->left == NULL && root->right == NULL){return root->key;} //bottom node, not a failure
  int pass = (root->left->key < root->key && root->key < root->right->key);
  return pass * isBSTHelper(root->left) * isBSTHelper(root->right); //only 1 if all levels pass
}



int isGoodFile(char* filename, char* mode){
  FILE* fptr = fopen(filename, mode);
  if(fptr == NULL){return 0;} //check failed
  fclose(fptr);
  return 1;
}
