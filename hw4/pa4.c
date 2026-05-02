#include "defs.h"

int main(int argc, char** argv){

  char mode = argv[1][1];
  char* inputFile = argv[2];
  char* outputFile = argv[argc - 1]; // somewhat weird hack

  if(DEBUG)printf("%d arguments entered\nmode: %c\ninput file: %s\noutput file: %s\n", argc, mode, inputFile, outputFile);

  if(mode == 'b'){
    if(buildTree(inputFile, outputFile) == EXIT_FAILURE){return EXIT_FAILURE;}
  }else if(mode == 'e'){
    if(eval(inputFile) == EXIT_FAILURE){return EXIT_FAILURE;}
  }else{
    if(DEBUG)printf("invalid mode argument\n");
    return EXIT_FAILURE; //invalid argument
  }
}
