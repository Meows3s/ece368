#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"

#define DEBUG 1
int getList(Node*, FILE*);
Node* getNextNode(Node*);
long getLong(FILE*);


Node* List_Load_From_File(char* filename, int* status){
  
  FILE* fptr = fopen(filename, "r");
  if(fptr == NULL){return NULL;}

  Node* head = calloc(1, sizeof(Node)); //create head of list
  getList(head, fptr); //create the rest of the list (simply)
 
  fclose(fptr);

  return head; //return the list
}

//recursive function to generate the list
int getList(Node* thisNode, FILE* fptr){
  if(feof(fptr)){return 1;}//if we are at the end of the file, return
  long thisLong = getLong(fptr);
  if(DEBUG) printf("long read: %ld\n", thisLong);
  thisNode->value = thisLong;
  return getList(getNextNode(thisNode), fptr);
}

//takes in the current node and sets its next pointer to the next node
Node* getNextNode(Node* thisNode){
  thisNode->next = calloc(1, sizeof(Node));
  return thisNode->next;
}

//get the next long from the file
long getLong(FILE* fptr){
  long toReturn;
  return ( fscanf(fptr, "%ld", &toReturn) ? toReturn : -1 );
}
