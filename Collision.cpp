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
			if		(player->direction == UP)		return UP_COLLISION;
			else if (player->direction == DOWN)		return DOWN_COLLISION;
			else if (player->direction == RIGHT)	return RIGHT_COLLISION;
			else if (player->direction == LEFT)		return LEFT_COLLISION;
		}
	}


	return NO_COLLISION;
}

void Collision::shell_collision(Player *player1,Player *player2,Map *map)
{
	short shell_size1 = player1->shells.size();
	short shell_size2 = player2->shells.size();
	
	short sections_size = map->sections.size();

	
	//chek player1 shells

	for (short i = 0; i < shell_size1; i++)
	{	
		if (player1->shells[i] == nullptr) continue;

		float shellX = player1->shells[i]->x;
		float shellY = player1->shells[i]->y;
		float shellW = player1->shells[i]->w;
		float shellH = player1->shells[i]->h;

		//first chek player and shell collision

		float pX = player2->x;
		float pY = player2->y;
		float pW = player2->w;
		float pH = player2->h;

		if (((shellY <= (pY + pH) && (shellY + shellH) >= pY)) && ((shellX <= (pX + pW) && (shellX + shellW) >= pX)))
		{
			std::cout << "Boom!" << std::endl;

			delete player1->shells[i];
			player1->shells[i] = nullptr;
			continue;
		}

		for (short j = 0; j < sections_size; j++)
		{
			float sX = map->sections[j]->x;
			float sY = map->sections[j]->y;
			float sW = map->sections[j]->w;
			float sH = map->sections[j]->h;

			if (((shellY <= (sY + sH) && (shellY + shellH) >= sY)) && ((shellX <= (sX + sW) && (shellX + shellW) >= sX)))
			{	
				player2->getLives()--;

				delete player1->shells[i];
				player1->shells[i] = nullptr;

				break;
			}
		}
	}

	for (short i = 0; i < shell_size2; i++)
	{	
		if (player2->shells[i] == nullptr) continue;

		float shellX = player2->shells[i]->x;
		float shellY = player2->shells[i]->y;
		float shellW = player2->shells[i]->w;
		float shellH = player2->shells[i]->h;


		float pX = player1->x;
		float pY = player1->y;
		float pW = player1->w;
		float pH = player1->h;

		if (((shellY <= (pY + pH) && (shellY + shellH) >= pY)) && ((shellX <= (pX + pW) && (shellX + shellW) >= pX)))
		{
			player1->getLives()--;

			delete player2->shells[i];
			player2->shells[i] = nullptr;
			continue;
		}

		for (short j = 0; j < sections_size; j++)
		{
			float sX = map->sections[j]->x;
			float sY = map->sections[j]->y;
			float sW = map->sections[j]->w;
			float sH = map->sections[j]->h;

			if (((shellY <= (sY + sH) && (shellY + shellH) >= sY)) && ((shellX <= (sX + sW) && (shellX + shellW) >= sX)))
			{
				delete player2->shells[i];
				player2->shells[i] = nullptr;
				break;
			}
		}
	}
}