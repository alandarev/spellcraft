void HookEvents() {
  HookEvent("player_death", PlayerDeathEvent, EventHookMode_Pre);
}

public Action PlayerDeathEvent(Handle event, const char[] name, bool dontBroadcast) {
  int victim = GetClientOfUserId(GetEventInt(event, "userid"));
  int attacker = GetClientOfUserId(GetEventInt(event, "attacker"));
  int assister = GetClientOfUserId(GetEventInt(event, "assister"));
  if(attacker)  {
    if(GetClientTeam(victim) != GetClientTeam(attacker))  {
      KillRewards(victim, attacker, assister);
    }
  }

}


KillRewards(victim, attacker, assister) {
  int killXp = 10;
  killXp += Player(victim).hero.level * 3;
  Player(attacker).hero.GiveXp(killXp);
  Player(assister).hero.GiveXp(killXp / 2);

  float dropChance = DROP_ON_KILL;
  float assistDropChance = dropChance / 2;
  RollOrbDrop(attacker, dropChance);
  RollOrbDrop(assister, assistDropChance);
}

RollOrbDrop(client, float chance) {
  if(GetURandomFloat() < chance)  {
    int orbId = RoundToFloor(GetURandomFloat() * MAXORBS);
    PrintToServer("orb id = %d. max = %d", orbId, MAXORBS);
    GiveOrbs(client, orbId, 1);
  }
}
