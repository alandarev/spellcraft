new ClientTracer;

public OnMapStart()
{
  g_RoundCount=-1;
}
public RoundStartEvent(Handle:event,const String:name[],bool:dontBroadcast)
{
  g_RoundCount++;
}