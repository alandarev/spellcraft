/*
* Player "Class" for Spellcraft mod
*/

/* Variables storing player information */

#define MAXHEROES 10

int __player_heroes[MAXPLAYERS][MAXHEROES];
int __hero_xp[MAXPLAYERS][MAXHEROES];

methodmap Hero  {

  property int xp {
    public get() {
      return __player_xp[this];
    }
    public set(int xp) {
      __player_xp[this] = xp;
    }
  }
  property int requireXp  {
    public get()  {
      return _getRequiredXp(this.level);
    }
  }
  public void GiveXP(int xp)  {

  }
}

methodmap Player {
  public Player(int index)  {
    return Player:index;
  }

  property Hero hero {
    public get()  {
      return __player_heroes[this][__player_current_hero[this]];
    }
  }
}


/**
 * Get required xp for the given level.
 * If hero is level 1, and you want to know get required xp to get to level 2, then call with level = 1, not 2.
 * Example: level 2 -> 3 xp needed = _getRequiredXp(2)
 */
int _getRequiredXp(level) {
  // TODO: hani? :)
}



