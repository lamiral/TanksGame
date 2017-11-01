#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include "TextureLoader.h"
#include "Section.h"
#include "Map.h"
#include "Log.h"

enum
{	
	WALL  = '#',
	OLD_WALL = '|',
	WATER = '&',
	GRASS = '$',
	WINN_1 = '1',
	WINN_2 = '2'
};

class MapLoader
{
public:

	static void loadMap(Map *map,const char *mapPath,int mapSize,int sectionSize);
};