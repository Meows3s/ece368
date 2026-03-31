#include "defs.h"

//currently broken 
int treeBtoC(char* inputFile, char* outputFile){

  FILE* inf = fopen(inputFile, "rb");
  FILE* outf = fopen(outputFile, "w");

  int retval = 1;
  uint32_t key, numChild;

  while(!feof(inf) && retval != 0){

    retval = fread(&key, sizeof(0x1FFFFFFF), 1, inf);//read all of the data
    retval = fread(&numChild, sizeof(0x7), 1, inf);
    //key = raw & 0x1FFFFFFF;
    //numChild = (raw >> 29) & 0x7;

    fprintf(outf, "%d,%d\n", key, numChild);

    if(DEBUG)printf("read value: %d and numchild %d\n", key, numChild);
  }
  fprintf(outf, "END\n");

  fclose(inf);
  fclose(outf);

  return 1; //success
}

//convert ops binary to text file
int opsBtoC(char* inputFile, char* outputFile){
  FILE* inf = fopen(inputFile, "rb");
  FILE* outf = fopen(outputFile, "w");
 
  int key;
  char op;

  while(1){

    (void)(fread(&key, sizeof(int), 1, inf)+1); //I really could not care less about the return value
    (void)(fread(&op, sizeof(char), 1, inf)+1);
    if(feof(inf)){break;}//end of file, exit loop

    fprintf(outf, "%d,%d\n", key, op); //save read values to output file

    if(DEBUG)printf("read value: %d and op %c\n", key, op);
  }
  fprintf(outf, "END\n");


  fclose(inf);
  fclose(outf);

 return 1;//success
}
