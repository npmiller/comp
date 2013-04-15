#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

#include "Parse.h"
#include "Vars.h"
#include "LinkedList.h"
#include "Identifiers.h"
#include "Eval.h"

void process(char *a) {
	LinkedList l;
	char** returns = (char**)malloc(sizeof(char*));
	void* res;
	l = P_parse(a);
	res = E_eval(l, NULL, returns);
	if(res != NULL) {
		E_printResult(*returns, res);
	}
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
