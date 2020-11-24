#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "spritesheet.h"

// Variables
ANISPRITE cursor;
int goInstr;

// Cursor states
enum {INSTR, GAME};

// Initalizes player cursor for selection
void initCursor() {
    cursor.worldRow = 75;
    cursor.worldCol = 80;
    cursor.width = 16;
    cursor.height = 32;
    cursor.aniState = INSTR;
    goInstr = 1;
    cursor.hide = 0;
}

// Update cursor
void updateCursor() {
    if (cursor.aniState == INSTR) { // if on instructions option
        // move to game option
        if (BUTTON_HELD(BUTTON_RIGHT)) {
            cursor.worldCol = 160;
            cursor.aniState = GAME;
            goInstr = 0;
        }
    } else if (cursor.aniState == GAME) { // if on game option
        // move to instr. option
        if (BUTTON_HELD(BUTTON_LEFT)) {
            cursor.worldCol = 80;
            cursor.aniState = INSTR;
        }
    }
}

// Draw cursor
void drawCursor() {
    // Set up sprite attributes
    if (cursor.hide) {
        shadowOAM[0].attr0 |= ATTR0_HIDE;
    } else {
        shadowOAM[0].attr0 = cursor.worldRow | ATTR0_TALL;
        shadowOAM[0].attr1 = cursor.worldCol | ATTR1_MEDIUM;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 0);
    }
}