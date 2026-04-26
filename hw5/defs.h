#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for memset
#include "node.h"
#include "queue.h"

#define DEBUG 1

//file stuff
#define OPEN_FLAG "r+"
#define WRITE_FLAG "w"

//util.c
int openFile(char*, char*, FILE**);
int min(int, int);

graph* newGraph(int, int);
node* newNode();

void freeGraph(graph*);
void freeNode(node*);
void freeQueue(queue*);

void dumpGraph(graph*);
void dumpNode(node*);
void dumpQueue(queue*);

int itemsInQueue(queue*);

//queue.c
queue* newQueue();
void enqueue(queue*, node*);
node* dequeue(queue**);

//explore.c
void shortestFromAny(graph**);
void shortestFromRow(graph**, int);
void traverse(graph**, queue*);
void enqueueNbors(queue*, node*);
queue* buildPath(graph*);
void writePath(char*, queue*);


//pa5.c


//loadNodes.c
graph* getNodesFromFile(char*);
