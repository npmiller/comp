#ifndef VARS_H
#define VARS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include "Type.h"

typedef struct {
	const char* name;
	Type type;
	void* value;
} Var;

void V_init(Var*);
void V_print(Var);
bool V_isEmpty(Var);
const char* V_getName(Var);
Type V_getType(Var);
void* V_getValue(Var);
void V_setValue(Var*, void*);
void V_setType(Var*, Type);
void V_setName(Var*, const char*);
void V_free(void**);

/* VLH : Variable-LinkedList Helpers */
Var VLH_getVar(LinkedList);
int VLH_getInt(LinkedList);
char* VLH_getString(LinkedList);
char* VLH_getName(LinkedList);
Type VLH_getType(LinkedList);
void* VLH_getValue(LinkedList);
void VLH_setType(LinkedList, Type);
void VLH_setName(LinkedList, const char*);
void VLH_setValue(LinkedList, void*);

#endif
