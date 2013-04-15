#include "Vars.h"

void V_init(Var* v) {
	v->name = NULL;
	v->type = NONE;
	v->value = NULL;
}

bool V_isEmpty(Var v) {
	return ((v.name == NULL) && (v.type == NONE) && (v.value == NULL));
}

const char* V_getName(Var v) {
	return v.name;
}

Type V_getType(Var v) {
	return v.type;
}

void* V_getValue(Var v) {
	return v.value;
}
void V_setName(Var* v, const char* name) {
	v->name = name;
}

void V_setValue(Var* v, void* value) {
	v->value = value;
}

void V_setType(Var* v, Type type) {
	v->type = type;
}

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

Type VLH_getType(LinkedList l) {
	return (Type)((Var*)(LL_getValue(l)))->type;
}

void* VLH_getValue(LinkedList l) {
	return (void*)((Var*)(LL_getValue(l)))->value;
}

void VLH_setType(LinkedList l, Type type) {
	((Var*)LL_getValue(l))->type = type;
}

void VLH_setName(LinkedList l, const char* name) {
	((Var*)LL_getValue(l))->name = name;
}

void VLH_setValue(LinkedList l, void* value) {
	((Var*)LL_getValue(l))->value = value;
}
