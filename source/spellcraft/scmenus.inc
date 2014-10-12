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
  menu.AddItem("meta-data", buffer); // Remove ITEMDRAW_DISABLED if not needed

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
  menu.AddItem("HeroMenu", buffer);

  Format(buffer, sizeof(buffer), "%T", "sc items menu", client);
  menu.AddItem("ItemsMenu", buffer);

  Format(buffer, sizeof(buffer), "%T", "sc premium menu", client);
  menu.AddItem("PremiumMenu", buffer);

  Format(buffer, sizeof(buffer), "%T", "sc other players menu", client);
  menu.AddItem("OtherPlayersMenu", buffer);

  Format(buffer, sizeof(buffer), "%T", "sc help menu", client);
  menu.AddItem("HelpMenu", buffer);

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

public void HeroMenu(int client) {

  Menu menu = Menu(HeroMenuHandler);
  menu.ExitBackButton = true;

  /*** Title ***/
  char title[128];
  Format(title,sizeof(title),"%T","sc hero menu",client);
  menu.SetTitle(title);

  /*** Menu Items ***/
  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", "placeholder", client);
  menu.AddItem("0", buffer);

  Format(buffer, sizeof(buffer), "%T", "placeholder", client);
  menu.AddItem("1", buffer);

  Format(buffer, sizeof(buffer), "%T", "placeholder", client);
  menu.AddItem("2", buffer);

  Format(buffer, sizeof(buffer), "%T", "placeholder", client);
  menu.AddItem("3", buffer);

  /*** Send to client ***/
  menu.Display(client,MENU_TIME_FOREVER);

}
public HeroMenuHandler(Menu menu,
                        MenuAction action,
                        client, slot) {
  if(action == MenuAction_Select) {
    char buffer[100];
    menu.GetItem(slot,buffer,sizeof(buffer));
    int spellSlot = StringToInt(buffer);

    SpellMenu(client, spellSlot);

  }

  if(action == MenuAction_Cancel)
    if(slot == MenuCancel_ExitBack) {
      MainMenu(client);
    }
  if(action == MenuAction_End)
    delete menu;

}

public void SpellMenu(int client, spellSlot) {

  Menu menu = Menu(SpellMenuHandler);
  menu.ExitBackButton = true;

  char title[128];
  char spellname[128];

  Spell spell = Player(client).hero.GetSpell(spellSlot);
  spell.GetName(spellname,sizeof(spellname));

  Format(title, sizeof(title), "%T", "placeholder", client);
  menu.SetTitle(title);

  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", spellname, client);
  menu.AddItem("meta-data", buffer);

  menu.Display(client,MENU_TIME_FOREVER);

}

public SpellMenuHandler(Menu menu, //rename
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
      HeroMenu(client);
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
