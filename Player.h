#pragma once

#include "Sprite.h"
#include "InputManager.h"

enum DIRECTION
{
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3
};

#define PLAYER_SPEED 5

class Player
{
private:
	
	Sprite *sprite;

	int lives;
	int points;

public:
	
	int	  direction;
	float x,y,w,h;

	Player(float _x,float _y,float _w,float _h);
	~Player();

	void setTexture(const char *pathTexture);
	void draw();
	void move(KEY_TYPE key);
};