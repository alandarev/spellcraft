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
 * External libraries
 */
#include <sourcemod>
#include <colors>
#include <sdkhooks>
#include <sdktools>
#include <smlib> // Do not use smlib's colors, use colors.inc instead.

/**
 * Declarations
 */
#include "spellcraft/declarations"

/**
 * Engine
 */
#include "spellcraft/damages"
#include "spellcraft/configuration"
#include "spellcraft/orbs"
#include "spellcraft/spells"
#include "spellcraft/hero"
#include "spellcraft/player"
#include "spellcraft/database"
#include "spellcraft/scmenus"

#include "spellcraft/hooks"
#include "spellcraft/messages"

/**
 * Content
 */
Database DB;

public Plugin:myinfo =
{
  name = "Spellcraft",
  author = "Check at GitHub",
  description = "RPG mod, allows players to craft their own spells and use in-game.",
  version = SPELLCRAFT_VERSION,
  url = "https://github.com/alandarev/spellcraft"
};

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
  PrintToServer("----------------|      Spellcraft Load Stage 1    |---------------");
  return APLRes_Success;
}

public void OnPluginStart() {
  PrintToServer("----------------|      Spellcraft Load Stage 2    |---------------");
  ReloadConfig();
  HookEvents();
  DB.Connect();

  PrintToServer("translations file loading");
  LoadTranslations("spellcraft.phrases");

  //Console commands
  //All of the following open the main menu:
  RegConsoleCmd("menu", Open_MainMenu);
  RegConsoleCmd("wcmenu", Open_MainMenu);
  RegConsoleCmd("scmenu", Open_MainMenu);

  RegConsoleCmd("test_colors", TestColors);
  RegConsoleCmd("hurt_all", TestDamage);

  // Some testing
  Player p = Player(1);
  p.hero.GiveXp(100);
  PrintToServer("Hero is level %d, has xp = %d, and needs xp = %d", p.hero.level, p.hero.xp, p.hero.requiredXp);
}

public void OnConfigsExecuted() {
  PrintToServer("----------------|      Spellcraft Config Loaded   |---------------");
}

public void OnClientAuthorized(int client, const char[] auth) {
  DB.LoadPlayer(client);
}

public void OnClientPutInServer(int client)
{
  SDKHook(client, SDKHook_OnTakeDamageAlive, SC_OnTakeDamageAliveHook);
  SDKHook(client, SDKHook_OnTakeDamageAlivePost, SC_OnTakeDamagePostHook);
}
public void OnClientDisconnect(int client)
{
  SDKUnhook(client, SDKHook_OnTakeDamageAlive, SC_OnTakeDamageAliveHook);
  SDKUnhook(client, SDKHook_OnTakeDamageAlivePost, SC_OnTakeDamagePostHook);
}

