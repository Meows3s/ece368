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
    
  seq[0] = 1;

  while(next_2 < less_than && next_3 < less_than){
    next_2 = seq[pt2] * 2;
    next_3 = seq[pt3] * 3;
    index++;

    if(next_2 < next_3){
      seq[index] = next_2;
      pt2++;
    }else if(next_2 > next_3){
      seq[index] = next_3;
      pt3++;
    }else{
      seq[index] = next_2;
      pt2++;
      pt3++;
    }
  }
  index++; 

  if(DEBUG) printf("final number of elements is %d\n", index);
  
  if(len == -1){//if we are in counting mode
    //dont bother freeing lol
    return index; //return number of elements
  }else{
      return -2;
    }
}
