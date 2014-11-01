stock CreateMovingEntity(client,String:model[256])  {

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
  //SetEntityModel(entity, "models/effects/combineball.mdl");
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
public Float:GetDistanceBetween(const Float:startvec[3],const Float:endvec[3])
{
  return SquareRoot((startvec[0]-endvec[0])*(startvec[0]-endvec[0])+(startvec[1]-endvec[1])*(startvec[1]-endvec[1])+(startvec[2]-endvec[2])*(startvec[2]-endvec[2]));
}
stock bool:IsClearPath(Float:loc[3],Float:loc2[3],target=-1)
{
  decl Float:vector[3],Float:angles[3];
  MakeVectorFromPoints(loc, loc2, vector);
  GetVectorAngles(vector, angles);

  TR_TraceRayFilter(loc, angles, MASK_SOLID, RayType_Infinite,AimTargetFilter);
  new Float:endvec[3];
  TR_GetEndPosition(endvec);
  new endEntity = TR_GetEntityIndex();
  if((target >= 0) && (endEntity == target))
  return true;
  //now check if distance of ray is more or equal to distance between players
  //if so then we can say there is no wall between
  //That's because of the bug on linux servers :(
  new Float:rayDistance = GetDistanceBetween(loc, endvec);
  new Float:targetDistance = GetDistanceBetween(loc, loc2);
  if(rayDistance < (targetDistance-35.0))
  return false; //Then there is a solid object between
  return true;
}
stock bool:IsEntityCollidable(entity, bool:includeplayer = true, bool:includehostage = true, bool:includeprojectile = true){

  decl String:classname[64];
  GetEdictClassname(entity, classname, 64);

  if((StrEqual(classname, "player", false) && includeplayer) || (StrEqual(classname, "hostage_entity", false) && includehostage)
      ||StrContains(classname, "physics", false) != -1 || StrContains(classname, "prop", false) != -1
      || StrContains(classname, "door", false)  != -1 || StrContains(classname, "weapon", false)  != -1
      || StrContains(classname, "break", false)  != -1 || ((StrContains(classname, "projectile", false)  != -1) && includeprojectile)
      || StrContains(classname, "brush", false)  != -1 || StrContains(classname, "button", false)  != -1
      || StrContains(classname, "physbox", false)  != -1 || StrContains(classname, "plat", false)  != -1
      || StrEqual(classname, "func_conveyor", false) || StrEqual(classname, "func_fish_pool", false)
      || StrEqual(classname, "func_guntarget", false) || StrEqual(classname, "func_lod", false)
      || StrEqual(classname, "func_monitor", false) || StrEqual(classname, "func_movelinear", false)
      || StrEqual(classname, "func_reflective_glass", false) || StrEqual(classname, "func_rotating", false)
      || StrEqual(classname, "func_tanktrain", false) || StrEqual(classname, "func_trackautochange", false)
      || StrEqual(classname, "func_trackchange", false) || StrEqual(classname, "func_tracktrain", false)
      || StrEqual(classname, "func_train", false) || StrEqual(classname, "func_traincontrols", false)
      || StrEqual(classname, "func_vehicleclip", false) || StrEqual(classname, "func_traincontrols", false)
      || StrEqual(classname, "func_water", false) || StrEqual(classname, "func_water_analog", false)){

    return true;

  }

  return false;

}
public bool:AimTargetFilter(entity,mask)
{
  return !(entity==ClientTracer);
}

public bool:WallTargetFilter(entity,mask) {
  return !(entity>0 && entity <= GetMaxClients());
}

stock GetNearClients(const String:matchstr[],Float:location[3],clients[],Float:distance, bool:ignoreWall=true )
{
  new count=0;
  new maxplayers=GetMaxClients();
  new Float:loc2[3];
  if(StrEqual(matchstr,"@all",false))
  {
    for(new x=1;x<=maxplayers;x++)
    {
      if(IsClientInGame(x))
      if(IsPlayerAlive(x))
      {
        GetClientAbsOrigin(x,loc2);
        loc2[2]+=20.0;
        if(GetDistanceBetween(location,loc2)<=distance)
        if(ignoreWall || IsClearPath(location, loc2,x))
        {

          clients[count]=x;
          count++;
        }
        else
        PrintToServer("Path is not clear");
      }
    }
  }
  else if(StrEqual(matchstr,"@t",false))
  {
    for(new x=1;x<=maxplayers;x++)
    {
      if(IsClientInGame(x)&&GetClientTeam(x)==2)
      if(IsPlayerAlive(x))
      {
        GetClientAbsOrigin(x,loc2);
        if(GetDistanceBetween(location,loc2)<=distance)
        if(ignoreWall || IsClearPath(location, loc2,x))
        {
          clients[count]=x;
          count++;
        }
      }
    }
  }
  else if(StrEqual(matchstr,"@ct",false))
  {
    for(new x=1;x<=maxplayers;x++)
    {
      if(IsClientInGame(x)&&GetClientTeam(x)==3)
      if(IsPlayerAlive(x))
      {
        GetClientAbsOrigin(x,loc2);
        if(GetDistanceBetween(location,loc2)<=distance)
        if(ignoreWall || IsClearPath(location, loc2,x))
        {
          clients[count]=x;
          count++;
        }
      }
    }
  }
  else if(matchstr[0]=='@')
  {
    new userid=StringToInt(matchstr[1]);
    if(userid)
    {
      new index=GetClientOfUserId(userid);
      if(index)
      {
        if(IsClientInGame(index))
        if(IsPlayerAlive(index))
        {
          GetClientAbsOrigin(index,loc2);
          if(GetDistanceBetween(location,loc2)<=distance)
          if(ignoreWall || IsClearPath(location, loc2,index))
          {
            clients[count]=index;
            count++;
          }
        }
      }
    }
  }
  else
  {
    for(new x=1;x<=maxplayers;x++)
    {
      if(IsClientInGame(x))
      {
        decl String:name[64];
        GetClientName(x,name,64);
        if(StrContains(name,matchstr,false)!=-1)
        if(IsPlayerAlive(x))
        {
          GetClientAbsOrigin(x,loc2);
          if(GetDistanceBetween(location,loc2)<=distance)
          if(ignoreWall || IsClearPath(location, loc2,x))
          {
            clients[count]=x;
            count++;
          }
        }
      }
    }
  }
  return count;
}