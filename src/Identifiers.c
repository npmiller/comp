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
	printf("%s\n", res);
	return NULL;
}

int I_getID(const char* string) {
	int res = 0;
	int i = 0;
	while(string[i] != '\0') {
		res += (int)string[i];
		i++;
	}
	return res;
}

bool I_compare(void* a, void* b) {
	return ((((Identifier*)a)->id) > (((Identifier*)b)->id));
}

Identifier I_find(const char* name, Identifiers I) {
	Identifiers It = I;
	int id = I_getID(name);
	int currentId;
	Identifier Id;
    Id.name = "NotFound";
	while(!BBT_isEmpty(It)) {
		currentId = ((Identifier*)BBT_getValue(It))->id;
		if(id == currentId) {
			return *((Identifier*)BBT_getValue(It));
		} else {
			if(id > currentId) {
				It = BBT_getLeftBranch(It);
			} else {
				It = BBT_getRightBranch(It);
			}
		}
	}
	return Id;
}

Identifier* I_create(const char* name, const char* args, const char* returns, void* (*function)(LinkedList)) {
	Identifier* I = (Identifier*)malloc(sizeof(Identifier));
	I->id = I_getID(name);
	I->name = name;
	I->args = args;
	I->returns = returns;
	I->function = function;
	return I;
}

Identifiers I_Identifiers() {
	Identifiers I;
	I = BBT_create((void*)I_create("add", "int int", "int", add), NULL, NULL);
	BBT_add(I,(void*)I_create("substract", "int int", "int", substract), I_compare);
	BBT_add(I,(void*)I_create("print", "string", "null", print), I_compare);

	return I;
}
