//pos defs
#define LEFT 0
#define RIGHT 1
#define TOP 2
#define BOTTOM 3

//bridge defs
#define BRIDGE 1
#define NOBRIDGE 0

//seen defs
#define SEEN 1
#define UNSEEN 0

typedef struct node_{
  int* bridge; //4 possible bridge connections
  int* pos; //x and y coordinates of the node
  int* fromNode; //the previous node with shortest distance used to get to this node
  int seen;
}node;


typedef struct graph_{
  int nrow;
  int ncol;
  node*** data; //2d array of node pointers (node addresses)
}graph;
