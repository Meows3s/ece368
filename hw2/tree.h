#define LEAF 'L'
#define VERT 'V'
#define HORIZ 'H'

#define DEBUG 1

typedef struct tree_{ //define the binary tree type
  char div;

  int blockNum;
  int xPos;
  int yPos;

  struct tree_* left;
  struct tree_* right;
}tree;

/*loaders and writers*/
tree* loadPreorder(char*);
int writePostorder(tree*, char*);

/*util stuff*/
int freeTree(tree*);
