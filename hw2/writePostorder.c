#include "defs.h"

int writePostorder(tree* root, char* filename){
  FILE* fptr = fopen(filename, FILE_WRITE_FLAG);
  if(fptr == NULL){
    if(DEBUG)printf("bad output file!\n");
    return EXIT_FAILURE;
  }

  moStack* stackHead = newStack();
  push(&stackHead, root);

  tree* thisNode = NULL;
  tree* lastWritten = root->left;

  while(!stackEmpty(stackHead)){
    
    thisNode = pop(&stackHead);

    //left, right, self
    if(thisNode->divType == LEAF){//leaf node, can write immidately
      lastWritten = thisNode;
      fprintf(fptr, "%d(%d,%d)\n", thisNode->blockNum, thisNode->width, thisNode->height);
    }else if(thisNode->divType != LEAF && thisNode->right == lastWritten){ //right child is done, can write self to file
      lastWritten = thisNode;
      fprintf(fptr, "%c\n", thisNode->divType);
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
