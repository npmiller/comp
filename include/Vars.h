#ifndef VARS_H
#define VARS_H

#include "LinkedList.h"

typedef struct {
	const char* name;
	const char* type;
	void* value;
} Var;

const char* V_getName(Var);

/* VLH : Variable-LinkedList Helpers */
Var VLH_getVar(LinkedList);
int VLH_getInt(LinkedList);
char* VLH_getString(LinkedList);
char* VLH_getName(LinkedList);
char* VLH_getType(LinkedList);
void* VLH_getValue(LinkedList);
void VLH_setType(LinkedList, const char*);
void VLH_setName(LinkedList, const char*);
void VLH_setValue(LinkedList, void*);

#endif
