#include <stdio.h>
#include <stdlib.h>
#include "moStack.h"

#define FILE_READ_FLAG "r"
#define FILE_WRITE_FLAG "w"

#define DEBUG 1


//readPost.c
Tnode* readPost(char*);

//reroot.c
Tnode* RRPath(Tnode**, int);
Tnode* pathGen(Tnode**, int);
Tnode* RRLeft(Tnode**);
Tnode* RRRight(Tnode**);

//util.c
int max(int, int);
void recalcDims(Tnode*);
Tnode* newTree(void);
void freeTree(Tnode*);
void dumpTree(Tnode*);
void dumpTreeNode(Tnode*);


