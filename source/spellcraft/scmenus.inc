/*
* Include file hanlding all the radio menus in the SpellCraft mod
*/


public ExampleMenu(client) { //RENAME

  new Handle:menu=CreateMenu(ExampleMenuHandler); //EDIT !!
  SetMenuExitBackButton(menu,true);

  /*** Title ***/
  decl String:title[128];
  Format(title,sizeof(title),"%T","sc menu title",client);
  SetMenuTitle(menu,title);


  /*** Menu Items ***/
  decl String:buffer[200];
  Format(buffer, sizeof(buffer), "%T", "My menu item", client);
  AddMenuItem(menu,"meta-data",buffer,ITEMDRAW_DISABLED);
  AddMenuItem(menu,"meta-data",buffer);

  /*** Example of Menu Item with meta-data as function with 'client'. ***/
  /*** Use it as preferred method for menus which do not need more info than clien ***/
  /*
  Format(buffer,sizeof(buffer),"%T","sc auction",client);
  AddMenuItem(menu,"AuctionsMenu",buffer);
  */

  /*** Send to client ***/
  DisplayMenu(menu,client,MENU_TIME_FOREVER);

}

public ExampleMenuHandler(Handle:menu, //rename
                        MenuAction:action,
                        client, slot) {
  if(action == MenuAction_Select) {
    //insert here

    /*** Comment out to treat meta-data as functions with 'client' argument ***/
    /*

    decl String:buffer[100];
    GetMenuItem(menu,slot,buffer,sizeof(buffer));

    //Call function
    new Function:func = GetFunctionByName(INVALID_HANDLE, buffer);
    Call_StartFunction(INVALID_HANDLE, func);
    Call_PushCell(client);
    if(Call_Finish() != SP_ERROR_NONE)  {
      decl String:err[100];
      Format(err,100,"Could not callback the function: %s",buffer);
      Logger_log(LogType:LT_file, LogLevel:LL_error, "Messages", err);
    }

    */
  }

  if(action == MenuAction_Cancel)
    if(slot == MenuCancel_ExitBack) {
      //Go previous menu?
    }
  if(action == MenuAction_End)
    CloseHandle(menu);

}



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
  //new Handle:menu = CreateMenu(MainMenu, MenuAction_Select | MenuAction_End | MenuAction_DisplayItem);
  new Handle:menu = CreateMenuEx(GetMenuStyleHandle(MenuStyle_Valve), MainMenu, MenuAction_Select | MenuAction_End | MenuAction_DisplayItem);

  SetMenuTitle(menu, "Menu");

  AddMenuItem(menu, "Items", "Items");
  AddMenuItem(menu, "Spells", "Spells");
  AddMenuItem(menu, "Characters", "Characters");
  AddMenuItem(menu, "Other Players", "Other Players");
  AddMenuItem(menu, "Scoreboard", "Scoreboard");

  DisplayMenu(menu, client, MENU_TIME_FOREVER);
}
public MainMenu(Handle:menu, MenuAction:action, param1, param2)
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
