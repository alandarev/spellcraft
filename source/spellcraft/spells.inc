int __components[3]={0,1,2};

public Action:SC_SpellCmd(client,args)
{
  if (args < 1)
  {
		ReplyToCommand(client, "[SC] Usage: spell <spell ID>");
		return Plugin_Handled;
  }
  decl String:Sspell[5];
  GetCmdArg(1, Sspell, sizeof(Sspell));
  new spell=StringToInt(Sspell);
  
  new String:smaxspell[20];
  IntToString(MAXHEROSPELLS, smaxspell, 20);
  
  if((spell>=MAXHEROSPELLS)||(spell<=0))
  {
		ReplyToCommand(client, "[SC] spell must be 1-%s",smaxspell);
		return Plugin_Handled;
  }

  new spellid=Player(client).hero.GetSpell(spell); //Gets the spell in slot 'spell'

  new rank=Player(client).hero.GetSpellRank(spell); //Gets the spell's rank

  TryCast(client, spellid, rank); //Attempts to cast the given spell based on its ID

  return Plugin_Handled;
}

public SetCdSpell(client,spellid,Float:cd)
{
  ClientCDSpells[client][spellid]=GetTickedTime()+cd;
}

public GetCDSpell(client,spellid)
{
  return (ClientCDSpells[client][spellid] - GetTickedTime());
}

bool:TryCast(client, spellid, rank)  {

  char trans[128];
  float timeleft = float(GetCDSpell(client,spellid));
  if(timeleft > 0.0)  {
    Format(trans,sizeof(trans),"%T","spell cooldown",timeleft);
    CPrintToChat(client, "%s", trans);
    return false;
  }
  
  RunSpell(client,spellid,rank);

  return true;
}

public RunSpell(client,spellid,rank)
{
  if(spellid == 1)
    Spell_Fireball(client, rank);



}
stock GetSpellName(spellid)
{
  new String:spellName[30];
  if(spellid == 1)
    Format(spellName,sizeof(spellName),"%T","fireball name");
  else
    Format(spellName,sizeof(spellName),"%T","no spell");
  
  return spellName[30];
}
public GetComponent(any index)
{
  return __components[index];
}





public Spell_Fireball(client, rank)
{
  PrintToChatAll("Test, rank is %i",rank);
}