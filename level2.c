#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "level2.h"
#include "sound.h"
#include "gojackets.h"
#include "loselife.h"
#include "cheat.h"

// Variables
ANISPRITE playerL2;
ANISPRITE livesL2[LIFECOUNT];
ANISPRITE dad;
int livesLeftL2, movesLeft;
ANISPRITE moves[DANCEMOVES];
ANISPRITE buzz;
ANISPRITE dadL2;
ANISPRITE team[TEAMCOUNT];
ANISPRITE fans[FANCOUNT];

// People Sprite Animation States
enum {PLAYERFRONT1, PLAYERBACK, PLAYERRIGHT, PLAYERLEFT, PLAYERFRONT2, PLAYERFRONT3, PLAYERIDLE}; // PLAYER
enum {SPRITEFRONT, SPRITEBACK, SPRITERIGHT, SPRITELEFT, SPRITEIDLE}; // ALL OTHER

// Initalize level 2 of game
void initLevel2() {

    // Initialize score
    movesLeft = DANCEMOVES;

    // Initialize playerL2
    initPlayerL2();
    // Initialize lives
    initLivesL2();
    // Initialize dance move sequence
    initDanceMoves();
    // Initialize Buzz
    initBuzz();
    // Initialize DaD coach
    initDadL2();
    // Initialize team
    initTeam();
    // Initialize fans
    initFans();
}

// Updates level 2 each frame
void updateLevel2() {
	// Update playerL2
    updatePlayerL2();
    // Update dance move sequence
    updateDanceMoves();
    // Update Buzz
    updateBuzz();
    // Update DaD coach
    updateDadL2();
    // Update team
    updateTeam();
    // Update fans
    updateFans();
}

// Draws level 2 each frame
void drawLevel2() {
    // Draw playerL2
    drawPlayerL2();
    // Draw lives
    drawLivesL2();
    // Draw dance move sequence
    drawDanceMoves();
    // Draw Buzz
    drawBuzz();
    // Draw DaD coach
    drawDadL2();
    // Draw team
    drawTeam();
    // Draw fans
    drawFans();

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128 * 4);
}

// Initalize playerL2
void initPlayerL2() { 
    playerL2.screenRow = 126;
    playerL2.screenCol = 120;
    playerL2.rdel = 1;
    playerL2.cdel = 1;
    playerL2.width = 16;
    playerL2.height = 32;
    playerL2.aniCounter = 0;
    playerL2.aniState = PLAYERFRONT1;
    playerL2.curFrame = 0;
    playerL2.numFrames = 4;
}

// Update the playerL2
void updatePlayerL2() {
    // playerL2 controls: movement and animation state
	if (BUTTON_HELD(BUTTON_LEFT)) {
        if ((playerL2.screenCol > 0)) {            
            playerL2.screenCol -= playerL2.cdel;
        }
	} else if (BUTTON_HELD(BUTTON_RIGHT) && playerL2.screenCol + playerL2.width - 1 < SCREENWIDTH - playerL2.cdel) {
		if ((playerL2.screenCol + playerL2.width < SCREENWIDTH)) {
            playerL2.screenCol += playerL2.cdel;
        }
	} else if (BUTTON_HELD(BUTTON_UP)) {
		if (playerL2.screenRow > 0) {
            playerL2.screenRow -= playerL2.rdel;
        }
    } else if (BUTTON_HELD(BUTTON_DOWN)) {
	 	if ((playerL2.screenRow + playerL2.height < SCREENHEIGHT)) {
            playerL2.screenRow += playerL2.rdel;
        }
	}
    animatePlayerL2();
}

// Handle playerL2 animation states
void animatePlayerL2() {

    // Set previous state to current state
    playerL2.prevAniState = playerL2.aniState;
    playerL2.aniState = PLAYERIDLE;

    // Change the animation frame every 8 frames of gameplay
    if(playerL2.aniCounter % 8 == 0) {
        playerL2.curFrame = (playerL2.curFrame + 1) % playerL2.numFrames;
    }

    // Control movement and change animation state
    if (BUTTON_PRESSED(BUTTON_L))
        playerL2.aniState = PLAYERFRONT2;
    if (BUTTON_PRESSED(BUTTON_R))
        playerL2.aniState = PLAYERFRONT3;
    if(BUTTON_HELD(BUTTON_UP))
        playerL2.aniState = PLAYERBACK;
    if(BUTTON_HELD(BUTTON_DOWN))
        playerL2.aniState = PLAYERFRONT1;
    if(BUTTON_HELD(BUTTON_LEFT))
        playerL2.aniState = PLAYERLEFT;
    if(BUTTON_HELD(BUTTON_RIGHT))
        playerL2.aniState = PLAYERRIGHT;

    if (playerL2.aniState == PLAYERIDLE) {
        playerL2.curFrame = 0;
        playerL2.aniCounter = 0;
        playerL2.aniState = playerL2.prevAniState;
    } else {
        playerL2.aniCounter++;
    }
}

// Draw playerL2
void drawPlayerL2() {
    // Set up sprite attributes
    if (playerL2.hide) {
        shadowOAM[0].attr0 |= ATTR0_HIDE;
    } else {
        shadowOAM[0].attr0 = (playerL2.screenRow) | ATTR0_TALL;
        shadowOAM[0].attr1 = (playerL2.screenCol) | ATTR1_MEDIUM;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(10 + playerL2.aniState*2, 16 + playerL2.curFrame*4);
    }
}

// Initialize lives
void initLivesL2() {
    livesLeftL2 = LIFECOUNT;
    int colStart = 2;
    for (int i = 0; i < LIFECOUNT; i++) {
        livesL2[i].screenRow = 2;
        livesL2[i].screenCol = colStart;
        livesL2[i].width = 8;
        livesL2[i].height = 8;
        livesL2[i].hide = 0;
        livesL2[i].active = 1;
        colStart += 10;
    }
}

// Update lives
void updateLivesL2() {
	playSoundA(loselife_data, loselife_length, 0);
    livesLeftL2--;
    if (livesLeftL2 >= 0) {
        livesL2[livesLeftL2].active = 0;
    }
}

// Draw Lives
void drawLivesL2() {
    for (int i = 0; i < LIFECOUNT; i++) {
        if (livesL2[i].active) {
            shadowOAM[i+1].attr0 = livesL2[i].screenRow | ATTR0_4BPP | ATTR0_SQUARE;
            shadowOAM[i+1].attr1 = livesL2[i].screenCol | ATTR1_TINY;
            shadowOAM[i+1].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(8, 2);     
        } else if (!livesL2[i].active || livesL2[i].hide) {
            shadowOAM[i+1].attr0 = ATTR0_HIDE;
        }
    }
}

// Initalize dance move sequence
void initDanceMoves() {
    for (int i = 0; i < DANCEMOVES; i++) {
        moves[i].width = 16;
        moves[i].height = 32;
        moves[i].hide = 0;
        moves[i].active = 1;
        moves[i].numFrames = 6;
    }
    moves[0].aniState = PLAYERFRONT1;
    moves[0].screenRow = 48;
    moves[0].screenCol = 4;
    moves[0].curFrame = 0;

    moves[1].aniState = PLAYERBACK;
    moves[1].screenRow = 126;
    moves[1].screenCol = 4;
    moves[1].curFrame = 1;

    moves[2].aniState = PLAYERRIGHT;
    moves[2].screenRow = 8;
    moves[2].screenCol = 40;
    moves[2].curFrame = 2;

    moves[3].aniState = PLAYERLEFT;
    moves[3].screenRow = 88;
    moves[3].screenCol = 40;
    moves[3].curFrame = 3;

    moves[4].aniState = PLAYERFRONT2;
    moves[4].screenRow = 126;
    moves[4].screenCol = 80;
    moves[4].curFrame = 4;

    moves[5].aniState = PLAYERFRONT3;
    moves[5].screenRow = 48;
    moves[5].screenCol = 120;
    moves[5].curFrame = 5;

    moves[6].aniState = PLAYERFRONT1;
    moves[6].screenRow = 8;
    moves[6].screenCol = 100;
    moves[6].curFrame = 0;

    moves[7].aniState = PLAYERBACK;
    moves[7].screenRow = 88;
    moves[7].screenCol = 180;
    moves[7].curFrame = 1;

    moves[8].aniState = PLAYERRIGHT;
    moves[8].screenRow = 8;
    moves[8].screenCol = 220;
    moves[8].curFrame = 2;

    moves[9].aniState = PLAYERLEFT;
    moves[9].screenRow = 126;
    moves[9].screenCol = 220; 
    moves[9].curFrame = 3;

    moves[10].aniState = PLAYERBACK;
    moves[10].screenRow = 88;
    moves[10].screenCol = 100;
    moves[10].curFrame = 1;

    moves[11].aniState = PLAYERFRONT3;
    moves[11].screenRow = 8;
    moves[11].screenCol = 180;
    moves[11].curFrame = 5;
}

// Update dance move sequence
void updateDanceMoves() {
    for (int i = 0; i < DANCEMOVES; i++) {
        if (collision(playerL2.screenCol, playerL2.screenRow, playerL2.width, playerL2.height, moves[i].screenCol, moves[i].screenRow, moves[i].width, moves[i].height)
        && BUTTON_PRESSED (BUTTON_A)) {
            if (playerL2.aniState == moves[i].aniState) {
                moves[i].active = 0;
                moves[i].hide = 1;
                movesLeft--;
                playSoundA(gojackets_data, gojackets_length, 0);
            } else {
                if (livesLeftL2 == 0) {
                    livesLeftL2 = -1;
                } else {

                    updateLivesL2();
                }
            }
            playerL2.screenRow = 126;
            playerL2.screenCol = 120;
        }
    }
}

// Draw dance move sequence
void drawDanceMoves() {
    int index = -1;
    for (int i = 0; i < DANCEMOVES; i++) {
        index++;
        if (moves[i].hide) {
            shadowOAM[i+4].attr0 = ATTR0_HIDE;
        } else {
            shadowOAM[i+4].attr0 = (moves[i].screenRow) | ATTR0_TALL;
            shadowOAM[i+4].attr1 = (moves[i].screenCol) | ATTR1_MEDIUM;
            /*if (index >= 6) {
                index = 0;
            }*/
            shadowOAM[i+4].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(26, moves[i].curFrame*4);    
        }
    }
}

// Initialize Buzz
void initBuzz() {
    buzz.screenRow = SCREENHEIGHT;
    buzz.screenCol = 60;
    buzz.rdel = 1;
    buzz.width = 16;
    buzz.height = 32;
    buzz.aniCounter = 0;
    buzz.aniState = SPRITEBACK;
    buzz.curFrame = 0;
    buzz.numFrames = 4;
    buzz.active = 1;
    buzz.hide = 0;
}

// Update Buzz
void updateBuzz() {
    if (buzz.screenRow < 0) {
        buzz.screenRow = SCREENHEIGHT;
    }
    // Make Buzz walk up screen
    buzz.screenRow -= buzz.rdel;
    buzz.aniCounter++;
    // Set previous state to current state
    buzz.prevAniState = buzz.aniState;
    buzz.aniState = SPRITEBACK;
    // Change the animation frame every 8 frames of gameplay
    if(buzz.aniCounter % 8 == 0) {
        buzz.curFrame = (buzz.curFrame + 1) % buzz.numFrames;
    }
    // Buzz Collision!
    if (collision(playerL2.screenCol, playerL2.screenRow, playerL2.width, playerL2.height, buzz.screenCol, buzz.screenRow, buzz.width, buzz.height)
    && BUTTON_PRESSED(BUTTON_B) && buzz.active) {
        playSoundA(cheat_data, cheat_length, 0);
        buzz.hide = 1;
        dadL2.hide = 1;
        dadL2.active = 0;
        buzz.active = 0;
        fans[0].hide = 1;
        fans[0].active = 0;
        fans[1].hide = 1;
        fans[1].active = 0;
        playerL2.screenRow = 126;
        playerL2.screenCol = 120;
    }
}

// Draw Buzz
void drawBuzz() {
    // Set up sprite attributes
    if (buzz.hide) {
        shadowOAM[19].attr0 |= ATTR0_HIDE;
    } else {
        shadowOAM[19].attr0 = (buzz.screenRow) | ATTR0_TALL;
        shadowOAM[19].attr1 = (buzz.screenCol) | ATTR1_MEDIUM;
        shadowOAM[19].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(buzz.aniState*8, 16 + buzz.curFrame*4);
    }
}

// Initialize DaD coach
void initDadL2() {
    dadL2.screenRow = 0;
    dadL2.screenCol = 200;
    dadL2.rdel = 1;
    dadL2.width = 16;
    dadL2.height = 32;
    dadL2.aniCounter = 0;
    dadL2.aniState = SPRITEFRONT;
    dadL2.curFrame = 0;
    dadL2.numFrames = 4;
    dadL2.active = 1;
    dadL2.hide = 0;
}

// Update DaD coach
void updateDadL2() {
    if (dadL2.screenRow >= SCREENHEIGHT) {
        dadL2.screenRow = 0;
    }
    // Make DaD walk down screen
    dadL2.screenRow += dadL2.rdel;
    dadL2.aniCounter++;
    // Set previous state to current state
    dadL2.prevAniState = dadL2.aniState;
    dadL2.aniState = SPRITEFRONT;
    // Change the animation frame every 8 frames of gameplay
    if(dadL2.aniCounter % 8 == 0) {
        dadL2.curFrame = (dadL2.curFrame + 1) % dadL2.numFrames;
    }
    // Oh no! Ran into DaD
    if (collision(playerL2.screenCol, playerL2.screenRow, playerL2.width, playerL2.height, dadL2.screenCol, dadL2.screenRow, dadL2.width, dadL2.height)
    && dadL2.active) {
        if (livesLeftL2 == 0) {
            livesLeftL2 = -1;
        } else {
            playerL2.screenRow = 126;
            playerL2.screenCol = 120;
            updateLivesL2();
        }
    }
}


// Draw DaD coach
void drawDadL2() {
    // Set up sprite attributes
    if (dadL2.hide) {
        shadowOAM[20].attr0 |= ATTR0_HIDE;
    } else {
        shadowOAM[20].attr0 = (dadL2.screenRow) | ATTR0_TALL;
        shadowOAM[20].attr1 = (dadL2.screenCol) | ATTR1_MEDIUM;
        shadowOAM[20].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(10 + dadL2.aniState*2, dadL2.curFrame*4);
    }
}

// Initialize teammates
void initTeam() {
    // row 1
    team[0].screenCol = 80;
    team[0].screenRow = 8;
    team[1].screenCol = 140;
    team[1].screenRow = 8;
    // row 2
    team[2].screenCol = 40;
    team[2].screenRow = 48;
    team[3].screenCol = 180;
    team[3].screenRow = 48;
    // row 3
    team[4].screenCol = 4;
    team[4].screenRow = 88;
    team[5].screenCol = 80;
    team[5].screenRow = 88;
    team[6].screenCol = 140;
    team[6].screenRow = 88;
    team[7].screenCol = 220;
    team[7].screenRow = 88;
    // row 4
    team[8].screenCol = 40;
    team[8].screenRow = 126;
    team[9].screenCol = 180;
    team[9].screenRow = 126;

    // set other attributes
    for (int i = 0; i < TEAMCOUNT; i++) {
        team[i].width = 16;
        team[i].height = 32;
        team[i].hide = 0;
        team[i].active = 1;
        team[i].aniCounter = 0;
        team[i].curFrame = 0;
        team[i].numFrames = 4;
        if (team[i].screenRow == 4 || team[i].screenRow == 88) {
            team[i].aniState = SPRITEFRONT;
        } else if (team[i].screenRow == 48 || team[i].screenRow == 126) {
            team[i].aniState = SPRITEBACK;
        }
    }
}

// Update teammates
void updateTeam() {
    for (int i = 0; i < TEAMCOUNT; i++) {
        // Make friend bounce
        team[i].aniCounter++;
        // Set previous state to current state
        team[i].prevAniState = team[i].aniState;
        if (team[i].screenRow == 8 || team[i].screenRow == 88) {
            team[i].aniState = SPRITEFRONT;
        } else if (team[i].screenRow == 48 || team[i].screenRow == 126) {
            team[i].aniState = SPRITEBACK;
        }
        // Change the animation frame every 8 frames of gameplay
        if (team[i].aniCounter % 8 == 0) {
            team[i].curFrame = (team[i].curFrame + 1) % team[i].numFrames;
        }
        // ahhh! you hit a friend!! not good!!
        if (collision(playerL2.screenCol, playerL2.screenRow, playerL2.width, playerL2.height, team[i].screenCol, team[i].screenRow, team[i].width, team[i].height)) {
            if (livesLeftL2 == 0) {
                livesLeftL2 = -1;
            } else {
                playerL2.screenRow = 126;
                playerL2.screenCol = 120;
                updateLivesL2();
            }
        }
    }
}

// Draw teammates
void drawTeam() {
    // Set up sprite attributes
    for (int i = 0; i < TEAMCOUNT; i++) {
        if (team[i].hide) {
            shadowOAM[i+21].attr0 = ATTR0_HIDE;
        } else {
            shadowOAM[i+21].attr0 = (team[i].screenRow) | ATTR0_TALL;
            shadowOAM[i+21].attr1 = (team[i].screenCol) | ATTR1_MEDIUM;
            if (team[i].screenRow == 8 || team[i].screenRow == 88) {
                shadowOAM[i+21].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(team[i].aniState*2, 16 + team[i].curFrame*4); 
            } else if (team[i].screenRow == 48 || team[i].screenRow == 126) {
                shadowOAM[i+21].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(team[i].aniState*2, 16 + team[i].curFrame*4); 
            }   
        }
    }
}

// Initialize fans
void initFans() {
    for (int i = 0; i < FANCOUNT; i++) {
        fans[i].width = 16;
        fans[i].height = 32;
        fans[i].hide = 0;
        fans[i].active = 1;
        fans[i].numFrames = 4;
        fans[i].curFrame = 0;
        fans[i].rdel = 1;
    }
    fans[0].screenCol = 22;
    fans[0].screenRow = 2;
    fans[0].aniState = SPRITEFRONT;

    fans[1].screenCol = 160;
    fans[1].screenRow = 159;
    fans[1].aniState = SPRITEBACK;
}

// Update fans
void updateFans() {
    for (int i = 0; i < FANCOUNT; i++) {
        if (fans[i].screenRow <= 0) {
            fans[i].screenRow = SCREENHEIGHT;
        } else if (fans[i].screenRow >= SCREENHEIGHT) {
            fans[i].screenRow = 0;
        }
        // Make fans walk on screen
        if (i == 0) {
            fans[i].screenRow += fans[i].rdel;
            fans[i].aniCounter++;
            // Set previous state to current state
            fans[i].prevAniState = fans[i].aniState;
            fans[i].aniState = SPRITEFRONT;
        } else {
            fans[i].screenRow -= fans[i].rdel;
            fans[i].aniCounter++;
            // Set previous state to current state
            fans[i].prevAniState = fans[i].aniState;
            fans[i].aniState = SPRITEBACK;
        }

        // Change the animation frame every 8 frames of gameplay
        if(fans[i].aniCounter % 8 == 0) {
            fans[i].curFrame = (fans[i].curFrame + 1) % fans[i].numFrames;
        }
        // Oh no! ran into fan with covid!
        if (collision(playerL2.screenCol, playerL2.screenRow, playerL2.width, playerL2.height, fans[i].screenCol, fans[i].screenRow, fans[i].width, fans[i].height)
        && fans[i].active) {
            if (livesLeftL2 == 0) {
                livesLeftL2 = -1;
            } else {
                playerL2.screenRow = 126;
                playerL2.screenCol = 120;
                updateLivesL2();
            }
        }
    }
}

// Draw fans
void drawFans() {
    // Set up sprite attributes
    for (int i = 0; i < FANCOUNT; i++) {
        if (fans[i].hide) {
            shadowOAM[i+31].attr0 = ATTR0_HIDE;
        } else {
            shadowOAM[i+31].attr0 = (fans[i].screenRow) | ATTR0_TALL;
            shadowOAM[i+31].attr1 = (fans[i].screenCol) | ATTR1_MEDIUM;
            shadowOAM[i+31].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(18+fans[i].aniState*2, fans[i].curFrame*4);  
        }
    }
}