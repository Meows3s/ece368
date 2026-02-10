#include <stdio.h>
#include <stdlib.h>

#include "shell_array.h"
#include "shell_list.h"
#include "sequence.h"

#define DEBUG 0
void freeList(Node*);
void dump(long*, int);
void listDump(Node*);

int main(int argc, char** argv){

  char* flag = argv[1]; //second char of flag bc first one is the dash
  char* fileIn = argv[2]; //zero is the program name
  char* fileOut = argv[3];
  
  if(flag[1] == 'a'){//use array method
    int numArray = 0;
    long numComp = 0;
    long* arrayToSort = Array_Load_From_File(fileIn, &numArray); //load array
    
    if(DEBUG)dump(arrayToSort, numArray);

    Array_Shellsort(arrayToSort, numArray, &numComp); //sort array
    
    if(DEBUG)dump(arrayToSort, numArray);

    Array_Save_To_File(fileOut, arrayToSort, numArray);
    printf("%ld\n", numComp);

  }else if(flag[1] == 'l'){//use list method
    
    int status = 0;
    long numComp = 0;

    Node* head = List_Load_From_File(fileIn, &status);

    if(DEBUG)listDump(head);

    List_Shellsort(head, &numComp);

    if(DEBUG)listDump(head);

    List_Save_To_File(fileOut, head);
    
    freeList(head); //free the linked list
    printf("%ld\n", numComp);

  }else{
    printf("incorrect arguments.\n");
  }

  return 0;
}


void freeList(Node* head){
  while(head->next != NULL){
    Node* next = head->next;
    free(head);
    head = next;
  }
}

void dump(long* array, int size){
  printf("starting array dump:\n");
  for(int i = 0; i < size; i++){
    printf("element at index %d is %ld\n", i, array[i]);
  }
}

void listDump(Node* head){
  printf("starting list dump:\n");
  while(head->next != NULL){
    printf("%ld\n", head->value);
    head = head->next;
  }
}
