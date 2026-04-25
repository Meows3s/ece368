#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "queue.h"

#define DEBUG 1

//file stuff
#define OPEN_FLAG "r+"


//util.c
int openFile(char*, char*, FILE**);
graph* newGraph(int, int);
node* newNode();

void freeGraph(graph*);
void freeNode(node*);
void freeQueue(queue*);

void dumpGraph(graph*);
void dumpNode(node*);
void dumpQueue(queue*);


//queue.c
queue* newQueue();
void enqueue(queue*, node*);
node* dequeue(queue*);
int isQueueEmpty(queue*);

//explore.c
void shortestFromAny(graph*);
void shortestFromRow(graph*, int);
void traverse(graph*, queue*);
void enqueueNbors(queue*, node*);

//pa5.c


//loadNodes.c
graph* getNodesFromFile(char*);
