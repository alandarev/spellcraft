int __components[3]={0,1,2};

methodmap Spell {
  public Spell(int id)  {
    return Spell:id;
  }
  public void GetName(char[] buffer, int maxlen)  {
    //TODO
    Format(buffer, maxlen, "no spell");
  }
  /*property int Components
  {
    public get()  {
      return GetComponent(this);
    }
  }*/
  public int GetComponent(any index)
  {
    return __components[index];
  }
}

public Action:SC_SpellCmd(client,args)
{
   if (args < 1)
   {
		ReplyToCommand(client, "[WC] Usage: spell <spell ID>");
		return Plugin_Handled;
   }
   decl String:Sspell[5];
   GetCmdArg(1, Sspell, sizeof(Sspell));
   new spell=StringToInt(Sspell);
   char maxspell[5] = IntToString(MAXHEROSPELLS);
   if((spell>=MAXHEROSPELLS)||(spell<=0))
   {
		ReplyToCommand(client, "[WC] spell must be 1-%s",maxspell);
		return Plugin_Handled;
   }

   new spellid=Hero.GetSpell(spell); //Gets the spell in slot 'spell'
   new rank=Hero.GetSpellRank(spell); //Gets the spell's rank

   TryCast(client, spellid, rank); //Attempts to cast the given spell based on its ID

   return Plugin_Handled;
}

bool:TryCast(client, spellid, rank)  {

  char trans[128];
  new Float:timeleft=GetCDSpell(client,spellid);
  if(timeleft > 0.0)  {
    Format(trans,sizeof(trans),"%T","spell cooldown",timeleft);
    CPrintToChat(client, "%s", trans);
    return false;
  }
  
  RunSpell(client,spellid,rank);

  return true;
}

stock RunSpell(client,spellid,rank);
{
  if(spellid == 1)
    Spell_Fireball(client, rank);



}

stock SetCdSpell(client,spellid,Float:cd)
{
  ClientCDSpells[client][spellid]=GetTickedTime()+cd;
}

stock GetCdSpell(client,spellid)
{
  float timeleft = ClientCDSpells[client][spellid] - GetTickedTime();
  return timeleft;
}





public Spell_Fireball(client, rank)
{
  PrintToChatAll("Test, rank is %i",rank);
}