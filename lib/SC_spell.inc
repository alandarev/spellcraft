/*
* Supporting code for SC Spells
*/

bool g_isSpellLoaded=false;

public OnPluginStart()  {
  if(SC_IsReady())  {
    __loadSpell();
  }
}

void __loadSpell()  {
  if(!g_isSpellLoaded)  {
    LoadSpell();
    g_isSpellLoaded = true;
  }
}

public SC_OnReady() {
  __loadSpell();
}

