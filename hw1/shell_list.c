#include <stdio.h>
#include <stdlib.h>

#include "sequence.h"
#include "shell_list.h"

#define DEBUG 0 //not needed anymore lol

static Node* getNodeAt(Node*, int);
static int listLength(Node*);

static Node* getNodeAt(Node* head, int index){
  for(int i = 0; i < index; i++){
    if(head == NULL) return NULL;
    head = head->next;
  }
  return head;
}

static int listLength(Node* head){
  int count = 0;
  while(head != NULL){ count++; head = head->next; }
  return count;
}

static void sortKsubseqList(Node* head, int n, int start, int k, long* n_comp){
  int count = 0;
  for(int i = start; i < n; i += k) count++;

  if(count < 2) return;
  int last_exchange = count;

  int sorted = 0;
  while(!sorted){
    sorted = 1;
    int last_element = last_exchange - 1;

    for(int j = 0; j < last_element; j++){
      Node* a = getNodeAt(head, start + j * k);
      Node* b = getNodeAt(head, start + (j + 1) * k);

      (*n_comp)++;
      if(a->value > b->value){
        long temp = a->value;
        a->value = b->value;
        b->value = temp;
        last_exchange = j + 1;
        sorted = 0;
      }
    }
  }
}

Node* List_Load_From_File(char* filename, int* status){
  FILE* fptr = fopen(filename, "rb");

  //file validity check
  if(fptr == NULL){
    *status = -1;
    return NULL;
  }

  Node* head = NULL;
  Node* tail = NULL;
  long thisLong = 0;

  while(fread(&thisLong, sizeof(long), 1, fptr) == 1){
    Node* newNode = calloc(1, sizeof(Node));
    if(newNode == NULL){
      *status = -1;
      while(head != NULL){ Node* tmp = head->next; free(head); head = tmp; }
      fclose(fptr);
      return NULL;
    }
    newNode->value = thisLong;
    newNode->next = NULL;

    if(head == NULL){ head = newNode; tail = newNode; }
    else { tail->next = newNode; tail = newNode; }
  }

  *status = 0;
  fclose(fptr);
  return head;
}

int List_Save_To_File(char* filename, Node* head){
  FILE* fptr = fopen(filename, "wb");
  if(fptr == NULL){ return -1; }

  int numElements = 0;

  while(head != NULL){
    fwrite(&(head->value), sizeof(long), 1, fptr);
    head = head->next;
    numElements++;
  }

  fclose(fptr);
  return numElements;
}

//actually do the sorting
Node* List_Shellsort(Node* list, long* n_comp){
  *n_comp = 0;

  if(list == NULL) return NULL;

  int n = listLength(list);
  int numKs = 0;
  long* kVals = Generate_2p3q_Seq(n, &numKs);

  if(kVals == NULL){
    sortKsubseqList(list, n, 0, 1, n_comp);
    return list;
  }

  for(int i = numKs - 1; i >= 0; i--){
    int k = (int)kVals[i];
    for(int start = 0; start < k && start < n; start++){
      sortKsubseqList(list, n, start, k, n_comp);
    }
  }



  free(kVals);
  return list;
}
