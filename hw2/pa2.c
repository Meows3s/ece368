#include "defs.h"

int main(int argn, char** argv){

  //if(argn != 5){return EXIT_FAILURE;} //fail because of too many arguments

  //argv[0] contains the program name
  char* inputFile = argv[1]; //-> input file
  char* outFile1 = argv[2]; //-> output file 1
  char* outFile2 = argv[3]; //-> output file 2
  char* outFile3 = argv[4]; //-> output file 3

  if(DEBUG){
    printf("\ntesting program on input file: %s\n", inputFile);
    printf("output file 1: %s\n", outFile1);
    printf("output file 2: %s\n", outFile2);
    printf("output file 3: %s\n\n", outFile3);
  }

  tree* root = loadPreorder(inputFile);

  //output one
  if(writePostorder(root, outFile1) == EXIT_FAILURE){return EXIT_FAILURE;}
  
  //output two
  if(writePack(&root, outFile2) == EXIT_FAILURE){return EXIT_FAILURE;}
  
  //output three
  if(writeBound(root, outFile3) == EXIT_FAILURE){return EXIT_FAILURE;}

  freeTree(root);

  return EXIT_SUCCESS;
}
