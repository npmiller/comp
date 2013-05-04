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


void process(char *a) {
	LinkedList l;
	Var res;
	l = P_parse(a);
	res = E_eval(l, NULL);
	V_print(res);
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
