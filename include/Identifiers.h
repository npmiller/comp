#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "LinkedList.h"
#include "BalancedBinaryTree.h"
#include "Vars.h"

typedef struct Identifier {
	int id;
	const char* name;
	const char* args;
	const char* returns;
	void* (*function)(LinkedList);
} Identifier;

typedef BalancedBinaryTree Identifiers;

Identifiers I_Identifiers();
Identifier I_find(const char*, Identifiers);
Identifier* I_create(const char*, const char*, const char*, void* (*)(LinkedList));

#endif
