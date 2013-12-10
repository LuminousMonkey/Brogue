/*
 * Dungeon Tiles
 *
 * Copyright 2013. All rights reserved.
 *
 * Just a placeholder to remove the tiles enum from the massive
 * Rogue.h include file.
 */

#ifndef TILES_H_
#define TILES_H_

#include "defines.h"

enum tileType {
    NOTHING = 0,
    GRANITE,
    FLOOR,
    FLOOR_FLOODABLE,
    CARPET,
    WALL,
    DOOR,
    OPEN_DOOR,
    SECRET_DOOR,
    LOCKED_DOOR,
    OPEN_IRON_DOOR_INERT,
    DOWN_STAIRS,
    UP_STAIRS,
    DUNGEON_EXIT,
    DUNGEON_PORTAL,
    TORCH_WALL, // wall lit with a torch
    CRYSTAL_WALL,
    PORTCULLIS_CLOSED,
    PORTCULLIS_DORMANT,
    WOODEN_BARRICADE,
    PILOT_LIGHT_DORMANT,
    PILOT_LIGHT,
    HAUNTED_TORCH_DORMANT,
    HAUNTED_TORCH_TRANSITIONING,
    HAUNTED_TORCH,
    WALL_LEVER_HIDDEN,
    WALL_LEVER,
    WALL_LEVER_PULLED,
    WALL_LEVER_HIDDEN_DORMANT,
    STATUE_INERT,
    STATUE_DORMANT,
    STATUE_CRACKING,
    PORTAL,
    TURRET_DORMANT,
    WALL_MONSTER_DORMANT,
    DARK_FLOOR_DORMANT,
    DARK_FLOOR_DARKENING,
    DARK_FLOOR,
    MACHINE_TRIGGER_FLOOR,
    ALTAR_INERT,
    ALTAR_KEYHOLE,
    ALTAR_CAGE_OPEN,
    ALTAR_CAGE_CLOSED,
    ALTAR_SWITCH,
    ALTAR_SWITCH_RETRACTING,
    ALTAR_CAGE_RETRACTABLE,
    PEDESTAL,
    MONSTER_CAGE_OPEN,
    MONSTER_CAGE_CLOSED,
    COFFIN_CLOSED,
    COFFIN_OPEN,

    GAS_TRAP_POISON_HIDDEN,
    GAS_TRAP_POISON,
    TRAP_DOOR_HIDDEN,
    TRAP_DOOR,
    GAS_TRAP_PARALYSIS_HIDDEN,
    GAS_TRAP_PARALYSIS,
    MACHINE_PARALYSIS_VENT_HIDDEN,
    MACHINE_PARALYSIS_VENT,
    GAS_TRAP_CONFUSION_HIDDEN,
    GAS_TRAP_CONFUSION,
    FLAMETHROWER_HIDDEN,
    FLAMETHROWER,
    FLOOD_TRAP_HIDDEN,
    FLOOD_TRAP,
    NET_TRAP_HIDDEN,
    NET_TRAP,
    MACHINE_POISON_GAS_VENT_HIDDEN,
    MACHINE_POISON_GAS_VENT_DORMANT,
    MACHINE_POISON_GAS_VENT,
    MACHINE_METHANE_VENT_HIDDEN,
    MACHINE_METHANE_VENT_DORMANT,
    MACHINE_METHANE_VENT,
    STEAM_VENT,
    MACHINE_PRESSURE_PLATE,
    MACHINE_PRESSURE_PLATE_USED,
    MACHINE_GLYPH,
    MACHINE_GLYPH_INACTIVE,

    DEEP_WATER,
    SHALLOW_WATER,
    MUD,
    CHASM,
    CHASM_EDGE,
    MACHINE_COLLAPSE_EDGE_DORMANT,
    MACHINE_COLLAPSE_EDGE_SPREADING,
    LAVA,
    LAVA_RETRACTABLE,
    LAVA_RETRACTING,
    SUNLIGHT_POOL,
    DARKNESS_PATCH,
    ACTIVE_BRIMSTONE,
    INERT_BRIMSTONE,
    OBSIDIAN,
    BRIDGE,
    BRIDGE_EDGE,
    STONE_BRIDGE,
    MACHINE_FLOOD_WATER_DORMANT,
    MACHINE_FLOOD_WATER_SPREADING,
    MACHINE_MUD_DORMANT,

    HOLE,
    HOLE_GLOW,
    HOLE_EDGE,
    FLOOD_WATER_DEEP,
    FLOOD_WATER_SHALLOW,
    GRASS,
    DEAD_GRASS,
    GRAY_FUNGUS,
    LUMINESCENT_FUNGUS,
    LICHEN,
    HAY,
    RED_BLOOD,
    GREEN_BLOOD,
    PURPLE_BLOOD,
    ACID_SPLATTER,
    VOMIT,
    URINE,
    UNICORN_POOP,
    WORM_BLOOD,
    ASH,
    BURNED_CARPET,
    PUDDLE,
    BONES,
    RUBBLE,
    JUNK,
    ECTOPLASM,
    EMBERS,
    SPIDERWEB,
    NETTING,
    FOLIAGE,
    DEAD_FOLIAGE,
    TRAMPLED_FOLIAGE,
    FUNGUS_FOREST,
    TRAMPLED_FUNGUS_FOREST,
    FORCEFIELD,
    MANACLE_TL,
    MANACLE_BR,
    MANACLE_TR,
    MANACLE_BL,
    MANACLE_T,
    MANACLE_B,
    MANACLE_L,
    MANACLE_R,
    PORTAL_LIGHT,
    GUARDIAN_GLOW,

    PLAIN_FIRE,
    BRIMSTONE_FIRE,
    FLAMEDANCER_FIRE,
    GAS_FIRE,
    GAS_EXPLOSION,
    DART_EXPLOSION,
    ITEM_FIRE,
    CREATURE_FIRE,

    POISON_GAS,
    CONFUSION_GAS,
    ROT_GAS,
    STENCH_SMOKE_GAS,
    PARALYSIS_GAS,
    METHANE_GAS,
    STEAM,
    DARKNESS_CLOUD,
    HEALING_CLOUD,

    BLOODFLOWER_STALK,
    BLOODFLOWER_POD,

    DEEP_WATER_ALGAE_WELL,
    DEEP_WATER_ALGAE_1,
    DEEP_WATER_ALGAE_2,

    STATUE_INERT_DOORWAY,
    STATUE_DORMANT_DOORWAY,

    CHASM_WITH_HIDDEN_BRIDGE,
    CHASM_WITH_HIDDEN_BRIDGE_ACTIVE,
    MACHINE_CHASM_EDGE,

    RAT_TRAP_WALL_DORMANT,
    RAT_TRAP_WALL_CRACKING,

    WORM_TUNNEL_MARKER_DORMANT,
    WORM_TUNNEL_MARKER_ACTIVE,
    WORM_TUNNEL_OUTER_WALL,

    BRAZIER,

    MUD_FLOOR,
    MUD_WALL,
    MUD_DOORWAY,

    NUMBER_TILETYPES,
};

/*
 * Different attributes that a dungeon tile can have.
 * Flag based, so each must be a single bit.
 */
enum tileFlags {
  NO_FLAGS = 0, /* No flags set. */
  DISCOVERED = Fl(0),
  /* Cell has sufficient light and is in field of view, ready to draw. */
  VISIBLE = Fl(1),
  HAS_PLAYER = Fl(2),
  HAS_MONSTER = Fl(3),
  /* Hidden monster on the square. */
  HAS_DORMANT_MONSTER = Fl(4),
  HAS_ITEM = Fl(5),
  /*
   * Player has unobstructed line of sight whether or not there is
   * enough light.
   */
  IN_FIELD_OF_VIEW = Fl(6),
  WAS_VISIBLE = Fl(7),
  HAS_DOWN_STAIRS = Fl(8),
  HAS_UP_STAIRS = Fl(9),
  /* So that a player gains an automatic stealth bonus. */
  IS_IN_SHADOW  = Fl(10),
  MAGIC_MAPPED = Fl(11),
  ITEM_DETECTED = Fl(12),
  CLAIRVOYANT_VISIBLE = Fl(13),
  WAS_CLAIRVOYANT_VISIBLE = Fl(14),
  /* Magical blindness from a cursed ring of clairvoyance. */
  CLAIRVOYANT_DARKENED = Fl(15),
  /* So that fire does not spread asymmetrically. */
  CAUGHT_FIRE_THIS_TURN = Fl(16),
  /* So that traps do not trigger repeatedly while you stand on them. */
  PRESSURE_PLATE_DEPRESSED = Fl(17),
  /* Redraws will simply be pulled from the memory array, not
   * recalculated. */
  STABLE_MEMORY = Fl(18),
  /* Keep track of where the player has stepped as he knows no traps
   * are there. */
  KNOWN_TO_BE_TRAP_FREE = Fl(19),
  /* The yellow trail leading to the cursor. */
  IS_IN_PATH = Fl(20),
  /* This cell is part of a terrain loop. */
  IN_LOOP = Fl(21),
  /* If this cell is blocked, part of the map will be rendered
   * inaccessible. */
  IS_CHOKEPOINT = Fl(22),
  /* Consider placing a locked door here. */
  IS_GATE_SITE = Fl(23),
  IS_IN_ROOM_MACHINE = Fl(24),
  IS_IN_AREA_MACHINE = Fl(25),
  /* Has been activated by machine power this turn (can probably be
   * eliminate if needed) */
  IS_POWERED = Fl(26),
  /* No tunneling allowed! */
  IMPREGNABLE = Fl(27),
  /* Colors here will sparkle when the game is idle. */
  TERRAIN_COLORS_DANCING = Fl(28),
  /* Potions of telepathy let you see through other creatures' eyes. */
  TELEPATHIC_VISIBLE = Fl(29),
  /* Potions of telepathy let you see through other creatures' eyes. */
  WAS_TELEPATHIC_VISIBLE = Fl(30),

  HAS_STAIRS = (HAS_UP_STAIRS | HAS_DOWN_STAIRS),
  /* Sacred ground; don't generate items here, or teleport randomly
   * to it. */
  IS_IN_MACHINE = (IS_IN_ROOM_MACHINE | IS_IN_AREA_MACHINE),

  PERMANENT_TILE_FLAGS = (DISCOVERED | MAGIC_MAPPED | ITEM_DETECTED |
                          HAS_ITEM | HAS_DORMANT_MONSTER | HAS_UP_STAIRS |
                          HAS_DOWN_STAIRS | PRESSURE_PLATE_DEPRESSED |
                          STABLE_MEMORY | KNOWN_TO_BE_TRAP_FREE | IN_LOOP |
                          IS_CHOKEPOINT | IS_GATE_SITE | IS_IN_MACHINE |
                          IMPREGNABLE),

  ANY_KIND_OF_VISIBLE = (VISIBLE | CLAIRVOYANT_VISIBLE | TELEPATHIC_VISIBLE),
};

#endif
