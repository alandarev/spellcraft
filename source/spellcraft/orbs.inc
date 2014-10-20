/*
* Orbs code
*/

void GetShortOrbName(int id, char[] buffer, length) {
  strcopy(buffer, length, g_orbNames[id]);
}

void GetOrbName(int id, char[] buffer, length) {
  GetShortOrbName(id, buffer, length);
  Format(buffer, length, "orb_%s", buffer);
}

int OrbNameToId(char[] name)  {
  for(int i=0; i<MAXORBS; i++)  {
    if(StrEqual(name, g_orbNames[i], false))  {
      return i;
    }
  }
  LogError("[SC] ERROR: Tried to get orb id for non-existent orb: %s", name);
  return -1;
}

