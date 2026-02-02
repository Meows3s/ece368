#include <stdlib.h>
#include <stdio.h>
#include "sequence.h"

#define DEBUG 0

int seq_util(int, long*, int);

long* Generate_2p3q_Seq(int, int*);

int main(){
  
  if(DEBUG) printf("starting program...\n");

  int test = 20;

  Generate_2p3q_Seq(40, &test);

  return 0;
}

long* Generate_2p3q_Seq(int less_than, int* seq_size){
  seq_size = calloc(0, sizeof(int)); //create a pointer to point to the length of the sequence
  *seq_size = seq_util(less_than, (long*)1, -1); //count the number of elements in the sequence
  long* seq_ptr = calloc(*seq_size, sizeof(long)); //create a pointer to point to the sequence
 
  seq_util(less_than, seq_ptr, *seq_size); //set the sequence pointer to an array with those elements
  return seq_ptr; //return the sequence pointer
}

//check is n is in the sequence by checking the last number

int seq_util(int less_than, long* seq_ptr, int len){
   
  int num_elements = 0, next_2 = 0, next_3 = 0, pt2 = 0, pt3 = 0;
  long* seq = calloc((len == -1 ? less_than + 2 : len), sizeof(long)); //allocate extra memory for an initial count. kinda jank ngl
  seq[0] = 1; //set first element

  //count the number of elements so we can initialize the array without using a linked list
  while(next_2 < less_than && next_3  < less_than){
    next_2 = seq[pt2] * 2;
    next_3 = seq[pt3] * 3;
    num_elements++; //keep track of the number of elements and current seq index

    if(next_2 < next_3){//if 2 is less than 3, pick 2 and increment its index
      seq[num_elements] = next_2;
      pt2++;
      if(DEBUG) printf("%d (next2)\n", next_2);
    }else if(next_3 < next_2){//if 3 is less than 2, pick 3 and increment its index
      seq[num_elements] = next_3;
      pt3++;
      if(DEBUG) printf("%d (next3)\n", next_3);
    }else{//if elements are the same, just pick 2 and increment both indicies
      seq[num_elements] = next_2;
      pt2++;
      pt3++;
    }
  }
  num_elements--; //subtract off the last one because it will be too large

  if(DEBUG) printf("final number of elements is %d\n", num_elements);
  
  if(len == -1){//if we are in counting mode
    free(seq); //free temp array
    return num_elements; //return number of elements
  }else{
      seq_ptr = seq; //otherwise set the pointer passed to the counting array
      free(seq); //free the temp counting array
      return -2;
    }
}
