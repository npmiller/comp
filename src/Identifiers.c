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

Var multiply(LinkedList l) {
	Var vRes;
	V_init(&vRes);
	int a = VLH_getInt(l);
	l = LL_getNext(l);
	int b = VLH_getInt(l);
	int* res = (int*)malloc(sizeof(int));
	*res = a * b;
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

void V_free_name(void** v) {
	free((void*)((*(Var**)v))->name);
	free(*v);
	*v = NULL;
}

Var call(LinkedList l) {
	Var result;
	V_init(&result);
	LinkedList ltemp;
	const char* sub = (const char*)LL_getValue(l);
	ltemp = l;
	l = LL_getNext(l);
	free(ltemp);
	const char* paramsString = (const char*)LL_getValue(l);
	ltemp = l;
	l = LL_getNext(l);
	free(ltemp);
	LinkedList params = P_parse(paramsString);
	ltemp = params;
	while(!LL_isEmpty(l)) {
		VLH_setValue(ltemp, VLH_getValue(l));
		l = LL_getNext(l);
		ltemp = LL_getNext(ltemp);
	}
	LinkedList toEval = P_parse(sub);
	result = E_eval(toEval, params);
	LL_free(&toEval, V_free);
	LL_free(&params, V_free_name);
	return result;
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

void I_free(void* i) {
	Identifier* I = (Identifier*)i;

	if(I->standard) {
		free(i);
	} else {
		free((void*)I->name);
		free((void*)I->params);
		free((void*)I->sub);
		free((void*)I->args);
		free(i);
	}
}

Var my_exit(LinkedList l) {
	BBT_free(identifiers, I_free);
	exit(0);
}

Var my_if(LinkedList l) {
	LinkedList formalParameters = LL_getValue(l);
	l = LL_getNext(l);
	const char* boolean = VLH_getString(l);
	l = LL_getNext(l);
	const char* sub1 = VLH_getString(l);
	l = LL_getNext(l);
	const char* sub2 = VLH_getString(l);
	if(strcmp(boolean, "true")==0) {
		return E_eval(P_parse(sub1), formalParameters);
	} else {
		return E_eval(P_parse(sub2), formalParameters);
	}
}

Var equals(LinkedList l) {
	Var v;
	V_init(&v);
	v.type = BOOLEAN;
	int a,b;
	a = VLH_getInt(l);
	l = LL_getNext(l);
	b = VLH_getInt(l);
	if(a == b) {
		v.value = (char*)malloc(sizeof(char)*5);
		strcpy(v.value, "true");
	} else {
		v.value = (char*)malloc(sizeof(char)*6);
		strcpy(v.value, "false");
	}
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
	BBT_add(I,(void*)I_create("exit", "", my_exit), I_compare);
	BBT_add(I,(void*)I_create("if", "boolean subexpression subexpression", my_if), I_compare);
	BBT_add(I,(void*)I_create("equals", "number number", equals), I_compare);
	BBT_add(I,(void*)I_create("multiply", "number number", multiply), I_compare);

	return I;
}
