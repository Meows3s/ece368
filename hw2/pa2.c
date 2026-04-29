#include "defs.h"

int main(int argn, char** argv){

  //if(argn != 5){return EXIT_FAILURE;} //fail because of too many arguments

  //argv[0] contains the program name
  char* inputFile = argv[1]; //-> input file
  char* outFile1 = argv[2]; //-> output file 1
  char* outFile2 = argv[3]; //-> output file 2
  char* outFile3 = argv[4]; //-> output file 3

  if(DEBUG)printf("testing program on input file: %s\n", inputFile);
  

  tree* root = loadPreorder(inputFile);

  //output one
  writePostorder(root, outFile1);
  
  //output two
  writePack(root, outFile2);
  
  //output three

  freeTree(root);

  return EXIT_SUCCESS;
}
