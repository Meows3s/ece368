#include <stdio.h>
#include "sequence.h"

#define DEBUG 1

long* Generate_2p3q_Seq(int, int*);
int moPow(int, int);


int main(){
  
  if(DEBUG) printf("starting program...\n");

  int test = 20;

  Generate_2p3q_Seq(20, &test);

  return 0;
}

long* Generate_2p3q_Seq(int less_than, int* test){
  
  int this_num = 0;
  int iter = 0;

  while(this_num < less_than){

    for(int j = 0; j < iter+1; j++){
      this_num = moPow(2, iter-j) * moPow(3, j);
      printf("i = %d, j = %d, number is %d\n", iter-j, j, this_num);
    }
    iter++;
  }
  return 100; 
}

//my power function (I am mo, in case you were wondering)
int moPow(int base, int power){
  int result = 1;
  while(power){
    result *= base;
    power--;
  }
  return result;
}
