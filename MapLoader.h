#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include "TextureLoader.h"
#include "Section.h"
#include "Map.h"
#include "Log.h"
#include "Player.h"

enum
{	
	WALL  = '#',
	OLD_WALL = '|',
	WATER = '&',
	GRASS = '$',
	WINN_1 = 'g',
	WINN_2 = 'z',
	PLAYER_1 = '1',
	PLAYER_2 = '2'
};

class MapLoader
{
public:

	static void loadMap(Map *map,const char *mapPath,int mapSize,int sectionSize);
	static void setPlayersPosition(Player *p1, Player *p2,const char *mapFile,int sectionSize);
};