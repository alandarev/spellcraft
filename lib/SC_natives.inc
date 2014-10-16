/** Double-include prevention */
#if defined _mynatives_included_
  #endinput
#endif
#define _mynatives_included_

/**
 * Deals SC mod damage to player
 */
native bool SC_DealDamage(int attacker, int victim, char[] weapon="Spell", int damage=100);

/**
 * Damage deal forward before it happens
 * Damage can be modified.
 * Note: It is better not to create new damage event inside of this forward. Use Damage Post forward instead.
 */
forward Action SC_OnTakeDamagePre(int &victim, int &attacker, bool isBullet, int &inflictor, float &damage, int &weapon);
