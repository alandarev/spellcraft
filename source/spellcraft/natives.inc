

void RegisterNatives()  {
  CreateNative("SC_DealDamage", Native_DealDamage);

  //Action SC_OnTakeDamage(int stage, DamageType dmgType, int &victim, int &attacker, float &damage, float &multiplier,char[] weapon)
  g_forward_OnDealDamagePre = CreateGlobalForward("SC_OnTakeDamage", ET_Hook, Param_Cell, Param_Cell, Param_CellByRef, Param_CellByRef, Param_FloatByRef, Param_FloatByRef, Param_CellByRef);

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
