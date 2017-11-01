#pragma once

#include "Map.h"
#include "Player.h"

enum COLLISION_TYPE
{
	RIGHT_COLLISION,
	LEFT_COLLISION,
	UP_COLLISION,
	DOWN_COLLISION,
	NO_COLLISION
};

class Collision
{
public:

	static COLLISION_TYPE player_collision(Player *player,Map *map);
	static void shell_collision(Player *player1,Player *player2,Map *map);
};