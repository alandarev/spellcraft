

public Action OnTakeDamageHook(int victim, int &attacker, int &inflictor, float &damage, int &damagetype, int &weapon,
  float damageForce[3], float damagePosition[3], int damagecustom)  {

  PrintToServer("On take damage start");
  PrintToServer("victim = %d, attacker = %d, dmg = %.2f", victim, attacker, damage);

  // Mod code
  damage = 10.0;


  PrintToServer("On take damage end. dmg = %.2f", damage);
  return Plugin_Changed;
}

