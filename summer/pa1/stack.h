// the stack in question:
typedef struct stack_ {
  int winNum;
  struct stack_* next;
} stack;

// function defs
stack* newStack(int);
stack* find(stack*, int);
void poke(stack*, int);
void push(stack*, int);
void pop(stack*);

int stackEmpty(stack*);
void dumpStack(stack*);
