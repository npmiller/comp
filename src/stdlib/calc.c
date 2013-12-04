#include "stdlib/calc.h"

void use_calc(Identifiers* I) {
	BBT_add(I,(void*)I_create("+", "number number", add), I_compare);
	BBT_add(I,(void*)I_create("-", "number number", substract), I_compare);
	BBT_add(I,(void*)I_create("*", "number number", multiply), I_compare);
}

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

