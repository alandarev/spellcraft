spellcraft
==========

I am thrilled to let you know that our small team of wowmod developers decided to work on a different RPG-like mod for CS:GO called **SpellCraft**

## Programming Language
The mod uses transitional SourcePawn syntax described in [this article][2]. Every developer is encouraged to introduce themselves to some new amazing benefits of that syntax.

Material on SourcePawn language used is found on [this wiki][3]

## Tools
* [Developer Panel]
* Test Game Server: connect wowmod.eu:27027

## Structure of a repository

* All source code goes into `./source`.
* All server files (sound, textures, models...) go into `./server` and shall assume the root path of `gameserver/csgo`. Example: `castSpellX.wav` will go into `gameserver/csgo/sound/spellcraft/`.
* All plugin files (translations, data) go into `./data` and shall assume the root path of `gameserver/csgo/addons/sourcemod`.

## Developing
Unless there is a need, developing will happen right on the Master branch. Specific features will have their own branches, granted they take significant period of time to be developed.

[Developer Panel]:http://dev.c-servers.com/
[2]:https://wiki.alliedmods.net/SourcePawn_Transitional_Syntax
[3]:https://wiki.alliedmods.net/Introduction_to_sourcepawn
