#include "Map.h"

Map::~Map()
{
	short size_sections = sections.size();

	for (short i = 0; i < size_sections; i++)
	{
		delete sections[i];
	}
}

void Map::draw()
{
	short size_sections = sections.size();

	for (short i = 0; i < size_sections; i++)
	{
		sections[i]->draw();
	}
}