#pragma semicolon 1


public Action:Open_MainMenu(client, args) //Args is necessary for console commands even if it doesn't do anything
{ 
	if (client)
	{
    OpenMenu(client);
	} else {
		PrintToServer("The server cannot open menu.");
	}

	return Plugin_Handled;
}

OpenMenu(client)
{
	new Handle:menu = CreateMenu(Test, MenuAction_Select | MenuAction_End | MenuAction_DisplayItem);
	SetMenuTitle(menu, "Menu");

  AddMenuItem(menu, "Items", "Items");
  AddMenuItem(menu, "Spells", "Spells");
  AddMenuItem(menu, "Characters", "Characters");
  AddMenuItem(menu, "Other Players", "Other Players");
  AddMenuItem(menu, "Scoreboard", "Scoreboard");

	DisplayMenu(menu, client, MENU_TIME_FOREVER);
}
public Test(Handle:menu, MenuAction:action, param1, param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			//param1 is client, param2 is item

			new String:item[64];
			GetMenuItem(menu, param2, item, sizeof(item));

			if (StrEqual(item, "Items"))
			{
        
			}
			else if (StrEqual(item, "Spells"))
			{

			}
			else if (StrEqual(item, "Characters"))
			{

			}
			else if (StrEqual(item, "Other Players"))
			{

			}
			else if (StrEqual(item, "Scoreboard"))
			{

			}
		}

		case MenuAction_End:
		{
			//param1 is MenuEnd reason, if canceled param2 is MenuCancel reason
			CloseHandle(menu);

		}

		case MenuAction_DisplayItem:
		{
			//param1 is client, param2 is item

			new String:item[64];
			GetMenuItem(menu, param2, item, sizeof(item));

			if (StrEqual(item, "Items"))
			{
				new String:translation[128];
				Format(translation, sizeof(translation), "%T", "Items", param1);
				return RedrawMenuItem(translation);
			}
			else if (StrEqual(item, "Spells"))
			{
				new String:translation[128];
				Format(translation, sizeof(translation), "%T", "Spells", param1);
				return RedrawMenuItem(translation);
			}
			else if (StrEqual(item, "Characters"))
			{
				new String:translation[128];
				Format(translation, sizeof(translation), "%T", "Characters", param1);
				return RedrawMenuItem(translation);
			}
			else if (StrEqual(item, "Other Players"))
			{
				new String:translation[128];
				Format(translation, sizeof(translation), "%T", "Other Players", param1);
				return RedrawMenuItem(translation);
			}
			else if (StrEqual(item, "Scoreboard"))
			{
				new String:translation[128];
				Format(translation, sizeof(translation), "%T", "Scoreboard", param1);
				return RedrawMenuItem(translation);
			}
		}

	}
	return 0;
}