#include "Eval.h"
#include "Parse.h"
#include <string.h>

bool match(void* a, void* b) {
	if(strcmp(V_getName(*((Var*)a)), (char*)b)==0) {
		return true;
	}
	return false;
}

void trySubExpression(Type type, const char* expectedType, LinkedList l, LinkedList formalParameters, bool* valid) {
	if(T_equals("subexpression", type)) {
		Var* subRes = (Var*)malloc(sizeof(Var));
		LinkedList params = P_parse(VLH_getString(l));
		*subRes = E_eval(params, formalParameters);
		if(!V_isEmpty(*subRes)) {
			if(!T_equals(expectedType, V_getType(*subRes))) {
				printf("Wrong type in subexpression returns : %s\nres : %d\n", VLH_getString(l), *((int*)V_getValue(*subRes)));
				*valid = false;
			} else {
				void* value = LL_getValue(l);
				V_free(&value);
				LL_setValue(l, (void*)subRes);
			}
		}
		LL_free(&params, V_free);
	}

}

void tryVariable(Type type, const char* expectedType, LinkedList l, LinkedList formalParameters, bool* valid) {
	if(T_equals("variable", type)) {
		Var* varTmp;
		if(formalParameters != NULL) {
			varTmp = LL_find(formalParameters, VLH_getName(l), match);
			*valid = (varTmp!=NULL);
			if(*valid) {
				VLH_setType(l, V_getType(*varTmp));
				VLH_setValue(l, V_getValue(*varTmp));
			}
		}
	}
}

void E_checkAndEval(const char* args, LinkedList l, LinkedList formalParameters, bool* valid) {
	LinkedList sign;
	if(strcmp(args, "")==0) {
		sign = NULL;
	} else {
		sign = P_parse(args);
	}
	LinkedList signTmp = sign;
	char* signType;
	Type paramType;
	*valid = true;
	while(!LL_isEmpty(sign) && !LL_isEmpty(l) && *valid) {
		signType = VLH_getName(sign);
		paramType = VLH_getType(l);
		if(!T_equals(signType, paramType)) {
			trySubExpression(paramType, signType, l, formalParameters, valid);
			tryVariable(paramType, signType, l, formalParameters, valid);
			if(!(*valid)) {
				printf("Wrong types, expected : '%s', got : '%s' \n", signType, T_toString(paramType));
			}
		}
		l = LL_getNext(l);
		sign = LL_getNext(sign);
		/*printf("%s\n", signType);*/
	}
	if((LL_isEmpty(sign) && !LL_isEmpty(l)) || (!LL_isEmpty(sign) && LL_isEmpty(l))) {
		printf("Wrong number of arguments !\n");
		*valid = false;
	}
	LL_free(&signTmp, V_free);	
}

void printLL(LinkedList l) {
	while(!LL_isEmpty(l)) {
		V_print(*((Var*)LL_getValue(l)));
		l = LL_getNext(l);
	}
}

Var E_eval(LinkedList l, LinkedList formalParameters) {
	/*printLL(l);*/
	LinkedList lt = l;
	Var v;
	V_init(&v);
	Identifier act = I_find(VLH_getName(lt));
	bool valid = true;
	if(!(strcmp(act.name, "NotFound") == 0)) {
		lt = LL_getNext(lt);
		E_checkAndEval(act.args, lt, formalParameters, &valid);
		if(!act.standard) {
			LL_add(&lt, (void*)act.params);
			LL_add(&lt, (void*)act.sub);
		}
		if(strcmp(act.name, "if") == 0) {
			LL_add(&lt, (void*)formalParameters);
		}
		if(valid) {
			v = act.function(lt);
		}
	} else {
		printf("Unknown Identifier : '%s'\n", VLH_getName(l));
	}
	if(!act.standard) {
		free(LL_getNext(lt));
		free(lt);
		lt = NULL;
	}
	if(strcmp(act.name, "if")==0) {
		free(lt);
		lt = NULL;
	}
	/*printLL(l);*/
	return v;
}
