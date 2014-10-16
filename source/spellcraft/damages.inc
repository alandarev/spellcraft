/**
 * Damage handling is inspired by war3source damage code
 */


/**
* Note that it is pre-reduced damage.. That is 10 damage of a glock will end up being around 4 true damage
 */
int g_restoreArmor;
bool g_isFakeDamage;


public Action SC_OnTakeDamageAliveHook(int victim, int &attacker, int &inflictor, float &damage, int &damagetype, int &weapon,
  float damageForce[3], float damagePosition[3], int damagecustom)  {

  // Restore armor if it was fake damage
  if(Client_IsIngame(victim) && IsPlayerAlive(victim))  {
    if(g_restoreArmor > 0)  {
      Client_SetArmor(victim, g_restoreArmor);
      g_restoreArmor = 0;
    }
  }
  int callResult;
  char sWeapon[] = "Not Imlemented";;
  /*Entity_GetName(weapon, sWeapon, 50);*/
  DamageType dmgType;
  if(g_isFakeDamage)  {
    dmgType = DT_SPELL_DAMAGE;
  }
  else  {
    dmgType = DT_BULLET_DAMAGE;
  }

  float multiplier = 1.0;
  // Stages
  for(int stage = 1; stage <= 3; stage++) { //that was there earlier try compiling now Ö=
    Call_StartForward(g_forward_OnDealDamagePre);
    //SC_OnTakeDamage(int stage, DamageType dmgType, int &victim, int &attacker, float &damage, float &multiplier,char[] weapon)
    Call_PushCell(stage);
    Call_PushCell(dmgType);
    Call_PushCellRef(victim);
    Call_PushCellRef(attacker);
    Call_PushFloatRef(damage);
    Call_PushFloatRef(multiplier);
    Call_PushString(sWeapon);
    Call_Finish(callResult);
  }

  return Plugin_Changed;
}

// Test if forward works
 public Action SC_OnTakeDamage(int stage, DamageType dmgType, int &victim, int &attacker, float &damage, float &multiplier,char[] weapon)  {
  PrintToChatAll("Stage %d, Weapon name is %s", stage, weapon);
  PrintToServer("Stage %d, Weapon name is %s", stage, weapon);


  return Plugin_Changed;
}

public void SC_OnTakeDamagePostHook(int victim, int attacker, int inflictor, float damage, int damagetype) {
}

public Action TestDamage(client, args)  {
  int prev = 0;
  for(int i=1; i < GetMaxClients(); i++)  {
    if (IsClientInGame(i) && IsPlayerAlive(i))  {
      SC_DealDamage(prev, i, "Spell", 20); // just to test if native works, we can used them inside of the mod too
      prev = i;
    }
  }
  return Plugin_Handled;
}

stock bool DealDamage(int attacker, int victim, char[] weapon="Spell", int damage=100)
{
  char dmg_str[16];
  IntToString(damage,dmg_str,16);
  char dmg_type_str[32];
  IntToString(DMG_CLUB,dmg_type_str,32);

  int clientArmor = Client_GetArmor(victim);
  if(clientArmor > 0) {
    g_restoreArmor = clientArmor;
    Client_SetArmor(victim, 0);
  }

  new pointHurt=CreateEntityByName("point_hurt");
  if(pointHurt)
  {
    g_isFakeDamage = true;
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
    g_isFakeDamage = false;
    return true;
  }
  return false;
}

