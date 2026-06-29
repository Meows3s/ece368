#include "defs.h"

// what can I say, I like macros
#define CMD_OPEN "open"
#define CMD_CLOSE "close"
#define CMD_SWITCH "switch"
#define CMD_LIST "list"

void open(stack*, int);
void close(stack*, int);
void closeAll(stack*);
void swch(stack*, int);
void list(stack*);

int main() {

  stack* head = newStack(-9);

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
    int winNum = 0;
    if (args[1] != NULL) {
      winNum = strtol(args[1], &end, 10);
    }

    if (!strcmp(args[0], CMD_OPEN)) {
      open(head, winNum);
      if (DEBUG) printf("running open\n");
    } else if (!strcmp(args[0], CMD_CLOSE)) {

      if (!strcmp(args[1], "all")) {
        closeAll(head);
      } else {
        close(head, winNum);
      }
      if (DEBUG) printf("running close\n");
    } else if (!strcmp(args[0], CMD_SWITCH)) {
      swch(head, winNum);
      if (DEBUG) printf("running switch\n");
    } else if (!strcmp(args[0], CMD_LIST)) {
      list(head);
      if (DEBUG) printf("running list\n");
    } else { // command not recognized
      if (DEBUG) printf("unknown command\n");
    }

    if (stackEmpty(head)) {
      break;
    } else {
      printf("%d\n", head->next->winNum); // the window in focus
    }
  }

  free(head);
  return 0;
}

void open(stack* sptr, int tgt) { push(sptr, tgt); }

void close(stack* sptr, int tgt) { poke(sptr, tgt); }

void closeAll(stack* sptr) {
  while (!stackEmpty(sptr)) {

    // pop(sptr);
  }
}

void swch(stack* sptr, int tgt) {
  int currentFocus = sptr->next->winNum;
  stack* tgtNode = find(sptr, tgt)->next;

  // switcheroo
  sptr->next->winNum = tgtNode->winNum;
  tgtNode->winNum = currentFocus;
}

void list(stack* sptr) { dumpStack(sptr); }
