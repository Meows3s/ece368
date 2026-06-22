#include "defs.h"

void setDims(Tnode*);

Tnode* readPost(char* filename){
  FILE* fptr = fopen(filename, FILE_READ_FLAG);
  if(fptr == NULL){return NULL;}//file check, nothing new here

  moStack* stack = newStack();
  char line[64]; //better than a single char

  while(fgets(line, sizeof(line), fptr)){
    Tnode* node = newTree();
    if(line[0] == VERT || line[0] == HORIZ){//internal node
      node->divType = line[0];
      if(itemsInStack(stack) < 2){free(node); break;}//weird input catcher
      node->right = pop(&stack);
      node->left  = pop(&stack);
    }else{
      sscanf(line, "%d(%d,%d)\n", &node->blockNum, &node->width, &node->height); //previously was just scanf-ing again, but this is a lot cleaner and eleminates trailing character special cases
      node->divType = LEAF;
    }
    push(&stack, node);
  }

  Tnode* root = pop(&stack);
  setDims(root); //update dimensions

  freeStack(stack);
  fclose(fptr);
  return root;
}

void setDims(Tnode* root){
  if(root == NULL || root->divType == LEAF){return;}
  setDims(root->left);
  setDims(root->right);
  if(root->divType == HORIZ){
    root->width  = max(root->left->width,  root->right->width);
    root->height = root->left->height + root->right->height;
  }else{//must be vert
    root->width  = root->left->width + root->right->width;
    root->height = max(root->left->height, root->right->height);
  }
}
