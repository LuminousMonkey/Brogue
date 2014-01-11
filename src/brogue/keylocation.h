/*
 * Key Location
 *
 * Copyright 2014. All rights reserved.
 *
 * Key location structure.
 */

#ifndef KEYLOCATION_H_
#define KEYLOCATION_H_

#include "types.h"

#define KEY_ID_MAXIMUM  20

typedef struct keyLocationProfile {
        short x;
        short y;
        short machine;
        boolean disposableHere;
} keyLocationProfile;

#endif
