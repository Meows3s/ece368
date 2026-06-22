#include "defs.h"

// make a new stack/stack node
stack* newStack(int winNum) {
  stack* toReturn = calloc(1, sizeof(stack));
  toReturn->winNum = winNum;
  return toReturn;
}

// push a new node to the top of the stack
void push(stack* sptr, int winNum) {
  stack* newHead = newStack(winNum);
  newHead->next = sptr->next;
  sptr->next = newHead;
}

// returns the node before the target node
stack* find(stack* sptr, int tgt) {
  while (sptr->next != NULL && sptr->next->winNum != tgt) {
    sptr = sptr->next;
  }
  return sptr;
}

// removes a node containing a specific value
void poke(stack* sptr, int tgt) {
  stack* prev = find(sptr, tgt);
  stack* next = prev->next->next;

  free(prev->next); // free the node

  if (next == NULL) {
    return;
  } // if that was the last node, we are done
  prev->next = next; // otherwise, fix the pointers
}
