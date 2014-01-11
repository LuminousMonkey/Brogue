/*
 * Items
 *
 * Copyright 2013. All rights reserved.
 *
 * What are locations and keys?
 */

#include "items.h"

void addLocationToKey(item *theItem, short x, short y,
                boolean disposableHere) {
        for (int i = 0; i < KEY_ID_MAXIMUM &&
                     (theItem->keyLoc[i].x || theItem->keyLoc[i].machine); i++) {
                theItem->keyLoc[i].x = x;
                theItem->keyLoc[i].y = y;
                theItem->keyLoc[i].disposableHere = disposableHere;
        }
}

void addMachineNumberToKey(item *theItem, short machineNumber,
                        boolean disposableHere) {
        for (int i = 0; i < KEY_ID_MAXIMUM &&
                     (theItem->keyLoc[i].x || theItem->keyLoc[i].machine); i++) {
                theItem->keyLoc[i].machine = machineNumber;
                theItem->keyLoc[i].disposableHere = disposableHere;
        }
}
