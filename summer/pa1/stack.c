#include "defs.h"
#include <string.h>

// make a new stack/stack node
stack* newStack(int winNum) {
  stack* toReturn = calloc(1, sizeof(stack));
  toReturn->winNum = winNum;
  toReturn->next = NULL;
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
  if (sptr == NULL || sptr->next == NULL) return NULL; // return if bad head
  while (sptr->next != NULL) {
    if (sptr->next->winNum == tgt) {
      return sptr;
    } // found the previous node, return
    sptr = sptr->next;
  }
  return NULL; // node not found, return null
}

// deletes an arbitrary node on the stack
void pop(stack* sptr) {
  if (sptr == NULL || sptr->next == NULL) {
    if (DEBUG) printf("node does not exist\n");
    return;
  }
  stack* next = sptr->next->next;
  stack* toFree = sptr->next;
  sptr->next = next;
  free(toFree);
}

// removes a node containing a specific value
void poke(stack* sptr, int tgt) {
  if (sptr == NULL) return;
  stack* prev = find(sptr, tgt);
  if (prev == NULL) return; // value does not exist in list, return
  pop(prev);
}

int stackEmpty(stack* sptr) {
  if (sptr == NULL || sptr->next == NULL) {
    return 1; // I guess null is empty... hopefully we never end up here
  } else {
    return 0;
  }
}

void dumpStack(stack* sptr) {
  sptr = sptr->next; // start at actual data instead of the head
  int count = 0;
  printf("\n---\n");
  printf("windows currently open:\n");
  while (sptr != NULL) {
    if (DEBUG) {
      printf("node %d contains window number %d\n", count, sptr->winNum);
    } else {
      printf("%d\n", sptr->winNum);
    }
    count++;
    sptr = sptr->next;
  }
  printf("number of windows open: %d", count);
  printf("\n---\n");
}
