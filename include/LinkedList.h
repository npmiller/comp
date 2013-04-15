#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct Node {
	void* value;
	struct Node* next;
} Node;

typedef Node* LinkedList;

LinkedList LL_getNext(LinkedList);
void* LL_getValue(LinkedList);
void LL_setNext(LinkedList, LinkedList);
void LL_setValue(LinkedList, void*);

bool LL_isEmpty(LinkedList);

void LL_add(LinkedList*, void*);
void LL_free(LinkedList*, void (*freeValue)(void*));

void* LL_find(LinkedList, void*,  bool (*)(void*, void*));

#endif
