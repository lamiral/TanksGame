#include "Map.h"

void Map::draw()
{
	short size_sections = sections.size();

	for (short i = 0; i < size_sections; i++)
	{
		sections[i]->draw();
	}
}