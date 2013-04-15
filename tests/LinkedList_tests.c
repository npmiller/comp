#include "LinkedList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>

int init_LL_suite_success(void) {
	return 0;
}

int clean_LL_suite_success(void) {
	return 0;
}

void test_add(void) {
	LinkedList l = NULL;
	LinkedList ltemp;
	char* a = "sdfghjklm";
	LL_add(&l, a);
	CU_ASSERT_PTR_NULL(l->next);
	CU_ASSERT_STRING_EQUAL((char*)l->value, a);

	char *b = "azerty";
	ltemp = l;
	LL_add(&l, b);
	CU_ASSERT_PTR_EQUAL(l->next, ltemp);
	CU_ASSERT_STRING_EQUAL((char*)l->value, b);
}

void test_getValue(void) {
	LinkedList l = NULL;
	char* a = "sdfghjklm";
	LL_add(&l, a);
	CU_ASSERT_STRING_EQUAL((char*)LL_getValue(l), a);
}


void test_getNext(void) {
	LinkedList l = NULL;
	LinkedList ltemp;
	char* a = "sdfghjklm";
	LL_add(&l, a);
	ltemp = l;
	LL_add(&l, a);
	CU_ASSERT_PTR_EQUAL(ltemp, LL_getNext(l));
}

void test_setValue(void) {
	LinkedList l = NULL;
	char* a = "sdfghjklm";
	LL_add(&l, a);
	LL_setValue(l, (void*)"coucou");
	CU_ASSERT_STRING_EQUAL((char*)LL_getValue(l), "coucou");
}


void test_setNext(void) {
	LinkedList l = NULL;
	LinkedList ltemp;
	char* a = "sdfghjklm";
	LL_add(&ltemp, a);
	LL_add(&l, a);
	LL_setNext(l, ltemp);
	CU_ASSERT_PTR_EQUAL(ltemp, LL_getNext(l));
}

bool match(void* a, void* b) {
	if(strcmp(a, b) == 0) {
		return true;
	}
	return false;
}

void test_find(void) {
	LinkedList l = NULL;
	LL_add(&l, "a");
	LL_add(&l, "b");
	LL_add(&l, "c");
	CU_ASSERT_STRING_EQUAL("b", LL_find(l, "b", match));
	CU_ASSERT_PTR_NULL(LL_find(l, "d", match));
}

