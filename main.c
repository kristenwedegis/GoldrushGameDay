/*
FINISHED
    - everything lol :-)
HOW TO PLAY
    - instructions outlined in game!
*/

#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "start.h"
#include "spritesheet.h"
#include "cursor.h"
#include "instructions1.h"
#include "level1.h"
#include "level1bg.h"
#include "pause.h"
#include "poms.h"
#include "borrowprompt.h"
#include "win1.h"
#include "lose1.h"
#include "instructions2.h"
#include "level2bg.h"
#include "level2.h"
#include "win2.h"
#include "lose2.h"
#include "sound.h"
#include "Fantasia.h"
#include "whiteandgold.h"
#include "almamater.h"
#include "fanfare.h"
#include "Budweiser.h"
#include "thirddown.h"
#include "cheat.h"

// Prototypes
void initialize();

// State Prototypes
void goToStart();
void start();
void goToInstructions1();
void instructions1();
void start();
void goToGame1();
void game1();
void goToPause();
void pause();
void goToBorrowMakeup();
void borrowMakeup();
void goToWin1();
void win1();
void goToLose1();
void lose1();
void goToInstructions2();
void instructions2();
void goToGame2();
void game2();
void goToWin2();
void win2();
void goToLose2();
void lose2();

// States
enum
{
    START,
    INSTRUCTIONS1,
    GAME1,
    PAUSE,
    BORROWMAKEUP,
    WIN1,
    LOSE1,
    INSTRUCTIONS2,
    GAME2,
    WIN2,
    LOSE2
};
int state;
int level;

// Button Variables
unsigned short buttons;
unsigned short oldButtons;

// Vertical and Horizontal Offset
int vOff;
int hOff;

// Shadow OAM
OBJ_ATTR shadowOAM[128];

int main()
{
    initialize();

    while (1)
    {
        // Update button variables
        oldButtons = buttons;
        buttons = BUTTONS;

        // State Machine
        switch (state)
        {
        case START:
            start();
            break;
        case INSTRUCTIONS1:
            instructions1();
            break;
        case GAME1:
            game1();
            break;
        case PAUSE:
            pause();
            break;
        case BORROWMAKEUP:
            borrowMakeup();
            break;
        case WIN1:
            win1();
            break;
        case LOSE1:
            lose1();
            break;
        case INSTRUCTIONS2:
            instructions2();
            break;
        case GAME2:
            game2();
            break;
        case WIN2:
            win2();
            break;
        case LOSE2:
            lose2();
            break;
        }
    }
}

// Sets up GBA
void initialize()
{
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_LARGE;

    buttons = BUTTONS;
    oldButtons = 0;

    setupSounds();
	setupInterrupts();

    goToStart();
}

// Sets up the start state
void goToStart() {
    // Set up start screen - load into DMA
    DMANow(3, startPal, PALETTE, startPalLen/2);
    DMANow(3, startTiles, &CHARBLOCK[0], startTilesLen/2);
    DMANow(3, startMap, &SCREENBLOCK[28], startMapLen/2);

    // Set up the sprites - load into DMA
    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen / 2);
    DMANow(3, spritesheetPal, SPRITEPALETTE, spritesheetPalLen / 2);

    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_LARGE;

    // Hide sprites, vBlank, and page flip
    hideSprites();
    waitForVBlank();
    flipPage();
    initCursor();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    // set level
    level = 1;
    // audio
    stopSoundA();
    stopSoundB();
	playSoundA(Fantasia_data, Fantasia_length, 1);

    // change state to START
    state = START;
}

// Runs every frame of the start state
void start() {
    waitForVBlank();
    updateCursor();
    drawCursor();
    // State transition
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        //REG_DISPCTL = SPRITE_ENABLE;
        if (goInstr == 1) {
            goToInstructions1();
        } else if (goInstr == 0) {
            initLevel1();
            stopSoundA();
            playSoundB(whiteandgold_data, whiteandgold_length, 1);
            goToGame1();
        }
    }
    DMANow(3, shadowOAM, OAM, 128 * 4);
}

// Sets up level 1 instructions state
void goToInstructions1() {
    // Set up instr. screen - load into DMA
    DMANow(3, instructions1Pal, PALETTE, instructions1PalLen/2);
    DMANow(3, instructions1Tiles, &CHARBLOCK[1], instructions1TilesLen/2);
    DMANow(3, instructions1Map, &SCREENBLOCK[26], instructions1MapLen/2);
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
    REG_BG0CNT = BG_CHARBLOCK(1) | BG_SCREENBLOCK(26) | BG_4BPP | BG_SIZE_LARGE;
    // Hide sprites, vBlank, and page flip
    hideSprites();
    waitForVBlank();
    flipPage();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    state = INSTRUCTIONS1;
}

// Runs every frame of level 1 instructions state
void instructions1() {
    // State transition
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToStart();
    } else if (BUTTON_PRESSED(BUTTON_START)) {
        initLevel1();
        stopSoundA();
        playSoundB(whiteandgold_data, whiteandgold_length, 1);
        goToGame1();
    }
}

// Sets up level 1 game state
void goToGame1() {

    // Set up level 1 game screen - load into DMA
    DMANow(3, level1bgPal, PALETTE, level1bgPalLen/2);
    DMANow(3, level1bgTiles, &CHARBLOCK[0], level1bgTilesLen/2);
    DMANow(3, level1bgMap, &SCREENBLOCK[28], 1024*4);

    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_LARGE;

    // Set up the sprites - load into DMA
    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen / 2);
    DMANow(3, spritesheetPal, SPRITEPALETTE, spritesheetPalLen / 2);
    // Hide sprites, vBlank, and page flip
    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    // change state to GAME1
    state = GAME1;
}

// Runs every frame of level 1 game state
void game1() {
    updateLevel1();
    drawLevel1();

    // State transitions
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPause();
    } else if (livesLeft == -1) {
        goToLose1();
    } else if (objsCollected == totalObjs) {
        goToWin1();
    } else if (borrowMup == 1) {
        goToBorrowMakeup();
        borrowMup = 0;
    }
}

// Sets up the pause state
void goToPause() {
    // Set up display control register
    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE;

    REG_BG0HOFF = 0;
    REG_BG0VOFF = 0;

    DMANow(3, pausePal, PALETTE, pausePalLen/2);
    REG_BG1CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_SIZE_WIDE | BG_4BPP;
    DMANow(3, pauseTiles, &CHARBLOCK[0], pauseTilesLen/2);
    DMANow(3, pauseMap, &SCREENBLOCK[28], pauseMapLen/2);
    REG_BG0CNT = BG_CHARBLOCK(2) | BG_SCREENBLOCK(26) | BG_SIZE_WIDE | BG_4BPP;
    DMANow(3, pomsTiles, &CHARBLOCK[2], pomsTilesLen/2);
    DMANow(3, pomsMap, &SCREENBLOCK[26], pomsMapLen/2);
  
    hideSprites();
    waitForVBlank();
    flipPage();

    pauseSoundB();
    playSoundA(almamater_data, almamater_length, 1);

    state = PAUSE;
}

// Runs every frame of the pause state
void pause() {
    hOff++;
    REG_BG0HOFF = hOff/2;
    REG_BG1HOFF = hOff/4;
    // State transition
    if (BUTTON_PRESSED(BUTTON_START)) {
        stopSoundA();
        unpauseSoundB();
        if (level == 1) {
            goToGame1();
        } else if (level == 2) {
            REG_BG0HOFF = 0;
            goToGame2();
        }
    } else if (BUTTON_PRESSED(BUTTON_SELECT)) {
        REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
        REG_BG0HOFF = 0;
        goToStart();
    }
    waitForVBlank();
}

// Sets up borrow makeup prompt state
void goToBorrowMakeup() {
    REG_BG0HOFF = 0;
    REG_BG0VOFF = 0;

    DMANow(3, borrowpromptPal, PALETTE, borrowpromptPalLen/2);
    DMANow(3, borrowpromptTiles, &CHARBLOCK[0], borrowpromptTilesLen/2);
    DMANow(3, borrowpromptMap, &SCREENBLOCK[28], borrowpromptMapLen/2);

    // Set up display controller
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    // Load pause screen into DMA
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_SIZE_WIDE;

    hideSprites();
    waitForVBlank();
    flipPage();
    state = BORROWMAKEUP;
}

// Runs every frame of borrow makeup state
void borrowMakeup() {
    // State transition
    if (BUTTON_PRESSED(BUTTON_B)) {
        playSoundA(cheat_data, cheat_length, 0);
        goToGame1();
    }
}

// Sets up level 1 win state
void goToWin1() {
    // Set up display controller
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    // Load win screen into DMA
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_SIZE_WIDE;
    hOff = 0;
    vOff = 0;
    REG_BG0VOFF = vOff;
    REG_BG0HOFF = hOff;
    // Load win screen into DMA
    DMANow(3, win1Pal, PALETTE, win1PalLen/2);
    DMANow(3, win1Tiles, &CHARBLOCK[0], win1TilesLen/2);
    DMANow(3, win1Map, &SCREENBLOCK[28], win1MapLen/2);
    hideSprites();
    waitForVBlank();
    flipPage();
    DMANow(3, shadowOAM, OAM, 128*4);
    // set level
    level = 2;

	stopSoundB();  
	playSoundA(fanfare_data, fanfare_length, 1);

    state = WIN1;
}

// Runs every frame of level 1 win state
void win1() {
    // State transition
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToInstructions2();
    }
}

// Sets up level 1 lose state
void goToLose1() {
    // Set up display controller
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    // Load pause screen into DMA
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_SIZE_WIDE;
    hOff = 0;
    vOff = 0;
    REG_BG0VOFF = vOff;
    REG_BG0HOFF = hOff;
    // Load lose screen into DMA
    DMANow(3, lose1Pal, PALETTE, lose1PalLen/2);
    DMANow(3, lose1Tiles, &CHARBLOCK[0], lose1TilesLen/2);
    DMANow(3, lose1Map, &SCREENBLOCK[28], lose1MapLen/2);
    hideSprites();
    waitForVBlank();
    flipPage();
    DMANow(3, shadowOAM, OAM, 128*4);

	stopSoundB();
	playSoundA(thirddown_data, thirddown_length, 1);

    state = LOSE1;
}

// Runs every frame of level 1 lose state
void lose1() {
    waitForVBlank();
    // State transition
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToStart();
    }
}

// Sets up level 2 instructions state
void goToInstructions2() {
    // Set up instr. screen - load into DMA
    DMANow(3, instructions2Pal, PALETTE, instructions2PalLen/2);
    DMANow(3, instructions2Tiles, &CHARBLOCK[0], instructions2TilesLen/2);
    DMANow(3, instructions2Map, &SCREENBLOCK[28], instructions2MapLen/2);
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_LARGE;
    // Hide sprites, vBlank, and page flip
    hideSprites();
    waitForVBlank();
    flipPage();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    state = INSTRUCTIONS2;
}

// Runs every frame of level 1 instructions state
void instructions2() {
    // State transition
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToStart();
    } else if (BUTTON_PRESSED(BUTTON_START)) {
        initLevel2();
        stopSoundA();  
	    playSoundB(Budweiser_data, Budweiser_length, 1);
        goToGame2();
    }
}

// Sets up level 2 game state
void goToGame2() {

    // Set up level 2 game screen - load into DMA
    DMANow(3, level2bgPal, PALETTE, level2bgPalLen/2);
    DMANow(3, level2bgTiles, &CHARBLOCK[0], level2bgTilesLen/2);
    DMANow(3, level2bgMap, &SCREENBLOCK[28], 1024*4);

    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_4BPP | BG_SIZE_LARGE;

    // Set up the sprites - load into DMA
    DMANow(3, spritesheetTiles, &CHARBLOCK[4], spritesheetTilesLen / 2);
    DMANow(3, spritesheetPal, SPRITEPALETTE, spritesheetPalLen / 2);
    // Hide sprites, vBlank, and page flip
    hideSprites();
    waitForVBlank();
    flipPage();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    // set level
    level = 2;

    // change state to GAME2
    state = GAME2;
}

// Runs every frame of level 2 game state
void game2() {
    updateLevel2();
    drawLevel2();

    // State transitions
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToPause();
    } else if (livesLeftL2 == -1) {
        goToLose2();
    } else if (movesLeft == 0) {
        goToWin2();
    }
}

// Sets up level 2 win state
void goToWin2() {
    // Set up display controller
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    // Load win screen into DMA
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_SIZE_WIDE;
    // Load win screen into DMA
    DMANow(3, win2Pal, PALETTE, win2PalLen/2);
    DMANow(3, win2Tiles, &CHARBLOCK[0], win2TilesLen/2);
    DMANow(3, win2Map, &SCREENBLOCK[28], win2MapLen/2);
    hideSprites();
    waitForVBlank();
    flipPage();
    DMANow(3, shadowOAM, OAM, 128*4);
    
    stopSoundB();  
	playSoundA(fanfare_data, fanfare_length, 1);

    state = WIN2;
}

// Runs every frame of level 2 win state
void win2() {
    // State transition
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToStart();
    }
}

// Sets up level 2 lose state
void goToLose2() {
    // Set up display controller
    REG_DISPCTL = MODE0 | BG0_ENABLE;
    // Load pause screen into DMA
    REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(28) | BG_SIZE_WIDE;
    // Load lose screen into DMA
    DMANow(3, lose2Pal, PALETTE, lose2PalLen/2);
    DMANow(3, lose2Tiles, &CHARBLOCK[0], lose2TilesLen/2);
    DMANow(3, lose2Map, &SCREENBLOCK[28], lose2MapLen/2);
    hideSprites();
    waitForVBlank();
    flipPage();
    DMANow(3, shadowOAM, OAM, 128*4);

    stopSoundB();  
	playSoundA(thirddown_data, thirddown_length, 1);

    state = LOSE2;
}

// Runs every frame of level 2 lose state
void lose2() {
    waitForVBlank();
    // State transition
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToStart();
    }
}