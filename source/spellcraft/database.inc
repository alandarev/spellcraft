/*
* Database "object" of SpellCraft
*/


methodmap Database {
  public Database() {
    return Database:0;
  }
  public void Connect() {
    SetReady();
  }
  public void LoadPlayer(int client) {
    Player player = Player(client);

    player.clean();

    player.hero = Hero:1;
    player.GetHero(1).xp = 123;
    player.GetHero(1).level = 2;
    player.GetHero(1).SetSpell(1, 1); // set spell in slot 1 (note there is slot 0 too)
    player.GetHero(1).SetSpellRank(1, 3); // Set spell rank 3 in slot 1
    player.SetOrbsAmount(0, 5);
    player.SetOrbsAmount(1, 3);
    player.SetOrbsAmount(2, 4);

  }
}

stock void SetReady() {
  g_isReady = true;
  Call_StartForward(g_forward_OnReady);
  int callResult;
  Call_Finish(callResult);
}

stock int RegisterSpell(char[] name, int orbs[3])  {
  int id = 1; // TODO
  strcopy(g_spellName[id], 30, name);
  for(int i=0; i<3; i++)  {
    g_spellOrbs[id][i] = orbs[i];
  }
  return id;
}


