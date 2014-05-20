#include "color.h"

#include "Rogue.h"

void applyColorMultiplier(color *baseColor, const color *multiplierColor) {
  baseColor->red = baseColor->red * multiplierColor->red / 100;
  baseColor->redRand = baseColor->redRand * multiplierColor->redRand / 100;
  baseColor->green = baseColor->green * multiplierColor->green / 100;
  baseColor->greenRand = baseColor->greenRand *
      multiplierColor->greenRand / 100;
  baseColor->blue = baseColor->blue * multiplierColor->blue / 100;
  baseColor->blueRand = baseColor->blueRand *
      multiplierColor->blueRand / 100;
  baseColor->rand = baseColor->rand * multiplierColor->rand / 100;
}

void applyColorAverage(color *baseColor,
                       const color *newColor,
                       short averageWeight) {
  short weightComplement = 100 - averageWeight;
  baseColor->red = (baseColor->red * weightComplement + newColor->red *
                    averageWeight) / 100;
  baseColor->redRand = (baseColor->redRand * weightComplement +
                        newColor->redRand * averageWeight) / 100;
  baseColor->green = (baseColor->green * weightComplement +
                      newColor->green * averageWeight) / 100;
  baseColor->greenRand = (baseColor->greenRand * weightComplement +
                          newColor->greenRand * averageWeight) / 100;
  baseColor->blue = (baseColor->blue * weightComplement + newColor->blue *
                     averageWeight) / 100;
  baseColor->blueRand = (baseColor->blueRand * weightComplement +
                         newColor->blueRand * averageWeight) / 100;
  baseColor->rand = (baseColor->rand * weightComplement + newColor->rand *
                     averageWeight) / 100;
  baseColor->colorDances = (baseColor->colorDances || newColor->colorDances);
}

void applyColorAugment(color *baseColor,
                       const color *augmentingColor,
                       short augmentWeight) {
  baseColor->red += (augmentingColor->red * augmentWeight) / 100;
  baseColor->redRand += (augmentingColor->redRand * augmentWeight) / 100;
  baseColor->green += (augmentingColor->green * augmentWeight) / 100;
  baseColor->greenRand += (augmentingColor->greenRand * augmentWeight) / 100;
  baseColor->blue += (augmentingColor->blue * augmentWeight) / 100;
  baseColor->blueRand += (augmentingColor->blueRand * augmentWeight) / 100;
  baseColor->rand += (augmentingColor->rand * augmentWeight) / 100;
}

void applyColorScalar(color *baseColor, short scalar) {
  baseColor->red = baseColor->red * scalar / 100;
  baseColor->redRand = baseColor->redRand * scalar / 100;
  baseColor->green = baseColor->green * scalar / 100;
  baseColor->greenRand = baseColor->greenRand * scalar / 100;
  baseColor->blue = baseColor->blue * scalar / 100;
  baseColor->blueRand = baseColor->blueRand * scalar / 100;
  baseColor->rand = baseColor->rand * scalar / 100;
}

void applyColorBounds(color *baseColor, short lowerBound, short upperBound) {
  baseColor->red = clamp(baseColor->red, lowerBound, upperBound);
  baseColor->redRand = clamp(baseColor->redRand, lowerBound, upperBound);
  baseColor->green = clamp(baseColor->green, lowerBound, upperBound);
  baseColor->greenRand = clamp(baseColor->greenRand, lowerBound, upperBound);
  baseColor->blue = clamp(baseColor->blue, lowerBound, upperBound);
  baseColor->blueRand = clamp(baseColor->blueRand, lowerBound, upperBound);
  baseColor->rand = clamp(baseColor->rand, lowerBound, upperBound);
}

void desaturate(color *baseColor, short weight) {
  short avg;
  avg = (baseColor->red + baseColor->green + baseColor->blue) / 3 + 1;
  baseColor->red = baseColor->red * (100 - weight) / 100 +
      (avg * weight / 100);
  baseColor->green = baseColor->green * (100 - weight) / 100 +
      (avg * weight / 100);
  baseColor->blue = baseColor->blue * (100 - weight) / 100 +
      (avg * weight / 100);

  avg = (baseColor->redRand + baseColor->greenRand + baseColor->blueRand);
  baseColor->redRand = baseColor->redRand * (100 - weight) / 100;
  baseColor->greenRand = baseColor->greenRand * (100 - weight) / 100;
  baseColor->blueRand = baseColor->blueRand * (100 - weight) / 100;

  baseColor->rand += avg * weight / 3 / 100;
}

static short randomizeByPercent(const short input, const short percent) {
  return (rand_range(input * (100 - percent) / 100,
                     input * (100 + percent) / 100));
}

void randomizeColor(color *baseColor, short randomizePercent) {
  baseColor->red = randomizeByPercent(baseColor->red, randomizePercent);
  baseColor->green = randomizeByPercent(baseColor->green, randomizePercent);
  baseColor->blue = randomizeByPercent(baseColor->blue, randomizePercent);
}

// Assumes colors are pre-baked.
void blendAppearances(const color *fromForeColor,
                      const color *fromBackColor,
                      const uchar fromChar,
                      const color *toForeColor,
                      const color *toBackColor,
                      const uchar toChar,
                      color *const retForeColor,
                      color *const retBackColor,
                      uchar *const retChar,
                      const short percent) {
  // Straight average of the back color:
  *retBackColor = *fromBackColor;
  applyColorAverage(retBackColor, toBackColor, percent);

  // Pick the character:
  if (percent >= 50) {
    *retChar = toChar;
  } else {
    *retChar = fromChar;
  }

  // Pick the method for blending the fore color.
  if (fromChar == toChar) {
    // If the character isn't changing, do a straight average.
    *retForeColor = *fromForeColor;
    applyColorAverage(retForeColor, toForeColor, percent);
  } else {
    // If it is changing, the first half blends to the current back
    // color, and the second half blends to the final back color.
    if (percent >= 50) {
      *retForeColor = *retBackColor;
      applyColorAverage(retForeColor, toForeColor, (percent - 50) * 2);
    } else {
      *retForeColor = *fromForeColor;
      applyColorAverage(retForeColor, retBackColor, percent * 2);
    }
  }
}

// if forecolor is too similar to back, darken or lighten it and return true.
// Assumes colors have already been baked (no random components).
boolean separateColors(color *const fore, color *const back) {
  color f, b, *modifier;
  short failsafe;
  boolean madeChange;

  f = *fore;
  b = *back;
  f.red = max(0, min(100, f.red));
  f.green = max(0, min(100, f.green));
  f.blue = max(0, min(100, f.blue));
  b.red = max(0, min(100, b.red));
  b.green = max(0, min(100, b.green));
  b.blue = max(0, min(100, b.blue));

  if (f.red + f.blue + f.green > 50 * 3) {
    modifier = (struct color *)&black;
  } else {
    modifier = (struct color *)&white;
  }

  madeChange = false;
  failsafe = 10;

  while(COLOR_DIFF(f, b) < MIN_COLOR_DIFF && --failsafe) {
    applyColorAverage(&f, modifier, 20);
    madeChange = true;
  }

  if (madeChange) {
    *fore = f;
  }

  return madeChange;
}

// basic colors
const struct color white =                 {100,   100,    100,    0,      0,          0,          0,      false};
const struct color gray =                  {50,    50,     50,     0,      0,          0,          0,      false};
const struct color darkGray =              {30,    30,     30,     0,      0,          0,          0,      false};
const struct color veryDarkGray =          {15,    15,     15,     0,      0,          0,          0,      false};
const struct color black =                 {0,     0,      0,      0,      0,          0,          0,      false};
const struct color yellow =                {100,   100,    0,      0,      0,          0,          0,      false};
const struct color darkYellow =            {50,    50,     0,      0,      0,          0,          0,      false};
const struct color teal =                  {30,    100,    100,    0,      0,          0,          0,      false};
const struct color purple =                {100,   0,      100,    0,      0,          0,          0,      false};
const struct color darkPurple =            {50,    0,      50,     0,      0,          0,          0,      false};
const struct color brown =                 {60,    40,     0,      0,      0,          0,          0,      false};
const struct color green =                 {0,     100,    0,      0,      0,          0,          0,      false};
const struct color darkGreen =             {0,     50,     0,      0,      0,          0,          0,      false};
const struct color orange =                {100,   50,     0,      0,      0,          0,          0,      false};
const struct color darkOrange =            {50,    25,     0,      0,      0,          0,          0,      false};
const struct color blue =                  {0,     0,      100,    0,      0,          0,          0,      false};
const struct color darkBlue =              {0,     0,      50,     0,      0,          0,          0,      false};
const struct color darkTurquoise =         {0,     40,     65,     0,      0,          0,          0,      false};
const struct color lightBlue =             {40,    40,     100,    0,      0,          0,          0,      false};
const struct color pink =                  {100,   60,     66,     0,      0,          0,          0,      false};
const struct color red  =                  {100,   0,      0,      0,      0,          0,          0,      false};
const struct color darkRed =               {50,    0,      0,      0,      0,          0,          0,      false};
const struct color tanColor =              {80,    67,     15,     0,      0,          0,          0,      false};

// bolt colors
const struct color rainbow =               {-70,   -70,    -70,    170,    170,        170,        0,      true};
const struct color descentBoltColor =      {-40,   -40,    -40,    0,      0,          80,         80,     true};
const struct color discordColor =          {25,    0,      25,     66,     0,          0,          0,      true};
const struct color poisonColor =           {0,     0,      0,      10,     50,         10,         0,      true};
const struct color beckonColor =           {10,    10,     10,     5,      5,          5,          50,     true};
const struct color invulnerabilityColor =  {25,    0,      25,     0,      0,          66,         0,      true};
const struct color dominationColor =       {0,     0,      100,    80,     25,         0,          0,      true};
const struct color empowermentColor =      {30,    100,    40,     25,     80,         25,         0,      true};
const struct color fireBoltColor =         {500,   150,    0,      45,     30,         0,          0,      true};
const struct color flamedancerCoronaColor ={500,   150,    100,    45,     30,         0,          0,      true};
//const struct color shieldingColor =      {100,   50,     0,      0,      50,         100,        0,      true};
const struct color shieldingColor =        {150,   75,     0,      0,      50,         175,        0,      true};

// tile colors
const struct color undiscoveredColor =     {0,     0,      0,      0,      0,          0,          0,      false};

const struct color wallForeColor =         {7,     7,      7,      3,      3,          3,          0,      false};

const struct color wallBackColor;
const struct color wallBackColorStart =    {45,    40,     40,     15,     0,          5,          20,     false};
const struct color wallBackColorEnd =      {40,    30,     35,     0,      20,         30,         20,     false};

const struct color mudWallForeColor =      {55,    45,     0,      5,      5,          5,          1,      false};
//const struct color mudWallForeColor =      {40,  34,     7,      0,      3,          0,          3,      false};
const struct color mudWallBackColor =      {20,    12,     3,      8,      4,          3,          0,      false};

const struct color graniteBackColor =      {10,    10,     10,     0,      0,          0,          0,      false};

const struct color floorForeColor =        {30,    30,     30,     0,      0,          0,          35,     false};

const struct color floorBackColor;
const struct color floorBackColorStart =   {2,     2,      10,     2,      2,          0,          0,      false};
const struct color floorBackColorEnd =     {5,     5,      5,      2,      2,          0,          0,      false};

const struct color stairsBackColor =       {15,    15,     5,      0,      0,          0,          0,      false};
const struct color firstStairsBackColor =  {10,    10,     25,     0,      0,          0,          0,      false};

const struct color refuseBackColor =       {6,     5,      3,      2,      2,          0,          0,      false};
const struct color rubbleBackColor =       {7,     7,      8,      2,      2,          1,          0,      false};
const struct color bloodflowerForeColor =  {30,    5,      40,     5,      1,          3,          0,      false};
const struct color bloodflowerPodForeColor = {50,  5,      25,     5,      1,          3,          0,      false};
const struct color bloodflowerBackColor =  {15,    3,      10,     3,      1,          3,          0,      false};

const struct color obsidianBackColor =     {6,     0,      8,      2,      0,          3,          0,      false};
const struct color carpetForeColor =       {23,    30,     38,     0,      0,          0,          0,      false};
const struct color carpetBackColor =       {15,    8,      5,      0,      0,          0,          0,      false};
const struct color doorForeColor =         {70,    35,     15,     0,      0,          0,          0,      false};
const struct color doorBackColor =         {30,    10,     5,      0,      0,          0,          0,      false};
//const struct color ironDoorForeColor =       {40,    40,     40,     0,      0,          0,          0,      false};
const struct color ironDoorForeColor =     {500,   500,    500,    0,      0,          0,          0,      false};
const struct color ironDoorBackColor =     {15,    15,     30,     0,      0,          0,          0,      false};
const struct color bridgeFrontColor =      {33,    12,     12,     12,     7,          2,          0,      false};
const struct color bridgeBackColor =       {12,    3,      2,      3,      2,          1,          0,      false};
const struct color statueBackColor =       {20,    20,     20,     0,      0,          0,          0,      false};
const struct color glyphColor =            {20,    5,      5,      50,     0,          0,          0,      true};
const struct color glyphLightColor =       {150,   0,      0,      150,    0,          0,          0,      true};

//const struct color deepWaterForeColor =  {5,     5,      40,     0,      0,          10,         10,     true};
//color deepWaterBackColor;
//const struct color deepWaterBackColorStart = {5, 5,      55,     5,      5,          10,         10,     true};
//const struct color deepWaterBackColorEnd =   {5,     5,      45,     2,      2,          5,          5,      true};
//const struct color shallowWaterForeColor =   {40,    40,     90,     0,      0,          10,         10,     true};
//color shallowWaterBackColor;
//const struct color shallowWaterBackColorStart ={30,30,       80,     0,      0,          10,         10,     true};
//const struct color shallowWaterBackColorEnd ={20,    20,     60,     0,      0,          5,          5,      true};

const struct color deepWaterForeColor =    {5,     8,      20,     0,      4,          15,         10,     true};
const struct color deepWaterBackColor;
const struct color deepWaterBackColorStart = {5,   10,     31,     5,      5,          5,          6,      true};
const struct color deepWaterBackColorEnd = {5,     8,      20,     2,      3,          5,          5,      true};
const struct color shallowWaterForeColor = {28,    28,     60,     0,      0,          10,         10,     true};
const struct color shallowWaterBackColor;
const struct color shallowWaterBackColorStart ={20,20,     60,     0,      0,          10,         10,     true};
const struct color shallowWaterBackColorEnd ={12,  15,     40,     0,      0,          5,          5,      true};

const struct color mudForeColor =          {18,    14,     5,      5,      5,          0,          0,      false};
const struct color mudBackColor =          {23,    17,     7,      5,      5,          0,          0,      false};
const struct color chasmForeColor =        {7,     7,      15,     4,      4,          8,          0,      false};
const struct color chasmEdgeBackColor;
const struct color chasmEdgeBackColorStart ={5,    5,      25,     2,      2,          2,          0,      false};
const struct color chasmEdgeBackColorEnd = {8,     8,      20,     2,      2,          2,          0,      false};
const struct color fireForeColor =         {70,    20,     0,      15,     10,         0,          0,      true};
const struct color lavaForeColor =         {20,    20,     20,     100,    10,         0,          0,      true};
const struct color brimstoneForeColor =    {100,   50,     10,     0,      50,         40,         0,      true};
const struct color brimstoneBackColor =    {18,    12,     9,      0,      0,          5,          0,      false};

const struct color lavaBackColor =         {70,    20,     0,      15,     10,         0,          0,      true};
const struct color acidBackColor =         {15,    80,     25,     5,      15,         10,         0,      true};

const struct color lightningColor =        {100,   150,    500,    50,     50,         0,          50,     true};
const struct color fungusLightColor =      {2,     11,     11,     4,      3,          3,          0,      true};
const struct color lavaLightColor =        {47,    13,     0,      10,     7,          0,          0,      true};
const struct color deepWaterLightColor =   {10,    30,     100,    0,      30,         100,        0,      true};

const struct color grassColor =            {15,    40,     15,     15,     50,         15,         10,     false};
const struct color deadGrassColor =        {20,    13,     0,      20,     10,         5,          10,     false};
const struct color fungusColor =           {15,    50,     50,     0,      25,         0,          30,     true};
const struct color grayFungusColor =       {30,    30,     30,     5,      5,          5,          10,     false};
const struct color foliageColor =          {25,    100,    25,     15,     0,          15,         0,      false};
const struct color deadFoliageColor =      {20,    13,     0,      30,     15,         0,          20,     false};
const struct color lichenColor =           {50,    5,      25,     10,     0,          5,          0,      true};
const struct color hayColor =              {70,    55,     5,      0,      20,         20,         0,      false};
const struct color ashForeColor =          {20,    20,     20,     0,      0,          0,          20,     false};
const struct color bonesForeColor =        {80,    80,     30,     5,      5,          35,         5,      false};
const struct color ectoplasmColor =        {45,    20,     55,     25,     0,          25,         5,      false};
const struct color forceFieldColor =       {0,     25,     25,     0,      25,         25,         0,      true};
const struct color wallCrystalColor =      {40,    40,     60,     20,     20,         40,         0,      true};
const struct color altarForeColor =        {5,     7,      9,      0,      0,          0,          0,      false};
const struct color altarBackColor =        {35,    18,     18,     0,      0,          0,          0,      false};
const struct color pedestalBackColor =     {10,    5,      20,     0,      0,          0,          0,      false};

// monster colors
const struct color goblinColor =           {40,    30,     20,     0,      0,          0,          0,      false};
const struct color jackalColor =           {60,    42,     27,     0,      0,          0,          0,      false};
const struct color ogreColor =             {60,    25,     25,     0,      0,          0,          0,      false};
const struct color eelColor =              {30,    12,     12,     0,      0,          0,          0,      false};
const struct color goblinConjurerColor =   {67,    10,     100,    0,      0,          0,          0,      false};
const struct color spectralBladeColor =    {15,    15,     60,     0,      0,          70,         50,     true};
const struct color spectralImageColor =    {13,    0,      0,      25,     0,          0,          0,      true};
const struct color toadColor =             {40,    65,     30,     0,      0,          0,          0,      false};
const struct color trollColor =            {40,    60,     15,     0,      0,          0,          0,      false};
const struct color centipedeColor =        {75,    25,     85,     0,      0,          0,          0,      false};
const struct color dragonColor =           {20,    80,     15,     0,      0,          0,          0,      false};
const struct color krakenColor =           {100,   55,     55,     0,      0,          0,          0,      false};
const struct color salamanderColor =       {40,    10,     0,      8,      5,          0,          0,      true};
const struct color pixieColor =            {60,    60,     60,     40,     40,         40,         0,      true};
const struct color darPriestessColor =     {0,     50,     50,     0,      0,          0,          0,      false};
const struct color darMageColor =          {50,    50,     0,      0,      0,          0,          0,      false};
const struct color wraithColor =           {66,    66,     25,     0,      0,          0,          0,      false};
const struct color pinkJellyColor =        {100,   40,     40,     5,      5,          5,          20,     true};
const struct color wormColor =             {80,    60,     40,     0,      0,          0,          0,      false};
const struct color sentinelColor =         {3,     3,      30,     0,      0,          10,         0,      true};
const struct color goblinMysticColor =     {10,    67,     100,    0,      0,          0,          0,      false};
const struct color ifritColor =            {50,    10,     100,    75,     0,          20,         0,      true};
const struct color phoenixColor =          {100,   0,      0,      0,      100,        0,          0,      true};

// light colors
color minersLightColor;
const struct color minersLightStartColor = {180,   180,    180,    0,      0,          0,          0,      false};
const struct color minersLightEndColor =   {90,    90,     120,    0,      0,          0,          0,      false};
const struct color torchColor =            {150,   75,     30,     0,      30,         20,         0,      true};
const struct color torchLightColor =       {75,    38,     15,     0,      15,         7,          0,      true};
//const struct color hauntedTorchColor =     {75,  30,     150,    30,     20,         0,          0,      true};
const struct color hauntedTorchColor =     {75,    20,     40,     30,     10,         0,          0,      true};
//const struct color hauntedTorchLightColor ={19,     7,       37,     8,      4,          0,          0,      true};
const struct color hauntedTorchLightColor ={67,    10,     10,     20,     4,          0,          0,      true};
const struct color ifritLightColor =       {0,     10,     150,    100,    0,          100,        0,      true};
//const struct color unicornLightColor =       {-50,   -50,    -50,    200,    200,        200,        0,      true};
const struct color unicornLightColor =     {-50,   -50,    -50,    250,    250,        250,        0,      true};
const struct color wispLightColor =        {75,    100,    250,    33,     10,         0,          0,      true};
const struct color summonedImageLightColor ={200,  0,      75,     0,      0,          0,          0,      true};
const struct color spectralBladeLightColor ={40,   0,      230,    0,      0,          0,          0,      true};
const struct color ectoplasmLightColor =   {23,    10,     28,     13,     0,          13,         3,      false};
const struct color explosionColor =        {10,    8,      2,      0,      2,          2,          0,      true};
const struct color dartFlashColor =        {500,   500,    500,    0,      2,          2,          0,      true};
const struct color lichLightColor =        {-50,   80,     30,     0,      0,          20,         0,      true};
const struct color forceFieldLightColor =  {10,    10,     10,     0,      50,         50,         0,      true};
const struct color crystalWallLightColor = {10,    10,     10,     0,      0,          50,         0,      true};
const struct color sunLightColor =         {100,   100,    75,     0,      0,          0,          0,      false};
const struct color fungusForestLightColor ={30,    40,     60,     0,      0,          0,          40,     true};
const struct color fungusTrampledLightColor ={10,  10,     10,     0,      50,         50,         0,      true};
const struct color redFlashColor =         {100,   10,     10,     0,      0,          0,          0,      false};
const struct color darknessPatchColor =    {-10,   -10,    -10,    0,      0,          0,          0,      false};
const struct color darknessCloudColor =    {-20,   -20,    -20,    0,      0,          0,          0,      false};
const struct color magicMapFlashColor =    {60,    20,     60,     0,      0,          0,          0,      false};
const struct color sentinelLightColor =    {20,    20,     120,    10,     10,         60,         0,      true};
const struct color telepathyColor =        {30,    30,     130,    0,      0,          0,          0,      false};
const struct color confusionLightColor =   {10,    10,     10,     10,     10,         10,         0,      true};
const struct color portalActivateLightColor ={300, 400,    500,    0,      0,          0,          0,      true};
const struct color descentLightColor =     {20,    20,     70,     0,      0,          0,          0,      false};
const struct color algaeBlueLightColor =   {20,    15,     50,     0,      0,          0,          0,      false};
const struct color algaeGreenLightColor =  {15,    50,     20,     0,      0,          0,          0,      false};

// flare colors
const struct color scrollProtectionColor = {375,   750,    0,      0,      0,          0,          0,      true};
const struct color scrollEnchantmentColor ={250,   225,    300,    0,      0,          450,        0,      true};
const struct color potionStrengthColor =   {1000,  0,      400,    600,    0,          0,          0,      true};
const struct color empowermentFlashColor = {500,   1000,   600,    0,      500,        0,          0,      true};
const struct color genericFlashColor =     {800,   800,    800,    0,      0,          0,          0,      false};
const struct color summoningFlashColor =   {0,     0,      0,      600,    0,          1200,       0,      true};
const struct color fireFlashColor =        {750,   225,    0,      100,    50,         0,          0,      true};
const struct color explosionFlareColor =   {10000, 6000,   1000,   0,      0,          0,          0,      false};

// color multipliers
const struct color colorDim25 =            {25,    25,     25,     25,     25,         25,         25,     false};
const struct color colorMultiplier100 =    {100,   100,    100,    100,    100,        100,        100,    false};
const struct color memoryColor =           {25,    25,     50,     20,     20,         20,         0,      false};
const struct color memoryOverlay =         {25,    25,     50,     0,      0,          0,          0,      false};
const struct color magicMapColor =         {60,    20,     60,     60,     20,         60,         0,      false};
const struct color clairvoyanceColor =     {50,    90,     50,     50,     90,         50,         66,     false};
const struct color telepathyMultiplier =   {30,    30,     130,    30,     30,         130,        66,     false};
const struct color omniscienceColor =      {140,   100,    60,     140,    100,        60,         90,     false};
const struct color basicLightColor =       {180,   180,    180,    180,    180,        180,        180,    false};

// blood colors
const struct color humanBloodColor =       {60,    20,     10,     15,     0,          0,          15,     false};
const struct color insectBloodColor =      {10,    60,     20,     0,      15,         0,          15,     false};
const struct color vomitColor =            {60,    50,     5,      0,      15,         15,         0,      false};
const struct color urineColor =            {70,    70,     40,     0,      0,          0,          10,     false};
const struct color methaneColor =          {45,    60,     15,     0,      0,          0,          0,      false};

// gas colors
const struct color poisonGasColor =        {75,    25,     85,     0,      0,          0,          0,      false};
const struct color confusionGasColor =     {60,    60,     60,     40,     40,         40,         0,      true};

// interface colors
const struct color itemColor =             {100,   95,     -30,    0,      0,          0,          0,      false};
const struct color blueBar =               {15,    10,     50,     0,      0,          0,          0,      false};
const struct color redBar =                {45,    10,     15,     0,      0,          0,          0,      false};
const struct color hiliteColor =           {100,   100,    0,      0,      0,          0,          0,      false};
const struct color interfaceBoxColor =     {7,     6,      15,     0,      0,          0,          0,      false};
const struct color interfaceButtonColor =  {18,    15,     38,     0,      0,          0,          0,      false};
const struct color buttonHoverColor =      {100,   70,     40,     0,      0,          0,          0,      false};
const struct color titleButtonColor =      {23,    15,     30,     0,      0,          0,          0,      false};

const struct color playerInvisibleColor =  {20,    20,     30,     0,      0,          80,         0,      true};
const struct color playerInLightColor =    {100,   90,     30,     0,      0,          0,          0,      false};
const struct color playerInShadowColor =   {60,    60,     100,    0,      0,          0,          0,      false};
const struct color playerInDarknessColor = {30,    30,     65,     0,      0,          0,          0,      false};

const struct color inLightMultiplierColor ={150,   150,    75,     150,    150,        75,         100,    true};
const struct color inDarknessMultiplierColor={66,  66,     120,    66,     66,         120,        66,     true};

const struct color goodMessageColor =      {60,    50,     100,    0,      0,          0,          0,      false};
const struct color badMessageColor =       {100,   50,     60,     0,      0,          0,          0,      false};
const struct color advancementMessageColor ={50,   100,    60,     0,      0,          0,          0,      false};
const struct color itemMessageColor =      {100,   100,    50,     0,      0,          0,          0,      false};
const struct color flavorTextColor =       {50,    40,     90,     0,      0,          0,          0,      false};
const struct color backgroundMessageColor ={60,    20,     70,     0,      0,          0,          0,      false};

const struct color superVictoryColor =     {150,   100,    300,    0,      0,          0,          0,      false};

//const struct color flameSourceColor = {0, 0, 0, 65, 40, 100, 0, true}; // 1
//const struct color flameSourceColor = {0, 0, 0, 80, 50, 100, 0, true}; // 2
//const struct color flameSourceColor = {25, 13, 25, 50, 25, 50, 0, true}; // 3
//const struct color flameSourceColor = {20, 20, 20, 60, 20, 40, 0, true}; // 4
//const struct color flameSourceColor = {30, 18, 18, 70, 36, 36, 0, true}; // 7**
const struct color flameSourceColor = {20, 7, 7, 60, 40, 40, 0, true}; // 8

//const struct color flameTitleColor = {0, 0, 0, 17, 10, 6, 0, true}; // pale orange
//const struct color flameTitleColor = {0, 0, 0, 7, 7, 10, 0, true}; // *pale blue*
const struct color flameTitleColor = {0, 0, 0, 9, 9, 15, 0, true}; // *pale blue**
//const struct color flameTitleColor = {0, 0, 0, 11, 11, 18, 0, true}; // *pale blue*
//const struct color flameTitleColor = {0, 0, 0, 15, 15, 9, 0, true}; // pale yellow
//const struct color flameTitleColor = {0, 0, 0, 15, 9, 15, 0, true}; // pale purple

const struct color *dynamicColors[NUMBER_DYNAMIC_COLORS][3] = {
  // used color           shallow color               deep color
    {&minersLightColor,     &minersLightStartColor,     &minersLightEndColor},
    {&wallBackColor,        &wallBackColorStart,        &wallBackColorEnd},
    {&deepWaterBackColor,   &deepWaterBackColorStart,   &deepWaterBackColorEnd},
    {&shallowWaterBackColor,&shallowWaterBackColorStart,&shallowWaterBackColorEnd},
    {&floorBackColor,       &floorBackColorStart,       &floorBackColorEnd},
    {&chasmEdgeBackColor,   &chasmEdgeBackColorStart,   &chasmEdgeBackColorEnd},
};
