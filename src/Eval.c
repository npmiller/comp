#include "Eval.h"
#include "Parse.h"
#include <string.h>

void E_checkAndEval(const char* args, LinkedList l, Identifiers I) {
	static int calls = 0;
	calls++;
	/*printf("%d\n", calls);*/
	/*printf("%s\n", args);*/
	LinkedList sign = P_parse(args);
	char* signType;
	char* paramType;
	void* subRes;
	char** returns = (char**)malloc(sizeof(char**));
	while(!LL_isEmpty(sign) && !LL_isEmpty(l)) {
		signType = (char*)(((Var*)sign->value)->name);
		paramType = (char*)(((Var*)l->value)->type);
		if(!(strcmp(signType,paramType) == 0)) {
			if((strcmp(paramType,"sub")==0)) {
				subRes = E_eval(P_parse(VLH_getString(l)), I, returns);
				if(!strcmp(signType,(const char*) *returns)==0) {
					printf("Wrong type in subexpression returns !\n");
					exit(1);
				}
				((Var*)(l->value))->type = (const char*) *returns;
				((Var*)(l->value))->value = subRes;
			} else {
				printf("Wrong types !\n");
				printf("%s:%s\n", signType, paramType);
				exit(1);
			}
		}
		l = LL_getNext(l);
		sign = LL_getNext(sign);
		/*printf("%s\n", signType);*/
	}
	if((LL_isEmpty(sign) && !LL_isEmpty(l)) || (!LL_isEmpty(sign) && LL_isEmpty(l))) {
		printf("Wrong number of arguments !\n");
		exit(1);
	}	
}

void* E_eval(LinkedList l, Identifiers I, char** returns) {
	LinkedList lt = l;
	void* res;
	Identifier act = I_find(((Var*)LL_getValue(l))->name, I);
	lt = LL_getNext(l);
	E_checkAndEval(act.args, lt, I);
	res = act.function(lt);
	*returns = (char*)malloc((strlen(act.returns)+1) * sizeof(char));
	strcpy(*returns, act.returns);
	return res;
	/*E_printResult(act.returns, res);*/
}

void E_printResult(const char* returns, void* result) {
	if(strcmp(returns,"int")==0) {
		printf("%d\n", *((int*)result));
	} else { 
		if(strcmp(returns, "string")==0) {
			printf("%s\n", (char*)result);
		}
	}
}
