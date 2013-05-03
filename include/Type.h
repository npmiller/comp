#ifndef TYPE_H
#define TYPE_H

#include <stdbool.h>
#include <string.h>

typedef enum { STRING, NUMBER, BOOLEAN, NONE, SUBEXPRESSION, SIGNATURE, VARIABLE } Type;

bool T_equals(const char*, Type);
char* T_toString(Type);
void* TV_copyVarValue(void* src); 

#endif
