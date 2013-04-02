#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "LinkedList.h"
#include "Vars.h"

typedef struct Identifier {
	const char* id;
	const char* args;
	const char* returns;
	void* (*function)(LinkedList);
} Identifier;

typedef Identifier* Identifiers;

Identifiers I_Identifiers();
Identifier I_find(const char*, Identifiers);
#endif
