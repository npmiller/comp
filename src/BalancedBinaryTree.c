#include "BalancedBinaryTree.h"
#include <math.h>

#define max(A,B) ((A) > (B) ? (A) : (B))

BalancedBinaryTree BBT_create(void *value, BalancedBinaryTree leftBranch, BalancedBinaryTree rightBranch) {
	BalancedBinaryTree b = (BalancedBinaryTree)malloc(sizeof(Branch));
	b->value = value;
	b->leftBranch = leftBranch;
	b->rightBranch = rightBranch;
	return b;
}

bool BBT_isEmpty(BalancedBinaryTree b) {
	return (b==NULL);
}

void* BBT_getValue(BalancedBinaryTree b) {
	return b->value;
}

BalancedBinaryTree BBT_getLeftBranch(BalancedBinaryTree b) {
	return b->leftBranch;
}

BalancedBinaryTree BBT_getRightBranch(BalancedBinaryTree b) {
	return b->rightBranch;
}

void BBT_setValue(BalancedBinaryTree b, void* value) {
	b->value = value;
}

void BBT_setLeftBranch(BalancedBinaryTree b, BalancedBinaryTree lb) {
	b->leftBranch = lb;
}
	
void BBT_setRightBranch(BalancedBinaryTree b, BalancedBinaryTree rb) {
	b->rightBranch = rb;
}

int BBT_heigth(BalancedBinaryTree b, int currentHeigth) {
	if(BBT_isEmpty(b)) {
		return currentHeigth; 
	} else {
		return max(BBT_heigth(BBT_getLeftBranch(b), currentHeigth + 1), BBT_heigth(BBT_getRightBranch(b), currentHeigth + 1));
	}
}

/* Retourne 1 si déséquilibré à gauche, 2 si déséquilibré à droite, 0 sinon */
int BBT_isBalanced(BalancedBinaryTree b) {
	int lh = BBT_heigth(BBT_getLeftBranch(b), 0);
	int rh = BBT_heigth(BBT_getRightBranch(b), 0);
	if(rh > (1+lh)) {
		return 2;
	} else {
		if(lh > (1+rh)) {
			return 1;
		} else {
			return 0;
		}
	}
}

void BBT_add(BalancedBinaryTree b, void* value, bool (*compare)(void*, void*)) {
	if(compare(value, BBT_getValue(b))) {
		BalancedBinaryTree lb = BBT_getLeftBranch(b);
		if(BBT_isEmpty(lb)) {
			BBT_setLeftBranch(b, BBT_create(value, NULL, NULL));
		} else {
			BBT_add(lb, value, compare);
		}
	} else {
		BalancedBinaryTree rb = BBT_getRightBranch(b);
		if(BBT_isEmpty(rb)) {
			BBT_setRightBranch(b, BBT_create(value, NULL, NULL));
		} else {
			BBT_add(rb, value, compare);
		}
	}
}

void BBT_free(BalancedBinaryTree b, void (*freeValue)(void*)) {
	BalancedBinaryTree lb,rb;
	if(b!=NULL) {
		lb = BBT_getLeftBranch(b);
		rb = BBT_getRightBranch(b);
		freeValue(BBT_getValue(b));
		free(b);
		BBT_free(lb, freeValue);
		BBT_free(rb, freeValue);
	}
}


