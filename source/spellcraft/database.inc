/*
* Database "object" of SpellCraft
*/


methodmap Database {
  public Database() {
    return Database:0;
  }
  public void Connect() {

  }
  public void LoadPlayer(int client) {
    Player player = Player(client);

    player.clean();

    player.hero = Hero:1;
    player.GetHero(1).xp = 123;
    player.GetHero(1).level = 2;
    player.GetHero(1).SetSpell(1, 1); // set spell in slot 1 (that is #2) to ID 1
    player.SetOrbsAmount(0, 5);
    player.SetOrbsAmount(1, 3);
    player.SetOrbsAmount(2, 4);

  }
}
