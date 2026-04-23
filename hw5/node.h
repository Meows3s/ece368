
#define LEFT 0
#define RIGHT 1
#define TOP 2
#define BOTTOM 3

typedef struct node_{
  int* bridge; //4 possible bridge connections
  int* pos; //x and y coordinates of the node
  int seen;
}node;

typedef struct graph_{
  int nrow;
  int ncol;
  node*** data; //2d array of node pointers (node addresses)
}graph;
