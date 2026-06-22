#include "defs.h"

int main(int argc, char** argv){
  char* inFile = argv[1];
  char* outFile1 = argv[2];
  char* outFile2 = argv[3];
  char* outFile3 = argv[4];
  char* outFile4 = argv[5];

  if(inFile == NULL){return EXIT_FAILURE;}

  //output 1
  if(outFile1 == NULL){return EXIT_FAILURE;}
  Tnode* root = readPost(inFile);
  //write();

  //output 2
  

  //output 3


  //output 4


  return EXIT_SUCCESS;
}
