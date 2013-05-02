#include "Parse.h"
#include "Parse_tests.h"
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>

int clean_P_suite_success(void) {
	return EXIT_SUCCESS;
}

int init_P_suite_success(void) {
	return EXIT_SUCCESS;
}
void P_matchingBracket_test(void) {
	const char* a = "(defkjv 4  + 5s4)   45 65 645 ";
	int pos = 0;
	char* res = P_matchingBracket(a, '(', ')', &pos);

	CU_ASSERT_STRING_EQUAL(res, "(defkjv 4  + 5s4");
	CU_ASSERT_EQUAL(pos, 17);
	CU_ASSERT_STRING_EQUAL(a, "(defkjv 4  + 5s4)   45 65 645 ");	
}
