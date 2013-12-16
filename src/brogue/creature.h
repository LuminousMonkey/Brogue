/*
 * Creature Functions
 *
 * Copyright 2013. All rights reserved.
 *
 * Creature functions, which covers monsters and the player.
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include "color.h"
#include "defines.h"
#include "features.h"
#include "light.h"
#include "random.h"
#include "types.h"

enum monsterTypes {
    MK_YOU,
    MK_RAT,
    MK_KOBOLD,
    MK_JACKAL,
    MK_EEL,
    MK_MONKEY,
    MK_BLOAT,
    MK_PIT_BLOAT,
    MK_GOBLIN,
    MK_GOBLIN_CONJURER,
    MK_GOBLIN_MYSTIC,
    MK_GOBLIN_TOTEM,
    MK_PINK_JELLY,
    MK_TOAD,
    MK_VAMPIRE_BAT,
    MK_ARROW_TURRET,
    MK_ACID_MOUND,
    MK_CENTIPEDE,
    MK_OGRE,
    MK_BOG_MONSTER,
    MK_OGRE_TOTEM,
    MK_SPIDER,
    MK_SPARK_TURRET,
    MK_WILL_O_THE_WISP,
    MK_WRAITH,
    MK_ZOMBIE,
    MK_TROLL,
    MK_OGRE_SHAMAN,
    MK_NAGA,
    MK_SALAMANDER,
    MK_EXPLOSIVE_BLOAT,
    MK_DAR_BLADEMASTER,
    MK_DAR_PRIESTESS,
    MK_DAR_BATTLEMAGE,
    MK_ACID_JELLY,
    MK_CENTAUR,
    MK_UNDERWORM,
    MK_SENTINEL,
    MK_ACID_TURRET,
    MK_DART_TURRET,
    MK_KRAKEN,
    MK_LICH,
    MK_PHYLACTERY,
    MK_PIXIE,
    MK_PHANTOM,
    MK_FLAME_TURRET,
    MK_IMP,
    MK_FURY,
    MK_REVENANT,
    MK_TENTACLE_HORROR,
    MK_GOLEM,
    MK_DRAGON,

    MK_GOBLIN_CHIEFTAN,
    MK_BLACK_JELLY,
    MK_VAMPIRE,
    MK_FLAMESPIRIT,

    MK_SPECTRAL_BLADE,
    MK_SPECTRAL_IMAGE,
    MK_GUARDIAN,
    MK_WINGED_GUARDIAN,
    MK_CHARM_GUARDIAN,
    MK_ELDRITCH_TOTEM,
    MK_MIRRORED_TOTEM,

    MK_UNICORN,
    MK_IFRIT,
    MK_PHOENIX,
    MK_PHOENIX_EGG,

    NUMBER_MONSTER_KINDS
};

// Defines all creatures, which include monsters and the player:
typedef struct creatureType {
    enum monsterTypes monsterID; // index number for the monsterCatalog
    char monsterName[COLS];
    uchar displayChar;
    const struct color *foreColor;
    short maxHP;
    short defense;
    short accuracy;
    struct randomRange damage;
    long turnsBetweenRegen;     // turns to wait before regaining 1 HP
    short movementSpeed;
    short attackSpeed;
    enum dungeonFeatureTypes bloodType;
    enum lightType intrinsicLightType;
    short DFChance;                     // percent chance to spawn the dungeon feature per awake turn
    enum dungeonFeatureTypes DFType;    // kind of dungeon feature
    unsigned long flags;
    unsigned long abilityFlags;
} creatureType;

#endif
