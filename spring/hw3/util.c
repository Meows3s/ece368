#include "defs.h"

void writeHelper(Tnode*, FILE*);

int max(int a, int b){
  return (a > b ? a : b);
}

void recalcDims(Tnode* node){
  if(node->divType == HORIZ){
    node->width  = max(node->left->width,  node->right->width);
    node->height = node->left->height + node->right->height;
  }else{
    node->width  = node->left->width  + node->right->width;
    node->height = max(node->left->height, node->right->height);
  }
}

Tnode* newTree(void){
  Tnode* toReturn = calloc(1, sizeof(Tnode));
  toReturn->left = NULL;
  toReturn->right = NULL;
  return toReturn;
}

void freeTree(Tnode* root){
  if(root == NULL){return;}
  //free left, then right, then self
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

//write to the file
void writePreorder(Tnode* root, char* filename){
  FILE* fptr = fopen(filename, FILE_WRITE_FLAG);
  if(fptr == NULL){return;}
  writeHelper(root, fptr);
  fclose(fptr);
}

//helper for the avove
void writeHelper(Tnode* root, FILE*  fptr){
  if(root==NULL){return;}
  if(root->divType == LEAF){
    fprintf(fptr,"%d(%d,%d)\n", root->blockNum, root->width, root->height);
  }else{
    fprintf(fptr, "%c\n", root->divType);
  }
  writeHelper(root->left, fptr);
  writeHelper(root->right, fptr);
}

//only used for debugging
void dumpTreeNode(Tnode* root){
  if(root == NULL){return;}
  if(root->divType == LEAF){
    printf("%d(%d,%d)\n", root->blockNum, root->width, root->height);
  }else{
    printf("%c\n", root->divType);
  }
}

//also only used for debugging
void dumpPost(Tnode* root){
  if(root == NULL){return;}
  dumpPost(root->left);
  dumpPost(root->right);
  dumpTreeNode(root);
  return;
}
