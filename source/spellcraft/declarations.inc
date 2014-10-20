/*
* Declarations of constants and variables
*/
bool g_isReady = false;
#define MAXORBS 3 // Amount of orbs in the game
char g_orbNames[MAXORBS][] = {"fire", "frost", "earth"};

// Spells
#define MAXSPELLS 100
char g_spellName[MAXSPELLS][30];
int g_spellOrbs[MAXSPELLS][3];

// Forwards
Handle g_forward_OnDealDamagePre;
Handle g_forward_OnReady;
