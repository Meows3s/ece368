#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"

#define DEBUG 1

int getList(Node*, FILE*);
Node* getNextNode(Node*);
int List_Save_To_File(char*, Node*);
Node* List_Load_From_File(char*, int*);

Node* List_Shellsort(Node* list, long* n_comp){
  return list;
}

Node* List_Load_From_File(char* filename, int* status){
  FILE* fptr = fopen(filename, "rb");

  if(fptr == NULL){ //if the file fails to open
    *status = -1; //fail
    return NULL;
  }else{
    *status = 1; //success
  }

  if(DEBUG)printf("file opened\n");
  
  Node* head = calloc(1, sizeof(Node)); //create head of list
  //getList(getNextNode(head), fptr); //create the rest of the list (simply)
  
  long thisLong = 0;
  while(fread(&thisLong, sizeof(long), 1, fptr) == 1){
    if(DEBUG)printf("read %ld\n", thisLong);
    head->value = thisLong;
    head->next = calloc(1, sizeof(Node*));
    head = head->next;
  }

  if(DEBUG)printf("done reading from file\n");

  fclose(fptr);
  return head; //return the list
}

int List_Save_To_File(char* filename, Node* head){
  FILE* fptr = fopen(filename, "wb");
  if(fptr == NULL){return -1;} //return if file fails to open
  
  int numElements = 0;
  Node* thisNode = head->next;
  
  do{
    if(DEBUG)printf("wrote %ld to file.\n", thisNode->value);

    fwrite(&thisNode->value, sizeof(long), 1, fptr); //write the contents of this node to the file
    thisNode = thisNode->next; //we are NOT asked to free the list here, so just move to the next node
    numElements++;
  }while(thisNode->next != NULL);

  if(DEBUG)printf("wrote %d elements to file.\n", numElements);

  return numElements;
}

/*
//recursive function to generate the list
int getList(Node* thisNode, FILE* fptr){
  long thisLong = 0;

  if(fread(&thisLong, sizeof(long), 1, fptr) != 1) {
    thisNode = NULL;
    return 0;
  }

  if(DEBUG) printf("long read: %ld\n", thisLong);
  thisNode->value = thisLong;

  //allocate next node and recurse
  thisNode->next = calloc(1, sizeof(Node));
  return getList(thisNode->next, fptr);
}

//takes in the current node and sets its next pointer to the next node
Node* getNextNode(Node* thisNode){
  thisNode->next = calloc(1, sizeof(Node));
  return thisNode->next;
}*/
