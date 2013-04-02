#include "Identifiers.h"
#include <string.h>

void* add(LinkedList l) {
	int a = VLH_getInt(l);
	l = LL_getNext(l);
	int b = VLH_getInt(l);
	int* res = (int*)malloc(sizeof(int));
	*res = a + b;
	return res;
}

void* substract(LinkedList l) {
	int a = VLH_getInt(l);
	l = LL_getNext(l);
	int b = VLH_getInt(l);
	int* res = (int*)malloc(sizeof(int));
	*res = a - b;
	return res;
}

void* print(LinkedList l) {
	char* res = VLH_getString(l);
	return res;
}

Identifier I_find(const char* name, Identifiers I) {
	int i;
	Identifier Id;
	for(i=0;i<10;i++) {
		if(strcmp(I[i].id,name) == 0) {
			return I[i];
		}
	}
	return Id;
}
Identifiers I_Identifiers() {
	Identifiers I = (Identifiers)malloc(10*sizeof(Identifier));
	Identifier I_add;
	I_add.id = "add";
	I_add.args = "int int";
	I_add.returns = "int";
	I_add.function = add;
	I[0] = I_add;

	Identifier I_substract;
	I_substract.id = "substract";
	I_substract.args = "int int";
	I_substract.returns = "int";
	I_substract.function = substract;
	I[1] = I_substract;

	Identifier I_print;
	I_print.id = "print";
	I_print.args = "string";
	I_print.returns = "string";
	I_print.function = print;
	I[2] = I_print;
	return I;
}
