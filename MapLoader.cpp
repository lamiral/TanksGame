#include "MapLoader.h"

void MapLoader::loadMap(Map *map,const char *mapPath,int mapSize,int sectionSize)
{
	std::ifstream file(mapPath);

	if (!file.is_open())
	{
		Log::error("error map file");
		return;
	}

	std::string str;

	float x = 0.0f;
	float y = 0.0f;

	short m = 0;

	while (std::getline(file,str) && m < mapSize)
	{	
		x = 0.0f;
		for (short i = 0;i < str.size(); i++)
		{
			if (str[i] == WALL)
			{
				Section *section = new Section(sectionSize,sectionSize, x, y,WALL_SECTION);
				section->setTexture("resources/textures/wall.png");
				map->sections.push_back(section);
			}
			else if (str[i] == WATER)
			{
				Section *section = new Section(sectionSize, sectionSize, x, y, WATER_SECTION);
				section->setTexture("resources/textures/water.jpg");
				map->sections.push_back(section);
			}
			else if (str[i] == GRASS)
			{
				Section *section = new Section(sectionSize, sectionSize, x, y, GRASS_SECTION);
				section->setTexture("resources/textures/grass.png");
				map->sections.push_back(section);
			}
			else if (str[i] == OLD_WALL)
			{
				Section *section = new Section(sectionSize, sectionSize, x, y, OLD_WALL_SECTION);
				section->setTexture("resources/textures/oldWall.png");
				map->sections.push_back(section);
			}
			else if (str[i] == WINN_1)
			{
				Section *section = new Section(sectionSize, sectionSize, x, y, OLD_WALL_SECTION);
				section->setTexture("resources/textures/winn1.png");
				map->sections.push_back(section);
			}
			else if (str[i] == WINN_2)
			{
				Section *section = new Section(sectionSize, sectionSize, x, y, OLD_WALL_SECTION);
				section->setTexture("resources/textures/winn2.png");
				map->sections.push_back(section);
			}
			x += sectionSize;
		}
		m++;
		y += sectionSize;
	}
}

void MapLoader::setPlayersPosition(Player *p1, Player *p2,const char *mapFile,int sectionSize)
{
	std::ifstream file(mapFile);

	if (!file.is_open())
	{
		Log::error("bad map filepath");
		return;
	}

	std::string str;

	float x = 0.0f;
	float y = 0.0f;
	int i = 0;

	while (getline(file, str))
	{	
		for (short i = 0; i < str.size(); i++)
		{
			if (str[i] == PLAYER_1)
			{	
				std::cout << "юсссс" << std::endl;
				p1->x = x;
				p1->y = y;
				i++;
			}
			else if (str[i] == PLAYER_2)
			{
				p2->x = x;
				p2->y = y;
				i++;
			}
			if (i >= 2) break;
			x += sectionSize;
		}

		y += sectionSize;
	}
}