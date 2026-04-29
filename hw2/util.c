#include "defs.h"

tree* newTree(void){
  tree* toReturn = calloc(1, sizeof(tree));
  toReturn->left = NULL;
  toReturn->right = NULL;

  toReturn->divType = UNDEFINED;
  toReturn->blockNum = -1;
  toReturn->pos[0] = -1;
  toReturn->pos[1] = -1;

  return toReturn;
}

void dumpTreeNode(tree* root){
  if(root == NULL){return;}
  if(root->divType == LEAF){
    printf("%d(%d,%d)\n", root->blockNum, root->pos[0], root->pos[1]);
  }else{
    printf("%c\n", root->divType);
  }
}

void dumpPost(tree* root){
  if(root == NULL){return;}
  dumpPost(root->left);
  dumpPost(root->right);
  dumpTreeNode(root);
  return;
}


