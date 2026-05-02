#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"
#include "sequence.h"

#define DEBUG 0

int getFileLength(FILE*);

void sortKsubseq(long* toSort, int n, int start, int k, long* n_comp){
  long count = 0;
  for(long i = start; i < n; i += k){ //count the number of subarrays, increment by a
    count++;
  }  
  for(long i = 0; i < count - 1; i++){
    for (long j = 0; j < count - i - 1; j++){

      long idx1 = start + j * k;
      long idx2 = start + (j + 1) * k;
      
      (*n_comp)++; //increment compare

      if(toSort[idx1] < toSort[idx2]){//swap
        
        long temp = toSort[idx1];
        toSort[idx1] = toSort[idx2];
        toSort[idx2] = temp;
      }
    }
  }
}

void everyKsort(long* toSort, int n, long* kVals, int numKs, long* n_comp){
  for (int i = 0; i < numKs; i++){
    if(DEBUG)printf("sorting for this kval %ld\n", kVals[i]);
    for(int start = 0; start < kVals[i] && start < n; start++){ //for every k
      sortKsubseq(toSort, n, start, kVals[i], n_comp); //sort that subsequence according to k
    }
  }    
}

void Array_Shellsort(long* array, int size, long* n_comp){
  int numKs = 0;
  long* kVals = Generate_2p3q_Seq(size, &numKs);
 
  if(DEBUG)printf("starting sorting of array size %d and numKs %d\n", size, numKs);
  
  everyKsort(array, size, kVals, numKs, n_comp); //run ksort for every value of k in this array
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
