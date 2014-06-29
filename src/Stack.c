#include "Stack.h"
#include "LinkedList.h"
#include <stdlib.h>

bool S_isEmpty(Stack s) {
	return LL_isEmpty(s);
}

void S_push(Stack* s, void* v) {
	LL_add(s, v);
}

void* S_pop(Stack* s) {
	Stack head = *s;
	Stack new = LL_getNext(*s);
	*s = new;
	void* value = LL_getValue(head);
	free(head);
	return value;
}
