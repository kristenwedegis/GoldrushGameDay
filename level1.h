// Constants
#define LIFECOUNT 3
#define MAPWIDTH 512
#define MAPHEIGHT 512
#define PEDESCNT 2

// Variables
extern ANISPRITE player;
extern ANISPRITE lives[LIFECOUNT];
extern int livesLeft, l1HOff, l1VOff;
extern int objsCollected, totalObjs, makeupCollected;
extern ANISPRITE dad;
extern ANISPRITE friend;
extern ANISPRITE pedestrians[PEDESCNT];
extern int borrowMup;

// Prototypes
void initLevel1();
void updateLevel1();
void drawLevel1();
void initPlayer();
void updatePlayer();
void animatePlayer();
void drawPlayer();
void initLives();
void updateLives();
void drawLives();
void initDad();
void updateDad();
void drawDad();
void initFriend();
void updateFriend();
void drawFriend();
void initCovid();
void updateCovid();
void drawCovid();