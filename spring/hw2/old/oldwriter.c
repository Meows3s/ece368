#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int postHelper(tree*, FILE*);

int writePostorder(tree* root, char* outputFile){
  FILE* fptr = fopen(outputFile, "w+");
  if(fptr == NULL){return 0;}

  int numWritten = postHelper(root, fptr);
  if(DEBUG)printf("%d nodes written.\n", numWritten);

  fclose(fptr);
  return 1;
}

int postHelper(tree* root, FILE* fptr){
  if(root == NULL){return 1;}

  //postorder: left, right, self
  int leftCount = postHelper(root->left, fptr);
  int rightCount = postHelper(root->right, fptr);

  if(DEBUG)printf("wrote blocknum %d of type %c to file\n", root->blockNum, root->div);

  if(root->div == LEAF){
    fprintf(fptr, "%d(%d,%d)\n", root->blockNum, root->xPos, root->yPos);
  }else{
    fprintf(fptr, "%c\n", root->div);
  }

  return leftCount + rightCount;
}
