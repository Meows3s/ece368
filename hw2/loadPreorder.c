#include "defs.h"

tree* loadPreorder(char* filename){
  FILE* fptr = fopen(filename, FILE_READ_FLAG);
  if(fptr == NULL){
    if(DEBUG)printf("bad input file!\n");
    return NULL;
  }

  tree* root = newTree();
  moStack* stackHead = newStack();

  push(&stackHead, root);
  while(!stackEmpty(stackHead)){
    tree* thisNode = pop(&stackHead);

    char mode = fgetc(fptr);

    if(mode == HORIZ || mode == VERT){
      fscanf(fptr, "\n"); //move to the end of the line
      thisNode->divType = mode;
      
      thisNode->left = newTree();
      thisNode->right = newTree();

      //push right then left so that left is popped first
      push(&stackHead, thisNode->right); 
      push(&stackHead, thisNode->left);
      
    }else{//leaf node
      thisNode->divType = LEAF;
      thisNode->blockNum = mode - 48;
      fscanf(fptr, "(%d,%d)\n", &(thisNode->width), &(thisNode->height));
    }
  }
  
  freeStack(stackHead);
  fclose(fptr);
  return root;
}
