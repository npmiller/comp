#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

typedef LinkedList Stack;

bool S_isEmpty(Stack);
void S_push(Stack*, void*);
void* S_pop(Stack*);


#endif
