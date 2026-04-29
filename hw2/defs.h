#include <stdio.h>
#include <stdlib.h>

#include "moStack.h"

#define FILE_READ_FLAG "r"
#define FILE_WRITE_FLAG "w"

#define DEBUG 1

//loadPreorder.c
tree* loadPreorder(char*);

//writePostorder.c
int writePostorder(char*, tree*);

//util.c
tree* newTree(void);

void dumpTreeNode(tree*);
void dumpPost(tree*);
