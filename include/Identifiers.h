#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "LinkedList.h"
#include "BalancedBinaryTree.h"
#include "Eval.h"
#include "Parse.h"
#include "Vars.h"

typedef struct Identifier {
	int id;
	const char* name;
	const char* args;
	const char* returns;
	bool standard;
	const char* sub;
	const char* params;
	void* (*function)(LinkedList);
} Identifier;

typedef BalancedBinaryTree Identifiers;

Identifiers I_Identifiers();
Identifier I_find(const char*);
Identifier* I_create(const char*, const char*, const char*, void* (*)(LinkedList));

Identifiers identifiers;

#endif
