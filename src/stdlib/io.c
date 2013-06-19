#include "stdlib/io.h"

void use_io(Identifiers* I) {
	BBT_add(I,(void*)I_create("print", "any", print), I_compare);
}

Var print(LinkedList l) {
	Var v;
	V_init(&v);
	Var res = VLH_getVar(l);
	V_print(res);
	return v;
}

