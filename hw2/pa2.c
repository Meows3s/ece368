#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void outputOne(char*, char*);
void outputTwo(char*, char*);
void outputThree(char*, char*);

void dumpPost(tree*);

int main(int argn, char** argv){

  //if(argn != 5){return EXIT_FAILURE;} //fail because of too many arguments

  //argv[0] contains the program name
  char* inputFile = argv[1]; //-> input file
  char* outFile1 = argv[2]; //-> output file 1
  char* outFile2 = argv[3]; //-> output file 2
  char* outFile3 = argv[4]; //-> output file 3

  if(DEBUG)printf("testing program on input file: %s\n", inputFile);
  
  //create each output file
  outputOne(inputFile, outFile1);
  outputTwo(inputFile, outFile2);
  outputThree(inputFile, outFile3);
  
  return EXIT_SUCCESS;
}

void outputOne(char* inputFile, char* outputFile){
  tree* root = loadPreorder(inputFile); //load tree in pre-order
  writePostorder(root, outputFile); //write to file in post-order
  freeTree(root); //free tree memory
}

void outputTwo(char* inputFile, char* outputFile){
  
}

void outputThree(char* inputFile, char* outputFile){
  
}

//debugging tool to print post order traversal
void dumpPost(tree* root){
  if(root == NULL){return;}
  dumpPost(root->left);
  dumpPost(root->right);
  printf("%d\n",root->blockNum);
  return;
}
