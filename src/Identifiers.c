#include "Identifiers.h"
#include <string.h>


Var add(LinkedList l) {
	Var vRes;
	V_init(&vRes);
	int a = VLH_getInt(l);
	l = LL_getNext(l);
	int b = VLH_getInt(l);
	V_setType(&vRes, NUMBER);
	int* res = (int*)malloc(sizeof(int));
	*res = a + b;
	V_setValue(&vRes, (void*)res);
	return vRes;
}

Var substract(LinkedList l) {
	Var vRes;
	V_init(&vRes);
	int a = VLH_getInt(l);
	l = LL_getNext(l);
	int b = VLH_getInt(l);
	int* res = (int*)malloc(sizeof(int));
	*res = a - b;
	V_setType(&vRes, NUMBER);
	V_setValue(&vRes, (void*)res);
	return vRes;
}

Var print(LinkedList l) {
	Var v;
	V_init(&v);
	char* res = VLH_getString(l);
	printf("%s\n", res);
	return v;
}

Var call(LinkedList l) {
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
	return E_eval(toEval, params);
}

bool I_compare(void* a, void* b) {
	return ((((Identifier*)a)->id) > (((Identifier*)b)->id));
}

Var function(LinkedList l) {
	Var v;
	V_init(&v);
	const char* name = VLH_getName(l);
	char* namecp = (char*)malloc((strlen(name)+1)*sizeof(char));
	strcpy(namecp, name);
	l = LL_getNext(l);
	const char* sign = VLH_getString(l);
	char* signcp = (char*)malloc((strlen(sign)+1)*sizeof(char));
	strcpy(signcp, sign);
	const char* params = VLH_getName(l);
	char* paramscp = (char*)malloc((strlen(params)+1)*sizeof(char));
	strcpy(paramscp, params);
	l = LL_getNext(l);
	const char* sub = VLH_getString(l);
	char* subcp = (char*)malloc((strlen(sub)+1)*sizeof(char));
	strcpy(subcp, sub);
	Identifier* I = I_create(namecp, signcp, call);
	I->standard = false;
	I->sub = subcp;
	I->params = paramscp;
	BBT_add(identifiers, I, I_compare);
	return v;
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

Identifier* I_create(const char* name, const char* args, Var (*function)(LinkedList)) {
	Identifier* I = (Identifier*)malloc(sizeof(Identifier));
	I->id = I_getID(name);
	I->name = name;
	I->args = args;
	I->standard = true;
	I->function = function;
	I->sub = NULL;
	I->params = NULL;
	return I;
}

Identifiers I_Identifiers() {
	Identifiers I;
	I = BBT_create((void*)I_create("add", "number number", add), NULL, NULL);
	BBT_add(I,(void*)I_create("substract", "number number", substract), I_compare);
	BBT_add(I,(void*)I_create("print", "string", print), I_compare);
	BBT_add(I,(void*)I_create("function", "variable signature subexpression", function), I_compare);

	return I;
}
