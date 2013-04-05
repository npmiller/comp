#include "Eval.h"
#include "Parse.h"
#include <string.h>

bool match(void* a, void* b) {
   if(strcmp((char*)b,(char*)((Var*)a)->value)) {
	   return true;
   }
   return false;
}

void E_checkAndEval(const char* args, LinkedList l, LinkedList formalParameters, bool* valid) {
	LinkedList sign = P_parse(args);
	Var* varTmp;
	char* signType;
	char* paramType;
	void* subRes;
	char** returns = (char**)malloc(sizeof(char**));
	while(!LL_isEmpty(sign) && !LL_isEmpty(l) && *valid) {
		signType = VLH_getName(sign);
		paramType = VLH_getType(l);
		if(!(strcmp(signType,paramType) == 0)) {
			if((strcmp(paramType,"sub")==0)) {
				subRes = E_eval(P_parse(VLH_getString(l)), formalParameters, returns);
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
				if((strcmp(paramType, "variable")==0)) {
					if(formalParameters != NULL) {
						varTmp = LL_find(formalParameters, VLH_getName(l), match);
						if(varTmp==NULL) {
							*valid = false;
						}
						VLH_setType(l, signType);
						VLH_setValue(l, varTmp->value);
					}
				} else {
					printf("Wrong types, expected : %s, got : %s \n", signType, paramType);
					*valid = false;
				}
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

void* E_eval(LinkedList l, LinkedList formalParameters, char** returns) {
	LinkedList lt = l;
	void* res;
	Identifier act = I_find(VLH_getName(l));
	bool valid = true;
	if(!(strcmp(act.name, "NotFound") == 0)) {
		lt = LL_getNext(l);
		E_checkAndEval(act.args, lt, formalParameters, &valid);
		if(!act.standard) {
			LL_add(&lt, act.params);
			LL_add(&lt, act.sub);
		}
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
