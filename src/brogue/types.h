/*
 * General Types
 *
 * Copyright 2013. All rights reserved.
 *
 * General system-wide types.
 *
 * Currently just used to hold types I don't know where to put that I
 * have to share between the original code and my refactored code.
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdbool.h>

/*
 * The original code uses "char" as the boolean type.
 * C99 provides "bool" from stdbool.h
 *
 * I can't test, since there are no unit tests at the moment, which is
 * what I'm trying to refactor to put in, but it shouldn't break
 * anything...
 *
 * TODO: Verify this doesn't break anything.
 */
#define boolean                 bool

/* For Unicode characters. */
#define uchar                   unsigned short

#endif
