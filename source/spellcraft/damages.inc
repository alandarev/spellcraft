

public Action OnTakeDamageHook(int victim, int &attacker, int &inflictor, float &damage, int &damagetype, int &weapon,
  float damageForce[3], float damagePosition[3], int damagecustom)  {

  PrintToServer("On take damage start");
  PrintToServer("victim = %d, attacker = %d, dmg = %d", victim, attacker, damage);

  damage = 10.0;
  PrintToServer("On take damage end");

  return Plugin_Changed;
}

