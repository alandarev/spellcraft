/*
 * =====================================================================================
 *
 *       Filename:  spellcraft.sp
 *
 *    Description:  SpellCraft mod for Counter-Strike:GO
 *
 *       Compiler:  spcomp
 *     Repository:  https://github.com/alandarev/spellcraft
 *
 * =====================================================================================
 */



#pragma semicolon 1
#define SPELLCRAFT_VERSION "0.1"
/**
 * Declarations
 */

/**
 * Engine
 */
#include "spellcraft/player"
#include "spellcraft/scmenus"

/**
 * Content
 */

public Plugin:myinfo =
{
  name = "SpellCraft",
  author = "Check at GitHub",
  description = "RPG mod, allows players to craft their own spells and use in-game.",
  version = SPELLCRAFT_VERSION,
  url = "https://github.com/alandarev/spellcraft"
};

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
  PrintToServer("----------------|      SpellCraft Load Stage 1    |---------------");
  return APLRes_Success;
}

public void OnPluginStart() {
  PrintToServer("----------------|      SpellCraft Load Stage 2    |---------------");

  PrintToServer("translations file loading");
  LoadTranslations("spellcraft.phrases");

  //Console commands
  //All of the following open the main menu:
  RegConsoleCmd("menu", Open_MainMenu);
  RegConsoleCmd("wcmenu", Open_MainMenu);
  RegConsoleCmd("scmenu", Open_MainMenu);

  // Some testing
  Player myPlayer = Player(1);
  PrintToServer("Player a = %d", myPlayer);
  int[] tests = {5, 6, 7};
  PrintToServer("Test = %d", tests[myPlayer]);
}

public void OnConfigsExecuted() {
  PrintToServer("----------------|      SpellCraft Config Loaded   |---------------");
}

int test;

