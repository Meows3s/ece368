#include <stdio.h>
#include <stdlib.h>
#include "node.h"

#define DEBUG 1

//node stuff
#define BRIDGE 1
#define NOBRIDGE 0
#define SEEN 1
#define UNSEEN 0

//file stuff
#define OPEN_FLAG "r+"


//util.c
int openFile(char*, char*, FILE**);
graph* newGraph(int, int);
node* newNode();

void freeGraph(graph*);
void freeNode(node*);

void dumpGraph(graph*);
void dumpNode(node*);

//pa5.c


//loadNodes.c
int getNodesFromFile(char*, graph*);
