#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

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
			default :
				printf("Erreur, retour non affichable (subexpression, variable, signature)");
		}
	}
}

void process(char *a) {
	LinkedList l;
	Var res;
	l = P_parse(a);
	res = E_eval(l, NULL);
	printResult(res);
	/*printf("%d\n", *((int*)((Var*)(l->value))->value));*/
}

int main() {
	char *a;	
	identifiers = I_Identifiers();
	while(true) {
		a = readline("> ");
		process(a);
		free(a);
	}
	return EXIT_SUCCESS;
}
