#define LEAF 'L'
#define VERT 'V'
#define HORIZ 'H'
#define UNDEFINED 'U'

typedef struct Tnode_{ //define the binary tree type
  char divType;

  int blockNum;
  int width;
  int height;

  struct Tnode_* left;
  struct Tnode_* right;
}Tnode;

typedef struct moStack_{
  struct moStack_* next;
  Tnode* data;
}moStack;

Tnode* pop(moStack**);
void push(moStack**, Tnode*);

moStack* newStack();
void freeStack(moStack*);

void dumpStack(moStack*);
int stackEmpty(moStack*);
int itemsInStack(moStack*);
