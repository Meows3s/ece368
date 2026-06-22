#include "defs.h"

int height(Tnode*); //needed by balance() below

int buildTree(char* inputFile, char* outputFile){
  FILE* fptrIN = fopen(inputFile, FILE_READ_FLAG);
  FILE* fptrOUT = fopen(outputFile, FILE_WRITE_FLAG);

  //prints following spec
  if(fptrIN == NULL){
    fprintf(stdout, "-1\n");
    if(fptrOUT) fclose(fptrOUT);
    return EXIT_FAILURE;
  }
  if(fptrOUT == NULL){
    fclose(fptrIN);
    return EXIT_FAILURE;
  }

  int key;
  char op;
  Tnode* root = NULL;

  while(1){
    if(fread(&key, sizeof(int), 1, fptrIN) != 1){
      if(feof(fptrIN)){break;}
      fprintf(stdout, "0\n"); //read error
      writeToFile(fptrOUT, root);
      freeTree(root);
      fclose(fptrIN);
      fclose(fptrOUT);
      return EXIT_FAILURE;
    }
    if(fread(&op, sizeof(char), 1, fptrIN) != 1){
      fprintf(stdout, "0\n"); //read error
      writeToFile(fptrOUT, root);
      freeTree(root);
      fclose(fptrIN);
      fclose(fptrOUT);
      return EXIT_FAILURE;
    }

    if(DEBUG)fprintf(stderr, "read value: %d and op %c\n", key, op);

    if(op == INSERT){
      Tnode* toInsert = newNode(key);
      if(toInsert == NULL){
        fprintf(stdout, "0\n"); //alloc failed (you better hope this doesnt happen)
        writeToFile(fptrOUT, root);
        freeTree(root);
        fclose(fptrIN);
        fclose(fptrOUT);
        return EXIT_FAILURE;
      }
      if(DEBUG)fprintf(stderr, "inserting node with key %d\n", toInsert->key);
      insert(&root, toInsert);
    }else if(op == DELETE){
      if(DEBUG)fprintf(stderr, "deleting node with key %d\n", key);
      delete(&root, key);
    }
  }

  fprintf(stdout, "1\n");

  if(DEBUG)fprintf(stderr, "writing to output file...\n");
  writeToFile(fptrOUT, root);

  freeTree(root);
  fclose(fptrIN);
  fclose(fptrOUT);
  return EXIT_SUCCESS; //success
}

void insert(Tnode** rootptr, Tnode* toInsert){
  if(*rootptr == NULL){//base case: empty slot found
    *rootptr = toInsert;
    return;
  }

  Tnode* root = *rootptr;

  if(toInsert->key <= root->key){//go left (equal keys also go left per spec)
    insert(&root->left, toInsert);
  }else{
    insert(&root->right, toInsert);
  }

  calcBalance(root);
  balance(rootptr);
}

void delete(Tnode** rootptr, int value){
  Tnode* root = *rootptr;
  if(root == NULL){return;}

  if(value < root->key){
    delete(&root->left, value);
  }else if(value > root->key){
    delete(&root->right, value);
  }else if(root->left == NULL && root->right == NULL){//no children
    free(root);
    *rootptr = NULL;
    return;
  }else if(root->left == NULL){//only right child
    *rootptr = root->right;
    free(root);
    return;
  }else if(root->right == NULL){//only left child
    *rootptr = root->left;
    free(root);
    return;
  }else{//two children, replace with in-order predecessor rightmost of left subtree
    Tnode** predPtr = &root->left;
    while((*predPtr)->right != NULL){
      predPtr = &(*predPtr)->right;
    }
    root->key = (*predPtr)->key;//copy up predecessor key
    delete(&root->left, root->key);//delete the predecessor
  }

  if(*rootptr != NULL){
    calcBalance(*rootptr);
    balance(rootptr);
  }
}

void rotate(Tnode** rootptr, int dir){
  Tnode* root = *rootptr; //this is a lot nicer than dereferencing it everywhere in the function :)
  if(root == NULL){return;}

  if(dir == R_RIGHT){
    Tnode* newRoot = root->left;
    if(newRoot == NULL){return;}

    root->left = newRoot->right;
    newRoot->right = root;
    *rootptr = newRoot;
    
    calcBalance((*rootptr)->right);//recalc old root first, then new root
    calcBalance(*rootptr);
  }else if(dir == R_LEFT){
    Tnode* newRoot = root->right;
    if(newRoot == NULL){return;}
    
    root->right = newRoot->left;
    newRoot->left = root;
    *rootptr = newRoot;
    
    calcBalance((*rootptr)->left); //recalc old root first, then new root
    calcBalance(*rootptr);
  }
}

void balance(Tnode** rootptr){
  if(*rootptr == NULL){return;}

  (*rootptr)->balance = height((*rootptr)->left) - height((*rootptr)->right);

  if((*rootptr)->balance == 2){ //left heavy
    Tnode* lc = (*rootptr)->left;
    lc->balance = height(lc->left) - height(lc->right);
    if(lc->balance < 0){rotate(&(*rootptr)->left, R_LEFT);} //LR case
    
    rotate(rootptr, R_RIGHT);
  }else if((*rootptr)->balance == -2){ //right heavy
    Tnode* rc = (*rootptr)->right;
    rc->balance = height(rc->left) - height(rc->right);
    if(rc->balance > 0){rotate(&(*rootptr)->right, R_RIGHT);} //RL case
    
    rotate(rootptr, R_LEFT);
  }
}

int height(Tnode* root){
  if(root == NULL){return -1;}
  
  int lHeight = height(root->left);
  int rHeight = height(root->right);
  
  return 1 + (lHeight > rHeight ? lHeight : rHeight);
}

void calcBalance(Tnode* root){ //bottom-up so children are accurate before parent
  if(root == NULL){return;}
  
  calcBalance(root->left);
  calcBalance(root->right);
  
  root->balance = height(root->left) - height(root->right);
}

void writeToFile(FILE* fileOUT, Tnode* root){
  if(root == NULL || fileOUT == NULL){return;}
  //preorder: current, left, right
  int key = root->key;
  char branchBits = 0;
  if(root->left  != NULL){branchBits |= 2;} //bit 1: has left child
  if(root->right != NULL){branchBits |= 1;} //bit 0: has right child

  if(DEBUG)fprintf(stderr, "wrote node with key %d to file\n", key);

  fwrite(&key, sizeof(int), 1, fileOUT);
  fwrite(&branchBits, sizeof(char), 1, fileOUT);

  writeToFile(fileOUT, root->left);
  writeToFile(fileOUT, root->right);
}

Tnode* newNode(int value){
  Tnode* toReturn = calloc(1, sizeof(Tnode));
  if(toReturn == NULL){return NULL;}
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
  fprintf(stderr, "found key %d\n", root->key);
  dumpTree(root->right);
}
