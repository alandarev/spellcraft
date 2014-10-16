/** Double-include prevention */
#if defined _mynatives_included_
  #endinput
#endif
#define _mynatives_included_
 
/**
 * Deals SC mod damage to player
 */
native bool SC_DealDamage(int attacker, int victim, char[] weapon="Spell", int damage=100);
