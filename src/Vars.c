#include "Vars.h"

Var VLH_getVar(LinkedList l) {
	return *((Var*)(l->value));
}

int VLH_getInt(LinkedList l) {
	return *((int*)((Var*)(LL_getValue(l)))->value);
}

char* VLH_getString(LinkedList l) {
	return (char*)((Var*)(LL_getValue(l)))->value;
}
