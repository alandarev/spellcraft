

void RegisterNatives()  {
  CreateNative("SC_DealDamage", Native_DealDamage);
  CreateNative("SC_IsReady", Native_IsReady);
  CreateNative("SC_RegisterSpell", Native_RegisterSpell);

  //Action SC_OnTakeDamage(int stage, DamageType dmgType, int &victim, int &attacker, float &damage, float &multiplier,char[] weapon)
  g_forward_OnDealDamagePre = CreateGlobalForward("SC_OnTakeDamage", ET_Hook, Param_Cell, Param_Cell, Param_CellByRef, Param_CellByRef, Param_FloatByRef, Param_FloatByRef, Param_String);
  g_forward_OnReady = CreateGlobalForward("SC_OnReady", ET_Ignore);

}

public int Native_RegisterSpell(Handle:plugin, numParams) {
  char name[30];
  GetNativeString(1, name, sizeof(name));
  char orbs[3][20];
  GetNativeString(2, orbs[0], 20);
  GetNativeString(3, orbs[1], 20);
  GetNativeString(4, orbs[2], 20);

  int iOrbs[3];
  for(int i=0;i<3;i++)  {
    iOrbs[i] = OrbNameToId(orbs[i]);
    if (iOrbs[i] == -1) {
      // Error finding orb, throw error
      return ThrowNativeError(SP_ERROR_NATIVE, "Orb %s does not exist", orbs[i]);
    }
  }
  return RegisterSpell(name, iOrbs);
}

public int Native_IsReady(Handle:plugin, numParams) {
  return _:g_isReady;
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
