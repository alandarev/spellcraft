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

  char spellName[30];
  Hero hero = Player(client).hero;

  /*** Menu Items ***/
  char buffer[200];

  for (int i=0; i<MAXSPELLS; i++) {
    char sI[5];
    IntToString(i, sI, sizeof(sI));
    Spell spell = hero.GetSpell(0);
    spell.GetName(spellName, sizeof(spellName));
    int rank = hero.GetSpellRank(0);

    Format(buffer, sizeof(buffer), "%T", "spell entry", client, spellName, rank);
    menu.AddItem(sI, buffer);
  }

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

public void SpellMenu(int client, int spellSlot) {

  Menu menu = Menu(SpellMenuHandler);
  menu.ExitBackButton = true;

  char title[128];
  char spellname[128];

  Spell spell = Player(client).hero.GetSpell(spellSlot);
  spell.GetName(spellname,sizeof(spellname));

  Format(title, sizeof(title), "%T", spellname, client);
  menu.SetTitle(title);

  char buffer[200];
  Format(buffer, sizeof(buffer), "%T", "sc combination menu", client);
  menu.AddItem("CombinationMenu", buffer);
  
  Format(buffer, sizeof(buffer), "%T", "sc delete spell", client);
  menu.AddItem("DeleteSpell", buffer);
  
  Format(buffer, sizeof(buffer), "%T", "sc spellinfo %s", client);
  menu.AddItem("DeleteSpell", buffer);

  menu.Display(client,MENU_TIME_FOREVER);

}

public SpellMenuHandler(Menu menu, //rename
                        MenuAction action,
                        client, slot) {
  if(action == MenuAction_Select) {
    char buffer[100];
    menu.GetItem(slot,buffer,sizeof(buffer));
    int spellSlot = StringToInt(buffer);
    
    CombinationMenu(client, spellSlot);
    
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

public void CombinationMenu(int client, int spellSlot) {

  Menu menu = Menu(CombinationMenuHandler);
  menu.ExitBackButton = true;

  char title[128];
  char spellname[128];
  int spellComponents[3];

  Spell spell = Player(client).hero.GetSpell(spellSlot);
  spell.GetName(spellname,sizeof(spellname));
  for(int i=0;i<3;i++){
    spellComponents[i]=spell.GetComponent(i);
    char orbName[100];
    GetOrbName(spellComponents[i],orbName,sizeof(orbName));
    menu.AddItem("CombinationChangeMenu", orbName);
  }

  Format(title, sizeof(title), "%T", spellname, client);
  menu.SetTitle(title);

  menu.Display(client,MENU_TIME_FOREVER);

}

public CombinationMenuHandler(Menu menu, //rename
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

public void ItemsMenu(int client) {

  Menu menu = Menu(ItemsMenuHandler);
  menu.ExitBackButton = true;

  /*** Title ***/
  char title[128];
  Format(title,sizeof(title),"%T","sc items menu",client);
  menu.SetTitle(title);

  //Hero hero = Player(client).hero;

  /*** Menu Items ***/
  char buffer[200]; //Hardcode
  for(int i=0;i<MAXORBS;i++){
    char orbName[100];
    GetOrbName(i,orbName,sizeof(orbName));
    int orbs = Player(client).GetOrbsAmount(i);
    char sI[10];
    IntToString(orbs, sI, sizeof(sI));
    if(orbs=1)
      Format(buffer, sizeof(buffer), "%s %s", sI, orbName);
    else
      Format(buffer, sizeof(buffer), "%s %ss", sI, orbName);
    menu.AddItem(sI, buffer);
  }

  /*** Send to client ***/
  menu.Display(client,MENU_TIME_FOREVER);

}
public ItemsMenuHandler(Menu menu,
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
