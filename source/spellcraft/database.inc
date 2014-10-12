/*
* Database "object" of SpellCraft
*/


methodmap Database {
  public Database() {
    return Database:0;
  }
  public void connect() {

  }
  public void LoadPlayer(Player player) {
    player.clean();

    player.hero = Hero:1;
    player.GetHero(1).xp = 123;
    player.GetHero(1).level = 2;
    player.GetHero(1).SetSpell(1, 1); // set spell in slot 1 (that is #2) to ID 1

  }
}
