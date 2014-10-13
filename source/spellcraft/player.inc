/*
* Player "Class" for Spellcraft mod
*/

/* Variables storing player information */

int __player_orbs[MAXPLAYERS][MAXORBS];
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
    public set(Hero slot)  {
      __player_current_hero[this] = _:slot;
    }
  }

  public Hero GetHero(int index)  {
    return Hero:ToHeroIndex(_:this, index);
  }

  public int GetOrbsAmount(int orbId) {
    return __player_orbs[this][orbId];
  }

  public int SetOrbsAmount(int orbId, int amount) {
    __player_orbs[this][orbId] = amount;
  }

  /**
   * Clean player dat
   */
  public void clean()  {
    for(int i=0; i < MAXHEROES; i++)  {
      Hero hero = this.GetHero(i);
      hero.clean();
    }

    // Now clean player data itself
    __player_current_hero[this] = 0;
    for (int i=0; i<MAXORBS; i++) {
      __player_orbs[this][i] = 0;
    }
  }


}






