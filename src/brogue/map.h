/*
 * Map Functions
 *
 * Copyright 2013. All rights reserved.
 *
 * All map related operations should go in here.
 */

#ifndef MAP_H_
#define MAP_H_

#include <stdbool.h>
#include "defines.h"
#include "tiles.h"
#include "items.h"
#include "types.h"

/*
 * TODO: Find out what this is exactly.
 */
enum dungeonLayers {
  NO_LAYER = -1,
  DUNGEON = 0,        /* Dungeon-level tile. (e.g. walls) */
  LIQUID,             /* Liquid-level tile. (e.g. lava) */
  GAS,                /* Gas-level tile. (e.g. fire, smoke, swamp gas) */
  SURFACE,            /* Surface-level tile. (e.g. grass) */
  NUMBER_TERRAIN_LAYERS
};

/*
 * Keeps track of graphics, so we only redraw if the cell has changed.
 */
typedef struct cellDisplayBuffer {
  uchar character;
  char foreColorComponents[3];
  char backColorComponents[3];
  char opacity;
  boolean needsUpdate;
} cellDisplayBuffer;

/*
 * Permanent cell.
 *
 * This is a unit of permanent map information, this needs to be
 * stored to save state between levels.
 *
 * layers - Terrain.
 * flags - Non-terrain cell flags.
 * volume - Quantity of gas in cell.
 * rememberedAppearance - How the player remembers the cell to look.
 *
 * rememberedItemCategory - What category of item the player
 *                          remembers lying there.
 *
 * rememberedTerrain - What the player remembers as the terrain
 *                     (i.e. highest priority terrain upon last seeing)
 */
struct pcell {
  enum tileType layers[NUMBER_TERRAIN_LAYERS];
  unsigned long flags;
  unsigned short volume;
  unsigned char machineNumber;
  cellDisplayBuffer rememberedAppearance;
  enum itemCategory rememberedItemCategory;
  enum tileType rememberedTerrain;
};

/*
 * Clears out the given permanent map.
 */
void clearLevel(struct pcell pmap[DCOLS][DROWS]);

/*
 * Copy a pmap struct from source to dest.
 */
void copyMap(struct pcell to[DCOLS][DROWS],
             struct pcell from[DCOLS][DROWS],
             boolean permanentFlagsOnly);

/*
 * Given coordinates on the map, return true if that location is in a
 * terrain loop.
 */
bool checkLoopiness(struct pcell pmap[DCOLS][DROWS],
                    const short x, const short y,
                    const short cDirs[8][2]);

#endif
