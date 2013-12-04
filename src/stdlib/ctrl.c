#include "stdlib/ctrl.h"

void use_ctrl(Identifiers* I) {
	BBT_add(I,(void*)I_create("return", "any", my_return), I_compare);
	BBT_add(I,(void*)I_create("function", "variable signature subexpression", function), I_compare);
	BBT_add(I,(void*)I_create("exit", "", my_exit), I_compare);
	BBT_add(I,(void*)I_create("if", "boolean subexpression subexpression", my_if), I_compare);
	BBT_add(I,(void*)I_create("=", "any any", equals), I_compare);
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
	BBT_add(&identifiers, I, I_compare);
	return v;
}

Var my_exit(LinkedList l) {
	BBT_free(identifiers, I_free);
	exit(0);
}

Var my_if(LinkedList l) {
	LinkedList formalParameters = LL_getValue(l);
	l = LL_getNext(l);
	bool boolean = VLH_getBool(l);
	l = LL_getNext(l);
	const char* sub1 = VLH_getString(l);
	l = LL_getNext(l);
	const char* sub2 = VLH_getString(l);
	LinkedList toEval = NULL;
	Var res;
	V_init(&res);
	if(boolean) {
		toEval = P_parse(sub1);
		res = E_eval(toEval, formalParameters);
		LL_free(&toEval, V_free);
	} else {
		toEval = P_parse(sub2);
		res = E_eval(toEval, formalParameters);
		LL_free(&toEval, V_free);
	}
	return res;
}

Var equals(LinkedList l) {
	Var v;
	V_init(&v);
	v.type = BOOLEAN;
	v.value = (bool*)malloc(sizeof(bool));
	Var a,b;
	a = VLH_getVar(l);
	l = LL_getNext(l);
	b = VLH_getVar(l);
	if(V_getType(a) == V_getType(b)) {
		switch(V_getType(a)) {
			case NUMBER :
				*((bool*)v.value) = (*((int*)V_getValue(a)) == *((int*)V_getValue(b)));
				break;
			case BOOLEAN :
				*((bool*)v.value) = (*((bool*)V_getValue(a)) == *((bool*)V_getValue(b)));
				break;
			case STRING :
				*((bool*)v.value) = (strcmp((char*)V_getValue(a), (char*)V_getValue(b))==0);
				break;
			case SIGNATURE :
				*((bool*)v.value) = (strcmp((char*)V_getValue(a), (char*)V_getValue(b))==0);
				break;
			default:
				*((bool*)v.value) = false;
		}
	} else {
		*((bool*)v.value) = false;
	}
	return v;
}

Var my_return(LinkedList l) {
	Var res;
	V_init(&res);
	V_setType(&res, VLH_getType(l));
	V_setValue(&res, V_copyValue(VLH_getValue(l), VLH_getType(l)));
	return res;
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
		VLH_setVType(ltemp, VLH_getType(l));
		l = LL_getNext(l);
		ltemp = LL_getNext(ltemp);
	}
	LinkedList toEval = P_parse(sub);
	result = E_eval(toEval, params);
	/*printf("------------------------- Call -------------------\n");*/
	/*printLL(toEval);*/
	LL_free(&toEval, V_free);
	LL_free(&params, V_free_name);
	return result;
}

