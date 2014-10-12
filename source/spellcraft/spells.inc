
methodmap Spell {
  public Spell(int id)  {
    return Spell:id;
  }

  public void GetName(char[] buffer, int maxlen)  {
    Format(buffer, maxlen, "no spell");
  }
}
