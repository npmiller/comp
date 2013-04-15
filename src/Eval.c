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
		*subRes = E_eval(P_parse(VLH_getString(l)), formalParameters);
		if(!V_isEmpty(*subRes)) {
			if(!T_equals(expectedType, V_getType(*subRes))) {
				printf("Wrong type in subexpression returns : %s\nres : %d\n", VLH_getString(l), *((int*)V_getValue(*subRes)));
				*valid = false;
			} else {
				LL_setValue(l, (void*)subRes);
			}
		}
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
	LinkedList sign = P_parse(args);
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

Var E_eval(LinkedList l, LinkedList formalParameters) {
	LinkedList lt = l;
	Identifier act = I_find(VLH_getName(lt));
	bool valid = true;
	if(!(strcmp(act.name, "NotFound") == 0)) {
		lt = LL_getNext(lt);
		E_checkAndEval(act.args, lt, formalParameters, &valid);
		if(!act.standard) {
			LL_add(&lt, (void*)act.params);
			LL_add(&lt, (void*)act.sub);
		}
		if(valid) {
			return act.function(lt);
		} else {
			Var v;
			V_init(&v);
			return v;
		}
	} else {
		printf("Unknown Identifier : '%s'\n", VLH_getName(l));
		Var v;
		V_init(&v);
		return v;
	}
}

void tryPrintInt(const char* returns, void* result) {
	if(strcmp(returns,"int")==0) {
		printf("%d\n", *((int*)result));
	}
}

void tryPrintString(const char* returns, void* result) {
	if(strcmp(returns, "string")==0) {
		printf("%s\n", (char*)result);
	}
}

void E_printResult(const char* returns, void* result) {
	if(result != NULL) {
		tryPrintString(returns, result);
		tryPrintInt(returns, result);
	}
}
