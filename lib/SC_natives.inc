/** Double-include prevention */
#if defined _mynatives_included_
  #endinput
#endif
#define _mynatives_included_


enum DamageType {
  DT_BULLET_DAMAGE,
  DT_SPELL_DAMAGE
};

/**
 * Deals SC mod damage to player
 */
native bool SC_DealDamage(int attacker, int victim, char[] weapon="Spell", int damage=100);

/**
 * Damage deal forward before it happens
 * Damage can be modified.
 * Note: It is better not to create new damage event inside of this forward. Use Damage Post forward instead.
 * Stages:
 * 1 - Initial
 * 2 - Middle
 * 3 - Final
 * To be able to code something like "Block spell", which neglets all damage,
 * it needs to happen after +damage spells. As a result stages are introduced.
 * If you are unsure what stage to use, very likely you want to use '2'.
 * Example of coding general +damage spell:
 * public Action SC_OnTakeDamage(int stage, DamageType dmgType, int &victim, int &attacker, float &damage, float &multiplier,char[] weapon) {
 *   if(stage != 1) return Plugin_Continue; // Ensure we are not applying spell on each stage
 *   if(dmgType != DT_BULLET_DAMAGE) return Plugin_Continue;  // We do not want to increase spell damage
 *   damage += 10.0; // Or multiplier *= 1.10; for +10% damage instead
 *   return Plugin_Changed;
 * }
 */
forward Action SC_OnTakeDamage(int stage, DamageType dmgType, int &victim, int &attacker, float &damage, float &multiplier,char[] weapon);
