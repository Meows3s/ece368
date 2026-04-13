#include "defs.h"

Tnode* newNode(int value);

int buildTree(char* inputFile, Tnode* root){
  FILE* inf = fopen(inputFile, "rb");
  
  int key;
  char op;

  while(1){

    (void)(fread(&key, sizeof(int), 1, inf)+1); //I really could not care less about the return value
    (void)(fread(&op, sizeof(char), 1, inf)+1);

    if(feof(inf)){break;}//end of file, exit loop

    if(DEBUG)printf("read value: %d and op %c\n", key, op);
  }

  fclose(inf);
 return EXIT_SUCCESS;//success
}


void insert(Tnode* root, int value){
  if(root->left == NULL && root->right == NULL){ //if we are at a node with no children
    if(root->key <= value){root->left = newNode(value);}
    if(root->key > value){root->right = newNode(value);}
  }
  
  if(root->key <= value){insert(root->left, value);} //always go left when inserting a key of less than or equal value
  if(root->key > value){insert(root->right, value);} //always go left when inserting a key of smaller value
}

void rotate(){
  
}

Tnode* newNode(int value){

  int key = (value) && 0x1d;
  char balance = (value >> 29) && 3;

  Tnode* toReturn = calloc(1, sizeof(Tnode));
  toReturn->key = key;
  toReturn->balance = balance;

  return toReturn;
}

void freeTree(Tnode* root){
  if(root == NULL){return;}
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}
