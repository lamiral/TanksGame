#include "MapLoader.h"

void MapLoader::loadMap(Map *map, const char *mapPath,int mapSize,int sectionSize)
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