#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "level1.h"
#include "level1objects.h"
#include "sound.h"
#include "gojackets.h"
#include "cheat.h"

// Variables
ANISPRITE poms[POMCOUNT];
ANISPRITE bag;
ANISPRITE water;
ANISPRITE makeup[MAKEUPCNT];
ANISPRITE snacks[SNACKCNT];
ANISPRITE mask;

// Initialize poms
void initPoms() {
    for (int i = 0; i < POMCOUNT; i++) {
        poms[i].width = 16;
        poms[i].height = 16;
        poms[i].hide = 0;
        if (i == 0) {
            poms[i].worldCol = 318;
            poms[i].worldRow = 488;
        } else if (i == 1) {
            poms[i].worldCol = 192; 
            poms[i].worldRow = 470;
        }
    }
}

// Update poms
void updatePoms() {
    // collected by player
    for (int i = 0; i < POMCOUNT; i++) {
        if (collision(player.worldCol, player.worldRow, player.width, player.height, poms[i].worldCol, poms[i].worldRow, poms[i].width, poms[i].height)
        && BUTTON_PRESSED(BUTTON_A)) {
            poms[i].hide = 1;
            objsCollected++;
            playSoundA(gojackets_data, gojackets_length, 0);
        }
    }
}

// Draw poms
void drawPoms() {
    for (int i = 0; i < POMCOUNT; i++) {
        if (poms[i].hide) {
            shadowOAM[i+5].attr0 = ATTR0_HIDE;
        } else {
            if ((poms[i].worldCol - l1HOff <= 240) && (poms[i].worldRow - l1VOff <= 160)
            && (poms[i].worldCol - l1HOff) >= -30 && (poms[i].worldRow - l1VOff >= 0)) {
                shadowOAM[i+5].attr0 = (ROWMASK & (poms[i].worldRow - l1VOff)) | ATTR0_4BPP | ATTR0_SQUARE;
                shadowOAM[i+5].attr1 = (COLMASK & (poms[i].worldCol - l1HOff)) | ATTR1_SMALL;
                shadowOAM[i+5].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 0); 
            } else {
                shadowOAM[i+5].attr0 = ATTR0_HIDE;
            }
        }
    }
}

// Initialize bag
void initBag() {
    bag.worldRow = 68;
    bag.worldCol = 440;
    bag.hide = 0;
    bag.width = 16;
    bag.height = 16;
}

// Update bag every frame
void updateBag(){
    // collected by player
    if (collision(player.worldCol, player.worldRow, player.width, player.height, bag.worldCol, bag.worldRow, bag.width, bag.height)
    && BUTTON_PRESSED(BUTTON_A)) {
        bag.hide = 1;
        objsCollected++;
        playSoundA(gojackets_data, gojackets_length, 0);
    }
}

// Draw bag
void drawBag() {
    // Set up sprite attributes
    if (bag.hide) {
        shadowOAM[7].attr0 |= ATTR0_HIDE;
    } else {
        if ((bag.worldCol - l1HOff <= 240) && (bag.worldRow - l1VOff <= 160)
        && (bag.worldCol - l1HOff) >= 0 && (bag.worldRow - l1VOff >= -30)) {
            shadowOAM[7].attr0 = (ROWMASK & (bag.worldRow - l1VOff)) | ATTR0_SQUARE;
            shadowOAM[7].attr1 = (COLMASK & (bag.worldCol - l1HOff)) | ATTR1_SMALL;
            shadowOAM[7].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 4);
        } else {
            shadowOAM[7].attr0 |= ATTR0_HIDE;
        }
    }
}

// Initialize water bottle
void initWater() {
    water.worldRow = 20;
    water.worldCol = MAPWIDTH/2;
    water.width = 8;
    water.height = 16;
    water.hide = 0;
}

// Update water bottle
void updateWater() {
    // collected by player
    if (collision(player.worldCol, player.worldRow, player.width, player.height, water.worldCol, water.worldRow, water.width, water.height)
    && BUTTON_PRESSED(BUTTON_A)) {
        water.hide = 1;
        objsCollected++;
        playSoundA(gojackets_data, gojackets_length, 0);
    }
}

// Draw water bottle
void drawWater() {
    // Set up sprite attributes
    if (water.hide) {
        shadowOAM[8].attr0 |= ATTR0_HIDE;
    } else {
        if ((water.worldCol - l1HOff <= 250) && (water.worldRow - l1VOff <= 160)
            && (water.worldCol - l1HOff) >= -10 && (water.worldRow - l1VOff >= -20)) {
            shadowOAM[8].attr0 = (ROWMASK & (water.worldRow - l1VOff)) | ATTR0_TALL;
            shadowOAM[8].attr1 = (COLMASK & (water.worldCol - l1HOff)) | ATTR1_TINY;
            shadowOAM[8].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 6);
        } else {
            shadowOAM[8].attr0 |= ATTR0_HIDE;
        }
    }
}

// Initialize makeup
void initMakeup() {
    for (int i = 0; i < MAKEUPCNT; i++) {
        makeup[i].hide = 0;
        if (i == 0) {
            makeup[i].worldCol = 50;
            makeup[i].worldRow = 20;
            makeup[i].width = 8;
            makeup[i].height = 8;
        } else if (i == 1) {
            makeup[i].worldCol = 480; 
            makeup[i].worldRow = 470;
            makeup[i].width = 8;
            makeup[i].height = 8;
        } else if (i == 2) {
            makeup[i].worldCol = 95; 
            makeup[i].worldRow = 195;
            makeup[i].width = 8;
            makeup[i].height = 16;
        }
    }
}

// Update makeup
void updateMakeup() {
    // collected by player
    for (int i = 0; i < MAKEUPCNT; i++) {
        if (collision(player.worldCol, player.worldRow, player.width, player.height, makeup[i].worldCol, makeup[i].worldRow, makeup[i].width, makeup[i].height)
        && BUTTON_PRESSED(BUTTON_A)) {
            makeup[i].hide = 1;
            objsCollected++;
            makeupCollected++;
            playSoundA(gojackets_data, gojackets_length, 0);
        }
    }
}

// Draw Makeup
void drawMakeup() {
    for (int i = 0; i < MAKEUPCNT; i++) {
        if (makeup[i].hide) {
            shadowOAM[i+9].attr0 = ATTR0_HIDE;
        } else {
            if ((makeup[i].worldCol - l1HOff <= 240) && (makeup[i].worldRow - l1VOff <= 170)
            && (makeup[i].worldCol - l1HOff) >= -10 && (makeup[i].worldRow - l1VOff >= -20)) {
                if (i < 2) {
                    shadowOAM[i+9].attr0 = (ROWMASK & (makeup[i].worldRow - l1VOff)) | ATTR0_4BPP | ATTR0_SQUARE;
                    shadowOAM[i+9].attr1 = (COLMASK & (makeup[i].worldCol - l1HOff)) | ATTR1_TINY;
                    if (i == 0) {
                        shadowOAM[i+9].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 10); 
                    } else if (i == 1) {
                        shadowOAM[i+9].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 12); 
                    }
                } else {
                    shadowOAM[i+9].attr0 = (ROWMASK & (makeup[i].worldRow - l1VOff)) | ATTR0_4BPP | ATTR0_TALL;
                    shadowOAM[i+9].attr1 = (COLMASK & (makeup[i].worldCol - l1HOff)) | ATTR1_TINY;
                    shadowOAM[i+9].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 14); 
                }
            } else {
                shadowOAM[i+9].attr0 = ATTR0_HIDE;
            }
        }
    }
}

// Initialize snacks
void initSnack() {
    for (int i = 0; i < POMCOUNT; i++) {
        snacks[i].width = 16;
        snacks[i].height = 8;
        snacks[i].hide = 0;
        if (i == 0) {
            snacks[i].worldCol = 8;
            snacks[i].worldRow = 440;
        } else if (i == 1) {
            snacks[i].worldCol = 440; 
            snacks[i].worldRow = MAPHEIGHT/2 + 10;
        }
    }
}

// Update snacks
void updateSnack() {
    // collected by player
    for (int i = 0; i < SNACKCNT; i++) {
        if (collision(player.worldCol, player.worldRow, player.width, player.height, snacks[i].worldCol, snacks[i].worldRow, snacks[i].width, snacks[i].height)
        && BUTTON_PRESSED(BUTTON_A)) {
            snacks[i].hide = 1;
            if (livesLeft < 3 && livesLeft >= 0) {
                lives[livesLeft].active = 1;
                livesLeft++;
                playSoundA(cheat_data, cheat_length, 0);
            }
        }
    }
}

// Draw snacks
void drawSnack() {
    for (int i = 0; i < SNACKCNT; i++) {
        if (snacks[i].hide) {
            shadowOAM[i+12].attr0 = ATTR0_HIDE;
        } else {
            if ((snacks[i].worldCol - l1HOff <= 260) && (snacks[i].worldRow - l1VOff <= 180)
            && (snacks[i].worldCol - l1HOff) >= -20 && (snacks[i].worldRow - l1VOff >= -10)) {
                shadowOAM[i+12].attr0 = (ROWMASK & (snacks[i].worldRow - l1VOff)) | ATTR0_4BPP | ATTR0_WIDE;
                shadowOAM[i+12].attr1 = (COLMASK & (snacks[i].worldCol - l1HOff)) | ATTR1_TINY;
                if (i == 0) {
                    shadowOAM[i+12].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 8); 
                } else if (i == 1) {
                    shadowOAM[i+12].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 9); 
                }
            } else {
                shadowOAM[i+12].attr0 = ATTR0_HIDE;
            }
        }
    }
}

// Initialize mask
void initMask() {
    mask.worldRow = MAPHEIGHT/2 - 20;
    mask.worldCol = 4;
    mask.width = 16;
    mask.height = 8;
    mask.hide = 0;
}

// Update mask
void updateMask() {
    // collected by player
    if (collision(player.worldCol, player.worldRow, player.width, player.height, mask.worldCol, mask.worldRow, mask.width, mask.height)
    && BUTTON_PRESSED(BUTTON_A)) {
        mask.hide = 1;
        objsCollected++;
        playSoundA(gojackets_data, gojackets_length, 0);
    }
}

// Draw mask
void drawMask() {
    // Set up sprite attributes
    if (mask.hide) {
        shadowOAM[15].attr0 |= ATTR0_HIDE;
    } else {
        if ((mask.worldCol - l1HOff <= 250) && (mask.worldRow - l1VOff <= 170)
        && (mask.worldCol - l1HOff) >= -10 && (mask.worldRow - l1VOff >= -10)) {
            shadowOAM[15].attr0 = (ROWMASK & (mask.worldRow - l1VOff)) | ATTR0_4BPP | ATTR0_WIDE;
            shadowOAM[15].attr1 = (COLMASK & (mask.worldCol - l1HOff)) | ATTR1_TINY;
            shadowOAM[15].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 3);
        } else {
            shadowOAM[15].attr0 |= ATTR0_HIDE;
        }
    }
}