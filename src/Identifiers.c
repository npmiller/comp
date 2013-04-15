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

void* call(LinkedList l) {
	char** returns = (char**)malloc(sizeof(char*));
	const char* sub = (const char*)LL_getValue(l);
	l = LL_getNext(l);
	const char* paramsString = (const char*)LL_getValue(l);
	l = LL_getNext(l);
	LinkedList params = P_parse(paramsString);
	LinkedList ltemp = params;
	while(!LL_isEmpty(l)) {
		VLH_setValue(ltemp, VLH_getValue(l));
		l = LL_getNext(l);
		ltemp = LL_getNext(ltemp);
	}
	LinkedList toEval = P_parse(sub);
	return E_eval(toEval, params, returns);
}

bool I_compare(void* a, void* b) {
	return ((((Identifier*)a)->id) > (((Identifier*)b)->id));
}

void* function(LinkedList l) {
	const char* name = VLH_getName(l);
	l = LL_getNext(l);
	const char* sign = VLH_getString(l);
	const char* params = VLH_getName(l);
	l = LL_getNext(l);
	const char* returns = VLH_getName(l);
	l = LL_getNext(l);
	const char* sub = VLH_getString(l);
	Identifier* I = I_create(name, sign, returns, call);
	I->standard = false;
	I->sub = sub;
	I->params = params;
	BBT_add(identifiers,I, I_compare);
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

int compare2(void* a, void* b) {
	int id = ((Identifier*)b)->id;
	int val = *((int*)a);
	if(val > id) {
		return 1;
	} else {
		if(val == id) {
			return 0;
		} else {
			return -1;
		}
	}
}

Identifier I_find(const char* name) {
	Identifier Id;
	Identifier* p_Id;
	int id = I_getID(name);
	p_Id = (Identifier*)BBT_find(identifiers, (void*)&id, compare2);
    if(p_Id == NULL) {
		Id.name = "NotFound";
	} else {
		Id = *p_Id;
	}	
	return Id;
}

Identifier* I_create(const char* name, const char* args, const char* returns, void* (*function)(LinkedList)) {
	Identifier* I = (Identifier*)malloc(sizeof(Identifier));
	I->id = I_getID(name);
	I->name = name;
	I->args = args;
	I->returns = returns;
	I->standard = true;
	I->function = function;
	return I;
}

Identifiers I_Identifiers() {
	Identifiers I;
	I = BBT_create((void*)I_create("add", "int int", "int", add), NULL, NULL);
	BBT_add(I,(void*)I_create("substract", "int int", "int", substract), I_compare);
	BBT_add(I,(void*)I_create("print", "string", "null", print), I_compare);
	BBT_add(I,(void*)I_create("function", "variable sign variable sub", "null", function), I_compare);

	return I;
}
