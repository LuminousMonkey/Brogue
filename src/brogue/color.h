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

#define NUMBER_DYNAMIC_COLORS 6

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

/*
 * applyColorMultiplier
 *
 * Given a base color, and a multiplier, update the basecolor by the
 * multiplier amount.
 */
void applyColorMultiplier(color *baseColor, const color *multiplierColor);

/*
 * applyColorAverage
 *
 */
void applyColorAverage(color *baseColor,
                       const color *newColor,
                       short averageWeight);

void applyColorAugment(color *baseColor,
                       const color *augmentingColor,
                       short augmentWeight);

void applyColorScalar(color *baseColor, short scalar);
void applyColorBounds(color *baseColor, short lowerBound, short upperBound);
void desaturate(color *baseColor, short weight);

// basic colors
extern const struct color white;
extern const struct color gray;
extern const struct color darkGray;
extern const struct color veryDarkGray;
extern const struct color black;
extern const struct color yellow;
extern const struct color darkYellow;
extern const struct color teal;
extern const struct color purple;
extern const struct color darkPurple;
extern const struct color brown;
extern const struct color green;
extern const struct color darkGreen;
extern const struct color orange;
extern const struct color darkOrange;
extern const struct color blue;
extern const struct color darkBlue;
extern const struct color darkTurquoise;
extern const struct color lightBlue;
extern const struct color pink;
extern const struct color red;
extern const struct color darkRed;
extern const struct color tanColor;

// bolt colors
extern const struct color rainbow;
extern const struct color descentBoltColor;
extern const struct color discordColor;
extern const struct color poisonColor;
extern const struct color beckonColor;
extern const struct color invulnerabilityColor;
extern const struct color dominationColor;
extern const struct color empowermentColor;
extern const struct color fireBoltColor;
extern const struct color flamedancerCoronaColor;
extern const struct color shieldingColor;

// tile colors
extern const struct color undiscoveredColor;

extern const struct color wallForeColor;

extern const struct color wallBackColor;
extern const struct color wallBackColorStart;
extern const struct color wallBackColorEnd;

extern const struct color mudWallForeColor;
extern const struct color mudWallBackColor;

extern const struct color graniteBackColor;

extern const struct color floorForeColor;

extern const struct color floorBackColor;
extern const struct color floorBackColorStart;
extern const struct color floorBackColorEnd;

extern const struct color stairsBackColor;
extern const struct color firstStairsBackColor;

extern const struct color refuseBackColor;
extern const struct color rubbleBackColor;
extern const struct color bloodflowerForeColor;
extern const struct color bloodflowerPodForeColor;
extern const struct color bloodflowerBackColor;

extern const struct color obsidianBackColor;
extern const struct color carpetForeColor;
extern const struct color carpetBackColor;
extern const struct color doorForeColor;
extern const struct color doorBackColor;

extern const struct color ironDoorForeColor;
extern const struct color ironDoorBackColor;
extern const struct color bridgeFrontColor;
extern const struct color bridgeBackColor;
extern const struct color statueBackColor;
extern const struct color glyphColor;
extern const struct color glyphLightColor;

extern const struct color deepWaterForeColor;
extern const struct color deepWaterBackColor;
extern const struct color deepWaterBackColorStart;
extern const struct color deepWaterBackColorEnd;
extern const struct color shallowWaterForeColor;
extern const struct color shallowWaterBackColor;
extern const struct color shallowWaterBackColorStart;
extern const struct color shallowWaterBackColorEnd;

extern const struct color mudForeColor;
extern const struct color mudBackColor;
extern const struct color chasmForeColor;
extern const struct color chasmEdgeBackColor;
extern const struct color chasmEdgeBackColorStart;
extern const struct color chasmEdgeBackColorEnd;
extern const struct color fireForeColor;
extern const struct color lavaForeColor;
extern const struct color brimstoneForeColor;
extern const struct color brimstoneBackColor;

extern const struct color lavaBackColor;
extern const struct color acidBackColor;

extern const struct color lightningColor;
extern const struct color fungusLightColor;
extern const struct color lavaLightColor;
extern const struct color deepWaterLightColor;

extern const struct color grassColor;
extern const struct color deadGrassColor;
extern const struct color fungusColor;
extern const struct color grayFungusColor;
extern const struct color foliageColor;
extern const struct color deadFoliageColor;
extern const struct color lichenColor;
extern const struct color hayColor;
extern const struct color ashForeColor;
extern const struct color bonesForeColor;
extern const struct color ectoplasmColor;
extern const struct color forceFieldColor;
extern const struct color wallCrystalColor;
extern const struct color altarForeColor;
extern const struct color altarBackColor;
extern const struct color pedestalBackColor;

// monster colors
extern const struct color goblinColor;
extern const struct color jackalColor;
extern const struct color ogreColor;
extern const struct color eelColor;
extern const struct color goblinConjurerColor;
extern const struct color spectralBladeColor;
extern const struct color spectralImageColor;
extern const struct color toadColor;
extern const struct color trollColor;
extern const struct color centipedeColor;
extern const struct color dragonColor;
extern const struct color krakenColor;
extern const struct color salamanderColor;
extern const struct color pixieColor;
extern const struct color darPriestessColor;
extern const struct color darMageColor;
extern const struct color wraithColor;
extern const struct color pinkJellyColor;
extern const struct color wormColor;
extern const struct color sentinelColor;
extern const struct color goblinMysticColor;
extern const struct color ifritColor;
extern const struct color phoenixColor;

// light colors
color minersLightColor;
extern const struct color minersLightStartColor;
extern const struct color minersLightEndColor;
extern const struct color torchColor;
extern const struct color torchLightColor;
extern const struct color hauntedTorchColor;
extern const struct color hauntedTorchLightColor;
extern const struct color ifritLightColor;
extern const struct color unicornLightColor;
extern const struct color wispLightColor;
extern const struct color summonedImageLightColor;
extern const struct color spectralBladeLightColor;
extern const struct color ectoplasmLightColor;
extern const struct color explosionColor;
extern const struct color dartFlashColor;
extern const struct color lichLightColor;
extern const struct color forceFieldLightColor;
extern const struct color crystalWallLightColor;
extern const struct color sunLightColor;
extern const struct color fungusForestLightColor;
extern const struct color fungusTrampledLightColor;
extern const struct color redFlashColor;
extern const struct color darknessPatchColor;
extern const struct color darknessCloudColor;
extern const struct color magicMapFlashColor;
extern const struct color sentinelLightColor;
extern const struct color telepathyColor;
extern const struct color confusionLightColor;
extern const struct color portalActivateLightColor;
extern const struct color descentLightColor;
extern const struct color algaeBlueLightColor;
extern const struct color algaeGreenLightColor;

// flare colors
extern const struct color scrollProtectionColor;
extern const struct color scrollEnchantmentColor;
extern const struct color potionStrengthColor;
extern const struct color empowermentFlashColor;
extern const struct color genericFlashColor;
extern const struct color summoningFlashColor;
extern const struct color fireFlashColor;
extern const struct color explosionFlareColor;

// color multipliers
extern const struct color colorDim25;
extern const struct color colorMultiplier100;
extern const struct color memoryColor;
extern const struct color memoryOverlay;
extern const struct color magicMapColor;
extern const struct color clairvoyanceColor;
extern const struct color telepathyMultiplier;
extern const struct color omniscienceColor;
extern const struct color basicLightColor;

// blood colors
extern const struct color humanBloodColor;
extern const struct color insectBloodColor;
extern const struct color vomitColor;
extern const struct color urineColor;
extern const struct color methaneColor;

// gas colors
extern const struct color poisonGasColor;
extern const struct color confusionGasColor;

// interface colors
extern const struct color itemColor;
extern const struct color blueBar;
extern const struct color redBar;
extern const struct color hiliteColor;
extern const struct color interfaceBoxColor;
extern const struct color interfaceButtonColor;
extern const struct color buttonHoverColor;
extern const struct color titleButtonColor;

extern const struct color playerInvisibleColor;
extern const struct color playerInLightColor;
extern const struct color playerInShadowColor;
extern const struct color playerInDarknessColor;

extern const struct color inLightMultiplierColor;
extern const struct color inDarknessMultiplierColor;

extern const struct color goodMessageColor;
extern const struct color badMessageColor;
extern const struct color advancementMessageColor;
extern const struct color itemMessageColor;
extern const struct color flavorTextColor;
extern const struct color backgroundMessageColor;

extern const struct color superVictoryColor;

extern const struct color flameSourceColor;

extern const struct color flameTitleColor;

extern const struct color *dynamicColors[NUMBER_DYNAMIC_COLORS][3];

#endif
