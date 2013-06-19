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

void BBT_setRoot(BalancedBinaryTree* b, BalancedBinaryTree r) {
	*b = r;
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

void BBT_add(BalancedBinaryTree* b, void* value, bool (*compare)(void*, void*)) {
	BalancedBinaryTree lb, rb;
	if(BBT_isEmpty(*b)) {
		BBT_setRoot(b, BBT_create(value, NULL, NULL));
	} else {
		if(compare(value, BBT_getValue(*b))) {
			lb = BBT_getLeftBranch(*b);
			BBT_add(&lb, value, compare);
			BBT_setLeftBranch(*b, lb);
		} else {
			rb = BBT_getRightBranch(*b);
			BBT_add(&rb, value, compare);
			BBT_setRightBranch(*b, rb);
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

/* compare renvoie 0 si il s'agit de la valeur recherchée, 1 là ou le compare du add renvoyait vrai et -1 sinon */
void* BBT_find(BalancedBinaryTree b, void* value, int (*compare)(void*, void*)) {
	int c;
	while(!BBT_isEmpty(b)) {
		c = compare(value, BBT_getValue(b));
		switch(c) {
			case 0:
				return BBT_getValue(b);
				break;

			case 1:
				b = BBT_getLeftBranch(b);
				break;

			case -1:
				b = BBT_getRightBranch(b);
		}
	}
	return NULL;
}


