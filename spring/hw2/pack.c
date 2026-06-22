#include "defs.h"
int writePack(tree** treeIn, char* outputFile2){
  FILE* fptr2 = fopen(outputFile2, FILE_WRITE_FLAG);
  
  if(fptr2 == NULL){
    if(DEBUG)printf("bad output file two!\n");
    return EXIT_FAILURE;
  }

  //lazy
  tree* root = *treeIn;

  moStack* stackHead = newStack();
  push(&stackHead, root);

  tree* thisNode = NULL;
  tree* lastWritten = root->left;
  int totalWidth = 0, totalHeight = 0;

  while(!stackEmpty(stackHead)){
    thisNode = pop(&stackHead);
    //left, right, self
    if(thisNode->divType == LEAF){//leaf node, can write immidately
      lastWritten = thisNode;
      fprintf(fptr2, "%d(%d,%d)\n", thisNode->blockNum, thisNode->width, thisNode->height);
    
    }else if(thisNode->divType != LEAF && thisNode->right == lastWritten){

      int potentialWidth = thisNode->left->width + thisNode->right->width;
      int potentialHeight = thisNode->left->height + thisNode->right->height;
      
      if(thisNode->divType == VERT && potentialWidth >= totalWidth){
        totalHeight = max(thisNode->left->height, thisNode->right->height);
        totalWidth = potentialWidth;
      }else if(thisNode->divType == HORIZ && potentialHeight >= totalHeight){
        totalHeight = potentialHeight;
        totalWidth = max(thisNode->left->width, thisNode->right->width);
      }

      thisNode->width = totalWidth;
      thisNode->height = totalHeight;
      lastWritten = thisNode;

      fprintf(fptr2, "%c(%d,%d)\n", thisNode->divType, thisNode->width, thisNode->height);

    }else{ //branch node with tree below, add children and self to stack
      push(&stackHead, thisNode);
      if(thisNode->right != NULL) push(&stackHead, thisNode->right);
      if(thisNode->left != NULL) push(&stackHead, thisNode->left);
    }
  }

  freeStack(stackHead);
  fclose(fptr2);
  return EXIT_SUCCESS;
}
