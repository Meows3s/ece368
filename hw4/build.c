#include "defs.h"

int buildTree(char* inputFile, char* outputFile){
  FILE* fptrIN = fopen(inputFile, FILE_READ_FLAG);
  FILE* fptrOUT = fopen(outputFile, FILE_WRITE_FLAG);
  if(fptrIN == NULL || fptrOUT == NULL){
    return EXIT_FAILURE;
  }

  int key;
  char op;
  int first = 1;
  Tnode* root;

  while(1){
    
    if(fread(&key, sizeof(int), 1, fptrIN));
    if(fread(&op, sizeof(char), 1, fptrIN));

    if(feof(fptrIN)){break;} //check for end of file here because fptr will move after freading

    if(first){//load the first node
      first = 0;
      root = newNode(key);
      continue; //skip this iteration
    }

    if(DEBUG)printf("read value: %d and op %c\n", key, op);
    
    if(op == INSERT){
      Tnode* toInsert = newNode(key);
      if(DEBUG)printf("inserting node with key %d\n", toInsert->key);
      insert(root, toInsert);
    }else if(op == DELETE){
      if(DEBUG)printf("deleting node with key %d\n", key);
      delete(&root, key);
    }
    //balance(root);
  }
  
  dumpTree(root); 

  if(DEBUG)printf("writing to output file...\n");
  writeToFile(fptrOUT, root);

  fclose(fptrIN);
  fclose(fptrOUT);
 return EXIT_SUCCESS;//success
}

void insert(Tnode* root, Tnode* toInsert){
  if(root == NULL){return;}

  if(toInsert->key <= root->key){//go left
    if(root->left == NULL){
      root->left = toInsert;
    }else{
      insert(root->left, toInsert);
    }
  }else{
    if(root->right == NULL){
      root->right = toInsert;
    }else{
      insert(root->right, toInsert);
    }
  }
}

void delete(Tnode** rootptr, int value){
  Tnode* root = *rootptr;
  if(root == NULL){return;}

  if(root->key == value && root->left == NULL && root->right == NULL){//no children
    free(root);
    *rootptr = NULL;
  }else if(root->key == value && root->left == NULL){//only right child
    *rootptr = root->right;
    free(root);
  }else if(root->key == value){//two children
    (*rootptr)->key = root->left->key; //copy up the new key from the predecessor (left)
    delete(&root->left, root->left->key); //delete the predecessor
  }else if(value <= root->key){
    delete(&root->left, value);
  }else{
    delete(&root->right, value);
  }
}

void rotate(Tnode** rootptr, int dir){
  Tnode* root = *rootptr; //this is a lot nicer than dereferencing it everywhere in the function :)
  if(root == NULL){return;}

  if(dir == R_RIGHT){
    Tnode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    *rootptr = newRoot;
  }else if(dir == R_LEFT){
    Tnode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    *rootptr = newRoot;
  }
}

int height(Tnode* root){
  if(root == NULL){return 0;}
  int lHeight = height(root->left);
  int rHright = height(root->right);
  return 1 + (lHeight > rHright ? lHeight : rHright);
}

void calcBalance(Tnode* root){
  if(root == NULL){return;}
  calcBalance(root->left);
  calcBalance(root->right);
  root->balance = height(root->right) - height(root->left);//TODO: make sure this complies
}

void writeToFile(FILE* fileOUT, Tnode* root){
  if(root == NULL || fileOUT == NULL){return;}
  //preorder: current, left, right
  int key = root->key;
  char balance = root->balance;

  if(DEBUG)printf("wrote node with key %d to file\n", key);

  fwrite(&key, sizeof(int), 1, fileOUT);
  fwrite(&balance, sizeof(char), 1, fileOUT);

  writeToFile(fileOUT, root->left);
  writeToFile(fileOUT, root->right);
}

Tnode* newNode(int value){

  Tnode* toReturn = calloc(1, sizeof(Tnode));
  toReturn->left = NULL;
  toReturn->right = NULL;

  toReturn->key = value;

  return toReturn;
}

void freeTree(Tnode* root){
  if(root == NULL){return;}
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}
//left, self, right
void dumpTree(Tnode* root){
  if(root == NULL){return;}
  dumpTree(root->left);
  printf("found key %d\n", root->key);
  dumpTree(root->right);
}
