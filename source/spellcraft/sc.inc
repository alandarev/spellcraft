new ClientTracer;

public OnMapStart()
{
  g_RoundCount=-1;
  PrecacheModel("models/effects/combineball.mdl");
}
public RoundStartEvent(Handle:event,const String:name[],bool:dontBroadcast)
{
  g_RoundCount++;
}