#ifndef STDLIB_CTRL_H
#define STDLIB_CTRL_H

#include <stdlib.h>
#include <stdbool.h>

#include "LinkedList.h"
#include "Vars.h"
#include "Identifiers.h"
#include "BalancedBinaryTree.h"
#include "Eval.h"

void use_ctrl(Identifiers*);

Var function(LinkedList);
Var my_exit(LinkedList);
Var my_if(LinkedList);
Var equals(LinkedList);
Var my_return(LinkedList);
Var call(LinkedList);

#endif
