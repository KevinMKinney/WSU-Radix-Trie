//#ifndef "func.h"
//#define "func.h"
#ifndef FUNC_H
#define FUNC_H
// include c libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
// macros
#define StringSize	35
// structs
struct node {
	char value[StringSize];
	struct node* nextNode[26];
};
// global var
struct node* root;
// functions
char* getSubstring(char* word, char* sub);
char* getPrefix(char* word, char* sub);
int searchWord(char* copyWord);
int insertWord(char* word, struct node* search);
void emptyTree(struct node* current);
int nodeNumber(struct node* current);
int wordNumber(struct node* current);
//void printTrie(struct node* current); 

#endif
