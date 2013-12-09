/*
 * Items
 *
 * Copyright 2013. All rights reserved.
 *
 * This file is not related to the original Items.c file.
 * Though in future refactorings it probably will be.
 */

#ifndef ITEMS_H_
#define ITEMS_H_

#include "defines.h"

enum itemCategory {
    FOOD = Fl(0),
    WEAPON = Fl(1),
    ARMOR = Fl(2),
    POTION = Fl(3),
    SCROLL = Fl(4),
    STAFF = Fl(5),
    WAND = Fl(6),
    RING = Fl(7),
    CHARM = Fl(8),
    GOLD = Fl(9),
    AMULET = Fl(10),
    GEM = Fl(11),
    KEY = Fl(12),

    CAN_BE_DETECTED = (WEAPON | ARMOR | POTION | SCROLL | RING | CHARM |
                       WAND | STAFF | AMULET),
    PRENAMED_CATEGORY = (FOOD | GOLD | AMULET | GEM | KEY),
    NEVER_IDENTIFIABLE = (FOOD | CHARM | GOLD | AMULET | GEM | KEY),
    COUNTS_TOWARD_SCORE = (GOLD | AMULET | GEM),
    ALL_ITEMS =  (FOOD | POTION | WEAPON | ARMOR | STAFF | WAND | SCROLL |
                  RING | CHARM | GOLD | AMULET | GEM | KEY),
};

#endif
