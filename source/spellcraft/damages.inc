/**
 * Damage handling is inspired by war3source damage code
 */


/**
* Note that it is pre-reduced damage.. That is 10 damage of a glock will end up being around 4 true damage
 */
public Action OnTakeDamageHook(int victim, int &attacker, int &inflictor, float &damage, int &damagetype, int &weapon,
  float damageForce[3], float damagePosition[3], int damagecustom)  {

  PrintToServer("On take damage start");
  PrintToServer("victim = %d, attacker = %d, dmg = %.2f", victim, attacker, damage);

  // Mod code


  PrintToServer("On take damage end. dmg = %.2f", damage);
  return Plugin_Changed;
}

public Action TestDamage(client, args)  {
  int prev = 0;
  for(int i=0; i < GetMaxClients(); i++)  {
    if (IsClientInGame(i) && IsPlayerAlive(i))  {
      DealDamage(prev, i, "Spell", 20);
      prev = i;
    }
  }
}

stock void DealDamage(attacker, victim, String:weapon[]="Spell", damage=100, bool:headshot=false)
{
  int dmg_bullet = 2;

  char dmg_str[16];
  IntToString(damage,dmg_str,16);
  char dmg_type_str[32];
  IntToString(dmg_bullet,dmg_type_str,32);

  new pointHurt=CreateEntityByName("point_hurt");
  if(pointHurt)
  {
    DispatchKeyValue(victim,"targetname","sc_hurtme");
    DispatchKeyValue(pointHurt,"DamageTarget","sc_hurtme");
    DispatchKeyValue(pointHurt,"Damage",dmg_str);
    DispatchKeyValue(pointHurt,"DamageType",dmg_type_str);
    if(!StrEqual(weapon,""))
    {
      DispatchKeyValue(pointHurt,"classname",weapon);
    }
    DispatchSpawn(pointHurt);
    AcceptEntityInput(pointHurt,"Hurt",(attacker>0)?attacker:-1);
    DispatchKeyValue(pointHurt,"classname","point_hurt");
    DispatchKeyValue(victim,"targetname","sc_no_hurtme");
    RemoveEdict(pointHurt);
  }
}

