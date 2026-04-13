#include "defs.h"
#define TEMPFILE "temp.txt"

int evaluate(char*);
int build(char*, char*);

int main(int argc, char** argv){

  char mode = argv[1][1];
  char* inputFile = argv[2];
  char* outputFile = argv[argc - 1]; // somewhat weird hack

  if(DEBUG)printf("%d arguments entered\nmode: %c\ninput file: %s\noutput file: %s\n", argc, mode, inputFile, outputFile);

  int exitMode = EXIT_FAILURE; //assume failure unless we explicitly succeed

  if(mode == 'b'){
    exitMode = build(inputFile, outputFile);
  }else if(mode == 'e'){
    exitMode = evaluate(inputFile);
  }else{
    if(DEBUG)printf("invalid mode argument\n");
    return EXIT_FAILURE; //invalid argument
  }

  return exitMode;
}

//balance the tree
int build(char* inputFile, char* outputFile){
  if(!isGoodFile(inputFile, "rb") || !isGoodFile(outputFile, "wb")){return EXIT_FAILURE;}
  
  

  return EXIT_SUCCESS;
}



//do some checks on the input tree FILE (not actually a tree)
int evaluate(char* inputFile){
  if(!isGoodFile(inputFile, "rb")){return EXIT_FAILURE;}

  int isGoodF = isGoodFile(inputFile, "rb"); //status: working
  int isBst = isBST(inputFile); //status: probably broken
  int isBal = isBalanced(inputFile); //status: should be working

  printf("%d,%d,%d\n", isGoodF, isBst, isBal);
  
  return isGoodF ? EXIT_SUCCESS : EXIT_FAILURE; //only return success if the file opening succeeded
}
