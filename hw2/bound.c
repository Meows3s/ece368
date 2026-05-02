#include "defs.h"

int writeBound(tree* root, char* outputFile){
  FILE* fptr = fopen(outputFile, FILE_WRITE_FLAG);
  if(fptr == NULL){
    if(DEBUG)printf("bad output file three!\n");
    return EXIT_FAILURE;
  }

  moStack* stackHead = newStack();
  push(&stackHead, root);

  tree* thisNode = NULL;
  tree* lastWritten = root->left;
  tree* lastSeen = NULL;

  int totalWidth = root->width, totalHeight = root->height;
  int Xplace = 0, Yplace = 0;

  //
  while(!stackEmpty(stackHead)){
    
    //dumpStack(stackHead);
    thisNode = pop(&stackHead);

    //left, right, self
    if(thisNode->divType == LEAF){//leaf node, claims a place on the packing
      lastWritten = thisNode;
  
      if(lastSeen->divType == HORIZ){
        Xplace = 
      }
      if(lastSeen->divType == VERT){
        
      }

      fprintf(fptr, "%d((%d,%d)(%d,%d))\n", thisNode->blockNum, thisNode->width, thisNode->height, Xplace, totalHeight - Yplace);
    }else if(thisNode->divType != LEAF && thisNode->right == lastWritten){
      lastWritten = thisNode;
    }else{ //branch node with tree below, add children and self to stack
      lastSeen = thisNode;
      push(&stackHead, thisNode);
      if(thisNode->right != NULL) push(&stackHead, thisNode->right);
      if(thisNode->left != NULL) push(&stackHead, thisNode->left);
    }
  }
  freeStack(stackHead);
  
  

  fclose(fptr);
  return EXIT_SUCCESS;
}
