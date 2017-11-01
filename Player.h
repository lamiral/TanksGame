#pragma once

#include <vector>
#include "Sprite.h"
#include "InputManager.h"
#include "Shell.h"

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

	float lastTime;

	int lives;
	int points;
	int playerNumber;

public:
	
	std::vector<Shell*> shells;

	DIRECTION direction;
	float x,y,w,h;

	Player(float _x,float _y,float _w,float _h,int _playerNumber);
	~Player();

	void setTexture(const char *pathTexture);
	void draw();

	void drawShells();
	void instantiateShell(float currTime);

	void move(KEY_TYPE key);

	int& getLives();
	int& getPoints();
};