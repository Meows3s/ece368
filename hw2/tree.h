typedef struct tree_{ //define the binary tree type
  char div;

  int blockNum;
  int xPos;
  int yPos;

  struct tree_* left;
  struct tree_* right;
}tree;

tree* loadTree(char*);
