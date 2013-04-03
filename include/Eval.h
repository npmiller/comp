#ifndef EVAL_H
#define EVAL_H

#include <stdbool.h>

#include "LinkedList.h"
#include "Vars.h"
#include "Identifiers.h"

void* E_eval(LinkedList, Identifiers, char**);
void E_checkAndEval(const char*, LinkedList, Identifiers, bool*);
void E_printResult(const char*, void*);

#endif
