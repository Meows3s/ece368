typedef struct queue_{
  node* data;
  int dir; //direction we came from
  struct queue_* next; //next queue node
}queue;
