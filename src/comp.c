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
#include "stdlib/ctrl.h"
#include "stdlib/calc.h"
#include "stdlib/io.h"
#include "stdlib/string.h"


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

Identifiers identifiers = NULL;

int main() {
	use_ctrl(&identifiers);
	use_calc(&identifiers);
	use_io(&identifiers);
	use_string(&identifiers);

	char *a;
	int pos = 0;
	while(true) {
		a = readline("> ");
		if(a != NULL) {
			discardBlankChars(a, &pos);
			if(pos != strlen(a)) {
				add_history(a);
				process(a);
			}
			free(a);
		} else { 
			free(a);
			BBT_free(identifiers, I_free);
			return EXIT_SUCCESS;
		}
	}
	return EXIT_SUCCESS;
}
