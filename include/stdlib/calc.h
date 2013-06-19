#ifndef STDLIB_CALC_H
#define STDLIB_CALC_H

#include <stdlib.h>

#include "LinkedList.h"
#include "Vars.h"
#include "Identifiers.h"
#include "BalancedBinaryTree.h"

void use_calc(Identifiers*);

Var add(LinkedList);
Var substract(LinkedList);
Var multiply(LinkedList);

#endif
