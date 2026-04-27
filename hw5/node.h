//pos defs
#define LEFT 0
#define RIGHT 1
#define TOP 2
#define BOTTOM 3

//bridge defs
#define BRIDGE 0

//seen defs
#define SEEN 1
#define UNSEEN 0

//undiscovered distance
#define MAX_DIST 999999999
#define NULL_DIST 999999999

typedef struct node_{
  int pos[2]; //x and y coordinates of the node
  int bridge[4]; //bridge rotation weights
  int seen[4]; //one resolution per direction

  int distFromSource[4]; //one distance per incoming direction
  
  struct node_** nbor; //array of node neighbors (oh no)
  struct node_** closest; //closest neighbor node for each incoming direction
  int closestDir[4]; //for each incoming direction, what direction is the closest node
}node;

typedef struct graph_{
  int nrow;
  int ncol;
  node*** data; //2d array of node pointers (node addresses)
}graph;
