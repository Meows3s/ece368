#include <stdio.h>
#include <stdlib.h>

#include "moStack.h"

#define FILE_READ_FLAG "r"
#define FILE_WRITE_FLAG "w"

#define DEBUG 1

//loadPreorder.c
tree* loadPreorder(char*);

//writePostorder.c
int writePostorder(tree*, char*);

//pack.c
int writePack(tree**, char*);

//writeBound.c
int writeBound(tree*, char*);

//util.c
int max(int, int);

tree* newTree(void);
void freeTree(tree*);

void dumpTreeNode(tree*);
void dumpPost(tree*);
