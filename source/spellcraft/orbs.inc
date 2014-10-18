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
