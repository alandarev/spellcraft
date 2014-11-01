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
  float time = ClientCDSpells[client][spellid] - GetTickedTime();
  return time;
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

stock setTakeDamage(entity, type){
  SetEntProp(entity, Prop_Data, "m_takedamage", type);

}



public Action:MoveSpellFireBall(Handle:timer,Handle:datapack)
{
  decl Float:loc[3];
  ResetPack(datapack);
  new client = ReadPackCell(datapack);
  new ent = ReadPackCell(datapack);
  new team = ReadPackCell(datapack);
  new Float:distance = ReadPackFloat(datapack);
  loc[0] = ReadPackFloat(datapack);
  loc[1] = ReadPackFloat(datapack);
  loc[2] = ReadPackFloat(datapack);
  new round = ReadPackCell(datapack);


  // Now get the targets it has already heal/damage
  new old_targets[65];
  new old_amount=0;
  while(IsPackReadable(datapack, 4))  {
    old_targets[old_amount++] = ReadPackCell(datapack);
  }

  // Check if client is in game and if entity still exists
  if (!IsValidEntity(ent))  {
    return Plugin_Stop;
  }
  if (ent <= 0) {
    return Plugin_Stop;
  }
  if (!IsClientInGame(client) || (team != GetClientTeam(client)))  {
    KillMovingEntity(ent);
    return Plugin_Stop;
  }

  if (g_RoundCount != round)  {
    KillMovingEntity(ent);
    return Plugin_Stop;
  }

  // See if there is anybody around
  decl Float:entpos[3];
  GetEntPropVector(ent, Prop_Send, "m_vecOrigin", entpos);


  new friends[65], enemies[65];
  new friends_amount, enemies_amount;

  if (team == 2)  {
    friends_amount = GetNearClients("@t",entpos,friends,distance);
    enemies_amount = GetNearClients("@ct",entpos,enemies,distance);
  }
  if (team == 3)  {
    friends_amount = GetNearClients("@ct",entpos,friends,distance);
    enemies_amount = GetNearClients("@t",entpos,enemies,distance);
  }

  decl String:name[255];
  decl Float:location[3];
  GetClientName(client,name,sizeof(name));
  // Ally targeting
  for(new i=0; i<friends_amount; i++) {
    new target = friends[i];
    // Check if it is old
    new bool:found = false;
    for (new y=0; y<old_amount; y++)  {
      if (old_targets[y] == target) {
        found = true;
      }
    }
    if (found)  {
      continue; // Don't heal/damage twice
    }
    WritePackCell(datapack, target);

    //Do stuff to ally here

  }

  // Enemy targeting
  for(new i=0; i<enemies_amount; i++) {
    new target = enemies[i];
    // Check if it is old
    new bool:found = false;
    for (new y=0; y<old_amount; y++)  {
      if (old_targets[y] == target) {
        found = true;
      }
    }
    if (found)  {
      continue; // Don't heal/damage twice
    }
    WritePackCell(datapack, target);
    
    //Do stuff to enemy here
    
  }

  return Plugin_Continue;



}

stock CreateMovingEntity(client,model[256])  {

  decl Float:clienteyeangle[3], Float:anglevector[3], Float:clienteyeposition[3], Float:resultposition[3], entity;
  GetClientEyeAngles(client, clienteyeangle);
  GetClientEyePosition(client, clienteyeposition);
  GetAngleVectors(clienteyeangle, anglevector, NULL_VECTOR, NULL_VECTOR);
  NormalizeVector(anglevector, anglevector);
  ScaleVector(anglevector, 30.0);
  AddVectors(clienteyeposition, anglevector, resultposition);
  NormalizeVector(anglevector, anglevector);
  ScaleVector(anglevector, 450.0);

  entity = CreateEntityByName("hegrenade_projectile");
  if (entity <= 0)  {
    return -1;
  }

  SetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity", client);
  setTakeDamage(entity, DAMAGE_NO);
  DispatchSpawn(entity);
  new Float:vecmax[3] = {4.0, 4.0, 4.0};
  new Float:vecmin[3] = {-4.0, -4.0, -4.0};
  SetEntPropVector(entity, Prop_Send, "m_vecMins", vecmin);
  SetEntPropVector(entity, Prop_Send, "m_vecMaxs", vecmax);
  SetEntProp(entity, Prop_Send, "m_nSolidType", 2 );
  SetEntProp(entity, Prop_Data, "m_CollisionGroup", 2, 4);
  SetEntProp(entity, Prop_Send, "m_CollisionGroup", 2, 4);

  SetEntityMoveType(entity, MOVETYPE_FLY);
  SetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity", client);
  SetEntityModel(entity, model);
  TeleportEntity(entity, resultposition, clienteyeangle, anglevector);

  new gascloud = CreateEntityByName("env_rockettrail");
  DispatchKeyValueVector(gascloud,"Origin", resultposition);
  DispatchKeyValueVector(gascloud,"Angles", clienteyeangle);

  new team = GetClientTeam(client);
  new Float:smokecolor[3] = {0.2, 0.0, 0.4};
  if (team == 2)  {
    smokecolor[0] = 0.82;
    smokecolor[2] = 0.22;
  }
  SetEntPropVector(gascloud, Prop_Send, "m_StartColor", smokecolor);
  SetEntPropFloat(gascloud, Prop_Send, "m_Opacity", 0.8);
  SetEntPropFloat(gascloud, Prop_Send, "m_SpawnRate", 150.0);
  SetEntPropFloat(gascloud, Prop_Send, "m_ParticleLifetime", 1.0);
  SetEntPropFloat(gascloud, Prop_Send, "m_StartSize", 5.0);
  SetEntPropFloat(gascloud, Prop_Send, "m_EndSize", 30.0);
  SetEntPropFloat(gascloud, Prop_Send, "m_SpawnRadius", 0.0);
  SetEntPropFloat(gascloud, Prop_Send, "m_MinSpeed", 0.0);
  SetEntPropFloat(gascloud, Prop_Send, "m_MaxSpeed", 20.0);
  SetEntPropFloat(gascloud, Prop_Send, "m_flFlareScale", 1.0);
  DispatchSpawn(gascloud);
  decl String:target[64];
  Format(target, 64, "target%d_%f", client, GetGameTime());
  DispatchKeyValue(entity, "targetname", target);
  SetVariantString(target);
  AcceptEntityInput(gascloud, "SetParent");
  SetEntPropEnt(entity, Prop_Send, "m_hEffectEntity", gascloud);

  SDKHook(entity, SDKHook_StartTouch, EntityTouchHook);
  SDKHook(entity, SDKHook_OnTakeDamage, EntityDamageHook);

  setTakeDamage(entity, DAMAGE_YES);

  return entity;
}



public Action:EntityTouchHook(entity, other){
  if(other != 0){
    if(other == GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity")){
      return Plugin_Continue;
    }else{
      // Dont include player into a check
      if(!IsEntityCollidable(other, false, false, true)){
        return Plugin_Continue;
      }
      if (other <= GetMaxClients() && other >= 1)  {
        return Plugin_Continue;
      }
    }
  }

  KillMovingEntity(entity);

  return Plugin_Continue;

}

public Action:EntityDamageHook(entity, &attacker, &inflictor, &Float:damage, &damagetype){
  if(GetEntProp(entity, Prop_Data, "m_takedamage") == DAMAGE_YES){
    KillMovingEntity(entity);
  }

  return Plugin_Continue;
}

stock KillMovingEntity(entity){

  SDKUnhook(entity, SDKHook_StartTouch, EntityTouchHook);
  SDKUnhook(entity, SDKHook_OnTakeDamage, EntityDamageHook);

  if(GetEntProp(entity, Prop_Data, "m_takedamage") == DAMAGE_YES){
    setTakeDamage(entity, DAMAGE_NO);
  }
  new gasentity = GetEntPropEnt(entity, Prop_Send, "m_hEffectEntity");
  if(gasentity > 0)
    AcceptEntityInput(gasentity, "Kill");
  AcceptEntityInput(entity, "Kill");


}



public Spell_Fireball(client, rank)
{
  PrintToChatAll("Fireball, rank is %i",rank);
  
  new Float:distance = 20.0;
  new Float:frequency = 0.10;
  new ent = CreateMovingEntity(client,"models/effects/combineball.mdl");

  decl Float:location[3];
  GetClientAbsOrigin(client, location);
  new Handle:datapack = CreateDataPack();
  WritePackCell(datapack, client);
  WritePackCell(datapack, ent);
  WritePackCell(datapack, GetClientTeam(client));
  WritePackFloat(datapack, distance); //The hitbox of the spell, default is 20
  WritePackFloat(datapack, location[0]);
  WritePackFloat(datapack, location[1]);
  WritePackFloat(datapack, location[2]);
  WritePackCell(datapack, g_RoundCount);
  CreateTimer(frequency, MoveSpellFireBall, datapack, TIMER_REPEAT | TIMER_FLAG_NO_MAPCHANGE | TIMER_DATA_HNDL_CLOSE);
}