#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"
#include "sequence.h"

#define DEBUG 1

long* Array_Load_From_File(char*, int*);
int Array_Save_To_File(char*, long*, int);
int getFileLength(FILE*);

int main(){
  
  
  
  return 0;
}

void Array_Shellsort(long* array, int size, long* n_comp){
  n_comp = calloc(1, sizeof(long)); //init n_comp
  
  //args: less than, *n_elements
  int numK = 0;
  long* kVals = Generate_2p3q_Seq(size, &numK);
  
  

}

long* Array_Load_From_File(char* filename, int* size){
  FILE* fptr = fopen("filename", "rb");
  size = calloc(1, sizeof(int));

  if(fptr == NULL){
    *size = 0; //fail
    return NULL;
  }

  *size = getFileLength(fptr); //count N elements
  long* array = calloc(*size, sizeof(long)); //allocate N elements
  int numR = fread(array, sizeof(long), *size, fptr);

  if(DEBUG)printf("counted %d elements; wrote %d elements.\n", *size, numR);
  
  return array;
}

int Array_Save_To_File(char* filename, long* array, int size){
  FILE* fptr = fopen("filename", "rb");

  if(fptr == NULL){
    return -1; //fail
  }

  int numW = fwrite(array, sizeof(long), size, fptr);

  if(DEBUG)printf("wrote %d elements.\n", numW);
  
  return numW; //return the number of elements written
}

int getFileLength(FILE* fptr){
  int numElements = 0;
  long read;

  while(fread(&read, sizeof(long), 1, fptr) == 1) numElements++;
  
  return numElements;
}
