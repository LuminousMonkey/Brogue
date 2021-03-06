/*
 * Map Functions
 *
 * Copyright 2013. All rights reserved.
 *
 * All map related operations should go in here.
 */

#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "tiles.h"

bool coordinatesAreInMap(const short x, const short y)
{
  return (x >= 0 && x < DCOLS && y >= 0 && y < DROWS);
}

/*
 * Clears out the level of the map.
 */
void clearLevel(struct pcell pmap[DCOLS][DROWS])
{
  if (pmap != NULL) {
    memset(pmap, 0, sizeof(struct pcell) * DCOLS * DROWS);
    for (int columnIdx = 0; columnIdx < DCOLS; ++columnIdx) {
      for (int rowIdx = 0; rowIdx < DROWS; ++rowIdx) {
        pmap[columnIdx][rowIdx].layers[DUNGEON] = GRANITE;
      }
    }
  }
}

void copyMap(struct pcell to[DCOLS][DROWS],
             struct pcell from[DCOLS][DROWS],
             boolean permanentFlagsOnly)
{
  for (int columnIdx = 0; columnIdx < DCOLS; ++columnIdx) {
    for (int rowIdx = 0; rowIdx < DROWS; ++rowIdx) {
      to[columnIdx][rowIdx] = from[columnIdx][rowIdx];

      if (permanentFlagsOnly) {
        to[columnIdx][rowIdx].flags =
            (from[columnIdx][rowIdx].flags & PERMANENT_TILE_FLAGS);
      }
    }
  }
}

/*
 * Given the x and y coordinate, checks the permanent map and returns
 * true if cell at the coordinates is considered to be in a terrain
 * loop.
 *
 * TDOD: Figure out what this does.
 * TODO: What is a terrain loop?
 * TODO: Remove magic numbers in parameters.
 */
bool checkLoopiness(struct pcell pmap[DCOLS][DROWS],
                    const short x, const short y,
                    const short cDirs[8][2])
{
  bool inString;
  short newX, newY, dir, sdir;
  short numStrings, maxStringLength, currentStringLength;

  if (!(pmap[x][y].flags & IN_LOOP)) {
    return false;
  }

  // find an unloopy neighbor to start on
  for (sdir = 0; sdir < 8; sdir++) {
    newX = x + cDirs[sdir][0];
    newY = y + cDirs[sdir][1];
    if (!coordinatesAreInMap(newX, newY)
        || !(pmap[newX][newY].flags & IN_LOOP)) {
      break;
    }
  }
  if (sdir == 8) { // no unloopy neighbors
    return false; // leave cell loopy
  }

  // starting on this unloopy neighbor, work clockwise and count up (a) the number of strings
  // of loopy neighbors, and (b) the length of the longest such string.
  numStrings = maxStringLength = currentStringLength = 0;
  inString = false;
  for (dir = sdir; dir < sdir + 8; dir++) {
    newX = x + cDirs[dir % 8][0];
    newY = y + cDirs[dir % 8][1];
    if (coordinatesAreInMap(newX, newY) && (pmap[newX][newY].flags & IN_LOOP)) {
      currentStringLength++;
      if (!inString) {
        if (numStrings > 0) {
          return false; // more than one string here; leave loopy
        }
        numStrings++;
        inString = true;
      }
    } else if (inString) {
      if (currentStringLength > maxStringLength) {
        maxStringLength = currentStringLength;
      }
      currentStringLength = 0;
      inString = false;
    }
  }
  if (inString && currentStringLength > maxStringLength) {
    maxStringLength = currentStringLength;
  }
  if (numStrings == 1 && maxStringLength <= 4) {
    pmap[x][y].flags &= ~IN_LOOP;

    for (dir = 0; dir < 8; dir++) {
      newX = x + cDirs[dir][0];
      newY = y + cDirs[dir][1];
      if (coordinatesAreInMap(newX, newY)) {
        checkLoopiness(pmap, newX, newY, cDirs);
      }
    }
    return true;
  } else {
    return false;
  }
}
