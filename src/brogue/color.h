/*
 * Color
 *
 * Copyright 2013. All rights reserved.
 *
 * Basic structure for defining colors, possibly to move merged with
 * other graphics functions.
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "types.h"

typedef struct color {
    // base RGB components:
    short red;
    short green;
    short blue;

    // random RGB components to add to base components:
    short redRand;
    short greenRand;
    short blueRand;

    // random scalar to add to all components:
    short rand;

    // Flag: this color "dances" with every refresh:
    boolean colorDances;
} color;

#endif
