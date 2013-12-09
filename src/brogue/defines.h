/*
 * Defines
 *
 * Copyright 2013. All rights reserved.
 *
 * This file just holds some #defines that I need to access from my
 * refactored code. I don't have a place for these just yet, but I
 * don't want to include in uber Rogue.h include into my refactored
 * code.
 *
 * The reason being is I want to start to reduce coupling, so anything
 * that needs to be shared between the original code and my
 * refactoring has to be put here.
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/*
 * Global constants.
 */
#define MESSAGE_LINES 3
#define MESSAGE_ARCHIVE_LINES ROWS

/*
 * Size of the entire terminal window. These need to be hard-coded
 * here and in Viewport.h
 */
#define COLS 100
#define ROWS (31 + MESSAGE_LINES)

/*
 * Size of the portion of the terminal window devoted to displaying
 * the dungeon:
 */
#define DCOLS (COLS - STAT_BAR_WIDTH - 1)

/*
 * n lines at the top for messages.
 * one line at the bottom for flavor text.
 * another line at the bottom for the menu bar.
 */
#define DROWS (ROWS - MESSAGE_LINES - 2)

/* Number of characters in the stats bar to the left of the map. */
#define STAT_BAR_WIDTH 20

/* For generating flags. */
#define Fl(N)                   (1 << (N))

#endif
