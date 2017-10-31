#include "Collision.h"

COLLISION_TYPE Collision::player_collision(Player *player, Map *map)
{	
	float pX = player->x;
	float pY = player->y;
	float pW = player->w;
	float pH = player->h;

	short size_map = map->sections.size();

	for (short i = 0; i < size_map; i++)
	{
		float sX = map->sections[i]->x;
		float sY = map->sections[i]->y;
		float sW = map->sections[i]->w;
		float sH = map->sections[i]->h;

		//Up collision
		if (((pY <= (sY + sH) && (pY+pH) >= sY)) && ((pX <= (sX + sW) && (pX + pW) >= sX)))
		{
			if	(player->direction == UP)		return UP_COLLISION;
			else if (player->direction == DOWN)		return DOWN_COLLISION;
			else if (player->direction == RIGHT)		return RIGHT_COLLISION;
			else if (player->direction == LEFT)		return LEFT_COLLISION;
		}
	}


	return NO_COLLISION;
}
