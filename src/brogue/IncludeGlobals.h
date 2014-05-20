/*
 *  Include Globals.h
 *  Brogue
 *
 *  Created by Brian Walker on 2/8/09.
 *  Copyright 2012. All rights reserved.
 *  
 *  This file is part of Brogue.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Rogue.h"
#include "map.h"

extern tcell tmap[DCOLS][DROWS];						// grids with info about the map

/*
 * Permanent map.
 *
 * This holds map information that needs to be saved, it's things that
 * can't be changed about a map.
 */
extern struct pcell pmap[DCOLS][DROWS];						// grids with info about the map
extern short **scentMap;
extern cellDisplayBuffer displayBuffer[COLS][ROWS];
extern short terrainRandomValues[DCOLS][DROWS][8];
extern short **safetyMap;										// used to help monsters flee
extern short **allySafetyMap;
extern short **chokeMap;
extern short **playerPathingMap;

extern const short nbDirs[8][2];
extern const short cDirs[8][2];
extern levelData *levels;
extern creature player;
extern playerCharacter rogue;
extern creature *monsters;
extern creature *dormantMonsters;
extern creature *graveyard;
extern item *floorItems;
extern item *packItems;
extern item *monsterItemsHopper;
extern short numberOfWaypoints;

extern char displayedMessage[MESSAGE_LINES][COLS];
extern boolean messageConfirmed[3];
extern char combatText[COLS];
short messageArchivePosition;
char messageArchive[MESSAGE_ARCHIVE_LINES][COLS*2];

extern char currentFilePath[BROGUE_FILENAME_MAX];
extern unsigned long randomNumbersGenerated;

extern char displayDetail[DCOLS][DROWS];

#ifdef AUDIT_RNG
extern FILE *RNGLogFile;
#endif

extern unsigned char inputRecordBuffer[INPUT_RECORD_BUFFER + 100];
extern unsigned short locationInRecordingBuffer;

extern unsigned long positionInPlaybackFile;
extern unsigned long lengthOfPlaybackFile;
extern unsigned long recordingLocation;
extern unsigned long maxLevelChanges;
extern char annotationPathname[BROGUE_FILENAME_MAX];	// pathname of annotation file
extern unsigned long previousGameSeed;

extern const autoGenerator autoGeneratorCatalog[NUMBER_AUTOGENERATORS];

extern floorTileType tileCatalog[NUMBER_TILETYPES];

extern dungeonFeature dungeonFeatureCatalog[NUMBER_DUNGEON_FEATURES];

extern lightSource lightCatalog[NUMBER_LIGHT_KINDS];

extern const blueprint blueprintCatalog[NUMBER_BLUEPRINTS];

extern creatureType monsterCatalog[NUMBER_MONSTER_KINDS];
extern monsterWords monsterText[NUMBER_MONSTER_KINDS];
extern hordeType hordeCatalog[NUMBER_HORDES];
extern const mutation mutationCatalog[NUMBER_MUTATORS];

extern const feat featTable[FEAT_COUNT];

extern color *boltColors[NUMBER_BOLT_KINDS];

// ITEMS
extern char itemTitles[NUMBER_SCROLL_KINDS][30];
extern char titlePhonemes[NUMBER_TITLE_PHONEMES][30];
extern char itemColors[NUMBER_ITEM_COLORS][30];
extern char itemWoods[NUMBER_ITEM_WOODS][30];
extern char itemMetals[NUMBER_ITEM_METALS][30];
extern char itemGems[NUMBER_ITEM_GEMS][30];

extern char itemColorsRef[NUMBER_ITEM_COLORS][30];
extern char itemWoodsRef[NUMBER_ITEM_WOODS][30];
extern char itemMetalsRef[NUMBER_ITEM_METALS][30];
extern char itemGemsRef[NUMBER_ITEM_GEMS][30];

extern itemTable keyTable[NUMBER_KEY_TYPES];
extern itemTable foodTable[NUMBER_FOOD_KINDS];
extern itemTable weaponTable[NUMBER_WEAPON_KINDS];
extern itemTable armorTable[NUMBER_ARMOR_KINDS];
extern itemTable scrollTable[NUMBER_SCROLL_KINDS];
extern itemTable potionTable[NUMBER_POTION_KINDS];
extern itemTable wandTable[NUMBER_WAND_KINDS];
extern itemTable staffTable[NUMBER_STAFF_KINDS];
extern itemTable ringTable[NUMBER_RING_KINDS];
extern itemTable charmTable[NUMBER_CHARM_KINDS];
extern const char weaponRunicNames[NUMBER_WEAPON_RUNIC_KINDS][30];

extern const char armorRunicNames[NUMBER_ARMOR_ENCHANT_KINDS][30];

extern char monsterBehaviorFlagDescriptions[32][COLS];
extern char monsterAbilityFlagDescriptions[32][COLS];
extern char monsterBookkeepingFlagDescriptions[32][COLS];
