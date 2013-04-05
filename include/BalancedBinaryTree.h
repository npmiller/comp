#ifndef BALANCED_BINARY_TREE_H
#define BALANCED_BINARY_TREE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct Branch {
	void* value;
	struct Branch* leftBranch;
	struct Branch* rightBranch;
} Branch; 

typedef Branch* BalancedBinaryTree;

BalancedBinaryTree BBT_create(void*, BalancedBinaryTree, BalancedBinaryTree);
bool BBT_isEmpty(BalancedBinaryTree);
BalancedBinaryTree BBT_getLeftBranch(BalancedBinaryTree);
BalancedBinaryTree BBT_getRightBranch(BalancedBinaryTree);
void* BBT_getValue(BalancedBinaryTree);
void BBT_setRightBranch(BalancedBinaryTree, BalancedBinaryTree);
void BBT_setLeftBranch(BalancedBinaryTree, BalancedBinaryTree);
void BBT_setValue(BalancedBinaryTree, void*);
void BBT_free(BalancedBinaryTree, void (*)(void*));
void BBT_add(BalancedBinaryTree, void*, bool (*)(void*, void*));
int BBT_isBalanced(BalancedBinaryTree);
int BBT_heigth(BalancedBinaryTree, int);

void* BBT_find(BalancedBinaryTree, void*, int (*)(void*, void*));
#endif
