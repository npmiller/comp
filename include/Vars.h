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
	Type vtype;
	void* value;
} Var;

void V_init(Var*);
void V_print(Var);
Var V_copy(Var);
void* V_copyValue(void*, Type);
bool V_isEmpty(Var);
const char* V_getName(Var);
Type V_getType(Var);
Type V_getVType(Var);
void* V_getValue(Var);
void V_setValue(Var*, void*);
void V_setType(Var*, Type);
void V_setVType(Var*, Type);
void V_setName(Var*, const char*);
void V_free(void**);
void V_free_name(void**);

/* VLH : Variable-LinkedList Helpers */
Var VLH_getVar(LinkedList);
int VLH_getInt(LinkedList);
bool VLH_getBool(LinkedList);
char* VLH_getString(LinkedList);
char* VLH_getName(LinkedList);
Type VLH_getType(LinkedList);
Type VLH_getVType(LinkedList);
void* VLH_getValue(LinkedList);
void VLH_setType(LinkedList, Type);
void VLH_setVType(LinkedList, Type);
void VLH_setName(LinkedList, const char*);
void VLH_setValue(LinkedList, void*);

#endif
