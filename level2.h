// Constants
#define LIFECOUNT 3
#define DANCEMOVES 12
#define TEAMCOUNT 10
#define FANCOUNT 2

// Variables
extern ANISPRITE playerL2;
extern ANISPRITE livesL2[LIFECOUNT];
extern int livesLeftL2, movesLeft;
extern ANISPRITE moves[DANCEMOVES];
extern ANISPRITE buzz;
extern ANISPRITE dadL2;
extern ANISPRITE team[TEAMCOUNT];
extern ANISPRITE fans[FANCOUNT];

// Prototypes
void initLevel2();
void updateLevel2();
void drawLevel2();
void initPlayerL2();
void updatePlayerL2();
void animatePlayerL2();
void drawPlayerL2();
void initLivesL2();
void updateLivesL2();
void drawLivesL2();
void initDanceMoves();
void updateDanceMoves();
void drawDanceMoves();
void initBuzz();
void updateBuzz();
void drawBuzz();
void initDadL2();
void updateDadL2();
void drawDadL2();
void initTeam();
void updateTeam();
void drawTeam();
void initFans();
void updateFans();
void drawFans();