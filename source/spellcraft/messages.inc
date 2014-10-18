// Possible colors for in-game chat:
// default, darkred, green, lightgreen, t_orange, t_blue, t_olive, lime, lightred, purple, grey, yellow
// Note that t_orange t_blue and t_olive cannot be used in same message, that is:
// WRONG:  "Hello {t_orange}Stinky, {t_blue}you look good". That will throw an error as only one team type color can be in one message
// OK:     "Hello {t_orange}Stinky, {t_orange}you look good"
// OK:     "Hello {t_orange}Stinky, {lime}you look good"

void AnnounceDrop(int client, int orbId, int amount) {
  char orbName[100];
  GetOrbName(orbId, orbName, sizeof(orbName));
  Format(orbName, sizeof(orbName), "%T", orbName, client, amount);

  char message[255];

  Handle panel = CreatePanel();

  Format(message, sizeof(message), "%T", "panel an drop title", client);
  SetPanelTitle(panel, message);
  Format(message, sizeof(message), "%T", "panel an drop item", client, orbName, amount);

  DrawPanelItem(panel, " \n", ITEMDRAW_RAWLINE|ITEMDRAW_SPACER);
  DrawPanelItem(panel, " \n", ITEMDRAW_RAWLINE|ITEMDRAW_SPACER);
  DrawPanelText(panel, message);
  DrawPanelItem(panel, " \n", ITEMDRAW_RAWLINE|ITEMDRAW_SPACER);
  int has = Player(client).GetOrbsAmount(orbId);
  if(has>1)
    Format(message, sizeof(message), "%T", "you now have x orbs", client, orbName, has);
  else
    Format(message, sizeof(message), "%T", "you now have x orb", client, orbName, has);
  DrawPanelText(panel, message);
  DrawPanelItem(panel, " \n", ITEMDRAW_RAWLINE|ITEMDRAW_SPACER);

  SetPanelCurrentKey(panel, 3);
  Format(message, sizeof(message), "%T", "exit", client);
  DrawPanelItem(panel, message, ITEMDRAW_CONTROL);
  SendPanelToClient(panel, client, PanelHandler, 15);

  CloseHandle(panel);
}

public PanelHandler(Handle:menu, MenuAction:action, client, slot)   {
}

public Action TestColors(client, args)  {
  CPrintToChatAll("{default}default{darkred}darkred{green}green");
  CPrintToChatAll("{lightgreen}lightgreen{t_orange}orange");
  CPrintToChatAll("{t_blue}blue");
  CPrintToChatAll("{t_olive}olive{lime}lime{lightred}lightred{purple}purple");
  CPrintToChatAll("{grey}grey{yellow}yellow");
  return Plugin_Handled;
}
