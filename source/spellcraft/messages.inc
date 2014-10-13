
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
  Format(message, sizeof(message), "%T", "you now have x orbs", client, orbName, has);
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
         /*Color_Default = 0,*/
	/*Color_Darkred,*/
	/*Color_Green,*/
	/*Color_Lightgreen,*/
	/*Color_Red,*/
	/*Color_Blue,*/
	/*Color_Olive,*/
	/*Color_Lime,*/
	/*Color_Lightred,*/
	/*Color_Purple,*/
	/*Color_Grey,*/
	/*Color_Orange*/
  CPrintToChatAll("{default}default{darkred}darkred{green}green");
  CPrintToChatAll("{lightgreen}lightgreen{red}red");
  CPrintToChatAll("{blue}blue");
  CPrintToChatAll("{olive}olive{lime}lime{lightred}lightred{purple}purple");
  CPrintToChatAll("{grey}grey{orange}orange");
  return Plugin_Handled;
}
