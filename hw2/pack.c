#include "defs.h"

int writePack(tree* root, char* outputFile){
  FILE* fptr = fopen(outputFile, FILE_WRITE_FLAG);
  if(fptr == NULL){
    if(DEBUG)printf("output two bad input file!\n");
    return EXIT_FAILURE;
  }
  
  moStack* stackHead = newStack();
  push(&stackHead, root);

  tree* thisNode = NULL;
  tree* lastWritten = root->left;

  while(!stackEmpty(stackHead)){
    
    dumpStack(stackHead);
    thisNode = pop(&stackHead);

    //left, right, self
    if(thisNode->divType == LEAF){//leaf node, can write immidately
      lastWritten = thisNode;
      fprintf(fptr, "%d(%d,%d)\n", thisNode->blockNum, thisNode->pos[0], thisNode->pos[1]);
      dumpTreeNode(lastWritten);
    }else if(thisNode->divType != LEAF && thisNode->right == lastWritten){ //right child is done, can write self to file

      //TODO: make this actuall do the thing (bounding box of each branch)
    
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
