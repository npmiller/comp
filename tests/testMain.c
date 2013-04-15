#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "LinkedList_tests.h"

int main(int argc, char** argv){
  CU_pSuite LL_suite = NULL;

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout d'une suite de test */
  LL_suite = CU_add_suite("LinkedList", init_LL_suite_success, clean_LL_suite_success);
  if (NULL == LL_suite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite de tests boite noire */
  if ((NULL == CU_add_test(LL_suite, "LL_add", test_add))
		  || (NULL == CU_add_test(LL_suite, "LL_find", test_find))
		  || (NULL == CU_add_test(LL_suite, "LL_getNext", test_getNext))
		  || (NULL == CU_add_test(LL_suite, "LL_getValue", test_getValue))
		  || (NULL == CU_add_test(LL_suite, "LL_setNext", test_setNext))
		  || (NULL == CU_add_test(LL_suite, "LL_setValue", test_setValue))
		  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Lancement des tests */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  /* Nettoyage du registre */
  CU_cleanup_registry();
  return CU_get_error();
}
