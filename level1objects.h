// Constants
#define POMCOUNT 2
#define MAKEUPCNT 3
#define SNACKCNT 2

// Variables
extern ANISPRITE poms[POMCOUNT];
extern ANISPRITE bag;
extern ANISPRITE water;
extern ANISPRITE makeup[MAKEUPCNT];
extern ANISPRITE snacks[SNACKCNT];
extern ANISPRITE mask;

// Prototypes
void initPoms();
void updatePoms();
void drawPoms();
void initBag();
void updateBag();
void drawBag();
void initWater();
void updateWater();
void drawWater();
void initMakeup();
void updateMakeup();
void drawMakeup();
void initSnack();
void updateSnack();
void drawSnack();
void initMask();
void updateMask();
void drawMask();