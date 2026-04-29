#include "defs.h"

tree* loadPreorder(char* filename){
  FILE* fptr = fopen(filename, FILE_READ_FLAG);
  if(fptr == NULL){
    if(DEBUG)printf("bad input file!\n");
    return NULL;
  }else{
    if(DEBUG)printf("good file, reading preorder\n");
  }


  tree* root = newTree();
  moStack* stackHead = newStack();

  push(&stackHead, root);
  while(!stackEmpty(stackHead)){
    tree* thisNode = pop(&stackHead);

    char mode = fgetc(fptr);
    if(DEBUG)printf("read mode as %c\n", mode);

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
      fscanf(fptr, "(%d,%d)\n", &(thisNode->pos[0]), &(thisNode->pos[1]));
    }
  }
  
  freeStack(stackHead);
  fclose(fptr);
  return root;
}
