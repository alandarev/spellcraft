
methodmap Spell {
  public Spell(int id)  {
    return Spell:id;
  }

  public void GetName(char[] buffer, int maxlen)  {
    //TODO
    Format(buffer, maxlen, "no spell");
  }
}




// Spell Codes
methodmap FrostBolt < Spell {
  public void GetName(char[] buffer, int maxlen)  {
    Format(buffer, maxlen, "frostbolt");
  }
}
