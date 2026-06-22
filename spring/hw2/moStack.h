#define LEAF 'L'
#define VERT 'V'
#define HORIZ 'H'
#define UNDEFINED 'U'

typedef struct tree_{ //define the binary tree type
  char divType;

  int blockNum;
  int width;
  int height;
  int oX; //origin x
  int oY; //origin y

  struct tree_* left;
  struct tree_* right;
}tree;

typedef struct moStack_{
  struct moStack_* next;
  tree* data;
}moStack;

tree* pop(moStack**);
void push(moStack**, tree*);

moStack* newStack();
void freeStack(moStack*);

void dumpStack(moStack*);
int stackEmpty(moStack*);
int itemsInStack(moStack*);
