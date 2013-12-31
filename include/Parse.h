#ifndef PARSE_H
#define PARSE_H

#define IGNORED '\t'
#define DELIM ' '
#define END '\0'

#define GOOD 1
#define EXPECTED_TOKEN 2
#define NOT_A_NUMBER 3

#include "LinkedList.h"
#include "BalancedBinaryTree.h"
#include <stdlib.h>
#include <errno.h>
#include "Vars.h"

LinkedList P_parse(const char*);
char* P_matchingBracket(const char*, const char , const char, int*);
char* P_getInBetween(const char*, char, int*);
char* P_getNextWord(const char*, int, int*);
char* P_process_string(const char*);
Var* P_process(const char* word);

void discardBlankChars(const char*, int*);

#endif
