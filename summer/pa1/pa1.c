#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  stack* head = newStack(-9);
  char command[32];
  int winNum = 0;

  scanf("%s %d", command, &winNum);

  while (head->next != NULL) {
  }

  return 0;
}

void open(stack* sptr, int tgt) { push(sptr, tgt); }

void close(stack* sptr, int tgt) { poke(sptr, tgt); }

void swch(stack* sptr, int tgt) {
  int currentFocus = sptr->next->winNum;
  stack* tgtNode = find(sptr, tgt)->next;

  // switcheroo
  sptr->next->winNum = tgtNode->winNum;
  tgtNode->winNum = currentFocus;
}
