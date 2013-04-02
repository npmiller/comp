#ifndef VARS_H
#define VARS_H

#include "LinkedList.h"

typedef struct {
	const char* name;
	const char* type;
	void* value;
} Var;

Var VLH_getVar(LinkedList);
int VLH_getInt(LinkedList);
char* VLH_getString(LinkedList);

#endif
