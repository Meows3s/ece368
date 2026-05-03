#include "defs.h"

int writeBound(tree* root, char* outputFile){
  FILE* fptr = fopen(outputFile, FILE_WRITE_FLAG);
  if(fptr == NULL){
    if(DEBUG)printf("bad output file three!\n");
    return EXIT_FAILURE;
  }

  moStack* stackHead = newStack();

  root->oX = 0;
  root->oY = 0;

  push(&stackHead, root);

  tree* thisNode = NULL;

  //update the coordinates
  while(!stackEmpty(stackHead)){
    thisNode = pop(&stackHead);

    //want to set the dimensions with a pre order traversal then print with a post order one
    if(thisNode->divType == LEAF){//leaf node, claims a place on the packing
      //do nothing
    }else if(thisNode->divType == HORIZ){
      thisNode->right->oX = thisNode->oX;
      thisNode->right->oY = thisNode->oY;
      thisNode->left->oX = thisNode->oX;
      thisNode->left->oY = thisNode->oY + thisNode->right->height;

      push(&stackHead, thisNode->right);
      push(&stackHead, thisNode->left);
    
    }else{ //branch node with tree below, add children and self to stack
      thisNode->left->oX = thisNode->oX;
      thisNode->left->oY = thisNode->oY;
      thisNode->right->oX = thisNode->oX + thisNode->left->width;
      thisNode->right->oY = thisNode->oY;

      push(&stackHead, thisNode->right);
      push(&stackHead, thisNode->left);
    
    }
  }
  freeStack(stackHead);

  //write to the file
  stackHead = newStack();
  push(&stackHead, root);
  tree* lastWritten = root->left;
  while(!stackEmpty(stackHead)){
    
    thisNode = pop(&stackHead);

    if(thisNode->divType == LEAF){//leaf node, claims a place on the packing
      fprintf(fptr, "%d((%d,%d)(%d,%d))\n", thisNode->blockNum, thisNode->width, thisNode->height, thisNode->oX, thisNode->oY);
      lastWritten = thisNode;
    }else if(thisNode->divType != LEAF && thisNode->right == lastWritten){
      lastWritten = thisNode;
    }else{ //branch node with tree below, add children and self to stack
      push(&stackHead, thisNode);
      if(thisNode->right != NULL) push(&stackHead, thisNode->right);
      if(thisNode->left != NULL) push(&stackHead, thisNode->left);
    }
  }
  freeStack(stackHead);
  
  fclose(fptr);
  return EXIT_SUCCESS;
}
