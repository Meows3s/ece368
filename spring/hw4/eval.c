#include "defs.h"

Tnode* readTree(FILE* fptr);
//local defs only
int checkBSTBounds(Tnode*, long long, long long);
int checkBalanced(Tnode*);
int treeHeight(Tnode*);

int eval(char* inputFile){
  FILE* fptr = fopen(inputFile, FILE_READ_FLAG);
  if(fptr == NULL){//can't open at all
    fprintf(stdout, "-1,%d,%d\n", 0, 0);
    return EXIT_FAILURE;
  }

  Tnode* root = readTree(fptr);

  fclose(fptr);

  int goodBst = checkBSTBounds(root, (long long)HBT_MIN - 1, (long long)HBT_MAX);
  int goodBal = checkBalanced(root);

  fprintf(stdout, "1,%d,%d\n", goodBst, goodBal);

  freeTree(root);
  return EXIT_SUCCESS;
}

Tnode* readTree(FILE* fptr){
  int key = 0;
  char branchBits = 0;

  if(fread(&key, sizeof(int), 1, fptr) != 1){return NULL;}
  if(fread(&branchBits, sizeof(char), 1, fptr) != 1){return NULL;}
  Tnode* node = newNode(key);

  if(node == NULL){return NULL;}

  if(branchBits & 2){//left child
    node->left = readTree(fptr);
  }
  if(branchBits & 1){//right child
    node->right = readTree(fptr);
  }
  return node;
}

int checkBSTBounds(Tnode* root, long long minExclusive, long long maxInclusive){
  if(root == NULL){return 1;}
  long long k = (long long)root->key;
  
  if(k <= minExclusive || k > maxInclusive){return 0;}
  
  int left  = checkBSTBounds(root->left,  minExclusive, k);
  int right = checkBSTBounds(root->right, k, maxInclusive);
  
  return left && right;
}

int treeHeight(Tnode* root){
  if(root == NULL){return -1;}
  
  int l = treeHeight(root->left);
  int r = treeHeight(root->right);
  
  return 1 + (l > r ? l : r);
}

int checkBalanced(Tnode* root){
  if(root == NULL){return 1;}//obv need base case lol
  
  int lh = treeHeight(root->left);
  int rh = treeHeight(root->right);
  
  int diff = lh - rh;
  if(diff < -1 || diff > 1){return 0;}
  
  return checkBalanced(root->left) && checkBalanced(root->right);
}
