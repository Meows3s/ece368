#include "defs.h"

//add an item to the top of the stack
void push(moStack** stackHead, Tnode* data){
  moStack* toPush = newStack();
  toPush->data = data;

  toPush->next = (*stackHead)->next;
  (*stackHead)->next = toPush;
}

//return the item off of the top of the stack
Tnode* pop(moStack** stackHead){
  Tnode* popped = (*stackHead)->next->data; //don't pop the head but the next one
  moStack* toFree = (*stackHead)->next;
  (*stackHead)->next = (*stackHead)->next->next; //remove the node from the stack chain
  free(toFree);
  return popped;
}

moStack* newStack(){
  moStack* toReturn = calloc(1, sizeof(moStack));
  toReturn->next = NULL;
  return toReturn;
}

void freeStack(moStack* stackHead){
  moStack* toFree;
  while(stackHead != NULL){
    toFree = stackHead;
    stackHead = stackHead->next;
    free(toFree);
  }
}

int stackEmpty(moStack* stackHead){
  if(stackHead == NULL || stackHead->next == NULL){
    return 1; //empty, head does not count as an item in the stack
  }
  return 0;
}

int itemsInStack(moStack* stackHead){
  int count = 0;
  while(stackHead->next != NULL){ //don't count the head
    stackHead = stackHead->next;
    count++;
  }
  return count;
}

void dumpStack(moStack* stackHead){
  printf("\nstack is currently:\n");
  while(stackHead != NULL){
    dumpTreeNode(stackHead->data);
    stackHead = stackHead->next;
  }
  printf("\n");
}


