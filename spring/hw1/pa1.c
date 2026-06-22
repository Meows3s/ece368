#include <stdio.h>
#include <stdlib.h>

#include "shell_array.h"
#include "shell_list.h"
#include "sequence.h"

void freeList(Node*);
void dump(long*, int);
void listDump(Node*);

int main(int argc, char** argv){
    if(argc != 4){
    fprintf(stderr, "Usage: %s -a/-l input.b output.b\n", argv[0]);
    return EXIT_FAILURE;
  }

  char* flag = argv[1];
  char* fileIn = argv[2];
  char* fileOut = argv[3];
  
  if(flag[1] == 'a'){
    int numArray = 0;
    long numComp = 0;
    long* arrayToSort = Array_Load_From_File(fileIn, &numArray);
    
    if(arrayToSort == NULL){
      return EXIT_FAILURE;
    }

    Array_Shellsort(arrayToSort, numArray, &numComp);
    
    int numWritten = Array_Save_To_File(fileOut, arrayToSort, numArray);
    free(arrayToSort);

    if(numWritten == -1){//check save failure??????
      return EXIT_FAILURE;
    }

    printf("%ld\n", numComp);

  }else if(flag[1] == 'l'){
    
    int status = 0;
    long numComp = 0;

    Node* head = List_Load_From_File(fileIn, &status);

    if(status == -1){//check for load failure
      return EXIT_FAILURE;
    }



    List_Shellsort(head, &numComp);

    int numWritten = List_Save_To_File(fileOut, head);
    
    freeList(head);

    if(numWritten == -1){//check save failure
      return EXIT_FAILURE;
    }

    printf("%ld\n", numComp);

  }else{
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
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
