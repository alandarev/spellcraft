

void RegisterNatives()  {
  CreateNative("SC_DealDamage", Native_DealDamage);
  
  //(int victim, int &attacker, bool isBullet, int &inflictor, float &damage, int &weapon);
  g_forward_OnDealDamagePre = CreateGlobalForward("SC_OnTakeDamagePre", ET_Hook, Param_Cell, Param_Cell, Param_Cell, Param_Cell, Param_Cell, Param_Cell);
  
}

public int Native_DealDamage(Handle:plugin, numParams)  {
  // DealDamage(int attacker, int victim, char[] weapon="Spell", int damage=100)
  new attacker = GetNativeCell(1);
  new victim = GetNativeCell(2);
  char weapon[50];
  GetNativeString(3, weapon, sizeof(weapon));
  new damage = GetNativeCell(4);
  
  bool success = DealDamage(attacker, victim, weapon, damage);
  return _:success;
}
