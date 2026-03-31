#include "defs.h"

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


