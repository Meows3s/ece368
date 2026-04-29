#include "defs.h"

int writePostorder(char* filename, tree* root){
  FILE* fptr = fopen(filename, FILE_WRITE_FLAG);
  if(fptr == NULL){
    if(DEBUG)printf("bad output file!\n");
    return EXIT_FAILURE;
  }else{
    if(DEBUG)printf("good file, writing postorder\n");
  }

  moStack* stackHead = newStack();
  
  //right then left so we pop left first, as usual
  push(&stackHead, root);
  push(&stackHead, root->right);
  push(&stackHead, root->left);

  tree* thisNode;
  tree* lastWritten;

  while(!stackEmpty(stackHead)){
    
    dumpStack(stackHead);
    thisNode = pop(&stackHead);

    //left, right, self
    if(thisNode->divType == LEAF){//leaf node, can write immidately
      lastWritten = thisNode;
      fprintf(fptr, "%d(%d,%d)\n", thisNode->blockNum, thisNode->pos[0], thisNode->pos[1]);
      dumpTreeNode(lastWritten);
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
