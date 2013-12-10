/*
 * Map tests
 *
 * Copyright 2013. All rights reserved.
 *
 * Unit tests for map related functions.
 */

#include <CUnit/CUnit.h>

/* Including the C file itself to get static functions. */
#include "../../brogue/map.c"

void testCoordinatesAreInMap() {
  CU_ASSERT_TRUE(coordinatesAreInMap(0, 0));
  CU_ASSERT_TRUE(coordinatesAreInMap(DCOLS / 2, DROWS / 2));
  CU_ASSERT_TRUE(coordinatesAreInMap(DCOLS - 1, DROWS - 1));

  CU_ASSERT_FALSE(coordinatesAreInMap(-1, 0));
  CU_ASSERT_FALSE(coordinatesAreInMap(0, -1));
  CU_ASSERT_FALSE(coordinatesAreInMap(-1, -1));
  CU_ASSERT_FALSE(coordinatesAreInMap(DCOLS, 0));
  CU_ASSERT_FALSE(coordinatesAreInMap(0, DROWS));
  CU_ASSERT_FALSE(coordinatesAreInMap(DCOLS, DROWS));
}
