#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"
#include "sequence.h"

#define DEBUG 1

long* Array_Load_From_File(char*, int*);
int Array_Save_To_File(char*, long*, int);
int getFileLength(FILE*);

void Array_Shellsort(long* array, int size, long* n_comp){
  n_comp = calloc(1, sizeof(long)); //init n_comp
  
  //args: less than, *n_elements
  int numK = 0;
  long* kVals = Generate_2p3q_Seq(size, &numK);

  
/*sorted = false
last_exchange = n
while (not sorted)
sorted = true
last_element = last_exchange - 1
for i = 1 to last_element
if A[i - 1] > A[i]
exchange A[i-1] and A[i]
last_exchange = i
sorted = false*/

  int sorted = 0; //start unsorted
  lastSwap = numK;
  while(!sorted){
    sorted = 1;
    array[numK-1] = array[lastSwap] - 1;
  }
  
}

long* Array_Load_From_File(char* filename, int* size){
  FILE* fptr = fopen(filename, "rb");

  if(fptr == NULL){
    if(DEBUG)printf("failed opening, returning.\n");
    *size = 0; //fail
    return NULL;
  }

  *size = getFileLength(fptr); //count N elements
  long* array = calloc(*size, sizeof(long)); //allocate N elements
  int numR = fread(array, sizeof(long), *size, fptr);

  if(DEBUG)printf("counted %d elements; read %d elements.\n", *size, numR);

  fclose(fptr);
  return array;
}

int Array_Save_To_File(char* filename, long* array, int size){
  FILE* fptr = fopen(filename, "wb");

  if(fptr == NULL){
    if(DEBUG)printf("failed opening, returning...\n");
    return -1; //fail
  }

  int numW = fwrite(array, sizeof(long), size, fptr);

  if(DEBUG)printf("wrote %d elements.\n", numW);
  
  fclose(fptr);
  return numW; //return the number of elements written
}

int getFileLength(FILE* fptr){
  int numElements = 0;
  long read;

  while(fread(&read, sizeof(long), 1, fptr) == 1) numElements++;
  
  rewind(fptr);
  return numElements;
}
