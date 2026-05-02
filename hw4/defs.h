#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hbt.h"

#define FILE_READ_FLAG "rb"
#define FILE_WRITE_FLAG "wb"
//#define TEMPFILE "temp.txt"

#define BRANCH 3
#define LEAF 0

//ops
#define INSERT 'i'
#define DELETE 'd'

#define R_LEFT 1
#define R_RIGHT 2

#define STEP (sizeof(char) *  5)

#define DEBUG 1

//conversions
int treeBtoC(char* inf, char* outf);
int opsBtoC(char* inf, char* outf);

//balance
int isBalanced(char*);
int isGoodFile(char*, char*);
int isBST(char*);

//eval.c
int eval(char*);

//build
Tnode* newNode(int value);
int buildTree(char*, char*);
void writeToFile(FILE*, Tnode*);

void insert(Tnode*, Tnode*);
void delete(Tnode**, int);
void rotate(Tnode**, int);
void calcBalance(Tnode*);

void freeTree(Tnode*);
void dumpTree(Tnode*);
