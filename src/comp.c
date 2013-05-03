#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "Parse.h"
#include "Vars.h"
#include "LinkedList.h"
#include "Identifiers.h"
#include "Eval.h"
#include "Type.h"

void printResult(Var v) {
	Type t = V_getType(v);
	if(t!=NONE) {
		switch(t) {
			case NUMBER :
				printf("%d\n", *((int*)V_getValue(v)));
				break;
			case STRING :
				printf("%s\n", (char*)V_getValue(v));
				break;
			case BOOLEAN :
				printf("%s\n", (char*)V_getValue(v));
				break;
			default :
				printf("Erreur, retour non affichable : %s\n", T_toString(t));
		}
	}
}

void process(char *a) {
	LinkedList l;
	Var res;
	l = P_parse(a);
	res = E_eval(l, NULL);
	printResult(res);
	/*printf("----------------- Process ------------------------\n");*/
	/*printLL(l);*/
	free(V_getValue(res));
	LL_free(&l, V_free);
	/*printf("%d\n", *((int*)((Var*)(l->value))->value));*/
}

int main() {
	char *a;	
	identifiers = I_Identifiers();
	while(true) {
		a = readline("> ");
		add_history(a);
		process(a);
		free(a);
	}
	return EXIT_SUCCESS;
}
