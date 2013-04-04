#include "Eval.h"
#include "Parse.h"
#include <string.h>

void E_checkAndEval(const char* args, LinkedList l, Identifiers I, bool* valid) {
	static int calls = 0;
	calls++;
	/*printf("%d\n", calls);*/
	/*printf("%s\n", args);*/
	*valid = true;
	LinkedList sign = P_parse(args);
	char* signType;
	char* paramType;
	void* subRes;
	char** returns = (char**)malloc(sizeof(char**));
	while(!LL_isEmpty(sign) && !LL_isEmpty(l) && *valid) {
		signType = VLH_getName(sign);
		paramType = VLH_getType(l);
		if(!(strcmp(signType,paramType) == 0)) {
			if((strcmp(paramType,"sub")==0)) {
				subRes = E_eval(P_parse(VLH_getString(l)), I, returns);
				if(subRes!=NULL) {
					if(!strcmp(signType,(const char*) *returns)==0) {
						printf("Wrong type in subexpression returns !\n");
						*valid = false;
					} else {
						VLH_setType(l, (const char*) *returns);
						VLH_setValue(l, subRes);
					}
				}
			} else {
				printf("Wrong types, expected : %s, got : %s \n", signType, paramType);
				*valid = false;
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
}

void* E_eval(LinkedList l, Identifiers I, char** returns) {
	LinkedList lt = l;
	void* res;
	Identifier act = I_find(VLH_getName(l), I);
	bool valid;
	if(!(strcmp(act.id, "NotFound") == 0)) {
		lt = LL_getNext(l);
		E_checkAndEval(act.args, lt, I, &valid);
		if(valid) {
			res = act.function(lt);
			*returns = (char*)malloc((strlen(act.returns)+1) * sizeof(char));
			strcpy(*returns, act.returns);
			return res;
		} else {
			return NULL;
		}
	} else {
		printf("Unknown Identifier : '%s'\n", VLH_getName(l));
		return NULL;
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
