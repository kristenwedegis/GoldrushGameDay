#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "level1.h"
#include "level1objects.h"
#include "collisionmap.h"
#include "sound.h"
#include "gojackets.h"
#include "loselife.h"
#include "cheat.h"

// Variables
ANISPRITE player;
ANISPRITE lives[LIFECOUNT];
ANISPRITE dad;
int livesLeft, l1HOff, l1VOff;
int objsCollected, totalObjs, makeupCollected;
ANISPRITE friend;
ANISPRITE pedestrians[PEDESCNT];
int borrowMup;

// People Sprite Animation States
enum {SPRITEFRONT, SPRITEBACK, SPRITERIGHT, SPRITELEFT, SPRITEIDLE};

// Initalize level 1 of game
void initLevel1() {

    // Place screen on map
    l1VOff = 160;
    l1HOff = 140;

    // Initialize score
    totalObjs = 8;
    objsCollected = 0;
    makeupCollected = 0;
    borrowMup = 0;

    // Initialize player
    initPlayer();
    // Initialize lives
    initLives();
    // Initialize DaD coach
    initDad();
    // Initialize poms
    initPoms();
    // Initialize bag
    initBag();
    // Initialize water bottle
    initWater();
    // Initialize makeup
    initMakeup();
    // Initialize snacks
    initSnack();
    // Initialize mask
    initMask();
    // Initialize teammate friend :)
    initFriend();
    // Initialize COVID-19 infected pedestrians
    initCovid();
}

// Updates level 1 each frame
void updateLevel1() {
	// Update player
    updatePlayer();
    // Update DaD coach
    updateDad();
    // Update poms
    updatePoms();
    // Update bag
    updateBag();
    // Update water bottle
    updateWater();
    // Update makeup
    updateMakeup();
    // Update snacks
    updateSnack();
    // Update mask
    updateMask();
    // Update teammate friend :)
    updateFriend();
    // Update COVID-19 infected pedestrians
    updateCovid();
}

// Draws level 1 each frame
void drawLevel1() {
    // Draw player
    drawPlayer();
    // Draw lives
    drawLives();
    // Draw DaD coach
    drawDad();
    // Draw poms
    drawPoms();
    // Draw bag
    drawBag();
    // Draw water bottle
    drawWater();
    // Draw makeup
    drawMakeup();
    // Draw snacks
    drawSnack();
    // Draw mask
    drawMask();
    // Draw teammate friend :)
    drawFriend();
    // Draw COVID-19 infected pedestrians
    drawCovid();

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    REG_BG0HOFF = l1HOff;
    REG_BG0VOFF = l1VOff;
}

// Initalize player
void initPlayer() { 
    player.worldRow = SCREENHEIGHT/2 - player.width/2 + l1VOff;
    player.worldCol = SCREENWIDTH/2 - player.height/2 + l1HOff;
    player.rdel = 1;
    player.cdel = 1;
    player.width = 16;
    player.height = 32;
    player.aniCounter = 0;
    player.aniState = SPRITEFRONT;
    player.curFrame = 0;
    player.numFrames = 4;
}

// Update the player
void updatePlayer() {
    // Player controls: movement and animation state
	if (BUTTON_HELD(BUTTON_LEFT)) {
        if ((player.worldCol > 0)
        && collisionmapBitmap[OFFSET(player.worldCol - player.cdel, player.worldRow, MAPWIDTH)]
        && collisionmapBitmap[OFFSET(player.worldCol - player.cdel, player.worldRow + player.height - 1, MAPWIDTH)]) {            
            player.worldCol -= player.cdel;
            if (l1HOff > 0 && player.worldCol - l1HOff < SCREENWIDTH / 2) {
                l1HOff--;
            }
        }
	} else if (BUTTON_HELD(BUTTON_RIGHT) && player.screenCol + player.width - 1 < SCREENWIDTH - player.cdel) {
		if ((player.worldCol + player.width < MAPWIDTH)
        && collisionmapBitmap[OFFSET(player.worldCol + player.width + player.cdel - 1, player.worldRow, MAPWIDTH)]
        && collisionmapBitmap[OFFSET(player.worldCol + player.width + player.cdel - 1, player.worldRow + player.height - 1, MAPWIDTH)]) {
            player.worldCol += player.cdel;
            if (l1HOff < MAPWIDTH - SCREENWIDTH && player.worldCol - l1HOff > SCREENWIDTH / 2) {
                l1HOff++;
            }
        }
	} else if (BUTTON_HELD(BUTTON_UP)) { 
		if ((player.worldRow > 0)
        && collisionmapBitmap[OFFSET(player.worldCol, player.worldRow - player.rdel, MAPWIDTH)]
        && collisionmapBitmap[OFFSET(player.worldCol + player.width - 1, player.worldRow - player.rdel, MAPWIDTH)]) {
            player.worldRow -= player.rdel;
            if (l1VOff > 0 && player.worldRow - l1VOff < SCREENHEIGHT / 2) { 
                l1VOff--;
            }
        }
    } else if (BUTTON_HELD(BUTTON_DOWN)) { 
	 	if ((player.worldRow + player.height < MAPHEIGHT)
            && collisionmapBitmap[OFFSET(player.worldCol, player.worldRow + player.height + player.rdel - 1, MAPWIDTH)]
            && collisionmapBitmap[OFFSET(player.worldCol + player.width - 1, player.worldRow + player.height + player.rdel - 1, MAPWIDTH)]) {
            player.worldRow += player.rdel;
            if (l1VOff < MAPHEIGHT - SCREENHEIGHT && player.worldRow - l1VOff > SCREENHEIGHT / 2) {
                l1VOff++;
            }
        }
	}
    animatePlayer();   
}

// Handle player animation states
void animatePlayer() {

    // Set previous state to current state
    player.prevAniState = player.aniState;
    player.aniState = SPRITEIDLE;

    // Change the animation frame every 8 frames of gameplay
    if(player.aniCounter % 8 == 0) {
        player.curFrame = (player.curFrame + 1) % player.numFrames;
    }

    // Control movement and change animation state
    if(BUTTON_HELD(BUTTON_UP))
        player.aniState = SPRITEBACK;
    if(BUTTON_HELD(BUTTON_DOWN))
        player.aniState = SPRITEFRONT;
    if(BUTTON_HELD(BUTTON_LEFT))
        player.aniState = SPRITELEFT;
    if(BUTTON_HELD(BUTTON_RIGHT))
        player.aniState = SPRITERIGHT;

    // If the player is idle, frame is player standing
    if (player.aniState == SPRITEIDLE) {
        player.curFrame = 0;
        player.aniCounter = 0;
        player.aniState = player.prevAniState;
    } else {
        player.aniCounter++;
    }
}

// Draw player
void drawPlayer() {
    // Set up sprite attributes
    if (player.hide) {
        shadowOAM[0].attr0 |= ATTR0_HIDE;
    } else {
        shadowOAM[0].attr0 = (ROWMASK & (player.worldRow - l1VOff)) | ATTR0_TALL;
        shadowOAM[0].attr1 = (COLMASK & (player.worldCol - l1HOff)) | ATTR1_MEDIUM;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(player.aniState*2, player.curFrame*4);
    }
}

// Initialize lives
void initLives() {
    livesLeft = LIFECOUNT;
    int colStart = 2;
    for (int i = 0; i < LIFECOUNT; i++) {
        lives[i].screenRow = 2;
        lives[i].screenCol = colStart;
        lives[i].width = 8;
        lives[i].height = 8;
        lives[i].hide = 0;
        lives[i].active = 1;
        colStart += 10;
    }
}

// Update lives
void updateLives() {
    playSoundA(loselife_data, loselife_length, 0);
	if (livesLeft > 0) {
        livesLeft--;
        lives[livesLeft].active = 0;
    }
}

// Draw Lives
void drawLives() {
    for (int i = 0; i < LIFECOUNT; i++) {
        if (lives[i].active) {
            shadowOAM[i+1].attr0 = lives[i].screenRow | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[i+1].attr1 = lives[i].screenCol | ATTR1_TINY;
            shadowOAM[i+1].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 2);     
        } else if (!lives[i].active || lives[i].hide) {
            shadowOAM[i+1].attr0 = ATTR0_HIDE;
        }
    }
}

// Initialize DaD coach
void initDad() {
    dad.worldRow = 332;
    dad.worldCol = 0;
    dad.cdel = 1;
    dad.width = 16;
    dad.height = 32;
    dad.aniCounter = 0;
    dad.aniState = SPRITERIGHT;
    dad.curFrame = 0;
    dad.numFrames = 4;
}

// Update DaD coach
void updateDad() {
    if (dad.worldCol >= MAPWIDTH) {
        dad.worldCol = 0;
    }
    // Make DaD walk across screen
    dad.worldCol += dad.cdel;
    dad.aniCounter++;
    // Set previous state to current state
    dad.prevAniState = dad.aniState;
    dad.aniState = SPRITERIGHT;
    // Change the animation frame every 8 frames of gameplay
    if(dad.aniCounter % 8 == 0) {
        dad.curFrame = (dad.curFrame + 1) % dad.numFrames;
    }
    // Oh no! Ran into DaD
    if (collision(player.worldCol, player.worldRow, player.width, player.height, dad.worldCol, dad.worldRow, dad.width, dad.height)) {
        if (livesLeft == 0) {
            livesLeft = -1;
        } else {
            l1VOff = 165;
            l1HOff = 150;
            player.worldRow = SCREENHEIGHT/2 - player.width/2 + l1VOff;
            player.worldCol = SCREENWIDTH/2 - player.height/2 + l1HOff;
            updateLives();
        }
    }
}


// Draw DaD coach
void drawDad() {
    // Set up sprite attributes
    if (dad.hide) {
        shadowOAM[4].attr0 |= ATTR0_HIDE;
    } else {
        if ((dad.worldCol - l1HOff <= 260) && (dad.worldRow - l1VOff <= 190)
        && (dad.worldCol - l1HOff) >= -20 && (dad.worldRow - l1VOff >= -40)) {
            shadowOAM[4].attr0 = (ROWMASK & (dad.worldRow - l1VOff)) | ATTR0_TALL;
            shadowOAM[4].attr1 = (COLMASK & (dad.worldCol - l1HOff)) | ATTR1_MEDIUM;
            shadowOAM[4].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(dad.aniState*7, dad.curFrame*4);
        } else {
            shadowOAM[4].attr0 |= ATTR0_HIDE;
        }
    }
}

// Initialize teammate friend
void initFriend() {
    friend.worldRow = 131;
    friend.worldCol = MAPWIDTH;
    friend.cdel = 1;
    friend.width = 16;
    friend.height = 32;
    friend.aniCounter = 0;
    friend.aniState = SPRITELEFT;
    friend.curFrame = 0;
    friend.numFrames = 4;
    friend.hide = 0;
    friend.active = 1;
}

// Update teammate friend
void updateFriend() {
    if (friend.worldCol <= 0) {
        friend.worldCol = MAPWIDTH;
    }
    // Make friend walk across screen
    friend.worldCol -= friend.cdel;
    friend.aniCounter++;
    // Set previous state to current state
    friend.prevAniState = friend.aniState;
    friend.aniState = SPRITELEFT;
    // Change the animation frame every 8 frames of gameplay
    if(friend.aniCounter % 8 == 0) {
        friend.curFrame = (friend.curFrame + 1) % friend.numFrames;
    }
    // YAY you ran into a friend!! no more makeup!
    if (collision(player.worldCol, player.worldRow, player.width, player.height, friend.worldCol, friend.worldRow, friend.width, friend.height)
    && friend.active == 1) {
        friend.hide = 1;
        friend.active = 0;
        l1VOff = 165;
        l1HOff = 150;
        player.worldRow = SCREENHEIGHT/2 - player.width/2 + l1VOff;
        player.worldCol = SCREENWIDTH/2 - player.height/2 + l1HOff;
        for (int i = 0; i < MAKEUPCNT; i++) {
            makeup[i].hide = 1;
        }
        totalObjs = 5;
        objsCollected = objsCollected - makeupCollected;
        borrowMup = 1;
    }
}

// Draw teammate friend
void drawFriend() {
    // Set up sprite attributes
    if (friend.hide) {
        shadowOAM[16].attr0 |= ATTR0_HIDE;
    } else {
        if ((friend.worldCol - l1HOff <= 260) && (friend.worldRow - l1VOff <= 190)
        && (friend.worldCol - l1HOff) >= -20 && (friend.worldRow - l1VOff >= -40)) {
            shadowOAM[16].attr0 = (ROWMASK & (friend.worldRow - l1VOff)) | ATTR0_TALL;
            shadowOAM[16].attr1 = (COLMASK & (friend.worldCol - l1HOff)) | ATTR1_MEDIUM;
            shadowOAM[16].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(friend.aniState*2, 16 + friend.curFrame*4);
        } else {
            shadowOAM[16].attr0 |= ATTR0_HIDE;
        }
    }
}

// Initialize pedestrians (potentially w COVID)
void initCovid() {
    for (int i = 0; i < PEDESCNT; i++) {
        pedestrians[i].rdel = 1;
        pedestrians[i].width = 16;
        pedestrians[i].height = 32;
        pedestrians[i].aniCounter = 0;
        pedestrians[i].curFrame = 0;
        pedestrians[i].numFrames = 4;
        if (i == 0) {
            pedestrians[i].worldRow = 0;
            pedestrians[i].worldCol = 145;
            pedestrians[i].aniState = SPRITEFRONT;
        } else if (i == 1) {
            pedestrians[i].worldRow = MAPHEIGHT;
            pedestrians[i].worldCol = 373;
            pedestrians[i].aniState = SPRITEBACK;
        }
    }
}

// Update pedestrians (potentially w COVID)
void updateCovid() {
    for (int i = 0; i < PEDESCNT; i++) {
        if (i == 0){
            if (pedestrians[i].worldRow >= MAPWIDTH) {
                pedestrians[i].worldRow = 0;
            }
            // Make pedestrian walk down screen
            pedestrians[i].worldRow += pedestrians[i].rdel;
            pedestrians[i].aniCounter++;
            // Set previous state to current state
            pedestrians[i].prevAniState = pedestrians[i].aniState;
            pedestrians[i].aniState = SPRITEFRONT;
        } else if (i == 1) {
            if (pedestrians[i].worldRow <= 0) {
                pedestrians[i].worldRow = MAPHEIGHT;
            }
            // Make pedestrian walk up screen
            pedestrians[i].worldRow -= pedestrians[i].rdel;
            pedestrians[i].aniCounter++;
            // Set previous state to current state
            pedestrians[i].prevAniState = pedestrians[i].aniState;
            pedestrians[i].aniState = SPRITEBACK;
        }
        
        // Change the animation frame every 8 frames of gameplay
        if(pedestrians[i].aniCounter % 8 == 0) {
            pedestrians[i].curFrame = (pedestrians[i].curFrame + 1) % pedestrians[i].numFrames;
        }
        // Oh no! Ran into COVID pedestrian
        if (collision(player.worldCol, player.worldRow, player.width, player.height, pedestrians[i].worldCol, pedestrians[i].worldRow, pedestrians[i].width, pedestrians[i].height)) {
            if (livesLeft == 0) {
                livesLeft = -1;
            } else {
                l1VOff = 165;
                l1HOff = 150;
                player.worldRow = SCREENHEIGHT/2 - player.width/2 + l1VOff;
                player.worldCol = SCREENWIDTH/2 - player.height/2 + l1HOff;
                updateLives();
            }
        }
    }
}

// Draw pedestrians (potentially w COVID)
void drawCovid() {
    for (int i = 0; i < PEDESCNT; i++) {
        // Set up sprite attributes
        if (pedestrians[i].hide) {
            shadowOAM[i+17].attr0 |= ATTR0_HIDE;
        } else {
            if ((pedestrians[i].worldCol - l1HOff <= 260) && (pedestrians[i].worldRow - l1VOff <= 190)
            && (pedestrians[i].worldCol - l1HOff) >= -20 && (pedestrians[i].worldRow - l1VOff >= -40)) {
                shadowOAM[i+17].attr0 = (ROWMASK & (pedestrians[i].worldRow - l1VOff)) | ATTR0_TALL;
                shadowOAM[i+17].attr1 = (COLMASK & (pedestrians[i].worldCol - l1HOff)) | ATTR1_MEDIUM;
                if (i == 0) {
                    shadowOAM[i+17].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(18+pedestrians[i].aniState*2, pedestrians[i].curFrame*4);                    
                } else if (i == 1) {
                    shadowOAM[i+17].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(18+pedestrians[i].aniState*2, pedestrians[i].curFrame*4);
                }
            } else {
                shadowOAM[i+17].attr0 |= ATTR0_HIDE;
            }
        }
    }
}