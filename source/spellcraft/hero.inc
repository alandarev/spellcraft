/*
* Hero "Class" for Spellcraft
*/

#define MAXHEROES 10
#define MAXSPELLS 4

// Array size to fit all the players multiplied by maximum heroes they can have
#define PHMAX MAXPLAYERS * MAXHEROES


int __hero_xp[PHMAX];
int __hero_level[PHMAX];
int __hero_spells[PHMAX][MAXSPELLS];

methodmap Hero  {
  /**
   * Clean hero data
   */
  public void clean() {
    __hero_xp[this] = 0;
    __hero_level[this] = 0;
    for(int i=0; i<MAXSPELLS; i++)  {
      __hero_spells[this][i] = 0;
    }
  }

  property int client {
    public get() {
      return HeroIndexToClient(this);
    }
  }
  property int slot {
    public get() {
      return HeroIndexToSlot(this);
    }
  }

  property int xp {
    public get() {
      return __hero_xp[this];
    }
    public set(int xp) {
      __hero_xp[this] = xp;
    }
  }

  property int level  {
    public get()  {
      return __hero_level[this];
    }
    public set(int level)  {
      __hero_level[this] = level;
    }
  }

  property int requiredXp  {
    public get()  {
      return _getRequiredXp(this.level);
    }
  }

  public void GiveXp(int xp)  {
    this.xp += xp;
    if(this.xp > this.requiredXp)  {
      // Level UP
      // TODO
    }
  }

  public Spell GetSpell(int slot) {
    return Spell:__hero_spells[this][slot];
  }
  public void SetSpell(int slot, int id)  {
    __hero_spells[this][slot] = id;
  }
}

int ToHeroIndex(client, slot) {
  return client * (MAXHEROES + 1) + slot;
}

int HeroIndexToClient(any index)  {
  return index / (MAXHEROES + 1);
}

int HeroIndexToSlot(any index)  {
  return index % (MAXHEROES + 1);
}


/**
 * Get required xp for the given level.
 * If hero is level 1, and you want to know get required xp to get to level 2, then call with level = 1, not 2.
 * Example: level 2 -> 3 xp needed = _getRequiredXp(2)
 */

int _getRequiredXp(level) {
  // TODO: hani? :)
  int levelReq = RoundToNearest(140.0 * 1.22 ^ float(level));
  return levelReq;
}
