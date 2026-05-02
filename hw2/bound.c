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

  //int totalWidth = root->width
  int totalHeight = root->height;
  int Xplace = 0, Yplace = totalHeight;

  int wroteLeft = 0;

  //
  while(!stackEmpty(stackHead)){
    
    //dumpStack(stackHead);
    thisNode = pop(&stackHead);

    //left, right, self
    if(thisNode->divType == LEAF){//leaf node, claims a place on the packing

      if(lastSeen->divType == HORIZ){
        if(wroteLeft){//lower node
          wroteLeft = 0;
          Yplace -= lastSeen->right->height;
        }else{//upper node
          wroteLeft = 1;
          Yplace -= lastWritten->height;
        }
        fprintf(fptr, "%d((%d,%d)(%d,%d))\n", thisNode->blockNum, thisNode->width, thisNode->height, Xplace, Yplace); 
      }
 
      if(lastSeen->divType == VERT){
        if(wroteLeft){//right node
          wroteLeft = 0;
          Xplace += lastWritten->width;
        }else{//left node
          wroteLeft = 1;
          Yplace -= lastSeen->height;
          //Xplace
        }

        fprintf(fptr, "%d((%d,%d)(%d,%d))\n", thisNode->blockNum, thisNode->width, thisNode->height, Xplace, Yplace);
      }

      lastWritten = thisNode;
    }else if(thisNode->divType != LEAF && thisNode->right == lastWritten){
      lastWritten = thisNode;
      wroteLeft = 0;
    }else{ //branch node with tree below, add children and self to stack
      wroteLeft = 0;
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
