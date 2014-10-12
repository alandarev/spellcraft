/*
* Player "Class" for Spellcraft mod
*/

/* Variables storing player information */


int __player_current_hero[MAXPLAYERS];

methodmap Player {
  public Player(int index)  {
    return Player:index;
  }

  property bool loaded  {
    public get()  {
      return false;
    }
  }

  property Hero hero {
    public get()  {
      return Hero:ToHeroIndex(_:this, __player_current_hero[this]);
    }
  }
}






