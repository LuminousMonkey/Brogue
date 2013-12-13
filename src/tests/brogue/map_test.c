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

void testCopyFunctions() {
  struct pcell test_pmap[DCOLS][DROWS];
  struct pcell test_dest[DCOLS][DROWS];

  /* Clear out everything. */
  clearLevel(test_pmap);

  copyMap(test_dest, test_pmap, true);

  CU_ASSERT_EQUAL(memcmp(test_pmap, test_dest, sizeof(struct pcell) * DCOLS * DROWS), 0);

  /*
   * The different between copyMap and copyMapWithLayers is that
   * copyMapWithLayers only keeps PERMANENT_TILE_FLAGS.
   *
   * IS_POWERED is not in PERMANENT_TILE_FLAGS.
   */
  test_pmap[0][0].flags = DISCOVERED | IS_POWERED;

  copyMap(test_dest, test_pmap, true);

  CU_ASSERT_NOT_EQUAL(memcmp(test_pmap, test_dest, sizeof(struct pcell) * DCOLS * DROWS), 0);
  CU_ASSERT_EQUAL(test_dest[0][0].flags, DISCOVERED);

  /* copyMap should copy the whole thing without modification. */
  copyMap(test_dest, test_pmap, false);

  CU_ASSERT_EQUAL(memcmp(test_pmap, test_dest, sizeof(struct pcell) * DCOLS * DROWS), 0);
}
