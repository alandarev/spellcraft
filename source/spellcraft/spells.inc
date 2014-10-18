int __components[3];

methodmap Spell {
  public Spell(int id)  {
    return Spell:id;
  }
  public void GetName(char[] buffer, int maxlen)  {
    //TODO
    Format(buffer, maxlen, "no spell");
  }
  property int Components
  {
    public get()  {
      return GetComponent(this);
    }
  }
  public int GetComponent(int slot)
  {
    return __components[slot];
  }
}




// Spell Codes - don't use it, it sucks.
methodmap FrostBolt < Spell {
  public void GetName(char[] buffer, int maxlen)  {
    Format(buffer, maxlen, "frostbolt");
  }
}
