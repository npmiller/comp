#include "Vars.h"

Var VLH_getVar(LinkedList l) {
	return *((Var*)LL_getValue(l));
}

int VLH_getInt(LinkedList l) {
	return *((int*)((Var*)(LL_getValue(l)))->value);
}

char* VLH_getString(LinkedList l) {
	return (char*)((Var*)(LL_getValue(l)))->value;
}

char* VLH_getName(LinkedList l) {
	return (char*)((Var*)(LL_getValue(l)))->name;
}

char* VLH_getType(LinkedList l) {
	return (char*)((Var*)(LL_getValue(l)))->type;
}

void VLH_setType(LinkedList l, const char* type) {
	((Var*)LL_getValue(l))->type = type;
}

void VLH_setName(LinkedList l, const char* name) {
	((Var*)LL_getValue(l))->name = name;
}

void VLH_setValue(LinkedList l, void* value) {
	((Var*)LL_getValue(l))->value = value;
}
