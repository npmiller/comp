#include "LinkedList.h"
#include <stdlib.h>

bool LL_isEmpty(LinkedList l) {
	return (l==NULL);
}

void LL_add(LinkedList* l, void* value) {
	LinkedList ltemp = NULL;
	if(LL_isEmpty(*l)) {
		*l = (LinkedList)malloc(sizeof(Node));
		(*l)->value = value;
		(*l)->next = NULL;
	} else {
		ltemp = *l;
		*l = (LinkedList)malloc(sizeof(Node));
		(*l)->value = value;
		(*l)->next = ltemp;
	}
}

void LL_free(LinkedList* l, void (*freeValue)(void*)) {
	LinkedList ltemp;
	while(!LL_isEmpty(*l)) {
		ltemp = (*l)->next;
		freeValue((*l)->value);
		free(*l);
		*l = ltemp;
	}
}

void LL_setNext(LinkedList l, LinkedList ln) {
	l->next = ln;
}

LinkedList LL_getNext(LinkedList l) {
	return l->next;
}

void* LL_getValue(LinkedList l) {
	return l->value;
}

void* LL_find(LinkedList l,void* val,  bool (*match)(void*, void*)) {
	while(!LL_isEmpty(l)) {
		if(match(LL_getValue(l), val)) {
			return LL_getValue(l);
		}
		l = LL_getNext(l);
	}
	return NULL;
}
