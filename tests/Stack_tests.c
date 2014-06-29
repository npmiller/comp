#include "Stack.h"
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>

int init_S_suite_success(void) {
	return 0;
}

int clean_S_suite_success(void) {
	return 0;
}

void test_push(void) {
	Stack s = NULL;
	Stack stemp;
	char* a = "sdfghjklm";
	S_push(&s, a);
	CU_ASSERT_PTR_NULL(s->next);
	CU_ASSERT_STRING_EQUAL((char*)s->value, a);

	char *b = "azerty";
	stemp = s;
	S_push(&s, b);
	CU_ASSERT_PTR_EQUAL(s->next, stemp);
	CU_ASSERT_STRING_EQUAL((char*)s->value, b);
}

void test_pop(void) {
	Stack s = NULL;
	Stack scomp;
	char* a = "sdfghjklm";
	char* b = "azerty";
	char* res;
	S_push(&s, a);
	scomp = s;
	S_push(&s, b);
	res = (char*)S_pop(&s);
	CU_ASSERT_STRING_EQUAL(res, b);
	CU_ASSERT_PTR_EQUAL(s, scomp);
	res = (char*)S_pop(&s);
	CU_ASSERT_STRING_EQUAL(res, a);
	CU_ASSERT_PTR_EQUAL(s, NULL);
}

