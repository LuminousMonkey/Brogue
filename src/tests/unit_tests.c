/*
 * Unit Test Runner
 *
 * Copyright 2013. All rights reserved.
 *
 * CUnit based test runner.
 */

#include <CUnit/Basic.h>

#include "brogue/map_test.h"

int main() {
  CU_pSuite pMapSuite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  pMapSuite = CU_add_suite("Map Tests", NULL, NULL);

  if (NULL == pMapSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pMapSuite, "Test Coordinate Limits",
                          testCoordinatesAreInMap)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
