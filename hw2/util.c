#include "defs.h"

int max(int a, int b){
  if(a > b){
    return a;
  }else{
    return b;
  }
}

tree* newTree(void){
  tree* toReturn = calloc(1, sizeof(tree));
  toReturn->left = NULL;
  toReturn->right = NULL;

  toReturn->divType = UNDEFINED;
  toReturn->blockNum = -1;
  toReturn->width = -1;
  toReturn->height -1;

  return toReturn;
}

//used "in production", no resurcion allowed :(
void freeTree(tree* root){
  moStack* stackHead = newStack();
  push(&stackHead, root);
  tree* lastFreed = root->left;
  while(!stackEmpty(stackHead)){
    //free left, then right, then self
    root = pop(&stackHead);
    if(root->divType == LEAF){
      lastFreed = root;
      free(root);
    }else if(root->divType != LEAF && root->right == lastFreed){
      lastFreed = root;
      free(root);
    }else{
      push(&stackHead, root);
      push(&stackHead, root->right);
      push(&stackHead, root->left);
    }
  }
  freeStack(stackHead);
}

//only used for debugging
void dumpTreeNode(tree* root){
  if(root == NULL){return;}
  if(root->divType == LEAF){
    printf("%d(%d,%d)\n", root->blockNum, root->width, root->height);
  }else{
    printf("%c\n", root->divType);
  }
}

//also only used for debugging
void dumpPost(tree* root){
  if(root == NULL){return;}
  dumpPost(root->left);
  dumpPost(root->right);
  dumpTreeNode(root);
  return;
}
