/*
* Include file hanlding all the radio menus in the Spellcraft mod
*/


public ExampleMenu(client) { //RENAME

  Menu menu = Menu(ExampleMenuHandler); // EDIT the Handler name
  menu.ExitBackButton = true;

  /*** Title ***/
  char title[128];
  Format(title,sizeof(title),"%T","sc menu title",client);
  menu.SetTitle(title);

  /*** Menu Items ***/
  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", "My menu item", client);
  menu.AddItem("meta-data", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  /*** Example of Menu Item with meta-data as function with 'client'. ***/
  /*** Use it as preferred method for menus which do not need more info than clien ***/
  /*
  Format(buffer,sizeof(buffer),"%T","sc auction",client);
  menu.AddItem("AuctionsMenu",buffer);
  */

  /*** Send to client ***/
  menu.Display(client,MENU_TIME_FOREVER);

}

public ExampleMenuHandler(Menu menu, //rename
                        MenuAction action,
                        client, slot) {
  if(action == MenuAction_Select) {
    //insert here

    /*** Comment out to treat meta-data as functions with 'client' argument ***/
    /*

    char buffer[100];
    menu.GetItem(slot,buffer,sizeof(buffer));

    //Call function
    Function func = GetFunctionByName(INVALID_HANDLE, buffer);
    Call_StartFunction(INVALID_HANDLE, func);
    Call_PushCell(client);
    if(Call_Finish() != SP_ERROR_NONE)  {
      char err[100];
      Format(err,100,"[SC] Could not callback the function: %s",buffer);
      LogError(err);
    }

    */
  }

  if(action == MenuAction_Cancel)
    if(slot == MenuCancel_ExitBack) {
      //Go previous menu?
    }
  if(action == MenuAction_End)
    delete menu;

}


// Main Menu using the ExampleMenu template

void MainMenu(client) {

  Menu menu = Menu(MainMenuHandler);
  menu.ExitButton = true;

  /*** Title ***/
  char title[128];
  Format(title,sizeof(title),"%T","sc main menu title",client);
  menu.SetTitle(title);

  /*** Menu Items ***/
  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", "sc hero menu", client);
  menu.AddItem("HeroMenu", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  Format(buffer, sizeof(buffer), "%T", "sc items menu", client);
  menu.AddItem("ItemsMenu", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  Format(buffer, sizeof(buffer), "%T", "sc premium menu", client);
  menu.AddItem("PremiumMenu", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  Format(buffer, sizeof(buffer), "%T", "sc other players menu", client);
  menu.AddItem("OtherPlayersMenu", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  Format(buffer, sizeof(buffer), "%T", "sc help menu", client);
  menu.AddItem("HelpMenu", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  /*** Send to client ***/
  menu.Display(client,MENU_TIME_FOREVER);

}

public MainMenuHandler(Menu menu,
                        MenuAction action,
                        client, slot) {
  if(action == MenuAction_Select) {
    char buffer[100];
    menu.GetItem(slot,buffer,sizeof(buffer));

    //Call function
    Function func = GetFunctionByName(INVALID_HANDLE, buffer);
    Call_StartFunction(INVALID_HANDLE, func);
    Call_PushCell(client);
    if(Call_Finish() != SP_ERROR_NONE)  {
      char err[100];
      Format(err,100,"[SC] Could not callback the function: %s",buffer);
      LogError(err);
    }

  }

  if(action == MenuAction_Cancel)
    if(slot == MenuCancel_ExitBack) {
      //Go previous menu?
    }
  if(action == MenuAction_End)
    delete menu;
}

public void HeroMenu(client) {

  Menu menu = Menu(HeroMenuHandler);
  menu.ExitBackButton = true;

  /*** Title ***/
  char title[128];
  Format(title,sizeof(title),"%T","sc hero menu",client);
  menu.SetTitle(title);

  /*** Menu Items ***/
  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", "My menu item", client);
  menu.AddItem("meta-data", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  /*** Example of Menu Item with meta-data as function with 'client'. ***/
  /*** Use it as preferred method for menus which do not need more info than clien ***/
  /*
  Format(buffer,sizeof(buffer),"%T","sc auction",client);
  menu.AddItem("AuctionsMenu",buffer);
  */

  /*** Send to client ***/
  menu.Display(client,MENU_TIME_FOREVER);

}

public void ItemsMenu(client) {

  Menu menu = Menu(HeroMenuHandler);
  menu.ExitBackButton = true;

  /*** Title ***/
  char title[128];
  Format(title,sizeof(title),"%T","sc items menu",client);
  menu.SetTitle(title);

  /*** Menu Items ***/
  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", "My menu item", client);
  menu.AddItem("meta-data", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  /*** Example of Menu Item with meta-data as function with 'client'. ***/
  /*** Use it as preferred method for menus which do not need more info than clien ***/
  /*
  Format(buffer,sizeof(buffer),"%T","sc auction",client);
  menu.AddItem("AuctionsMenu",buffer);
  */

  /*** Send to client ***/
  menu.Display(client,MENU_TIME_FOREVER);

}

public void PremiumMenu(client) {

  Menu menu = Menu(HeroMenuHandler);
  menu.ExitBackButton = true;

  /*** Title ***/
  char title[128];
  Format(title,sizeof(title),"%T","sc premium menu",client);
  menu.SetTitle(title);

  /*** Menu Items ***/
  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", "My menu item", client);
  menu.AddItem("meta-data", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  /*** Example of Menu Item with meta-data as function with 'client'. ***/
  /*** Use it as preferred method for menus which do not need more info than clien ***/
  /*
  Format(buffer,sizeof(buffer),"%T","sc auction",client);
  menu.AddItem("AuctionsMenu",buffer);
  */

  /*** Send to client ***/
  menu.Display(client,MENU_TIME_FOREVER);

}

public void OtherPlayersMenu(client) {

  Menu menu = Menu(HeroMenuHandler);
  menu.ExitBackButton = true;

  /*** Title ***/
  char title[128];
  Format(title,sizeof(title),"%T","sc other players menu",client);
  menu.SetTitle(title);

  /*** Menu Items ***/
  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", "My menu item", client);
  menu.AddItem("meta-data", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  /*** Example of Menu Item with meta-data as function with 'client'. ***/
  /*** Use it as preferred method for menus which do not need more info than clien ***/
  /*
  Format(buffer,sizeof(buffer),"%T","sc auction",client);
  menu.AddItem("AuctionsMenu",buffer);
  */

  /*** Send to client ***/
  menu.Display(client,MENU_TIME_FOREVER);

}

public void HelpMenu(client) {

  Menu menu = Menu(HeroMenuHandler);
  menu.ExitBackButton = true;

  /*** Title ***/
  char title[128];
  Format(title,sizeof(title),"%T","sc help menu",client);
  menu.SetTitle(title);

  /*** Menu Items ***/
  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", "My menu item", client);
  menu.AddItem("meta-data", buffer, ITEMDRAW_DISABLED); // Remove ITEMDRAW_DISABLED if not needed

  /*** Example of Menu Item with meta-data as function with 'client'. ***/
  /*** Use it as preferred method for menus which do not need more info than clien ***/
  /*
  Format(buffer,sizeof(buffer),"%T","sc auction",client);
  menu.AddItem("AuctionsMenu",buffer);
  */

  /*** Send to client ***/
  menu.Display(client,MENU_TIME_FOREVER);

}

public HeroMenuHandler(Menu menu, //rename
                        MenuAction action,
                        client, slot) {
  if(action == MenuAction_Select) {
    char buffer[100];
    menu.GetItem(slot,buffer,sizeof(buffer));

    //Call function
    Function func = GetFunctionByName(INVALID_HANDLE, buffer);
    Call_StartFunction(INVALID_HANDLE, func);
    Call_PushCell(client);
    if(Call_Finish() != SP_ERROR_NONE)  {
      char err[100];
      Format(err,100,"[SC] Could not callback the function: %s",buffer);
      LogError(err);
    }

  }

  if(action == MenuAction_Cancel)
    if(slot == MenuCancel_ExitBack) {
      MainMenu(client);
    }
  if(action == MenuAction_End)
    delete menu;

}




public Action:Open_MainMenu(client, args)
{
  if (client)
  {
    MainMenu(client);
  }
  else
  {
    PrintToServer("The server cannot open menu.");
  }
  return Plugin_Handled;
}

/*
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
        */
