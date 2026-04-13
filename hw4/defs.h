#include "modebug.h"
#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BRANCH 3
#define LEAF 0

#define STEP (sizeof(char) *  5)

//conversions
int treeBtoC(char* inf, char* outf);
int opsBtoC(char* inf, char* outf);

//balance
int isBalanced(char*);
int isGoodFile(char*, char*);
int isBST(char*);

//build
int buildTree(char*, Tnode*);
void freeTree(Tnode*);
