#include <stdlib.h>
#include <stdio.h>
#include "sequence.h"

#define DEBUG 0

int seq_util(int, long*, int);
long* Generate_2p3q_Seq(int, int*);

long* Generate_2p3q_Seq(int less_than, int* seq_size){

  long* tempCounter = calloc(less_than + 2, sizeof(long));
  *seq_size = seq_util(less_than, tempCounter, -1); //count the number of elements in the sequence
    
  free(tempCounter);

  long* seq = calloc(*seq_size, sizeof(long)); //create a pointer to point to the sequence
  seq_util(less_than, seq, *seq_size); //set the sequence pointer to an array with those elements
  return seq; //return the sequence pointer
}

//check is n is in the sequence by checking the last number

int seq_util(int less_than, long* seq, int len){
   
  int index = 0, next_2 = 0, next_3 = 0, pt2 = 0, pt3 = 0;
  //long* seq = calloc((len == -1 ? less_than + 2 : len), sizeof(long)); //allocate extra memory for an initial count. kinda jank ngl
  seq[0] = 1; //set first element

  //count the number of elements so we can initialize the array without using a linked list
  while(next_2 < less_than && next_3  < less_than){
    next_2 = seq[pt2] * 2;
    next_3 = seq[pt3] * 3;
    index++; //keep track of the number of elements and current seq index

    if(next_2 < next_3){//if 2 is less than 3, pick 2 and increment its index
      seq[index] = next_2;
      pt2++;
      if(DEBUG) printf("%d (next2) at index %d pt2 %d\n", next_2, index, pt2);
    }else if(next_2 > next_3){//if 3 is less than 2, pick 3 and increment its index
      seq[index] = next_3;
      pt3++;
      if(DEBUG) printf("%d (next3) at index %d pt3 %d\n", next_3, index, pt2);
    }else{ //if they are equal, don't add this to the list and increment one of the indicies
      pt2++;
      index--;
    }
  }
  index++; //increment 1 more time to include zero-th element

  if(DEBUG) printf("final number of elements is %d\n", index);
  
  if(len == -1){//if we are in counting mode
    //dont bother freeing lol
    return index; //return number of elements
  }else{
      return -2;
    }
}
