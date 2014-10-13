#define DROP_ON_KILL FindSettingFloat("orbs", "drop_on_kill")


char WIKI_PAGE[100];
Handle config;

void ReloadConfig() {
  ServerCommand("alias screset \"sm plugins unload spellcraft;changelevel de_dust2;\"");
  if(config!=INVALID_HANDLE)  {
    CloseHandle(config);
  }
  config=CreateKeyValues("SPConfig");
  char path[PLATFORM_MAX_PATH];
  BuildPath(Path_SM, path, PLATFORM_MAX_PATH, "configs/spellcraft.cfg");
  if(!FileToKeyValues(config, path))  {
    SetFailState("[SC] ERROR: configs/spellcraft.cfg could not be loaded");
  }
  UpdateStringConfigs();
}

void UpdateStringConfigs()  {
  FindSettingString("general", "wiki_page", WIKI_PAGE, sizeof(WIKI_PAGE));
}

public bool FindSettingBool(const char[] category, const char[] name) {
  KvRewind(config);
  KvJumpToKey(config, category);
  return bool:KvGetNum(config, name);
}

public int FindSettingInt(const char[] category, const char[] name) {
  KvRewind(config);
  KvJumpToKey(config, category);
  return KvGetNum(config, name);
}

public float FindSettingFloat(const char[] category, const char[] name) {
  KvRewind(config);
  KvJumpToKey(config, category);
  return KvGetFloat(config, name);
}

public void FindSettingString(const char[] category, const char[] name, char[] output, int maxlen)  {
  KvRewind(config);
  KvJumpToKey(config, category);
  KvGetString(config, name, output, maxlen);
}

