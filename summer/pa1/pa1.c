#include "defs.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

// what can I say, I like macros
#define CMD_OPEN "open"
#define CMD_CLOSE "close"
#define CMD_SWITCH "switch"
#define CMD_LIST "ls"

#define ARG_ALL "all"

void open(stack*, int);
void close(stack*, int);
void closeAll(stack*);
void swch(stack*, int);
void list(stack*);

int main() {

  stack* head = newStack(UNINIT_STACK_VAL);

  while (1) {

    char input[32] = {0};
    char* args[8] = {0};

    if (!fgets(input, sizeof(input), stdin)) {
      return 1;
    }

    // seperate out arguments and command
    char* tok = strtok(input, " \n");
    for (int i = 0; tok != NULL; i++) {
      args[i] = tok;
      tok = strtok(NULL, " \n");
    }

    char* end;
    int winNum = INT_MIN;
    if (args[1] != NULL) {
      winNum = strtol(args[1], &end, 10);
      if (errno != 0 || end == args[1]) {
        winNum = INT_MAX;
      }
    }

    if (winNum != INT_MIN && !strcmp(args[0], CMD_OPEN)) {
      open(head, winNum);
      if (DEBUG) printf("running open\n");
    } else if (winNum != INT_MIN && !strcmp(args[0], CMD_CLOSE)) {
      if (!strcmp(args[1], ARG_ALL)) {
        closeAll(head);
        break;
      } else if (winNum != INT_MIN) {
        close(head, winNum);
      }
      if (stackEmpty(head)) {
        break;
      }
      if (DEBUG) printf("running close\n");
    } else if (winNum != INT_MIN && !strcmp(args[0], CMD_SWITCH)) {
      swch(head, winNum);
      if (DEBUG) printf("running switch\n");
    } else if (!strcmp(args[0], CMD_LIST)) {
      list(head);
      if (DEBUG) printf("running list\n");
    } else { // command not recognized
      if (DEBUG) printf("unknown command\n");
    }

    printf("%d\n", head->next->winNum); // the window in focus
  }

  free(head);
  return 0;
}

void open(stack* sptr, int tgt) { push(sptr, tgt); }

void close(stack* sptr, int tgt) { poke(sptr, tgt); }

void closeAll(stack* head) {
  head = head->next; // skip head
  while (1) {
    stack* toPop = head;
    head = head->next;
    if (head == NULL) {
      return;
    }
    free(toPop);
  }
}

void swch(stack* sptr, int tgt) {
  if (sptr == NULL || sptr->next == NULL) return; // bad stack
  stack* tgtNode = find(sptr, tgt);
  if (tgtNode == NULL || tgtNode->next == NULL) return; // node does not exist
  tgtNode = tgtNode->next;

  int moveUp = tgtNode->winNum;

  poke(sptr, moveUp); // remove old node
  push(sptr, moveUp); // add it to the front.
}

void list(stack* sptr) { dumpStack(sptr); }
