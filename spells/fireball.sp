/*
 * =====================================================================================
 *
 *       Filename:  fireball.sp
 *
 *    Description:  Fireball spell for Spellcraft
 *        Created:  10/20/2014 09:24:35 AM
 *
 *
 * =====================================================================================
 */

#include <SC_natives>
#include <SC_spell>

char[] NAME = "Fireball";

public Plugin:myinfo =
{
  name = "(SC) Fireball",
  author = "SC Team",
  description = "First SC Spell",
  version = "1.0",
  url = "http://github.com/alandarev/spellcraft"
};

stock LoadSpell() {
  SC_RegisterSpell(NAME, "fire", "fire", "fire");
}


