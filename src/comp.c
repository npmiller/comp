#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

#include "Parse.h"
#include "Vars.h"
#include "LinkedList.h"
#include "Identifiers.h"
#include "Eval.h"

/*void printArgs(Operation op) {*/
	/*Link l = op.params;*/
	/*while(l!=NULL) {*/
		/*printf("%s\n", l->value);*/
		/*l = l->next;*/
	/*}*/
/*}*/

void process(char *a) {
	LinkedList l;
	char** returns = (char**)malloc(sizeof(char*));
	void* res;
	l = P_parse(a);
	Identifiers Is;
	Is = I_Identifiers();
	res = E_eval(l, Is, returns);
	E_printResult(*returns, res);
	/*printf("%d\n", *((int*)((Var*)(l->value))->value));*/
}

int main() {
	char *a;	
	while(true) {
		a = readline("> ");
		process(a);
	}
	free(a);
	return EXIT_SUCCESS;
}
