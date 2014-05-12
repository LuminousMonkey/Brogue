/*
 * Utility Functions
 *
 * Copyright 2014. All rights reserved.
 *
 * Just various functions I'm not sure where to put yet.
 */

#include "utility.h"

boolean fileExists(const char *const restrict pathname) {
  FILE *openedFile;
  openedFile = fopen(pathname, "rb");
  if (openedFile) {
    fclose(openedFile);
    return true;
  } else {
    return false;
  }
}
