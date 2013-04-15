#ifndef EVAL_H
#define EVAL_H

#include <stdbool.h>

#include "LinkedList.h"
#include "Vars.h"
#include "Identifiers.h"
#include "Type.h"

Var E_eval(LinkedList, LinkedList);
void E_checkAndEval(const char*, LinkedList, LinkedList, bool*);
void E_printResult(const char*, void*);

#endif
