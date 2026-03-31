#include "modebug.h"
#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#define EXIT_FAILURE 0
//#define EXIT_SUCCESS 1

//conversions
int treeBtoC(char* inf, char* outf);
int opsBtoC(char* inf, char* outf);

//balance
int isBalanced(Tnode*);
int isGoodFile(char*, char*);
int isBST(Tnode*);

//build
int buildTree(char*, Tnode*);
void freeTree(Tnode*);
